#include "ItemType.h"
// File ItemType.h must be provided by the user of this class.
// ItemType.h must contain the following definitions:
// MAX_ITEMS:       the maximum number of items on the list
// ItemType:        the definition of the objects on the list
// RelationType:    {LESS, GREATER, EQUAL}
// Member function ComparedTo(ItemType item), which returns
//      LESS, if self "comes before" item
//      GREATER, if self "comes after" item
//      EQUAL, if self and item are the same


class SortedType {
    public:
        SortedType();
        bool IsFull() const;
        int LengthIs() const;
        void RetrieveItem(ItemType& item, bool& found);
        void InsertItem(ItemType item);
        void DeleteItem(ItemType item);
        void ResetList();
        void GetNextItem(ItemType& item);
    private:
        int length;
        ItemType info[MAX_ITEMS];
        int currentPos;
};


SortedType::SortedType(){
    length = 0;
}


bool SortedType::IsFull() const {
    return (length == MAX_ITEMS);
}

int SortedType::LengthIs() const {
    return length;
}

void SortedType::RetrieveItem(ItemType& item, bool& found) {
    // Pre: Key member(s) of item is initialized.
    // Post: If found, item's key matches an element's key in the
    //       list and a copy of that element has been stored in item;
    //       otherwise, item is unchanged.
    int midPoint;
    int first = 0;
    int last = length - 1;

    bool moreToSearch = first <= last;
    found = false;

    while (moreToSearch && !found) {

        midPoint = (first + last) / 2;
        
        switch (item.ComparedTo(info[midPoint])) {
            case LESS:
                last = midPoint - 1;
                moreToSearch = first <= last;
                break;
            case GREATER:
                first = midPoint + 1;
                moreToSearch = first <= last;
                break;
            case EQUAL:
                found = true;
                item = info[midPoint];
                break;
        }
    }
}

void SortedType::InsertItem(ItemType item) {
    // Post: item is in the list.
    bool moreToSearch;
    int location = 0;

    moreToSearch = (location < length);

    while (moreToSearch) {
        switch (item.ComparedTo(info[location])) {
            case LESS:
                moreToSearch = false;
                break;
            case GREATER:
                location++;
                moreToSearch = (location < length);
                break;
        }
    }

    for (int index = length; index > location; index--)
        info[index] = info[index - 1];

    info[location] = item;
    length++;
}

void SortedType::DeleteItem(ItemType item) {
    // Pre:  item's key has been initialized.
    //       An element in the list has a key that matches item's.
    // Post: No element in the list has a key that matches item's.
    int location = 0;

    while (item.ComparedTo(info[location]) != EQUAL)
        location++;

    for (int index = location+1; index < length; index++)
        info[index-1] = info[index];

    length--;
}

void SortedType::ResetList() {
    // Post: currentPos has been initialized.
    currentPos = -1;
}

void SortedType::GetNextItem(ItemType& item) {
    // Pre:  No transformer has been executed since last call
    // Post: item is current item.
    //       Current position has been updated.
    currentPos++;
    item = info[currentPos];
}

// Ejercicio 5: función que funsiona 2 listas ordenadas por ComparedTo en una única lista ordenada

void MergeLists(SortedType list1, SortedType list2, SortedType& result){
    ItemType item1, item2; //declaramos los items donde se guardarán las claves que estemos usando en un momento

    int longitud_lista1 = list1.LengthIs(); //guardamos la longitud de ambas listas
    int longitud_lista2 = list2.LengthIs();
    int clave_procesada1 = 0, clave_procesada2 = 0; // estos iteradores son para saber cuántas claves habrán extraídas de cada lista
    list1.ResetList(), list2.ResetList(); //ponemos ambas lista en currentPos = -1

    if (clave_procesada1 < longitud_lista1) { // miramos las primeras claves de cada lista, paa tener al menos un valor ya listo para procesar
        list1.GetNextItem(item1); // guarda una clave en "item1" y pasa a la siguiente
        clave_procesada1++; //el contador de claves extraídas aumenta
    }              
    if (clave_procesada2 < longitud_lista2) { //lo mismo, pero con la segunda lista
        list2.GetNextItem(item2);
        clave_procesada2++;
    }

    // se supone que no tienen claves en común, por tanto no hace falta comprobar

    // Ahora, debemos comparar de ambas listas, las claves aún no procesadas hasta igualar los contadores con al menos 1 de las 2 listas
    while (clave_procesada1 <= longitud_lista1 && clave_procesada2 <= longitud_lista2) {
        if (item1.ComparedTo(item2) == LESS) { //ahora, comparamos los items de la lista 1 con los de la lista 2 ("item1 de la posición 2" es MENOR que "item2 de la posición 2"?)
            result.InsertItem(item1); // si el de la lista 1 es menor, se mete a la lista final

            if (clave_procesada1 < longitud_lista1) { // y avanzamos en la lista 1 para pillar el siguiente item, como hicimos antes
                list1.GetNextItem(item1);
                clave_procesada1++;
            } else {  //si las claves procesadas es = a la longitud de la lista, añadimos 1 valor más para que se rompa el bucle while
                clave_procesada1++;
            }
        } else { // como no hay claves iguales, si item1 no es menor, entonces item2 será el menor
            result.InsertItem(item2); //metemos el item 2 de la lista 2 en la lista final

            if (clave_procesada2 < longitud_lista2) { //y avanzamos en la lista 2 como antes
                list2.GetNextItem(item2);
                clave_procesada2++;
            } else {  //si las claves procesadas es = a la longitud de la lista, añadimos 1 valor más para que se rompa el bucle while
                clave_procesada2++;
            }
        }
    }

    // Como el bucle se abrá roto sólo porque 1 de las 2 listas se acabó, rellenaremos la lista final con lo que falte de la lista no acabada
    while (clave_procesada1 <= longitud_lista1) { // en caso de que la lista 1 no esté acabada
        result.InsertItem(item1);

        if (clave_procesada1 < longitud_lista1) { // se comprueba si se procesaron todos ya o no
            list1.GetNextItem(item1); // si no, pasamos al siguiente item a introducir
        }
        clave_procesada1++;
    }

    while (clave_procesada2 <= longitud_lista2) { // en caso de que la lista 2 no esté acabada
        result.InsertItem(item2);
        
        if (clave_procesada2 < longitud_lista2) {// se comprueba si se procesaron todos ya o no
            list2.GetNextItem(item2); // si no, pasamos al siguiente item a introducir
        }
        clave_procesada2++;
    }
}
