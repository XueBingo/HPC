#include <cstring>
#include <random>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <fstream>
#include <ratio>
#include <math.h>
#include <cassert>
#include "omp.h"

using namespace std;

const unsigned long seed = 0;

double* init_matrix(const int n, const double p) {
  static uniform_real_distribution<double> flip(0, 1);
  mt19937_64 rand_engine(seed);

  double* output = new double[n * n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        output[i*n + j] = 0;
      } else if (flip(rand_engine) < p) {
        output[i*n + j] = drand48();
      } else {
        output[i*n + j] = numeric_limits<double>::max()/2;
      }
    }
  }

  return output;
}

void floyd_warshall(const double* input, double* output, const int n) {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        output[i*n + j] = min(output[i*n + j], output[i*n + k] + output[k*n + j]);
      }
    }
  }
}

// i -> k + k -> j = i ->j
inline void floyd_warshall_in_place(double* C, const double* A, const double* B, const double b, const int n) {
  for (int k = 0; k < b; k++) {
    for (int i = 0; i < b; i++) {
      for (int j = 0; j < b; j++) {
        C[i*n + j] = min(C[i*n + j], A[i*n + k] + B[k*n + j]);
      }
    }
  }
}

void floyd_warshall_blocked(const double* input, double* output, const int n, const int b) {
  std::memcpy(output, input, n * n * sizeof(double));
  const int blocks = n / b;

  for (int k = 0; k < blocks; k++) {
    floyd_warshall_in_place(&output[k*b*n + k*b], &output[k*b*n + k*b], &output[k*b*n + k*b], b, n);

#pragma omp parallel for
    for (int j = 0; j < blocks; j++) {
      if (j == k) continue;
      floyd_warshall_in_place(&output[k*b*n + j*b], &output[k*b*n + k*b], &output[k*b*n + j*b], b, n);
    }
    
#pragma omp parallel for
    for (int i = 0; i < blocks; i++) {
      if (i == k) continue;
      floyd_warshall_in_place(&output[i*b*n + k*b], &output[i*b*n + k*b], &output[k*b*n + k*b], b, n);
      for (int j = 0; j < blocks; j++) {
        if (j == k) continue;
        floyd_warshall_in_place(&output[i*b*n + j*b], &output[i*b*n + k*b], &output[k*b*n + j*b], b, n);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  int n = 1024;
  double p = 0.4;
  int block_size = 64;
  int thread_count = 6;

  // parse parameters
  extern char* optarg;
  int opt;
  while ((opt = getopt(argc, argv, "n:p:d:t:")) != -1) {
    switch (opt) {
      case 'p':
        p = std::stod(optarg);
        break;
      case 'n':
        n = std::stoi(optarg);
        break;
      case 'd':
        block_size = std::stoi(optarg);
        break;
      case 't':
	      thread_count = std::stoi(optarg);
        break;
    }
  }

  if (n % block_size != 0) {
    cout << "n % block_size != 0\n";
    return 1;
  }
  cout << "number of nodes: " << n << "\nextent of density: " << p << "\nblock_size: " << block_size \
  << "\nthread_count: " << thread_count << endl;

  double* matrix = init_matrix(n, p);

  // sequential algorithm as solution
  double* solution = new double[n * n];
  memcpy(solution, matrix, n * n * sizeof(double));
  auto start = chrono::high_resolution_clock::now();
  floyd_warshall(matrix, solution, n);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> seq_time = end - start;
  cout << "sequential runtime: " << seq_time.count() << "ms\n";
  cout << "flops rate: " << 2.0 * n * n * n / seq_time.count() / 1e6 << "Gflop/s\n";
  cout << "bandwidth: " << 3.0 * n * n * n * sizeof(double) * 1e3 / seq_time.count() \
   / (1024 * 1024 * 1024)  << "GB/s\n";

  // parallelized algorithm
  double* output = new double[n * n];
  omp_set_num_threads(thread_count);
  start = chrono::high_resolution_clock::now();
  floyd_warshall_blocked(matrix, output, n, block_size);
  end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> para_time = end - start;
  cout << "parallelized runtime: " << para_time.count() << "ms\n";
  // 2 * num_blocks^3 * b^3
  cout << "flops rate: " << 2.0 * n * n * n / para_time.count() / 1e6 << "Gflop/s\n";
  // 3 * b^3 * (1 + 2*(num_blocks-1) + 2*(num_blocks-1)*num_blocks) * num_block * sizeof(double)
  cout << "bandwidth: " << 3.0 * block_size * block_size * block_size \
  * (2 * (n/block_size) * (n/block_size) - 1)* (n/block_size) * sizeof(double) * 1e3 \
  / para_time.count() / (1024 * 1024 * 1024)  << "GB/s\n";

  // check correctness
  double err = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      err += fabs(output[i*n + j] - solution[i*n + j]);
    }
  }
  cout << "accumulated error: " << err << endl;
  cout << "speedup: " << seq_time/para_time << endl;

  delete[] matrix;
  delete[] output;
  delete[] solution;

  return 0;
}