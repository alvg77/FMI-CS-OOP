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

//task 3
template <typename T>
auto repeat(T (*f)(T), unsigned n) {
    auto function = f;

    for (int i = 0; i < n; ++i) {
        function = [function](T x) {
            return function(x);
        };
    }

    return function;
}

//task 4
template <typename T>
auto derivative(T (*f)(T)) {
    constexpr double h = 1e-5;

    return [f, h](T x) {
        std::cout << h << std::endl;
        return (f(x + h) - f(x - h)) / (2 * h);
    };
}

//task 5
template <typename T>
void print(T* arr, unsigned n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // task 1
    std::cout << std::boolalpha << is_fixed_point<int>([](int n){ return n * 5;}, 0) << '\n'; // -> true
    std::cout << std::boolalpha << is_fixed_point<int>([](int n){ return n * 5;}, 2) << '\n'; // -> false

    // task 2
    std::cout << composition<int, int, int>([](int x){ return x + 1;}, 
                                        [](int x){ return x * 2;})(5) << '\n'; // -> 12

    // task 4
    std::cout << derivative<double>([](double x){ return x * x;})(5) << '\n'; // -> ~10
    
    // task 5
    int arr[] = {1, 2, 3, 4};
    print(arr, 4); // -> 1 2 3 4

    // task 6

    return 0;
}
