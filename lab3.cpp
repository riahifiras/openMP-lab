#include <iostream>
#include <omp.h>
#include <vector>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void find_primes(int limit) {
    std::vector<int> primes;
    #pragma omp parallel for
    for (int i = 2; i <= limit; ++i) {
        if (is_prime(i)) {
            #pragma omp critical
            primes.push_back(i);
        }
    }
    std::cout << "Total primes up to " << limit << ": " << primes.size() << std::endl;
}

int main() {
    find_primes(10);
    find_primes(100);
    find_primes(1000);
    find_primes(10000);
    find_primes(100000);
    return 0;
}
