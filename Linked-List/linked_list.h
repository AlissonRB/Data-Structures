//! Copyright [2022] <ALISSON RAFAEL BARBOSA>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  //  std::size_t
#include <stdexcept>  // exptions

namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};  // head = nuullptr;
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T >
void structures::LinkedList<T>::clear() {
    while (size_ > 0) {
        pop_front();
    }
}

template<typename T >
void structures::LinkedList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        insert(data, size_);
    }
}

template<typename T >
void structures::LinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data, head);
    if (novo == nullptr) {
        throw std::out_of_range("Lista Cheia");
    } else {
        head = novo;
        size_++;
    }
}

template<typename T >
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Posição invalida");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_-1) {
        push_back(data);
    } else {
        Node *novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("Lista Cheia!");
        }
        Node *p = head;
        for (std::size_t i = 1; i < index; i++) {
            p = p->next();
        }
        novo->next(p->next());
        p->next(novo);
        size_++;
    }
}

template<typename T >
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node *p = head;
    std::size_t posicao = 0;
    if (empty()) {
        delete p;
        push_front(data);
    } else {
        while (p->next() != nullptr && data > p->data()) {
            p = p->next();
            posicao++;
        }
        if (data > p->data()) {
            insert(data, posicao + 1);
        } else {
            insert(data, posicao);
        }
    }
}

template<typename T >
T& structures::LinkedList<T>::at(std::size_t index) {
if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    } else if (index >= size() || index < 0) {
        throw std::out_of_range("Posição inválida!");
    } else {
        Node *aux = head;
        for (size_t i = 0; i < index; i++) {
            aux = aux->next();
        }
        return aux->data();
    }
}

template<typename T >
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    } else if (index >= size_) {
        throw std::out_of_range("Posição Inválida!");
    } else if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node *p = head;
        for (std::size_t i = 0; i < index-1; i++) {
            p = p->next();
        }
        Node *aux = p->next();
        T saida = aux->data();
        p->next(aux->next());
        delete aux;
        size_--;
        return saida;
    }
}

template<typename T >
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Fila Vazia!");
    } else if (size_ == 1) {
        return pop_front();
    } else {
        Node *p = head;
        for (std::size_t i = 1; i < size_ -1; i++) {
            p = p->next();
        }
        T saida;
        saida = p->next()->data();
        delete p->next();
        p->next(nullptr);
        size_--;
        return saida;
    }
}

template<typename T >
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Fila Vazia!");
    } else {
        Node *aux = head;
        head = head->next();
        T saida = aux->data();
        delete aux;
        size_--;
        return saida;
    }
}

template<typename T >
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T >
bool structures::LinkedList<T>::empty() const {
    return (size_ == 0);
}

template<typename T >
bool structures::LinkedList<T>::contains(const T& data) const {
    Node *p = head;
    while (p != nullptr) {
        if (p->data() == data) {
            return true;
        }
        p = p->next();
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty()) {
        return -1;
    } else {
        Node *p = head;
        for (std::size_t i = 0; i < size_; i++) {
            if (data == p->data()) {
                return i;
            }
            p = p->next();
        }
        return size_;
    }
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
