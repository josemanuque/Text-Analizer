#ifndef UNSORTEDARRAYDICTIONARY_H
#define UNSORTEDARRAYDICTIONARY_H

#include "Dictionary.h"
#include "ArrayList.h"
#include "DLinkedList.h"
#include "KVPair.h"
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::cin;

/*
    Clase UnsortedArrayDictionary


    Clase que hereda de Dictionary. Es un tipo de diccionario.

    Funcionalidades:
    .Diccionario (permite almacenar pares llave-valor) que se basa en la estructura ArrayList.
    .Permite, entre muchas cosas, obtener de forma rápida valores a partir de las llaves,
    así como obtener listas de los pares y de los valores.
    .Permite crear actualizar el diccionario con dos listas respectivamente.

    Hecho por Profesor Mauricio Avilés, modificado y extendido por José Manuel Quesada y Christopher Jiménez.
*/

template <typename K, typename V>
class UnsortedArrayDictionary : public Dictionary<K, V> {
private:
    ArrayList<KVPair<K, V>> *pairs;

    void checkNotExisting(K key) { // chequea que no exista (para insert)
        KVPair<K, V> p(key);
        if (pairs->contains(p))
            throw runtime_error("Key already exists.");
    }
    void checkExisting(K key) { // chequea que exista (para buscar)
        KVPair<K, V> p(key);
        if (!pairs->contains(p))
            throw runtime_error("Key not found.");
    }

public:
    UnsortedArrayDictionary(int max = DEFAULT_MAX_SIZE) {
        pairs = new ArrayList<KVPair<K, V>>(max);
    }
    ~UnsortedArrayDictionary() {
        delete pairs; // ejecuta destructor de ArrayList
    }
    void insert(K key, V value) {
        //checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs->append(p);
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p(key);
        pairs->goToPos(pairs->indexOf(p));
        p = pairs->remove();
        return p.value;
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p(key);
        pairs->goToPos(pairs->indexOf(p));
        p = pairs->getElement();
        return p.value;
    }
    void setValue(K key, V value) {
        checkExisting(key);
        KVPair<K, V> p(key, value);
        pairs->goToPos(pairs->indexOf(p));
        // equivalente a setElement, no implementado en ArrayList
        pairs->remove();
        pairs->append(p);
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs->contains(p);
    }
    List<K>* getKeys() {
        DLinkedList<K> *keys = new DLinkedList<K>();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            auto p = pairs->getElement();
            keys->append(p.key);
        }
        return keys;
    }
    List<V>* getValues() {
        DLinkedList<V> *values = new DLinkedList<V>();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            auto p = pairs->getElement(); // da el KVPair del diccionario
            values->append(p.value); // añade la llave del KVPair anterior a la DLinkedList
        }
        return values;
    }
    int getSize() {
        return pairs->getSize();
    }
    void update(Dictionary<K, V>* D) {
        List<K>* keys = new DLinkedList<K>();
        List<V>* values = new DLinkedList<V>();
        keys = D->getKeys();
        values = D->getValues();
        for (int i = 0; i < D->getSize(); i++) {
            keys->goToPos(i);
            K key = keys->getElement();
            values->goToPos(i);
            V value = values->getElement();
            insert(key, value);
        }
    }
    void print() {
        cout << "[ ";
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()){
            auto p = pairs->getElement();
            cout << p.key << ":" << p.value << " ";
        }
        cout << "]" << endl;
    }
};

#endif // UNSORTEDARRAYDICTIONARY_H
