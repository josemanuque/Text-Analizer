#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "List.h" // hereda de la clase List
#include <stdexcept>

// definir constante para el compilador
#define DEFAULT_MAX_SIZE 1024 // durante la compilación si se encuentra con DEFAULT_MAX_SIZE sustituya por un 1024.
using std::runtime_error;
using std::cout;
using std::endl;


/*
Clase ArrayList

-Descripción: Clase de Lista de arreglo.
-Funcionalidades:
. crea un arreglo de n tamaño, en el cual almacena elementos genéricos, del mismo tipo entre ellos,
. permite almacenas elementos, recuperarlos, borrarlos, buscar su indice, etc.
. permite determinar si la lista contiene a un elemento.
. al ser un arreglo, en caso de que se llene por completo, tiene la posibilidad de expandirse.


Hecho por: Profesor Mauricio Avilés

*/



// Limitantes ArrayList: -Capacidad, - Inserciones son lentas.
template <typename E>
class ArrayList : public List<E> { // para heredar de la clase List de tipo genérico E se escribe así.
private:
    E *elements;
    int max;
    int pos;
    int size;

    void checkCurrentElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (pos == size)
            throw runtime_error("No current element.");
    }
    void expand() {
        E *temp = new E[2 * max];
        for (int i = 0; i < size; i++)
            temp[i] = elements[i];
        delete [] elements;
        elements = temp;
        max = 2 * max;
    }

public:
    ArrayList(int max = DEFAULT_MAX_SIZE) {
        elements = new E[max];
        this->max = max;
        size = pos = 0; // como las asignaciones retornan el valor, se le puede asignar a size lo que se le asigna a pos.
        // se le asigna a size lo que retorna la asignación de pos (0).
    }
    ~ArrayList() {
        delete [] elements;
    }
    void insert(E element) {
        if (size == max)
            expand();
        for (int i = size; pos < i; i--)
            elements[i] = elements[i - 1];

        elements[pos] = element;
        size++;
    }
    void append(E element) {
        if (size == max)
            expand();
        elements[size] = element;
        size++;
    }
    E remove() {
        checkCurrentElement();
        E result = elements[pos];
        for (int i = pos + 1; i < size; i++)
            elements[i - 1] = elements[i];
        size--;
        return result;
    }
    void clear() {
        size = pos = 0;
        // lo de borrar no es necesario pero asegura que todo se borre creando un array nuevo
        // tiene el problema de que es más lento porque devuelve memoria y vuelve a pedir
        delete [] elements;
        elements = new E[max];
    }
    E getElement() {
        checkCurrentElement();
        return elements[pos];
    }
    void goToStart() {
        pos = 0;
    }
    void goToEnd() {
        pos = size;
    }
    void goToPos(int newPos) {
        if (newPos < 0 || newPos > size)
            throw runtime_error("Position out of range.");
        pos = newPos;
    }
    void next() {
        if (pos < size)
            pos++;
    }
    void previous() {
        if (pos > 0)
            pos--;
    }
    bool atStart() {
        return pos == 0;
    }
    bool atEnd() {
        return pos == size;
    }
    int getPos() {
        return pos;
    }
    int getSize() {
        return size;
    }
    void print() {
        int oldPos = pos;
        cout << "[ ";
        for (goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]" << endl;
        pos = oldPos;
    }
    int indexOf(E element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element)
                return i;
        }return -1;
    }
    bool contains(E element) { //se puede usar el indexOf
        if (indexOf(element) != -1)
            return true;
        return false;
    }
    void extend(List<E> *L) { //shorten both extend and equals using methods in the for
        if (L == this)
            return;
        int posL = L->getPos();
        for (L->goToStart(); !(L->atEnd()); L->next()){
            append(L->getElement());
        }
        L->goToPos(posL);
    }
    bool equals(List<E> *L) {
        if (this->size != L->getSize())
            return false;
        int posL = L->getPos();
        for (int i = 0; i < L->getSize(); i++){
            L->goToPos(i);
            if (elements[i] != L->getElement()){
                L->goToPos(posL);
                return false;
            }
        }
        L->goToPos(posL);
        return true;
    }
};

#endif // ARRAYLIST_H
