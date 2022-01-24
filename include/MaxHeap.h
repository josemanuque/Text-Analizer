#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DLinkedList.h"
#define DEFAULT_MAX_SIZE 1024

using std::cout;
using std::endl;
using std::runtime_error;


/*
    Clase MaxHeap


    Clase que crea objetos de tipo MaxHeap, basado en la estructura de heap.

    Funcionalidades:
    .Permite insertar valores comparables en desorden, y después sacarlos en orden.
    .Ordena internamente los valores, los almacena en orden.

    Hecho por Profesor Mauricio Avilés, modificado y extendido por José Manuel Quesada y Christopher Jiménez.
*/

// con esta clase se puede crear el heapSort
template <typename E> // el tipo E debe ser comparable
class MaxHeap {
private:
    E *elements;
    int max;
    int size;

    // inline le indica al compilador que no haga llamada a funcion, sino que inserta la linea donde este método es llamado
    // da mas eficiencia
    inline int leftChild(int pos) {
        return 2 * pos + 1;
    }
    inline int rightChild(int pos) {
        return 2 * pos + 2;
    }
    inline int parent(int pos) {
        return (pos - 1) / 2;
    }
    bool isLeaf(int pos) {
        return leftChild(pos) >= size;
    }
    void swap(int pos1, int pos2) {
        E temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }
    void siftUp(int pos) {
        while (pos != 0 && elements[pos] > elements[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }
    void siftDown(int pos) {
        // llamar solo una vez a greaterChild y guardarlo en variable para que no ocurran errores
        while (!isLeaf(pos) && elements[greaterChild(pos)] > elements[pos]) {
            int child = greaterChild(pos);
            swap(pos, child);
            pos = child;
        }
    }
    int greaterChild(int pos) { // greater in terms of priority
        if (rightChild(pos) >= size || elements[leftChild(pos)] > elements[rightChild(pos)])
            return leftChild(pos);
        return rightChild(pos);
    }

public:
    MaxHeap(int max = DEFAULT_MAX_SIZE) {
        if (max < 1)
            throw runtime_error("Max size must be positive.");
        elements = new E[max];
        this->max = max;
        size = 0;
    }
    ~MaxHeap() {
        delete [] elements;
    }
    void insert(E element) {
        if (size == max)
            throw runtime_error("Heap is full.");
        elements[size] = element;
        siftUp(size);
        size++;
    }
    E first() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return elements[0];
    }
    E remove(int pos) {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        if (pos < 0 || pos >= size)
            throw runtime_error("Index out of range.");
        swap(pos, size - 1);
        size--;
        if (size > 0) // si size es 0 no es necesario hacer un siftDown.
            siftDown(pos);
        return elements[size]; // size señala al elemento borrado (casilla "vacía")
    }
    E removeFirst() {
        return remove(0);
    }
    int getSize() {
        return size;
    }
    void printArray(){
        for (int i = 0; i < size; i++)
            cout << elements[i] << " ";
    }
    bool isEmpty(){
        return size == 0;
    }
    void heapify(E *arr, int n){
        if (n > max)
            throw runtime_error("Array size is bigger than Heap's max size.");
        delete [] elements;
        elements = arr;
        size = n;
        for (int i = n - 1; i >= 0; i--){
            siftDown(i);
        }
    }
    void merge(MaxHeap<E> *other){
        if (size + other->getSize() > max)
            throw runtime_error("Merged size exceeds Heap's max size.");
        for (int i = 0; i < other->getSize(); i++){
            insert(other->elements[i]);
        }
    }
    List<E>* removeTop(int n) {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        if (n > size)
            throw runtime_error("Top number is bigger than Heap.");
        List<E> *list  = new DLinkedList<E>();
        for (int i = 0; i < n; i++)
            list->append(removeFirst());
        return list;
    }
};

#endif // MAXHEAP_H
