#ifndef TRIENODE_H
#define TRIENODE_H

#include "AVLTreeDictionary.h"
#include "DLinkedList.h"

/*
    Clase TrieNode

    Clase nodo, el cual almacena un char que forma parte de una palabra
    que guarda del Trie. (Trie se compone de estos nodos)

    Funcionalidades:
    .Almacena un char. Tambi�n almacena a sus hijos en un diccionario de par <char, puntero a hijos>.
    Usado en el trie para representar strings en la estructura.
    .Contiene una lista de la cual se obtiene las l�neas de texto
    donde se encuentra la palabra. (Solo el nodo final de palabra no tiene la lista vac�a)

    Hecho por Profresor Mauricio Avil�s, modificado por Jos� Manuel Quesada y Christopher Jim�nez.
*/



class TrieNode{ // si uno quiere que sirva con caracteres unicode no usen char, usen otro tipo que sea unicode. Hay que investigar
private:
    AVLTreeDictionary<char, TrieNode*> children;
    List<unsigned int> *lines = new DLinkedList<unsigned int>();

public:
    bool isFinal;
    unsigned int prefixCount;

    TrieNode() : children(){
        isFinal = false;
        prefixCount = 0;
    }

    ~TrieNode() {}

    bool contains(char c){
        return children.contains(c);
    }
    void add(char c){
        TrieNode *newNode = new TrieNode();
        children.insert(c, newNode);
    }
    void remove(char c) {
        // Puede ser que ese delete haya que quitarlo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        children.remove(c);
    }
    TrieNode* getChild(char c){
        return children.getValue(c);
    }
    List<char>* getChildren(){
        return children.getKeys();
    }
    List<TrieNode*>* getChildrenPointers(){
        return children.getValues();
    }
    void insertIndex(unsigned int index){
        lines->append(index);
    }
    List<unsigned int>* getIndexes(){
        return lines;
    }

};

#endif // TRIENODE_H
