#include <fstream>

const int MAX_ITEMS = 5;

enum RelationType {LESS, GREATER, EQUAL};

class ItemType {
    public:
        ItemType();
        RelationType ComparedTo(ItemType) const;
        void Print(std::ofstream&) const;
        void Initialize(int number);

//
// Ejercicio 3: Implementar la sobrecarga de operadores relacionales para sustituir al método ComparedTo
//
// con estas sobrecargas redefinimos los operadores " ==, !=, <, >, <=, >= "
// para que funcionen con objetos de clases hechos por mí. En resumen, permite usar 
// expresiones simples como "if (bola1 <= bola2)"
// 
        bool operator==(const ItemType& otro) const;
        bool operator!=(const ItemType& otro) const;
        bool operator<(const ItemType& otro) const;
        bool operator>(const ItemType& otro) const;
        bool operator<=(const ItemType& otro) const;
        bool operator>=(const ItemType& otro) const;

    private:
        int value;
};