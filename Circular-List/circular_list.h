//! Copyright [2022] <ALISSON RAFAEL BARBOSA>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

template<typename T>

class CircularList {
 public:
    CircularList();
    ~CircularList();

    void clear();  // limpar lista

    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem

    T& at(std::size_t index);  // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const;  // versão const do acesso ao indice

    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover dado específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // lista contém determinado dado?
    std::size_t find(const T& data) const;  // posição de um item na lista

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
    Node* head;  // head = nuullptr;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::CircularList<T>::CircularList() {
    head = nullptr;
    size_ = 0;
    Node *sentinela = new Node(0);
    head = sentinela;
    tail = sentinela;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
    delete head;
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (size() > 0) {
        pop_front();
    }
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Lista Cheia");
    } else {
        novo->next(head->next());
        head->next(novo);
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("Posição invalida");
    } else if (index == 0) {
        push_front(data);
    } else {
        Node *novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("Lista Cheia!");
        } else {
        Node *p = head->next();
        for (std::size_t i = 0; i < index - 1; i++) {
            p = p->next();
        }
        novo->next(p->next());
        p->next(novo);
        size_++;
        }
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *p = head;
        std::size_t posicao = 0;
        while (data > p->data() && p->next() != head) {
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

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {  // acessar em um indice
    if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    } else if (index >= size() || index < 0) {
        throw std::out_of_range("Posição inválida!");
    } else {
        Node *aux = head->next();
        for (size_t i = 0; i < index; i++) {
            aux = aux->next();
        }
        return aux->data();
    }
}

template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    } else if (index >= size() || index < 0) {
        throw std::out_of_range("Posição inválida!");
    } else {
        Node *aux = head->next();
        for (size_t i = 0; i < index; i++) {
            aux = aux->next();
        }
        return aux->data();
    }
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia!");
    } else if (index >= size_) {
        throw std::out_of_range("Posição Inválida!");
    } else if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node *p = head->next();
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

template<typename T>
T structures::CircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Fila Vazia!");
    } else if (size_ == 0) {
        return pop_front();
    } else {
        Node *p = head->next();
        for (std::size_t i = 0; i < size_-1; i++) {
            p = p->next();
        }
        T saida;
        saida = p->next()->data();
        delete p->next();
        p->next(head);
        tail = p;
        size_--;
        return saida;
    }
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Fila Vazia!");
    } else {
        Node *aux = head->next();
        head->next(aux->next());
        T saida = aux->data();
        delete aux;
        size_--;
        return saida;
    }
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {  // remover dado espec
    pop(find(data));
}

template<typename T>
bool structures::CircularList<T>::empty() const {
        return (size_ == 0);
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    Node *p = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        if (p->data() == data) {
            return true;
        }
        p = p->next();
    }
    return false;
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    if (empty()) {
        return -1;
    } else {
        Node *p = head->next();
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
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
