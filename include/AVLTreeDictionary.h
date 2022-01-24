#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H


#include <stdexcept>
#include <iostream>
#include "Dictionary.h"
#include "AVLTree.h"
#include "DLinkedList.h"
#include "KVPair.h"

using std::runtime_error;
using std::cout;
using std::endl;

/*
    Clase AVLTreeDictionary


    Clase que hereda de Dictionary. Es un tipo de diccionario.

    Funcionalidades:
    .Diccionario (permite almacenar pares llave-valor) que se basa en la estructura AVLTree.
    .Permite, entre muchas cosas, obtener valores a partir de las llaves,
    así como listas de los pares y de los valores

    Hecho por Profesor Mauricio Avilés, modificado y extendido por José Manuel Quesada y Christopher Jiménez.
*/



template <typename K, typename V>
class AVLTreeDictionary : public Dictionary<K, V> {
private:
    AVLTree<KVPair<K, V>> elements;

public:
    AVLTreeDictionary() : elements() {}
    ~AVLTreeDictionary() {}
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        elements.insert(p);
    }
    V remove(K key) {
        KVPair<K, V> p(key);
        p = elements.remove(p);
        return p.value;
    }
    void clear(){
        elements.clear();
    }
    V getValue(K key) {
        KVPair<K, V> p(key);
        p = elements.find(p);
        return p.value;
    }
    void setValue(K key, V value) {
        KVPair<K, V> p(key, value);
        elements.remove(p);
        elements.insert(p);
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return elements.contains(p);
    }
    List<K>* getKeys() {
        List<K> *keys = new DLinkedList<K>();
        List<KVPair<K, V>> *pairs = elements.getElements();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.key);
        }
        delete pairs; // para no tener fugas de memoria
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new DLinkedList<V>();
        List<KVPair<K, V>> *pairs = elements.getElements();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            values->append(p.value);
        }
        delete pairs; // para no tener fugas de memoria
        return values;
    }
    int getSize(){
        return elements.getSize();
    }
    void print() {
        cout << "[";
        auto *pairs = elements.getElements();
        //cout << "SIZE: " << pairs->getSize() <<endl << endl;
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            auto p = pairs->getElement();
            cout << p.key << ":" << p.value << " ";
        }
        cout << "]" << endl;
    }

    void update(Dictionary<K, V> *D) {
        List<K> *keys = new DLinkedList<K>();
        keys = D->getKeys();
        for (int i = 0; i < D->getSize(); i++){
            keys->goToPos(i);
            K key = keys->getElement();

            if (elements.contains(key)){
                setValue(key, D->getValue(key));
            }
            else
                insert(key, D->getValue(key));
        }
    }
    void zip(List<K> *keys, List<V> *values) {
        int size;
        if (keys->getSize() < values->getSize())
            size = keys->getSize();
        else
            size = values->getSize();
        if (size == 0)
            throw runtime_error("Not enough items to match.");
        K key;
        V value;
        for (int i = 0; i < size; i++){
            keys->goToPos(i);
            values->goToPos(i);
            key = keys->getElement();
            value = values->getElement();
            insert(key, value);
        }
    }

};

#endif // AVLTREEDICTIONARY_H
