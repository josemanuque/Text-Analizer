#ifndef DNODE_H
#define DNODE_H

/*
Clase DNode

-Descripción: Clase encargada de crear nodos doblemente enlazados.
-Funcionalidades:
. crea nodos, los cuales permiten guardar dos punteros y un elemento.
. permiten crear listas y colas doblemente enlazadas.

Hecho por: Profesor Mauricio Avilés

*/



template<typename E>
class DNode{
public:
    E element;
    DNode<E> *next;
    DNode<E> *previous;
    DNode(E element, DNode<E> *next, DNode<E> *previous) {
        this->element = element;
        this->next = next;
        this->previous = previous;
    }
    DNode(DNode<E> *next, DNode<E> *previous) {
        this->next = next;
        this->previous = previous;
    }

};

#endif // DNODE_H
