# OpenMP Labs

## Lab 1: HelloWorld with Different Clauses

### Objective
To observe how different OpenMP clauses (`private`, `firstprivate`, `shared`) affect variable scope and behavior inside and outside a parallel region.

### Code Summary
- The program declares three variables:
  - `shared_var` is shared across all threads.
  - `private_var` is private to each thread, initialized only outside the parallel region.
  - `firstprivate_var` is also private but initialized with the value it had before the parallel region.
- Inside the parallel region, each thread modifies its private variables and accesses the shared variable within a critical section to avoid race conditions.

### Conclusion
- **Shared variables** retain their values across all threads but require synchronization (using `#pragma omp critical`) to prevent race conditions.
- **Private variables** are local to each thread and are not shared between threads, but any changes inside the parallel region are not reflected outside.
- **Firstprivate variables** are similar to private but initialized with the value outside the parallel region, which can be useful for keeping consistent initial states.
- Without `critical`, simultaneous access to shared resources would lead to data corruption due to race conditions.

---

## Lab 2: Sum Reduction with Atomic and Critical

### Objective
To compare the efficiency of summing an array using `reduction`, `atomic`, and `critical` constructs in OpenMP.

### Code Summary
- Three methods were implemented to compute the sum of an array:
  1. **Reduction**: Uses OpenMP's `reduction` clause to handle the summing automatically.
  2. **Atomic**: Uses `#pragma omp atomic` to safely update the sum in a thread-safe manner.
  3. **Critical**: Uses `#pragma omp critical` to protect the sum update, ensuring only one thread at a time updates the sum.

### Results
| Method     | Time (seconds)  |
|------------|----------------|
| Reduction  | Fastest         |
| Atomic     | Slower than Reduction |
| Critical   | Slowest         |

### Conclusion
- The **reduction** clause is the most efficient for operations like summing, as it minimizes thread contention and overhead.
- The **atomic** directive performs decently but introduces some overhead compared to reduction.
- The **critical** directive is the slowest due to the overhead of forcing all threads to wait for access, making it inefficient for frequent updates to shared variables.

---

## Lab 3: Prime Number Calculation

### Objective
To implement a parallel code that calculates prime numbers up to various limits (10, 100, 1000, 10000, 100000) and analyze performance using OpenMP.

### Code Summary
- A function checks if a number is prime by testing divisibility.
- The `find_primes` function finds all primes up to a specified limit using OpenMP for parallelization.
- Each prime found is added to a shared vector, using `#pragma omp critical` to ensure thread-safe access to the vector.

### Results
| Limit      | Total Primes   |
|------------|----------------|
| 10         | 4              |
| 100        | 25             |
| 1000       | 168            |
| 10000      | 1229           |
| 100000     | 9592           |

### Conclusion
- Parallelizing the prime-finding algorithm with OpenMP yields correct results, but the **critical section** introduces significant overhead due to serialized access to the shared vector.
- Optimizing this further could involve reducing the use of critical sections, perhaps by assigning prime-finding tasks to each thread and combining results afterward, minimizing shared data access.

---

## Final Remarks

- OpenMP provides powerful constructs to parallelize tasks, but their efficiency depends on the task and the way shared data is managed.
- **Reduction** and **private variables** offer efficient ways to parallelize without contention, while **critical** sections should be avoided in performance-sensitive areas due to the bottleneck they create.
- For tasks that require frequent shared access (like updating a shared variable or vector), alternatives to **critical** sections (such as local aggregation with later merging) should be considered to reduce overhead and maximize parallel performance.
