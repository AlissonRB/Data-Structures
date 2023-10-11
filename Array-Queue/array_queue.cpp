#include "array_queue.h"

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("Fila cheia");
    } else {
        end_ = (end_ + 1) % max_size();
        contents[end_] = data;
        size_ +=1;
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila vazia");
    } else {
        T aux;
        aux = contents[begin_];
        begin_ = (begin_ + 1) % max_size();
        size_ -= 1;
        return aux;
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("Fila vazia");
    return contents[end_];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    end_ = -1;
    size_ = 0;
    begin_ = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return (size() == 0);
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return (size() == max_size());
}
