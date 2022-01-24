#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"
#include "UnsortedArrayDictionary.h"
#include "MaxHeap.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;


/*
    Clase Trie

    Es un arbol de prefijos.
    Árbol que se encarga de almacenar palabras por medio de trie nodes.
    Útil para realizar busquedas eficientes.

    Funcionalidades:
    .Permite almacenar palabras y buscarlas por prefijo, palabra, tamaño de palabra.
    .Además permite saber cuales son las palabras más usadas (más repetidas).

    Hecho por Profesor Mauricio Avilés, modificado y extendido por José Manuel Quesada y Christopher Jiménez.
*/


class Trie{ //string y char no sirve para todos los caracteres
private:
    TrieNode *root;
    UnsortedArrayDictionary<int, string> *wordsAppearance = new UnsortedArrayDictionary<int, string>();

    void clearAux(TrieNode *current){
        List<TrieNode*> *pointers = current->getChildrenPointers();
        for (pointers->goToStart(); !pointers->atEnd(); pointers->next())
            clearAux(pointers->getElement());
        delete current;
    }
    void getMatchesAux(TrieNode* current, string prefix, List<string> *words){
        if (current->isFinal)
            words->append(prefix);
        List<char> *children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()){
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1, c);
            getMatchesAux(current->getChild(c), newPrefix, words);
        }
        delete children;
    }
    void lengthSearchAux(TrieNode* current, string prefix, List<string>* words, int length) {
        if (length == 0 && current->isFinal)
            words->append(prefix);
        if (length == 0 && !current->isFinal)
            return;
        List<char>* children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()) {
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1, c);
            lengthSearchAux(current->getChild(c), newPrefix, words, length - 1);
        }
        delete children;
    }
    void saveRepetitionsAux(TrieNode* current, string prefix) {
        if (current->isFinal) {
            wordsAppearance->insert(current->getIndexes()->getSize(), prefix);
        }
        List<char>* children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()) {
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1, c);
            saveRepetitionsAux(current->getChild(c), newPrefix);
        }
        delete children;
    }



public:
    Trie(){
        root = new TrieNode();
    }

    ~Trie(){
        clear();
        delete root;
    }
    void insert(string word,unsigned int line){
        TrieNode *current = root;
//        cout << "Palabra " << word << "contiene" << this->containsWord(word) << endl;
        if (this->containsWord(word)){
            for (unsigned int i = 0; i < word.size(); i++){
//                cout << word[i] << endl;
                current = current->getChild(word[i]);
            }
//            cout << "-------------------------" << endl;
            current->insertIndex(line);
            //int size = current->getIndexes()->getSize();
            return;
        }
        for (unsigned int i = 0; i < word.size(); i++){
            current->prefixCount++;
            if (!current->contains(word[i]))
                current->add(word[i]);
            current = current->getChild(word[i]);
        }
        current->prefixCount++;
        current->isFinal = true;
        current->insertIndex(line);
        //int size = current->getIndexes()->getSize();
    }
    void saveWordAppearances() {

    }
    List<unsigned int>* searchWord(string word){ // busca palabra y retorna lista con todas la lineas donde está
        List<unsigned int> *indexes;
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++){
//            cout << " Contiene " << current->contains(word[i]) << endl;
            if (!current->contains(word[i])){
                indexes = new DLinkedList<unsigned int>();
                return indexes;
            }
            //cout << word[i] << endl;
            current = current->getChild(word[i]);
        }
        if (current->isFinal){
            indexes = current->getIndexes();
            return indexes;
        }
        indexes = new DLinkedList<unsigned int>();
        return indexes;
    }
    bool containsWord(string word){
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++){
            if (!current->contains(word[i]))
                return false;
            current = current->getChild(word[i]);
        }
        return current->isFinal;
    }
    bool containsPrefix(string prefix){
        TrieNode *current = root;
        for (unsigned int i = 0; i < prefix.size(); i++){
            if (!current->contains(prefix[i]))
                return false;
            current = current->getChild(prefix[i]);
        }
        return true;
    }
    int prefixCount(string prefix) {
        TrieNode *current = root;
        for (unsigned int i = 0; i < prefix.size(); i++){
            if (!current->contains(prefix[i]))
                return 0;
            current = current->getChild(prefix[i]);
        }
        return current->prefixCount;
    }
    void remove(string word){
        if (!containsWord(word))
            throw runtime_error("Word not found.");
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++){
            current->prefixCount--;
            TrieNode *child = current->getChild(word[i]);
            if (current->prefixCount == 0)
                delete current;
            else if (child->prefixCount == 1)
                current->remove(word[i]);
            current = child;
        }
        current->prefixCount--;
        if (current->prefixCount == 0)
            delete current;
        else
            current->isFinal = false;
    }
    void clear() {
        clearAux(root);
        root = new TrieNode();
    }
    List<string>* getMatches(string prefix){
        List<string> *words = new DLinkedList<string>();
        TrieNode* current = root;
        for (unsigned int i = 0; i < prefix.size(); i++){
            if (!current->contains(prefix[i]))
                return words;
            current = current->getChild(prefix[i]);
        }
        getMatchesAux(current, prefix, words);
        return words;
    }
    List<string>* lengthSearch(int length) {
        List<string>* words = new DLinkedList<string>();
        //TrieNode* current = root;
        lengthSearchAux(root,"", words, length);
        return words;
    }
    void saveRepetitions() {
        saveRepetitionsAux(root, "");
    }
    List<string>* topSearch(int top, List<string>* words) {
        int oldQty = wordsAppearance->getKeys()->getSize();
        UnsortedArrayDictionary<int, string>* temp = new UnsortedArrayDictionary<int, string>(oldQty);
        temp->update(wordsAppearance);
        int ignoreSize = words->getSize();
        int index;
        List<int>* keys = temp->getKeys();
        List<string>* values = temp->getValues();
        //List<string>* oldvalues = wordsAppearance->getValues();
        for (int i = 0; i < ignoreSize; i++) {
            words->goToPos(i);
            index = values->indexOf(words->getElement());
            if (index != -1) {
                values->goToPos(index);
                keys->goToPos(index);
                keys->remove();
                //cout << "Palabra Ignorada: " << values->getElement() << endl;
                values->remove();
            }
        }
        int keysQuantity = keys->getSize();
        List<string>* topWords = new DLinkedList<string>();
        if (top > keysQuantity) {
            cout << "Top excede la cantidad de palabras en el texto. No se retornará nada. " << endl;
            return topWords;
        }
        cout << "Cargando top..." << endl;
        MaxHeap<int> heap(keysQuantity);
        for (int i = 0; i < keysQuantity; i++) {
            keys->goToPos(i);
            heap.insert(keys->getElement());
        }
        delete keys;
        delete values;
        int heapQty;
        for (int i = 0; i < top; i++) {
            heapQty = heap.removeFirst();
            topWords->append(temp->getValue(heapQty));
            temp->remove(heapQty);
        }
        delete temp;
        return topWords;
    }
    void print() {
        List<string> *words = getMatches("");
        cout << "[ ";
        for (words->goToStart(); !words->atEnd(); words->next()){
            cout << words->getElement() << " ";
        }
        cout << "]" << endl;
        delete words;
    }
    int getSize() {
        return root->prefixCount;
    }
};

#endif // TRIE_H
