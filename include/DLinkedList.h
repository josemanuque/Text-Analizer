#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "List.h"
#include "DNode.h"
#include <stdexcept>


using std::runtime_error;
using std::cout;
using std::endl;

/*
Clase DLinkedList

-Descripción: Clase de lista doblemente enlazada.
-Funcionalidades:
. crea nodos, los cuales permiten almacenar elementos del mismo tipo.
. imprime sus elementos.


Hecho por: Profesor Mauricio Avilés, modificado y extendido por José Manuel Quesada

*/

// Doubly linked list
template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E> *head;
    DNode<E> *current;
    DNode<E> *tail;
    int size;


    void checkCurrentElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
    }
    // recordar que current->next es el nodo actual.
public:
    DLinkedList() { //DNode<E>(next, previous)
        current = head = new DNode<E>(nullptr, nullptr);
        head->next = tail = new DNode<E>(nullptr, head);
        size = 0;
    }
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }
    void insert(E element) {
        current->next = current->next->previous =
        new DNode<E>(element, current->next, current);
        size++;
    }
    void append(E element) {
        tail->previous = tail->previous->next = new DNode<E>(element, tail, tail->previous);
        size++;
    }
    E remove() {
        checkCurrentElement();
        E result = current->next->element;
        current->next = current->next->next;
        delete current->next->previous;
        current->next->previous = current;
        size--;
        return result;
    }
    void clear() {
        while (head->next != tail) {
            current = head->next;
            head->next = current->next;
            delete current;
        }
        tail->previous = current = head;
        size = 0;
    }
    E getElement() {
        checkCurrentElement();
        return current->next->element;
    }
    void goToStart() {
        current = head;
    }
    void goToEnd() {
        current = tail->previous;
    }
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of range.");
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }
    void next() {
        if (current != tail->previous)
            current = current->next;
    }
    void previous() {
        if (current != head)
            current = current->previous;
    }
    bool atStart() {
        return current == head;
    }
    bool atEnd() {
        return current == tail->previous;
    }
    int getPos() { // usando un for
        int pos = 0;
        for (DNode<E> *temp = head;
            temp != current;
            temp = temp->next)
            pos++;
        return pos;
    }
    int getSize() {
        return size;
    }
    void print() {
        DNode<E> *oldCurrent = current;
        cout << "[ ";
        for (goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]" << endl;
        current = oldCurrent;
    }
    int indexOf(E element) {
        int tempPos = getPos();
        int index = -1;
        for (goToStart(); !atEnd(); next()){
            if (getElement() == element){
                index = getPos();
                break;
            }
        }
        goToPos(tempPos);
        return index;
    }
    bool contains(E element) {
        if (indexOf(element) != -1)
            return true;
        return false;
    }
    void extend(List<E> *L) {
        if (L == this)
            return;
        int posL = L->getPos();
        for (L->goToStart(); !(L->atEnd()); L->next())
            append(L->getElement());
        L->goToPos(posL);
    }
    bool equals(List<E> *L) {
        if (this->size != L->getSize())
            return false;
        if (L == this)
            return true;
        DNode<E> *oldCurrent = current;
        int posL = L->getPos();
        goToStart();
        for (L->goToStart(); !(L->atEnd()); L->next(), next()){
            if (getElement() != L->getElement()){
                L->goToPos(posL);
                current = oldCurrent;
                return false;
            }
        }
        L->goToPos(posL);
        current = oldCurrent;
        return true;
    }
};

#endif // DLINKEDLIST_H
