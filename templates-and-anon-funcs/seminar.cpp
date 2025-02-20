#include <iostream>

//task 1
template <typename T>
using Fixed = T (*)(T);

template <typename T>
bool is_fixed_point(Fixed<T> f, T x) {
    return f(x) == x;
}

//task 2
template <typename T, typename U>
using CompFuncFirst = T (*)(U);

template <typename U, typename S>
using CompFuncSecond = U (*)(S);

template <typename T, typename U, typename S>
auto composition(CompFuncFirst<T,U> f, CompFuncSecond<U,S> s) {
    return [f, s] (T x) {
        return s(f(x));
    };
}

int main() {
    // task 1
    std::cout << std::boolalpha << is_fixed_point<int>([](int n){ return n * 5;}, 0) << '\n'; // -> true
    std::cout << std::boolalpha << is_fixed_point<int>([](int n){ return n * 5;}, 2) << '\n'; // -> false

    // task 2
    std::cout << composition<int, int, int>([](int x){ return x + 1;}, 
                                        [](int x){ return x * 2;})(5) << '\n'; // -> 12

    return 0;
}
