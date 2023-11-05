#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "pedido.h"

typedef struct{

    Pedido vipd;
    struct Nodo *punterosiguiente;

}Nodo;


typedef struct{

    Nodo *acceso;
    Nodo *cursor;
    Nodo *aux;

}lista_pedido;

void InicializarLista(lista_pedido *lista){

    lista->acceso=NULL;
    lista->cursor=NULL;
    lista->aux=NULL;

}

void InsertarEnLista(lista_pedido *lista, Pedido p){

    Nodo *nuevoNodo;
    nuevoNodo=(Nodo*)malloc(sizeof(Nodo)); // hecho el control de asignacion de memoria
    if(nuevoNodo==NULL){
        printf("Error al asignar memoria al nuevoNodo");
        exit(1);
    }else{
        if(lista->cursor==lista->acceso){

            lista->acceso=nuevoNodo;
            nuevoNodo->punterosiguiente=lista->cursor; // cursor apunta a null, que es a lo que apuntará el puntero del nuevo nodo
            lista->cursor=lista->acceso;
            lista->aux=lista->acceso;
        }
        else{  // este caso ya hay un nodo en la lista y queremos insertar uno nuevo
                (lista->aux)->punterosiguiente=nuevoNodo;
                nuevoNodo->punterosiguiente=lista->cursor;
                (lista->cursor)=nuevoNodo;
        }
        (lista->cursor)->vipd=p; //inservo el vehiculo en la vipd del nuevo nodo
    }

}


void SupressLista(lista_pedido *lista){

    if(lista->cursor == lista->acceso){

        lista->acceso=(lista->cursor)->punterosiguiente;
        free((void *)lista->cursor);//LIBERO MEMORIA DEL NODO QUE QUIERO BORRAR //seria necesario
        lista->cursor=lista->acceso;
        lista->aux=lista->acceso;
     }
     else{//caso lista->cursor!= lista->acceso

        (lista->aux)->punterosiguiente=(lista->cursor)->punterosiguiente;
        free((void *)lista->cursor);//LIBERO MEMORIA DEL NODO QUE QUIERO BORRAR
        lista->cursor=(lista->aux)->punterosiguiente;

     }



}

Pedido CopyLista(lista_pedido lista){

    return (lista.cursor)->vipd; //CONSULTAR PORQUE NO SE PUEDE USAR (lista.cursor).vipd;

}

int isEmpty(lista_pedido lista){

    if(lista.acceso==NULL)

        return 1;

    else
        return 0;

}

int isFull(void){

    Nodo *NuevoNodo;
    NuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    if(NuevoNodo==NULL)
        return 1;//si no hay mas memoria para crear nodos, retornar.
    else
        return 0;//si hay memoria para crear nodos, retornar 0.
    free(NuevoNodo);//libero la memoria usada para testear si hay memoria.

}

void ForwardCursores(lista_pedido *lista){

    lista->aux=lista->cursor;
    lista->cursor=(lista->cursor)->punterosiguiente;//entra al nodo siguiente y apunta al puntero que tiene ese nodo
    //le digo al cursor de la lista que apunte al cursor que apunta al puntero siguiente

}

void ResetCursores(lista_pedido *lista){

    lista->cursor=lista->acceso;
    lista->aux=lista->acceso;
    //les ordeno que vuelvan al inicio de la lista, que es el acceso de la lista
}

int isOos(lista_pedido lista){

    if(lista.cursor==NULL)

    {
        return 1; //si cursor apunta fuera de la lista, es porque se salió de estructura(lista)
    }
    else
    {
        return 0;//si apunta a algun nodo o acceso, entonces no está fuera de estructura(lista)
    }
}

#endif // LISTA_H_INCLUDED
