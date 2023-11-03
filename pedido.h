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
    int cupon;
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
    (*a).cupon=0;
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

<<<<<<< HEAD
void set_nombre_pedido(Pedido *a, char n[])
=======

void set_nombre(Pedido *a, char n[])
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    strcpy((*a).nombre, n);
}


<<<<<<< HEAD
void set_vendedor(Pedido *a, int codigo)
{
    (*a).vendedor=codigo;
}

int get_vendedor(Pedido a)
{
    return a.vendedor;
}

char * get_nombre_pedido(Pedido a)
{
    char *p;
    p=(char *)malloc(strlen(a.nombre)+1);
    if(p==NULL)
        return ("1");
    else
    {
        strcpy(p,a.nombre);
        return p;
    }
}
=======
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
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
void set_descuento_pedido(Pedido *a, int opcion)
{
    (*a).cupon=opcion;
}
=======
<<<<<<< HEAD
=======
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d

int get_descuento_pedido(Pedido a)
{
    return a.cupon;
}

<<<<<<< HEAD
void set_arreglo_para_combo(Pedido *a, int cual, int cuantos)
=======
>>>>>>> e0bd152b62a6efef8e77b90bb085a2d3d0ec8505
void combo(Pedido *a, int cual, int cuantos)
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    (*a).arreglo_para_combos[cual]=cuantos;
}

<<<<<<< HEAD
void set_forma_de_pago (Pedido *a, int eleccion)
=======

void set_pago(Pedido *a, int eleccion)
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    (*a).forma_pago=eleccion;
}

<<<<<<< HEAD
int get_forma_de_pago (Pedido a)
=======

void subtotal(Pedido *a, float descuento)
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    return a.forma_pago;

<<<<<<< HEAD
}
int get_arreglo_para_combos(Pedido a, int pocision)
{
    return a.arreglo_para_combos[pocision];
}
void set_total (Pedido *a)
=======

void total (Pedido *a)
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    if((*a).donde_consume==0)
    {
        (*a).total=(*a).sub_total;
    }
    else
    {
        (*a).total=(*a).sub_total+500;
    }
}

<<<<<<< HEAD
float get_total(Pedido a)
{
    return a.total;
}

void set_subtotal(Pedido *a, Combos cbs[])
{
    int i;
    float semi_sub_total=0;
    for(i=0; i<10; i++)
    {
        semi_sub_total=semi_sub_total+get_arreglo_para_combos(*a,i)*get_precio(cbs[i]);
        if(get_descuento_pedido(&a)==1 && get_descuento(cbs[i])==1)
        {
            semi_sub_total=semi_sub_total-(semi_sub_total*15)/100;
        }

    }
    (*a).sub_total=semi_sub_total;
}

float get_subtotal(Pedido a)
{
    return a.sub_total;
}



void set_donde_consume (Pedido *a, int opcion)
=======
<<<<<<< HEAD

void lugar (Pedido *a, int opcion)
=======
void set_lugar (Pedido *a, int opcion)
>>>>>>> e0bd152b62a6efef8e77b90bb085a2d3d0ec8505
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    (*a).donde_consume=opcion;
}

<<<<<<< HEAD
int get_donde_consume(Pedido a)
=======
<<<<<<< HEAD
=======
int get_lugar (Pedido a)
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{
    return a.donde_consume;
}
>>>>>>> e0bd152b62a6efef8e77b90bb085a2d3d0ec8505

void set_fecha_del_pedido(Pedido *a)
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
<<<<<<< HEAD
void set_entregado(Pedido *a, int info)
=======


void condicion (Pedido *a, int info)
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
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
int get_entregado(Pedido a)
{
    return a.entregado;
}

fecha get_fecha(Pedido a)
{
    return a.fecha_pedido;
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
