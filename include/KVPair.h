#ifndef KVPAIR_H
#define KVPAIR_H
#include <iostream>

using std::ostream;

/*
Clase KVPair

-Descripción: Clase encargada de crear pares llave-valor.
-Funcionalidades:
. crea llaves y valores, ambos de tipo genérico, los engloba en una clase.
. Permite comparar comparar hacer comparaciones de objetos de esta clase.
(comparando las llaves)

Hecho por: Profesor Mauricio Avilés

*/



// Key-Value Pair
template <typename K, typename V>
class KVPair {
public:
    K key;
    V value;

    KVPair() {}
    KVPair(K key) {
        this->key = key;
    }
    KVPair(K key, V value) {
        this->key = key;
        this->value = value;
    } // const y & se usan juntos cuando se quiere recibir un objeto que no va a ser modificado dentro del método.
    void operator =(const KVPair& other) { // & envia la referencia para no tener que copiar el valor (usa valor original)
        this->key = other.key;
        this->value = other.value;
    }
    // -------- Operadores de Asignación ---------
    bool operator==(const KVPair& other) {
        return this->key == other.key;
    }
    bool operator!=(const KVPair& other) {
        return this->key != other.key;
    }
    bool operator<(const KVPair& other) {
        return this->key < other.key;
    }
    bool operator<=(const KVPair& other) {
        return this->key <= other.key;
    }
    bool operator>(const KVPair& other) {
        return this->key > other.key;
    }
    bool operator>=(const KVPair& other) {
        return this->key >= other.key;
    }
};

// Esta función "solitaria" sirve para sobrescribir el funcionamiento
// del operador << con el KVPair.
// Aparentemente no se puede sobrescribir desde dentro de la clase
// y hay que hacerlo en una función aparte.
template<typename K, typename V>
ostream& operator<<(ostream& os, const KVPair<K, V>& p) {
    os << p.key << ", " << p.value;
    return os;
}

#endif // KVPAIR_H
