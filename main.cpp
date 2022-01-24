#include <iostream>
#include <string>
#include <fstream>
#include "AVLTreeDictionary.h"
#include "Trie.h"
#include "MaxHeap.h"
#include "ArrayList.h"
#include "DLinkedList.h"
#include <time.h>
#include <windows.h>
#include<bits/stdc++.h>

using namespace std;

/*
    Main del programa de indización de textos.
    Contiene toda la interfaz del programa, encargandose de mostrar menús
    opciones, entre otros.
    Hecho por José Manuel Quesada y Christopher Jiménez.
*/

int test() {
    //    Trie t;
    //    t.insert("comando");
    //    t.insert("comemos");
    //    t.insert("cometa");
    //    t.insert("cometido");
    //    t.insert("como");
    //    t.insert("cono");
    //    t.insert("conocido");
    //    t.insert("nueva palabra");
    //    t.insert("nuca");
    //    t.insert("nueva york");
    //    t.insert("nunca");
    //    t.insert("risa");
    //    t.insert("ritmo");
    //    t.insert("ritual");
    //    t.print();
    //    List<string> *m = t.getMatches("ri");
    //    cout << endl << m->getSize() << endl;
    //    for (m->goToStart(); !m->atEnd(); m->next()) {
    //        cout << m->getElement() << endl;
    //    }

    //    delete m;

    //    srand(time(0));
    //    MaxHeap<int> *heap = new MaxHeap<int>();
    //    cout << "Insertando: ";
    //    for (int i = 0; i < 10; i++){
    //        int r = rand();
    //        heap->insert(r);
    //    }
    //    for (int i = 0; i < 10; i++){
    //        cout << heap->removeFirst() << endl;
    //    }
    return 0;
}



Trie trie;
ArrayList<string>* lineas;

void searchPrefix(string prefix) {
    cout << "---------------Palabras con prefijo: " << prefix << "---------------" << endl;
    List<string>* words = trie.getMatches(prefix);
    unsigned int listSize = words->getSize();
    int apariciones;
    string word;
    for (unsigned int i = 0; i < listSize; i++) {
        words->goToPos(i);
        word = words->getElement();
        apariciones = trie.searchWord(word)->getSize();
        cout << word << ". (" << apariciones << " apariciones)." << endl;
    }
    cout << endl << endl;
}

void searchWord(string word) {
    cout << "---------------Bucando la palabra: " << word << "---------------" << endl;
    List<unsigned int>* indexes = trie.searchWord(word);
    unsigned int listSize = indexes->getSize();
    int lineIndex;
    if (listSize == 0) {
        cout << "No se encontró la palabra..." << endl;
    }
    cout << "La palabra aparece " << listSize << " veces." << endl;
    for (unsigned int i = 0; i < listSize; i++) {
        indexes->goToPos(i);
        lineIndex = indexes->getElement();
        lineas->goToPos(lineIndex);
        string line = lineas->getElement();
        cout << (lineIndex + 1) << ": " << line << endl;
    }
    cout << endl << endl;
}

