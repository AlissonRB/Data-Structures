#include "array_stack.h"

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        top_++;
        contents[top_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    T aux;
    aux = contents[top_];
    top_--;
    return aux;
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty())
    throw std::out_of_range("pilha vazia");
    return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return (top_ == -1);
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return (top_ == static_cast<int>(max_size()-1));
}
