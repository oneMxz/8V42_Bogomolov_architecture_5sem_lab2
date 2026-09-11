#include <iostream>
#include <algorithm>
#include <chrono>

int min_number_cpp_1(int& a, int &b,int &c){
    int m = std::min({a,b,c});
    return m;
}

int min_number_cpp_2(int& a, int &b,int &c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

int countEven_cpp(int N) {
    int count = 0;
    for (int i = 1; i <= N; ++i)
        if (i % 2 == 0) ++count;
    return count;
}

int min_number_asm(int& a,int& b,int& c){
    int result;
    asm(
        "movl %1, %0\n\t"
        "cmp %2, %0\n\t"
        "cmovg %2, %0\n\t"
        "cmp %3, %0\n\t"

        "cmovg %3, %0"
        : "=&r" (result)
        : "r" (a), "r" (b), "r" (c)
        : "cc"
    );
    return result;
}

int countEven_asm(int n){
    int cnt;
    asm volatile(
        "xor %%ecx,%%ecx\n\t"    // ecx — счётчик
        "mov $1, %%eax\n\t"        // i = 1 

        "1:\n\t"                 
        "cmp %1, %%eax\n\t"        // сравнить i и N
        "jg  2f\n\t"

        "test $1, %%eax\n\t"       // проверить младший бит (i & 1)
        "jnz 3f\n\t"               // 
        "add $1, %%ecx\n\t"        // увеличиваем cnt  (только для чётных)

        "3:\n\t"
        "add $1, %%eax\n\t"        // увеличиваем i
        "jmp 1b\n\t"               // назад к метке 1 (backward)

        "2:\n\t"                    // выход из цикла подсчёта
        "mov %%ecx, %0"            // передаеv в cnt
        : "=&r" (cnt)
        : "r" (n)
        : "ecx","eax","cc" //пердупреждаем, что регистры и флаги были изменены
    );
    return cnt;
}

// Блок 1: нахождение минимума из трёх чисел. 
void program_1() {
    int a,b,c;
    std::cout << "Enter number:\n";
    std::cin >> a >> b >> c;
    std::cout << "Min.number (cpp_1): " << min_number_cpp_1(a,b,c) << "\n";
    std::cout << "Min.number (cpp_2): " << min_number_cpp_2(a,b,c) << "\n";
    std::cout << "Min.number (asm+cpp): " << min_number_asm(a,b,c) << "\n";
    
}

// Блок 2: подсчёт количества чётных чисел от 1 до N. 
void program_2() {
    int n;
    std::cout << "Введите число N: ";
    std::cin >> n;

    constexpr int ITER = 1000;
    volatile int sink = 0;

    auto t0 = std::chrono::steady_clock::now();
    
    int r1 = 0;
    for (int k = 0; k < ITER; ++k){ 
        r1 = countEven_cpp(n); 
        sink += r1;
    }

    auto t1 = std::chrono::steady_clock::now();
    
    int r2 = 0;
    for (int k = 0; k < ITER; ++k){ 
        r2 = countEven_asm(n); 
        sink += r2;
    }

    auto t2 = std::chrono::steady_clock::now();

    double cpp_ns = std::chrono::duration<double>(t1 - t0).count() / ITER * 1e9;
    double asm_ns = std::chrono::duration<double>(t2 - t1).count() / ITER * 1e9;

    std::cout << "Even (cpp): " << r1 << " | " << cpp_ns << " нс/вызов\n";
    std::cout << "Even (asm): " << r2 << " | " << asm_ns << " нс/вызов\n";
}