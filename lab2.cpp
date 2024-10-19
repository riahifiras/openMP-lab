#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>

int main() {
    int n = 1000000;
    std::vector<int> arr(n, 1);
    int sum = 0;

    // Reduction
    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> reduction_time = end - start;
    std::cout << "Reduction sum: " << sum << ", Time: " << reduction_time.count() << "s" << std::endl;

    // Atomic
    sum = 0;
    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        #pragma omp atomic
        sum += arr[i];
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> atomic_time = end - start;
    std::cout << "Atomic sum: " << sum << ", Time: " << atomic_time.count() << "s" << std::endl;

    // Critical
    sum = 0;
    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        #pragma omp critical
        {
            sum += arr[i];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> critical_time = end - start;
    std::cout << "Critical sum: " << sum << ", Time: " << critical_time.count() << "s" << std::endl;

    return 0;
}

