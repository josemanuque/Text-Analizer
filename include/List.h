#ifndef LIST_H
#define LIST_H

/*
Clase List

-Descripción: Clase abstracta de una lista.
-Funcionalidades:
. define los métodos que deben tener las listas, para ser implementados en otra clase.

Hecho por: Profesor Mauricio Avilés

*/


template <typename E>
class List {
private:
    void operator =(const List&) {}
    List(const List&) {}

public:
    List() {} // virtual que se puede sobreescribir en una subclase (se definen en las subclases).
    virtual ~List() {}
    virtual void insert(E element) = 0; // el = 0 permite forzar a que la subclase deba hacer la implementacion de este método.
    virtual void append(E element) = 0;
    virtual E remove() = 0;
    virtual void clear() = 0;
    virtual E getElement() = 0;
    virtual void goToStart() = 0;
    virtual void goToEnd() = 0;
    virtual void goToPos(int pos) = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual bool atStart() = 0;
    virtual bool atEnd() = 0;
    virtual int getPos() = 0;
    virtual int getSize() = 0;
    virtual void print() = 0;
    virtual int indexOf(E element) = 0;
    virtual bool contains(E element) = 0;
    virtual void extend(List<E> *L) = 0;
    virtual bool equals(List<E> *L) = 0;
};

#endif // LIST_H
