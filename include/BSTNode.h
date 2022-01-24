#ifndef BSTNODE_H
#define BSTNODE_H

/*
Clase BSTNode

-Descripción: Clase encargada de crear nodos de árboles de búsqueda binaria.
-Funcionalidades:
. crea nodo BST, los cuales permiten guardar un elemento y dos punteros, uno al hijo izquierdo, otro al hijo derecho.
. incluye métodos para poder obtener la cantidad de hijos, saber si es hoja. Además obtener hijo único.

Hecho por: Profesor Mauricio Avilés.

*/

template <typename E>
class BSTNode {
public:
    E element;
    BSTNode<E> *left;
    BSTNode<E> *right;

    BSTNode(E element, BSTNode<E> *left = nullptr, BSTNode<E> *right = nullptr){
        this->element = element;
        this->left = left;
        this->right = right;

    }

    bool isLeaf(){
        return left == nullptr && right == nullptr;
    }

    int childrenCount(){
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }
    BSTNode<E>* getUniqueChild(){
        return left == nullptr? right : left;
    }


};

#endif // BSTNODE_H
