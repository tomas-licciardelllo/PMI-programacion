#include <stdio.h>
#include <time.h>
#include "lista.h"




void calcular_totales(Pedido *a, Combos todos[])
{
    int cuantos_de_cada;
    int i;
    float total_de_los_combos=0, descuentos=0;
    for(i=0; i<10; i++)
    {
         total_de_los_combos=total_de_los_combos+((*a).arreglo_para_combos[i]*get_precio(todos[i]));
         if(get_descuento(todos[i])==1)
         {
             descuentos=descuentos+(((get_precio(todos[i])*(*a).arreglo_para_combos[i])*15)/100);
         }
    }

    //solo se calcula el sub total

    (*a).sub_total=total_de_los_combos+descuentos;
    if((*a).donde_consume==2)
    {
        (*a).total=(*a).sub_total+500;
    }
    else
    {
        (*a).total=(*a).sub_total;
    }
}


void ingresar_pedido(lista_pedido a, Combos cms[])
{

    int i,forma_de_pago, num_de_combo, cantCombos,opcion_de_comer=0, opcion_cargar, opcion_descuento;
    Pedido aux;
    init(&aux);
    printf("Inserte el nombre del cliente.\n");
    getchar();
    gets(aux.nombre);
    id(&aux);
    printf("\n");
    printf("Codigo %s \n", get_id_pedido(aux));

    do{
            do{
                        //en esta parte se pregunta si va a seguir cargando
                        printf("Ingrese el combo que va ingresar.\n");
                        for(i=0; i<10; i++)
                        {
                            printf("%i_%s\n", get_id_combo(cms[i])+1, get_descipcion(cms[i]));
                        }

                        do{
                            scanf("%i", &num_de_combo);
                            if(num_de_combo>10 || num_de_combo<0)
                            {
                                printf("El numero ingresado no es valido, ingrese otro numero.\n");
                            }
                        }while(num_de_combo>10 || num_de_combo<0);
                        //control de los numeros ingresados por el usuraio
                        printf("Tiene descuento?\n");
                        printf("Ingrese 1: si tiene.\n");
                        printf("Ingrese 2: si no tiene\n");
                        do{
                            scanf("%d", &opcion_descuento);
                            if(opcion_descuento<0 || opcion_descuento>2)
                            {
                                printf("Ingrese un numero valido, por favor.\n");
                            }
                        }while(opcion_descuento<0 || opcion_descuento>2);
                        //control de los numeros ingresados por el usuario

                        set_descuento(&cms[num_de_combo-1],opcion_descuento);
                        printf("Ingrese la cantidad de combos.\n");

                        do{
                                scanf("%d", &cantCombos);
                                if(cantCombos<0)
                                {
                                    printf("La cantidad no puede ser negativa.\n");
                                }

                        }while(cantCombos<0);


                        if(get_stock(cms[num_de_combo-1])<cantCombos)
                        {
                            printf("No hay stock suficiente de ese tipo de combos.\n");
                            printf("Hay %i combos de ese tipo.\n", get_stock(cms[num_de_combo-1]));
                        }
            }while(get_stock(cms[num_de_combo-1])<cantCombos);
            set_stock(&cms[num_de_combo-1],get_stock(cms[num_de_combo-1])-cantCombos);
            //actualizacion  de la cantidad de combos disponibles

            combo(&aux, num_de_combo-1,cantCombos);
            //funcion que ingresa los combos en el arreglo de los combos del pedido
            printf("Quiere seguir cargando combos?\n");
            printf("Ingrese 1: si quiere seguir cargando.\n");
            printf("Ingrese 2: si no quiere seguir cargando.\n");

            do{
                scanf("%i", &opcion_cargar);
                if(opcion_cargar<=0 || opcion_cargar>2)
                {
                    printf("Ingrese una opcion valida.\n");
                }
            }while(opcion_cargar<=0 || opcion_cargar>2);
            //validacion de la opcion de carga

    }while(get_stock(cms[num_de_combo-1])!=0 && opcion_cargar==1);

    printf("Ingrese la forma de pago que va a utilizar.\n");
    printf("<1>Para efectivo.\n");
    printf("<2>Para debito.\n");
    printf("<3>Para QR\n");
    printf("<4>Para credito.\n");
    do{
        scanf("%i", &forma_de_pago);
        if(forma_de_pago>4 || forma_de_pago<1)
        {
            printf("El numero ingresado no es valido, ingrese un caracter valido por favor.\n");
        }
    }while(forma_de_pago>4 || forma_de_pago<1);

    pago(&aux, forma_de_pago);
    printf("Ingrese donde consume.\n");
    printf("1: En el establecimiento.\n");
    printf("2: Delivery.\n");
    do{
        scanf("%d", &opcion_de_comer);
        if(opcion_de_comer<1 || opcion_de_comer>2)
        {
            printf("Ingrese un numero valido por favor.\n");
        }

    }while(opcion_de_comer<1 || opcion_de_comer>2);

    set_lugar(&aux, opcion_de_comer);
    if(get_lugar(aux)==2)
    {
        printf("El costo del delivery es $500\n");

    }
    else
    {
        if(get_lugar(aux)==1)
        {
            printf("El costo del delivery es $0\n");
        }
    }

    calcular_totales(&aux,cms);

    printf("El subtotal es: $%0.2f \n", aux.sub_total);
    printf("El total es : $%0.2f \n", aux.total);
    InsertarEnLista(&a, aux);
}

