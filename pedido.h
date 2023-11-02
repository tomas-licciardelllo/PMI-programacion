#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED
#define VENDEDOR 8423864623
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TDA_Combo.h"

typedef struct
{
    int dia;
    int mes;
    int ano;
}fecha;

typedef struct
{
    char nombre[31];
    char id[11];
    //int cuantos_combos;
    //varianle de arriba no posee utilidad teniendo el arreglo
    int forma_pago;
    float sub_total;
    int donde_consume;
    float total;
    fecha fecha_pedido;
    int entregado;
    int vendedor;
    int arreglo_para_combos[10];
}Pedido;


void init(Pedido *a)
{
    int i;
    (*a).forma_pago=0;
    (*a).sub_total=0;
    (*a).donde_consume=0;
    (*a).total=0;
    (*a).entregado=0;
    (*a).vendedor=VENDEDOR;
    //(*a).cuantos_combos=0;
    strcpy((*a).nombre, "-");
    strcpy((*a).id, "-");
    for(i=0; i<10; i++)
    {
        (*a).arreglo_para_combos[i]=0;
    }
}


// Función para generar un carácter aleatorio en minúsculas
char generarCaracterAleatorio() {
    return 'a' + (rand() % 26);
}


// Función para generar un dígito aleatorio
char generarDigitoAleatorio() {
    return '0' + (rand() % 10);
}


void set_nombre(Pedido *a, char n[])
{
    strcpy((*a).nombre, n);
}


void id(Pedido *a)
{
    int i;
    // Inicializar la semilla del generador de números aleatorios
    srand(time(NULL));

    char cadena[12]; // Un arreglo de caracteres para almacenar la cadena

    // Generar el primer número aleatorio y colocarlo al principio
    cadena[0] = generarDigitoAleatorio();

    // Generar las 8 letras aleatorias
    for (i = 1; i <= 8; i++) {
        cadena[i] = generarCaracterAleatorio();
    }

    // Generar el segundo número aleatorio y colocarlo al final
    cadena[9] = generarDigitoAleatorio();

    // Agregar el carácter nulo al final de la cadena para formar una cadena de caracteres válida
    cadena[10] = '\0';

    // Imprimir la cadena generada
    //printf("Cadena: %s\n", cadena);

    strcpy((*a).id, cadena);
}


<<<<<<< HEAD
=======


>>>>>>> e0bd152b62a6efef8e77b90bb085a2d3d0ec8505
void combo(Pedido *a, int cual, int cuantos)
{
    (*a).arreglo_para_combos[cual]=cuantos;
}


void set_pago(Pedido *a, int eleccion)
{
    (*a).forma_pago=eleccion;
}


void subtotal(Pedido *a, float descuento)
{
    int i;
    Combos uno;
    for(i=0; i<10; i++)
    {
        if((*a).arreglo_para_combos[i]!=0)
        {
          (*a).sub_total=(*a).arreglo_para_combos[i]*get_precio(uno);//aca va la funcion que muestra el precio del combo que sale del TDA COMBO;
        }
    }
    (*a).sub_total=(*a).sub_total-descuento;
}


void total (Pedido *a)
{
    if((*a).donde_consume==0)
    {
        (*a).total=(*a).sub_total;
    }
    else
    {
        (*a).sub_total=(*a).sub_total+500;
    }
}

<<<<<<< HEAD

void lugar (Pedido *a, int opcion)
=======
void set_lugar (Pedido *a, int opcion)
>>>>>>> e0bd152b62a6efef8e77b90bb085a2d3d0ec8505
{
    (*a).donde_consume=opcion;
}

<<<<<<< HEAD
=======
int get_lugar (Pedido a)
{
    return a.donde_consume;
}
>>>>>>> e0bd152b62a6efef8e77b90bb085a2d3d0ec8505

void fecha_del_pedido(Pedido *a)
{

    time_t tiempoActual;
    struct tm *infoTiempo;

    // Obtiene el tiempo actual
    time(&tiempoActual);
    infoTiempo = localtime(&tiempoActual);

    // Carga la fecha en la estructura Fecha
    (*a).fecha_pedido.dia = infoTiempo->tm_mday;
    (*a).fecha_pedido.mes = infoTiempo->tm_mon + 1;  // Sumar 1 porque tm_mon es 0-based
    (*a).fecha_pedido.ano = infoTiempo->tm_year + 1900;  // Sumar 1900 porque tm_year es el número de años desde 1900
}


void condicion (Pedido *a, int info)
{
    if(info=0)
    {
        (*a).entregado=0;
    }
    else
    {
        (*a).entregado=1;
    }
}

char * get_id_pedido (Pedido a)
{
    char *p;
    p=(char *)malloc(strlen(a.id)+1);
    if(p==NULL)
        return ("1");
    else
    {
        strcpy(p,a.id);
        return p;
    }
}


#endif // PEDIDO_H_INCLUDED
