#include "ItemType.h" 

    // se incluye el ItemType.h, el cual contiene estas definiciones:

    // MAX_ITEMS:       the maximum number of items on the list
    // ItemType:        the definition of the objects on the list
    // RelationType:    {LESS, GREATER, EQUAL}
    // Member function ComparedTo(ItemType item), which returns
    //      LESS, if self "comes before" item
    //      GREATER, if self "comes after" item
    //      EQUAL, if self and item are the same

class UnsortedType {
    public:
        UnsortedType();
        bool IsFull() const;
        int LengthIs() const;
        void RetrieveItem(ItemType& item, bool& found);
        void InsertItem(ItemType item);
        void DeleteItem(ItemType item);
        void ResetList();
        void GetNextItem(ItemType& item);

        bool IsThere(ItemType& item) const; // Declaramos el método dentro de la clase en el bloque public: (para que no modifique nada, le ponemos que sea una const.) 
                                            // que reciba una variable de tipo ItemType (el elemento a comprobar) y devuelva un valor True si el elemento está en la lista y False si no lo está

    private:
        int length; // Como el método IsThere pertenece a la clase UnsortedType, no necesita funciones aux. que le dén permiso a acceder a los atributos private de la clase
        ItemType info[MAX_ITEMS];
        int currentPos;
};

UnsortedType::UnsortedType(){
    length = 0;
}

bool UnsortedType::IsFull() const {
    return (length == MAX_ITEMS);
}

int UnsortedType::LengthIs() const {
    return length;
}
/* Ejercicio 4: Sustituir los ComparedTo con las Sobrecargas del ejercicio 3:

Así es el viejo RetrieveItem:

void UnsortedType::RetrieveItem(ItemType& item, bool& found) {
    // Pre: Key member(s) of item is initialized.
    // Post: If found, item's key matches an element's key in the
    //       list and a copy of that element has been stored in item;
    //       otherwise, item is unchanged.
    bool moreToSearch;
    int location = 0;
    found = false;

    moreToSearch = (location < length);
    
    while (moreToSearch && !found) {
        switch (item.ComparedTo(info[location])) {
            case LESS:
            case GREATER:
                location++;
                moreToSearch = (location < length);
                break;
            case EQUAL:
                found = true;
                item = info[location];
                break;
        }
    }
}
*/

// Y así es el nuevo:
void UnsortedType::RetrieveItem(ItemType& item, bool& found) {
    int location = 0;
    found = false;

    while (location < length && !found) { // al ser una lista desordenada, quitamos el switch y usamos un simple if-else
        if (item == info[location]) {
            found = true;
            item = info[location];
        } else {
            location++;
        }
    }
}


void UnsortedType::InsertItem(ItemType item) { // Sabemos que el array info guarda consecutivamente los elementos
    // Post: item is in the list.              // porque según el código de InsertItem, el nuevo dato se mete en la primera casilla disponble,
    info[length] = item;                       // siendo esta la de la posición lenght, de forma que nunca deja huecos vaciós de por medio.
    length++;                        // Además, seguramente la lista esté desordenada ya que no hace comprobaciones con los datos ya metidos cuando entra uno nuevo,
}                                    // y abajo, en DeleteItem, cuando se borra un elemento, los datos restantes no se mueven de lugar, dejando un hueco vacío

/* Así es el viejo DeletemItem

void UnsortedType::DeleteItem(ItemType item) {
    // Pre:  item's key has been initialized.
    //       An element in the list has a key that matches item's.
    // Post: No element in the list has a key that matches item's.
    int location = 0;
    while (item.ComparedTo(info[location]) != EQUAL)
        location++;

    info[location] = info[length - 1];
    length--;
}
*/

