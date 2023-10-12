// Copyright [2022] <Alisson Rafael Barbosa>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista Cheia");
    } else {
        contents[size_] = data;
        size_ += 1;
    }
}

template<typename T >
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        for (std::size_t i = size_; i > 0; i--) {
	        contents[i] = contents[i-1];
        }
        contents[0] = data;
        size_ += 1;
    }
}

template<typename T >
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("Fila cheia");
    } else if (index > size_ || index < 0) {
        throw std:: out_of_range("erro de posição");
    } else {
        for (std::size_t i = size_; i > index; i--) {
            contents[i] = contents[i-1];
        }
        contents[index] = data;
        size_++;
    }
}

template<typename T >
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else if (empty() || data > contents[size_ -1]) {
        push_back(data);
    } else {
        std::size_t pos;
        pos = 0;
        while (data > contents[pos]) {
            pos = pos + 1;
        }
        insert(data, pos);
    }
}

template<typename T >
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if (index > size_ - 1 || index < 0) {
        throw std:: out_of_range("erro de posição");
    } else {
        T valor;
        size_ -= 1;
        valor = contents[index];
        for (std::size_t i = index; i < size_; i++) {
            contents[i] = contents[i + 1];
        }
        return valor;
    }
}

template<typename T >
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    T aux = contents[size_-1];
    size_--;
    return aux;
}

template<typename T >
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        std::size_t pos;
        T aux;
        size_ -= 1;
        aux = contents[0];
        pos = 0;
        while (pos <= size_) {
            contents[pos] = contents[pos + 1];
            pos += 1;
        }
        return aux;
    }
}

template<typename T >
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        for (std::size_t i = 0; i < max_size_; i++) {
            if (contents[i] == data) {
                pop(i);
            }
        }
    }
}

template<typename T >
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

template<typename T >
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (std::size_t i = 0; i< size_; i++) {
        if (data == contents[i]) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    std::size_t pos = 0;
    while (pos <= size_ -1 && contents[pos] != data) {
        pos = pos + 1;
    }
    return pos;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T >
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("Posição invalida");
    } else {
        return contents[index];
    }
}

template<typename T >
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T >
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("Posição invalida");
    } else {
        return contents[index];
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
