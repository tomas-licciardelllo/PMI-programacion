#ifndef TDA_COMBO_H_INCLUDED
#define TDA_COMBO_H_INCLUDED
#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct{
    int id_combo;
    char descripcion[100];
    int stock; //usuario//
    float precio; //usuario/
    int descuento;
}Combos;

//Inicializacion
 void inic_combo(Combos *a){
    (*a).id_combo=0;
    strcpy((*a).descripcion,"-");
    (*a).stock=0;
    (*a).precio=0;
    (*a).descuento=0;
}

//Set
void set_id_combo(Combos *a, int cmb){
    (*a).id_combo=cmb;
}

void set_descripcion(Combos *a, char *desc){
    strcpy((*a).descripcion,desc);
}

void set_stock(Combos *a, int st){
    (*a).stock=st;
}

void set_precio(Combos *a, float pr){
    (*a).precio=pr;
}

void set_descuento(Combos *a, int desc){
    (*a).descuento=desc;
}

//Get
int get_id_combo(Combos a){
    return a.id_combo;
}

char* get_descipcion(Combos a){
    char *p;
    p=(char *)malloc(strlen(a.descripcion)+1);
    if (p==NULL){
         return ("1");
    }else{
        strcpy(p,a.descripcion);
        return p;
    }
}

int get_stock(Combos a){
    return a.stock;
}

float get_precio(Combos a){
    return a.precio;
}

int get_descuento(Combos a){
    return a.descuento;
}


#endif // TDA_COMBO_H_INCLUDED
