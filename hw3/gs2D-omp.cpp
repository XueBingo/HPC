#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <omp.h>

#define MAX_ITERATIONS 100

using namespace std;

typedef long long ll;

int main(int argc, char **argv) {
    int num_threads = atoi(argv[1]);
    ll N = atoi(argv[2]);
    // int num_threads = 8;
    // ll N = 1000;
    double h = (double)1./(double)(N+1);
    ll steps = 1;

    double **unew, **uold, **tmp;

    // i, j = 0, 1, ..., N, N+1
	unew = (double**)malloc(sizeof(double*) * (N+2));
	uold = (double**)malloc(sizeof(double*) * (N+2));
	for (ll i = 0; i < N+2; i++) {
		*(unew + i) = (double*)malloc(sizeof(double) * (N+2));
		*(uold + i) = (double*)malloc(sizeof(double) * (N+2));
	}
	for (ll i = 0; i <= N+1; i++){
		for (ll j = 0; j <= N+1; j++){
			uold[i][j]=0.0;
			unew[i][j]=0.0;
		}
	}

    cout << "GS" << endl;
    printf("num_threads = %lld\tN = %lld\th = %lf\n", num_threads, N, h);

    auto start_time = std::chrono::high_resolution_clock::now();
    while (steps++ < MAX_ITERATIONS) {
        #pragma omp parallel for num_threads(num_threads)
        for (ll i = 1; i <= N; i++){
            for (ll j = i%2 + 1; j <= N; j += 2){
                unew[i][j] = (1.0*h*h + uold[i-1][j] + uold[i+1][j] + uold[i][j-1] + uold[i][j+1])/4.0;
            }
        }
        #pragma omp parallel for num_threads(num_threads)
        for (ll i = 1; i <= N; i++){
            for (ll j = i%2 + 1; j <= N; j += 2){
                unew[i][j] = (1.0*h*h + uold[i-1][j] + uold[i+1][j] + uold[i][j-1] + uold[i][j+1])/4.0;
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "Elapsed time: " << elapsed_time_ms.count() << "ms" << std::endl;

    for (ll i = 0; i < N+2; i++){
		free(*(unew+i));
		free(*(uold+i));
	}
	free(unew); 
	free(uold);

    return 0;
}