/*int  Busca_pedido(lista_pedido lista){
char id_buscado[11];

    do{
        printf("Ingrese el id para verificar y buscar el pedido\n:");
        gets(id_buscado);

            if (id_buscado<11){
                printf("Porfavor ingrese un id valido para buscar el pedido.\n");
            }
    }
    while(strlen(id_buscado)<11);

ResetCursores(&lista);

    do{
        ForwardCursores(&lista);
    }
    while(strcmp(CopyLista(lista).id,id_buscado)!=0 || isOos(lista)==1);

    if(CopyLista(lista).id==id_buscado && isOos(lista)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}*/


void iniciar_combos(Combos opciones_combo[]){
    int i;
    FILE *all_combos;
    all_combos = fopen("menu.txt", "r");
    if (all_combos == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;}
    for (i = 0; i < 10; i++) {
        fscanf(all_combos, "%d", &opciones_combo[i].id_combo);
        fscanf(all_combos, "%*[\n]");
        fgets(opciones_combo[i].descripcion, sizeof(opciones_combo[i].descripcion), all_combos);
        opciones_combo[i].descripcion[strcspn(opciones_combo[i].descripcion, "\n")] = '\0';
        fscanf(all_combos, "%d", &opciones_combo[i].stock);
        fscanf(all_combos, "%f", &opciones_combo[i].precio);
        fscanf(all_combos, "%d", &opciones_combo[i].descuento);
        fscanf(all_combos, "%*[\n]");}

        fclose(all_combos);

}





int main()
{
    lista_pedido la_lista;
    Combos arreglo_combos[10];
    iniciar_combos(arreglo_combos);
    InicializarLista(&la_lista);
    int opcion;

    do{
    printf("------------------Menu---------------------------\n");
    printf("<1>Ingresar un pedido.\n");
    printf("<2>Buscar un pedido por el ID.\n");
    printf("<3>Mostrar los datos del pedido buscado por ID.\n");
    printf("<4>Mostrar los pedidos de un mes ordenados por fecha.\n");
    printf("<5>Mostrar los pedidos por nombre.\n");
    printf("<6>Mostrar los pedidos realizados por un vendedor, solo el idpedido y el total.\n");//es una recursiva muestra el idpedido total
    printf("<7>Contar los pedidos realizados por un vendedor.\n");
    printf("<8>Modificar el estado del pedido a entregado por idpedido.\n");
    printf("<9>Modificar la forma de pago de un pedido \n");
    printf("<10>Modificar nombre de un pedido segun su idpedido.\n");
    printf("<11>Eliminar un pedido por idpedido.\n");
    printf("<12>Almacenar los datos de los pedidos pagados de un tipo de forma de pago.\n");
    printf("<13>Historial de los pedidos.\n");
    printf("<14>Mostrar los pedidos no entregados\n");
    printf("<15>Modificar precio y stock del combo segun idcombo.\n");
    printf("<16>Mostrar todos los combos.\n");
    printf("<17>Mostrar precio y stock de un combo por idcombo.\n");
    printf("<18>Mostrar los combos sin stock.\n");
    printf("<19>Mostrar cual es el vendedor que realizo mas ventas en el mes.\n");
    printf("<20>Cambiar el vendedor,\n");
    scanf("%i", &opcion);
    switch(opcion)
    {
        case 1:
            ingresar_pedido(la_lista, arreglo_combos);
        break;

        case 2:
                //Busca_pedido();
        break;

    };
    }while(opcion<=20 && opcion>=1);
    return 0;
}
