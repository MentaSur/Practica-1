#include <fstream>
#include "ItemType.h"

ItemType::ItemType() {
    value = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const {
    if (value < otherItem.value)
        return LESS;
    else if (value > otherItem.value)
        return GREATER;
    else 
        return EQUAL;
}

void ItemType::Initialize(int number) {
    value = number;
}

void ItemType::Print(std::ofstream& out) const {
    // Pre: out has been opened.
    // Post: value has been sent to the stream out.
    out << value << " ";
}

// Aquí continúa el Ejercicio 3:
//
// una vez definidas las sobrecargas, debemos hacer que cada operador
// compare el atributo privado "value" del objeto actual con el que recibe por parámetro "otro.value"
//

// tal es igual a tal
bool ItemType::operator==(const ItemType& otro) const {
    return value == otro.value;
}

// tal NO es igual a tal
bool ItemType::operator!=(const ItemType& otro) const {
    return value != otro.value;
}

// menor que tal
bool ItemType::operator<(const ItemType& otro) const {
    return value < otro.value;
}

// mayor que tal
bool ItemType::operator>(const ItemType& otro) const {
    return value > otro.value;
}

// menor o igual que tal
bool ItemType::operator<=(const ItemType& otro) const {
    return value <= otro.value;
}

// mayor o igual que tal
bool ItemType::operator>=(const ItemType& otro) const {
    return value >= otro.value;
}