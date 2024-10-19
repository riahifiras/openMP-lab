#include <iostream>
#include <omp.h>

int main() {
    int shared_var = 0;
    int private_var = 10;
    int firstprivate_var = 10;

    std::cout << "Outside parallel region:" << std::endl;
    std::cout << "Shared Var: " << shared_var << ", Private Var: " << private_var << ", FirstPrivate Var: " << firstprivate_var << std::endl;

    #pragma omp parallel shared(shared_var) private(private_var) firstprivate(firstprivate_var)
    {
        private_var += 1;
        firstprivate_var += 1;
        #pragma omp critical
        {
            shared_var += 1;
            std::cout << "Inside parallel region: Thread " << omp_get_thread_num() 
                      << ", Private Var: " << private_var 
                      << ", FirstPrivate Var: " << firstprivate_var 
                      << ", Shared Var: " << shared_var << std::endl;
        }
    }

    std::cout << "After parallel region: Shared Var: " << shared_var << std::endl;
    return 0;
}
