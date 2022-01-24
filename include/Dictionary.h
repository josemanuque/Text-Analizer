#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "List.h"

/*
Clase List

-Descripción: Clase abstracta de un diccionario.
-Funcionalidades:
. define los métodos que deben tener los diccionarios, para ser implementados en otra clase.

Hecho por: Profesor Mauricio Avilés

*/

template <typename K, typename V>
class Dictionary {
private:
    Dictionary(const Dictionary<K, V> &other) {}
    void operator=(const Dictionary<K,V> &other) {}

public:
    Dictionary() {}
    virtual ~Dictionary() {}
    virtual void insert(K key, V value) = 0;
    virtual V remove(K key) = 0;
    virtual V getValue(K key) = 0;
    virtual void setValue(K key, V value) = 0;
    virtual bool contains(K key) = 0;
    virtual List<K>* getKeys() = 0;
    virtual List<V>* getValues() = 0;
    virtual int getSize() = 0;
    virtual void print() = 0;
};

#endif // DICTIONARY_H
