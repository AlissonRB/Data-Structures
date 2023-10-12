//! Copyright [2022] <ALISSON RAFAEL BARBOSA>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  //  std::size_t
#include <stdexcept>  // exptions

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  //  limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

    // getter: info
        T& data() {
            return data_;
        }

        // getter-constante: info
        const T& data() const {
            return data_;
        }

        // getter: próximo
        Node* next() {
            return next_;
        }

        // getter-constante: próximo
        const Node* next() const {
            return next_;
        }

        // setter: próximo
        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (size() > 0) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *novo = new Node(data, top_);
    if (novo == nullptr) {
        throw std::out_of_range("Pilha Cheia!");
    } else {
        top_ = novo;
        size_++;
    }
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha Vazia!");
    } else {
        Node *aux = top_;
        T saida = aux->data();
        top_ = top_->next();
        delete aux;
        size_--;
        return saida;
    }
}

template<typename T>
T& structures::LinkedStack<T>::top() const {  // dado no topo
    if (empty()) {
        throw std::out_of_range("Pilha Vazia");
    }
    return (top_->data());
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return (size_);
}
