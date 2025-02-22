#include <iostream>

template <typename T>
using Unary = T(*)(T);

// task 1
template <typename T>
bool is_fixed_point(Unary<T> f, T x) {
    return f(x) == x;
}

// task 2
template <typename T, typename U, typename S>
auto composition(T(*f)(U), U(*s)(S)) {
    return [f, s] (T x) {
        return s(f(x));
    };
}

// task 3
template <typename T>
auto repeat(Unary<T> f, unsigned n) {
    return [f, n] (T x) {
        for (int i = 0; i < n; ++i) {
            x = f(x);
        }

        return x;
    };
}

// task 4
template <typename T>
auto derivative(Unary<T> f) {
    constexpr double h = 1e-5;

    return [f, h](T x) {
        std::cout << h << std::endl;
        return (f(x + h) - f(x - h)) / (2 * h);
    };
}

// task 5
template <typename T>
void print(T* arr, unsigned n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// task 6
template <typename T, typename U>
U* map(T* arr, unsigned n, U(*f)(T)) {
    U* new_arr = new U[n];
    for (int i = 0; i < n; ++i) {
        new_arr[i] = f(arr[i]);
    }

    return new_arr;
}

// task 7
template <typename T>
T* filter(T* arr, unsigned n, bool(*f)(T)) {
    T* new_arr = new T[n];
    unsigned count = 0;

    for (int i = 0; i < n; ++i) {
        if (f(arr[i])) {
            new_arr[count++] = arr[i];
        }
    }

    return new_arr;
}

// task 8
template <typename T, typename U>
U reduce(U(*f)(T, U), U init, T* arr, unsigned n) {
    for (int i = n - 1; i >= 0; --i) {
        init = f(arr[i], init);
    } 
    
    return init;
}

// task 9
int sum_odd_squares(int* arr, unsigned n) {
    int* sq_arr = map<int, int>(arr, n, [](int x) -> int {
        return x * x;
    });

    int* odd_sq_arr = filter<int>(sq_arr, n, [](int x) -> bool {
        return x % 2 != 0;
    });

    delete[] sq_arr;

    int sum = reduce<int, int>([](int curr, int res) -> int {
        return res + curr;
    }, 0, odd_sq_arr, n);

    delete[] odd_sq_arr;

    return sum;
}

// task 10
template <typename T>
bool all(bool(*f)(T), T* arr, unsigned n) {
    bool valid = true;
    int i = 0;

    while (valid && i < n) {
        valid = f(arr[i++]);
    }

    return valid;
}

template <typename T>
bool any(bool(*f)(T), T* arr, unsigned n) {
    bool valid = false;
    int i = 0;
    
    while (!valid && i < n) {
        valid = f(arr[i++]);
    }

    return valid;
}

// task 11
template <typename T>
void sort_by(bool(*cmp)(T, T), T* arr, unsigned n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (cmp(arr[j], arr[j+1])) {
                T temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    // // task 1
    // std::cout << std::boolalpha << is_fixed_point<int>([](int n){ return n * 5;}, 0) << '\n'; // -> true
    // std::cout << std::boolalpha << is_fixed_point<int>([](int n){ return n * 5;}, 2) << '\n'; // -> false

    // // task 2
    // std::cout << composition<int, int, int>([](int x){ return x + 1;}, 
    //                                     [](int x){ return x * 2;})(5) << '\n'; // -> 12

    // // task 4
    // std::cout << derivative<double>([](double x){ return x * x;})(5) << '\n'; // -> ~10
    
    // // task 5
    // int arr[] = {1, 2, 3, 4};
    // print(arr, 4); // -> 1 2 3 4

    // // task 6
    // int arr[] = {1, 2, 3, 4};
    // int* result = map<int, int>(arr, 4, [](int element){ return element * element;});
    
    // print(result, 4); // -> 1 4 9 16
    
    // delete[] result;

    // // task 7
    // int arr[] = {1, 2, 3, 4};
    // int* result = filter<int>(arr, 4, [](int element){ return element % 2 == 0;});

    // print(result, 2); // -> 2 4

    // delete[] result;

    // // task 8
    // int arr[] = {1, 2, 3, 4, 5};
    // std::cout << reduce<int, int>([](int curr, int res){
    //     return res * curr;
    // }, 1, arr, 5) << '\n'; // -> 120

    // // task 9
    // int arr[] = {1, 2 ,3 , 4, 5, 6, 7, 8, 9, 10};
    // std::cout << sum_odd_squares(arr, 10) << '\n'; // -> 165

    // // task 10
    // int arr[] = {1, 2, 3, 4, 5};

    // std::cout << std::boolalpha << all<int>([](int x){ return x % 2 == 0; }, arr, 5) << '\n'; // -> false
    // std::cout << std::boolalpha << any<int>([](int x){ return x % 2 == 0; }, arr, 5) << '\n'; // -> true
    
    // // task 11
    // int arr[] = {1, 2, 3, 4, 5};
    // sort_by<int>([](int a, int b){
    //     return a <= b;
    // }, arr, 5);

    // print(arr, 5); // -> 1 2 3 4 5

    // sort_by<int>([](int a, int b){
    //     return a > b;
    // }, arr, 5);

    // print(arr, 5); // -> 5 4 3 2 1

    return 0;
}
