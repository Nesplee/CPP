#ifndef ITER_HPP
# define ITER_HPP

template <typename T>
void    iter(T *array, const int length, void (*func)(T)) {
    for (int i = 0; i < length; i++)
        func(array[i]);
}

template <typename T>
void    iter(T* array, const int length, void (*func)(const T &)) {
    for (int i = 0; i < length; i++) {
        func(array[i]);
    }
}

#endif

