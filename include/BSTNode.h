#ifndef BSTNODE_H
#define BSTNODE_H

/*
Clase BSTNode

-Descripci�n: Clase encargada de crear nodos de �rboles de b�squeda binaria.
-Funcionalidades:
. crea nodo BST, los cuales permiten guardar un elemento y dos punteros, uno al hijo izquierdo, otro al hijo derecho.
. incluye m�todos para poder obtener la cantidad de hijos, saber si es hoja. Adem�s obtener hijo �nico.

Hecho por: Profesor Mauricio Avil�s.

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