// Y ssí es el nuevo:
void UnsortedType::DeleteItem(ItemType item) {
    int location = 0;
    while (item != info[location] ) // Se compsra directamente usando !=
        location++;

    info[location] = info[length - 1];
    length--;

void UnsortedType::ResetList() {
    // Post: currentPos has been initialized.
    currentPos = -1;
}

void UnsortedType::GetNextItem(ItemType& item) {
    // Pre:  No transformer has been executed since last call
    // Post: item is current item.
    //       Current position has been updated.
    currentPos++;
    item = info[currentPos];
}
//
// Ejercicio 1: Extender la Clase UnsortedType creando un IsThere y buscar si hay o no, un elemento ItemType con la misma clave en la lista ya.
//
void UnsortedType::IsThere(ItemType& item) {  // Aquí se determinará si ya existe o no, un elemento con la misma clave en la lista
    bool encontrado = false; // este booleano indicará si al final hubo uno con la misma clave o no
    int location = 0; // el int se usará para moverse por el array info

    while (location < lenght && encontrado == false) { // usamos un bucle donde mientras que la posición actual sea menor al tamaño del array, Y aún no se haya encontrado algo...
        if (item.ComparedTo(info[location]) == EQUAL) { //usamos el ComparedTo para comparar cada elemento item con la posicion del array, hasta encontrar alguno que tenga la misma clave, si es que hay
            encontrado = true; // si se encuentra algo, cambiamos el booleano a True, para salir del bucle
            // break;   no sé si es necesario, por eso lo dejo como comentario
        } else { // si no se encuentra nada, avanzamos en el array
            location++
        }
    }
    return encontrado;  // indicamos que sí se encontro una clave igual
}

//
// Ejercicio 2: Lo mismo que el 1, pero hecho una función externa, fuera de la clase UnsortedType
//
// Al ser externa, no podemos acceder ahora a los atributos privados. Si no que
// ahora debemos usar los públicos como (LenghtIs, ResetList, GetNextItem)
//
bool IsThere(UnsortedType lista, ItemType& item){ // Creamos un iterador "lista" que nos ayude a acceder a los métodos públicos de la clase UnsortedType
    int tamaño = lista.LenghtIs(); //pilla el valor del lenght del array
    ItemType item_actual; //indica el item actual que se comprobará
    bool encontrado = false; //se encontró parecido o no
    int position = 0; //auxiliar para el bucle

    lista.ResetList(); // para devolver la posición del array al inicio, es decir, currentPos = -1 (en caso de estar en otra posicion)

    while(position < tamaño && encontrado == false){ //usamos el bucle while igual que antes
        lista.GetNextItem(item_actual); // cuando se entre al bucle ó se repita, se cambia el item actual al que le sigue en el array.

        if (item.ComparedTo(item_actual) == EQUAL) { //usamos el ComparedTo para comparar uno a uno cada elemento item que nos dé el GetNextItem, hasta encontrar alguno que tenga la misma clave, si es que hay
            encontrado = true;
            // break;    igual, dudo si se pone o no

        } else{
            position++; // si no hay, pasamos a la siguiente posicion (que quede claro, este solo indica posicion para el bucle while. El que cambia de posicion real es el GetNextItem)
        }
    }
    return encontrado; // indicamos que sí se encontro una clave igual
}

// Lo bueno del primero, es que tenemos acceso directo a los métodos privados,
// ya que en el segundo debemos hacer accesos indirectos usando los metodos publicos, haciendo que el numero de operaciones sea mayor.

// respecto a la eficiencia es más de lo mismo, la primera al ser directa es más eficiente que la segunda al requerir menos llamadas
// para obtener los datos necesarios de los metodos privados

// Así sería el nuevo IsThere del ejercicio 1, sin sobrecargas:

/*
void UnsortedType::IsThere(ItemType& item) {
    bool encontrado = false;
    int location = 0;

    while (location < lenght && encontrado == false) {
        if (item == info[location]) {
            encontrado = true;
            // break;   no sé si es necesario, por eso lo dejo como comentario
        } else {
            location++
        }
    }
    return encontrado;
}
// En el ejercicio 2, sería el mismo cambio que aquí
*/
