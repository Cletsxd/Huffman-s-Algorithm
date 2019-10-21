#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/* ARITMÉTICA DE APUNTADORES
- Para "reservar" memoria de forma dinámica se utliza el '*', por ejemplo: int *p, lo que nos quiere decir
    que se almacenarán 4 bytes de memoria (por el tamaño del dato int) en algún lugar de la RAM.
- Si el tipo de dato es compuesto y a la vez es apuntador, ejemplo: Nodo *p, los datos se "recorren" de esta forma:
    p -> dato1 = 'c';
    p -> dato2 = 3;
    NÓTESE la "flechita".
- Los arreglos, ejemplo: int array_ints[30], se ven como un apuntador. Cuando se almacena espacio para un arreglo o vector
    simplemente se "toma" la dirección de memoria de la primera casilla de ese vector. De esta forma, los vectores se pueden
    mandar a una función: void print_vect_chars(int *array_ints, int tam){...} y recorrer: array_ints[i], array_ints[cualquier_valor].
*/

// Tipo de dato struct: es un tipo de dato compuesto.
// Dist: nos va a servir para almacenar la frecuencia de cada caracter.
struct Dist{
    char c;
    int d;
};

/* Tipo de dato class: es un tipo de dato compuesto y funcional.
- Dentro de este tipo de dato se pueden ocupar los métodos de acceso como: public, private o protected
    cada uno con funciones en específico.
- Nodo: es un nodo de una cola. Contiene dos datos: dato1 (caracter), dato2 (frecuencia del dato1).
  además, tiene un "apuntador" al siguiente nodo.
*/
class Nodo{
    public:
        char dato1;
        int dato2;
        Nodo *sig;
};

/* Cola: una lista con función de cola. FIFO (First In, First Out).
- Contiene dos características: un nodo inicial (ini) y un nodo final (fin).
- Tiene 6 funcionalidades...
*/
class Cola{
    public:
        Nodo *ini;
        Nodo *fin;
        Cola(); // Constructor de una cola.
        ~Cola(); // Destructor de una cola.
        int estaVacia(); // Si la cola está vacía manda 1, si no, manda 0.
        void mete(char c, int x); // Mete datos a la cola (c: caracter, x: frecuencia del caracter).
        void saca(); // Saca datos de la cola y los elimina.
        char datoFte(); // Regresa el dato inicial (ini).
};

Cola::~Cola(){
    Nodo *p = ini;
    
    while(p != NULL){
        ini = p->sig;
        delete p;
        p = ini;
    }
}

Cola::Cola(){
    ini = NULL;
    fin = NULL;
}

int Cola::estaVacia(){
    if (ini == NULL && fin == NULL){
        return 1;
    }else{
        return 0;
    }
}

void Cola::mete(char c, int x){
    Nodo *p;
    p = new Nodo();
    p->dato1 = c;
    p->dato2 = x;
    p->sig = NULL;

    if(fin != NULL){
        fin->sig = p;
    }

    fin = p;

    if(ini == NULL){
        ini = p;
    }
}

void Cola::saca(){
    if(ini==NULL && fin == NULL){
       cout<<"Error Cola vacia";
       exit(1);
    }

    Nodo *p = ini;
    ini = ini->sig;

    if(ini == NULL){
        fin = NULL;
    }

    delete p;
}

char Cola::datoFte(){
    Nodo *p = ini;
    if(p == NULL){
        cout<<"Error: Apuntador nulo";
        exit(1);
    }
    return p->dato1;
}

bool is_in_vector(char *cont_diff, char c, int tam){
    for(int i = 0; i < tam; i++){
        if(c == cont_diff[i]){
            return true;
        }
    }

    return false;
}

int check_tam_dist(char *vect, int tam_vec, char *cont_diff){
    int cont = 0;

    cont_diff[cont] = vect[0];
    cont ++;

    for(int i = 1; i < tam_vec; i++){
        if(!is_in_vector(cont_diff, vect[i], tam_vec)){
            cont_diff[cont] = vect[i];
            cont ++;
        }
    }

    return cont;
}

void dist(char *chars, char *c_diff, Dist *dist, int tam_chars, int tam_dist){
    for(int i = 0; i < tam_dist; i++){
        dist[i].c = c_diff[i];
        int value_for_char = 0;

        for(int j = 0; j < tam_chars; j++){
            if(c_diff[i] == chars[j]){
                value_for_char ++;
            }
        }

        dist[i].d = value_for_char;
    }
}

void print_vect_chars(char *v, int t){
    for(int i = 0; i < t; i++){
        printf("%c, ", v[i]);
    }
}

void print_dist(Dist *dist, int t){
    for(int i = 0; i < t; i++){
        printf("%c: %i\n", dist[i].c, dist[i].d);
    }
}

void stick(Dist *v, Dist *list1, Dist *list2, Dist *listx, int len1, int len2, int lenx, int len){
    int i = 0, j = 0, k = 0;

    if(list1){
        while(i < len1){
            v[i].d = list1[i].d;
            v[i].c = list1[i].c;
            i ++;
        }
    }

    if(listx){
        while(k < lenx){
            v[i].d = listx[k].d;
            v[i].c = listx[k].c;
            i ++;
            k ++;
        }
    }

    if(list2){
        while(j < len2){
            v[i].d = list2[j].d;
            v[i].c = list2[j].c;
            i ++;
            j ++;
        }
    }
}

int uniform_distribution(int rangeLow, int rangeHigh) {
    double myRand = rand()/(1.0 + RAND_MAX); 
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}

void quick_sort3(Dist *v, int len){
    if(len < 2){
        return;
    }

    int x = v[uniform_distribution(0, len - 1)].d;
    int cont_comp = 0;

    Dist *list1 = (Dist*) malloc(len * sizeof(Dist));
    Dist *list2 = (Dist*) malloc(len * sizeof(Dist));
    Dist *listx = (Dist*) malloc(len * sizeof(Dist));
    int cont1 = 0, cont2 = 0, contx = 0;

    for(int i = 0; i < len; i++){
        if(v[i].d < x){
            list1[cont1].d = v[i].d;
            list1[cont1].c = v[i].c;
            cont1 ++;
        }else if(v[i].d == x){
            listx[contx].d = v[i].d;
            listx[contx].c = v[i].c;
            contx ++;
        }else{
            list2[cont2].d = v[i].d;
            list2[cont2].c = v[i].c;
            cont2 ++;
        }
    }

    quick_sort3(list1, cont1);
    quick_sort3(list2, cont2);

    // pegar listas en v
    stick(v, list1, list2, listx, cont1, cont2, contx, len);
}

int main(){
    // Llenar el vector de caracteres
    char vect_chars[20] = {'a', 'i', 'j', 's', 'd', 'a', 'k', 's', 'u', 'h', 'a', 'i', 's', 'd', 'a', 's', 'd', 'a', 'b', 's'};

    // Contar Frecuencias
    char *cont_diff = (char*) malloc(20 * sizeof(char));
    int tam_dist = check_tam_dist(vect_chars, 20, cont_diff);
    printf("Tam dist: %i\n", tam_dist);
    print_vect_chars(cont_diff, tam_dist);

    // Ordenar por frecuencias, meter de menor a mayor a la cola
    Dist *vect_dist = (Dist*) malloc(tam_dist * sizeof(Dist));
    dist(vect_chars, cont_diff, vect_dist, 20, tam_dist);

    printf("\n");
    print_dist(vect_dist, tam_dist);

    quick_sort3(vect_dist, tam_dist);

    printf("\n\n");
    print_dist(vect_dist, tam_dist);
}