void lengthSearch(int length) {
    cout << "---------------Palabras de " << length << " letras---------------" << endl;
    List<string>* foundWords = trie.lengthSearch(length);
    unsigned int wordsQuantity = foundWords->getSize();
    int apariciones;
    string word;
    if (wordsQuantity == 0){
        cout << "No se encontraron palabras con " << length << " letras." << endl;
        return;
    }
    for (unsigned int i = 0; i < wordsQuantity; i++) {
        foundWords->goToPos(i);
        word = foundWords->getElement();
        apariciones = trie.searchWord(word)->getSize();
        cout << word << ". (" << apariciones << " apariciones)." << endl;
    }
    cout << endl << endl;
}
void mostUsedWords(char letter) {
    string word;
    switch (letter) {
    case 'a': {
        cout << "Ingrese la palabra a añadir: ";
        cin >> word;
        string s;
        ArrayList<string>* words = new ArrayList<string>(1021);
        ifstream ignoreFile("Ignorar.txt");
        if (ignoreFile.is_open()) {

            while (!ignoreFile.eof()) {
                getline(ignoreFile, s);
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                words->append(s);

            }

            ignoreFile.close();
            ofstream newFile;
            newFile.open("Ignorar.txt", ofstream::out | ofstream::trunc);
            int wordsSize = words->getSize();
            string current;
            //bool located = false;
            for (int i = 0; i < wordsSize; i++) {
                words->goToPos(i);
                current = words->getElement();
                if (current != word)
                    newFile << current << endl;


            }

            newFile << word << endl;
            cout << "Palabra agregada con éxito." << endl;
            newFile.close();
        }

        else cerr << "Error de apertura del archivo." << endl;
        cout << endl << endl;
        break;
    }
    case 'b': {
        cout << "Ingrese la palabra a eliminar: ";
        cin >> word;
        string s;
        ArrayList<string>* words = new ArrayList<string>(1021);
        ifstream ignoreFile("Ignorar.txt");
        if (ignoreFile.is_open()) {

            while (!ignoreFile.eof()) {
                getline(ignoreFile, s);
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                words->append(s);

            }

            ignoreFile.close();
            ofstream newFile;
            newFile.open("Ignorar.txt", ofstream::out | ofstream::trunc);
            int wordsSize = words->getSize();
            string current;
            bool located = false;
            for (int i = 0; i < wordsSize; i++) {
                words->goToPos(i);
                current = words->getElement();
                if (current != word)
                    newFile << current << endl;
                else located = true;

            }

            if (!located) {
                cout << "Palabra a borrar no encontrada." << endl;
            }
            newFile.close();
        }
        else cerr << "Error de apertura del archivo." << endl;
        cout << endl << endl;
        break;
    }
    case 'c': {
        string s;
        ArrayList<string>* words = new ArrayList<string>(1021);
        ifstream ignoreFile("Ignorar.txt");
        if (ignoreFile.is_open()) {

            while (!ignoreFile.eof()) {
                getline(ignoreFile, s);
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                words->append(s);

            }
        }
        else {
            cerr << "Error de apertura en el archivo de palabras a ignorar." << endl;
            return;
        }
        string cantidad;
        int top;
        bool invalidInput;
        cout << "Ingrese el top de palabras más repetidas que quiere observar: ";
        cin >> cantidad;
        invalidInput = true;
        while (invalidInput) {
            try{
                top = stoi(cantidad);
                invalidInput = true;
                if (top > 0 ) {
                    invalidInput = false;
                }
                else {
                    cout << "Debe ingresar un número entero positivo. Intente de nuevo: ";
                    cin >> cantidad;
                }
            }
            catch(...){
                cout << "Debe ingresar un número entero positivo. Intente de nuevo: ";
                cin >> cantidad;
            }
        }
        List<string>* topWords = trie.topSearch(top, words);
        unsigned int wordsQuantity = topWords->getSize();
        int apariciones;
        string word;
        cout << "---------------Top " << top << " palabras más usadas---------------" << endl;
        for (unsigned int i = 0; i < wordsQuantity; i++) {
            topWords->goToPos(i);
            word = topWords->getElement();
            apariciones = trie.searchWord(word)->getSize();
            cout << (i + 1) << ". " << word << " (" << apariciones << " apariciones)." << endl;
        }
        ignoreFile.close();
        cout << endl << endl;
        break;
    }
    case 'd':
        cout << "Regresando al menú principal." << endl;
        cout << endl << endl;
        break;
    }
}
int main()
{
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    cout << "Indización de un texto utilizando Tries" << endl;
    cout << "---------------------------------------" << endl << endl;
    cout << "Bienvenido!" << endl;
    cout << "Este programa esta destinado al analisis de un texto." << endl;
    cout << "Almacena el texto de un archivo linea por linea para obtener las palabras más usadas," << endl;
    cout << "buscar por prefijos, palabra y muchas cosas más";
    cout << " :) " << endl << endl;
    string fileName;
    cout << "Ingrese el nombre del archivo: ";
    cin >> fileName;
    string s;
    lineas = new ArrayList<string>(10000);
    ifstream f(fileName);
    if (f.is_open()) {
        while (!f.eof()) {
            getline(f, s);
            lineas->append(s);
        }
        cout << "Lista terminada" << endl;
        cout << "Cantidad de líneas: " << lineas->getSize() << endl;
        //        lineas->goToPos(5000);



        string currentLine;
        int cantidadLineas = lineas->getSize();
        for (int i = 0; i < cantidadLineas; i++) {
            lineas->goToPos(i);
            //            cout << lineas->getElement() << endl;
            currentLine = lineas->getElement();
            transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::tolower);
            string word = "";
            for (unsigned int j = 0; j < currentLine.length(); j++) {
                char character = currentLine[j];
                if (isalpha(character) || character == 'ñ' || character == 'á' || character == 'é'
                    || character == 'í' || character == 'ó' || character == 'ú' || character == 'ä'
                    || character == 'ü') {
                    word += character;
                }
                else {
                    if (word != "")
                        trie.insert(word, i);
                    word = "";
                }
            }
            if (word.size() > 0) {
                //                cout << word << endl;
                trie.insert(word, i);
                word = "";
            }

        }
        trie.saveRepetitions();
        //List<unsigned int>* indexes = trie.searchWord("ñ");
        //cout << "Tamaño " << indexes->getSize() << endl;
        //indexes->print();
        //trie.print();
        //        cout << trie.getSize();
        //        cout << trie.containsWord("ho");

        bool run = true;
        bool invalidInput = true;
        bool invalidString;
        string option;
        int numericOption;
        int number;
        unsigned int stringSize;
        while (run) {
            cout << "1. Consultar palabras por prefijo." << endl;
            cout << "2. Buscar palabra." << endl;
            cout << "3. Buscar palabras por cantidad de letras" << endl;
            cout << "4. Ver palabras más utilizadas. " << endl;
            cout << "5. Salir del programa" << endl;
            cout << "Ingrese el número de acción a realizar: ";
            cin >> option;

            invalidInput = true;
            while (invalidInput) {
                try {
                    numericOption = stoi(option);
                    invalidInput = true;
                    if (numericOption >= 0 && numericOption < 6) {
                        invalidInput = false;
                    }
                    else {
                        cout << "Acción inválida. Intente de nuevo: ";
                        cin >> option;
                    }
                }
                catch (...) {
                    cout << "Acción inválida. Intente de nuevo: ";
                    cin >> option;
                }
            }
            switch (numericOption) {
            case 1:
                cout << "Ingrese el prefijo a buscar: ";
                cin >> option;
                invalidInput = true;
                while (invalidInput) {
                    if (option.size() < 1) {
                        cout << "No puede ingresar un string vacío. Intente de nuevo: ";
                        cin >> option;
                    }
                    stringSize = option.size();
                    invalidString = false;
                    for (unsigned int i = 0; i < stringSize; i++) {
                        char c = option[i];
                        if (!isalpha(c) && c != 'ñ' && c != 'á' && c != 'é'
                            && c != 'í' && c != 'ó' && c != 'ú' && c != 'ä'
                            && c != 'ü') {
                            invalidString = true;
                        }
                    }
                    if (invalidString) {
                        cout << "Palabra con símbolos no válidos. Intente de nuevo: ";
                        cin >> option;
                    }
                    else {
                        invalidInput = false;
                    }
                }
                searchPrefix(option);
                break;
            case 2:
                cout << "Ingrese la palabra a buscar: ";
                cin >> option;
                invalidInput = true;
                while (invalidInput) {
                    if (option.size() < 1) {
                        cout << "No puede ingresar un string vacío. Intente de nuevo: ";
                        cin >> option;
                    }
                    stringSize = option.size();
                    invalidString = false;
                    for (unsigned int i = 0; i < stringSize; i++) {
                        char c = option[i];
                        if (!isalpha(c) && c != 'ñ' && c != 'á' && c != 'é'
                            && c != 'í' && c != 'ó' && c != 'ú' && c != 'ä'
                            && c != 'ü') {
                            invalidString = true;
                        }
                        if (invalidString) {
                            cout << "Palabra con símbolos no válidos. Intente de nuevo: ";
                            cin >> option;
                        }
                        else {
                            invalidInput = false;
                        }
                    }
                }
                searchWord(option);
                break;
            case 3:
                cout << "Ingrese la cantidad de letras de las palabras a buscar: ";
                cin >> option;
                invalidInput = true;
                while (invalidInput) {
                    try{
                        number = stoi(option);
                        invalidInput = true;
                        if (number > 0 ) {
                            invalidInput = false;
                        }
                        else {
                            cout << "Debe ingresar un número entero positivo. Intente de nuevo: ";
                            cin >> option;
                        }
                    }
                    catch(...){
                        cin.clear();
                        cout << "Debe ingresar un número entero positivo. Intente de nuevo: ";
                        cin >> option;
                    }
                }
                lengthSearch(number);
                break;
            case 4:
                cout << "a. Agregar palabra a ignorar." << endl;
                cout << "b. Borrar palabra de la lista a ignorar" << endl;
                cout << "c. Ver TOP de palabras más usadas." << endl;
                cout << "d. Regresar al menú principal." << endl;
                cout << "Ingrese la letra de la acción a realizar: ";
                cin >> option;
                invalidInput = true;
                while (invalidInput) {
                    if (option != "a" && option != "b" && option != "c" && option != "d") {
                        cout << "Entrada inválida. Intente de nuevo: ";
                        cin >> option;
                    }
                    else {
                        char character = option[0];
                        mostUsedWords(character);
                        invalidInput = false;
                    }
                }
                break;
                break;
            case 5:
                cout << "Cerrando el programa....";
                return 0;
                break;
            }
        }
    }
    else
        cout << "Error de apertura del archivo." << endl;
    return 0;
}



