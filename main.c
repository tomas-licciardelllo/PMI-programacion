#include <stdio.h>
#include <time.h>
#include "lista.h"


<<<<<<< HEAD

void ingresar_pedido(lista_pedido *a, Combos cms[])
=======
void modifica_pago(lista_pedido *a, int modif){ /** j) Modificar la forma de pago de un pedido según su idpedido */
    Pedido aux;
    ResetCursores(a);
    while(!isOos(a)){
        aux=CopyLista(a);
        if(strcmp(get_id_pedido(aux),modif)==0){
            SupressLista(a);
            set_pago(aux, modif)
            InsertarEnLista(a,aux);
        }else{
        ForwardCursores(a);
        }
    }
}

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
>>>>>>> b58f9e17b7f0872e07cd083917accfc3a456580d
{

    int i,forma_de_pago, num_de_combo, cantCombos,opcion_de_comer=0, opcion_cargar, opcion_descuento;
    char nombre_aux[31];
    Pedido aux;
    init(&aux);
    printf("Inserte el nombre del cliente.\n");
    getchar();
    gets(nombre_aux);
    set_nombre_pedido(&aux, nombre_aux);
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

                        printf("Tiene cupon?\n");
                        printf("Ingrese 1: si no tiene.\n");
                        printf("Ingrese 2: si tiene\n");
                        do{
                            scanf("%d", &opcion_descuento);
                            if(opcion_descuento<0 || opcion_descuento>2)
                            {
                                printf("Ingrese un numero valido, por favor.\n");
                            }
                        }while(opcion_descuento<0 || opcion_descuento>2);
                        //control de los numeros ingresados por el usuario

                        set_descuento_pedido(&aux, opcion_descuento-1);
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

            set_arreglo_para_combo(&aux, num_de_combo-1,cantCombos);
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

    set_forma_de_pago(&aux, forma_de_pago);
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

    set_donde_consume(&aux, opcion_de_comer-1);
    if(get_donde_consume(aux)==1)
    {
        printf("El costo del delivery es $500\n");

    }
    else
    {
        if(get_donde_consume(aux)==0)
        {
            printf("El costo del delivery es $0\n");
        }
    }
    set_fecha_del_pedido(&aux);
    set_subtotal(&aux, cms);
    set_total(&aux);

    printf("El subtotal es: $%0.2f \n", get_subtotal(aux));
    printf("El total es: $%0.2f \n", get_total(aux));
    printf("Fecha %i/%i/%i. \n", get_fecha(aux).dia, get_fecha(aux).mes, get_fecha(aux).ano);
    InsertarEnLista(a, aux);
}


void mostrar_lista(lista_pedido lista)
{
    Pedido aux;
    ResetCursores(&lista);
    int i;
    while(!isOos(lista))
    {
        aux=CopyLista(lista);
        printf("El nombre del cliente %s \n", get_nombre_pedido(aux));
        printf("El id del pedido es %s \n", get_id_pedido(aux));
        if(get_forma_de_pago(aux)==1)
        {
            printf("El forma de pago es efectivo.\n");
        }
        else
        {
            if(get_forma_de_pago(aux)==2)
            {
                printf("El forma de pago es debito.\n");
            }
            else
            {
                    if(get_forma_de_pago(aux)==3)
                    {
                        printf("El forma de pago es QR.\n");
                    }
                    else
                    {
                        if(get_forma_de_pago(aux)==4)
                        {
                             printf("El forma de pago es QR.\n");

                        }
                    }
            }
        }
        printf("El subtotal es: $%0.2f", get_subtotal(aux));
        printf("EL total es: $%0.2f", get_total(aux));
        if(get_donde_consume(aux)==1)
        {
            printf("Delivery\n");
        }
        else
        {
            printf("Consume en el local.\n");
        }
        printf("La fecha de la compra fue %i/%i/%i. \n", get_fecha(aux).dia, get_fecha(aux).mes, get_fecha(aux).ano);
        for(i=0; i<10; i++)
        {
            printf("Pidio el combo %i %i unidades.\n", i+1 ,get_arreglo_para_combos(aux,i));
        }
        ForwardCursores(&lista);
    }
}






void buscar_ventas_mes(lista_pedido lista, int mes_pedido)
{
    Pedido aux;
    int suma=0;
    fecha fecha_aux;
    ResetCursores(&lista);
    while(isOos(lista)==0 )
    {
        aux=CopyLista(lista);
        fecha_aux=get_fecha(aux);
        if(fecha_aux.mes==mes_pedido)
        {
            suma++;
        }
       ForwardCursores(&lista);
    }
    Pedido arreglo_aux[suma];
    int n=0;
    ResetCursores(&lista);
    while(isOos(lista)==0)
    {
        aux=CopyLista(lista);
        fecha_aux=get_fecha(aux);
        if(fecha_aux.mes==mes_pedido)
        {
            arreglo_aux[n]=aux;
        }
        ForwardCursores(&lista);
        n++;
    }
    int i,x;
    //revisa en cada pedido el mes si es igual del 1 al 12 y muestra los datos de menor a mayor
    for(i=0; i<suma; i++)
    {
        for(x=1; x<31; x++)
        {
            fecha_aux=get_fecha(aux);
            if(fecha_aux.dia==x)
            {
                printf("Nombre del cliente es %s \n", get_nombre_pedido(arreglo_aux[i]));
                printf("Fecha %i/%i/%i. \n", get_fecha(arreglo_aux[i]).dia, get_fecha(arreglo_aux[i]).mes, get_fecha(arreglo_aux[i]).ano);
                printf("El codigo del pedido es %s \n", get_id_pedido(arreglo_aux[i]));
                if(get_forma_de_pago(aux)==1)
                    {
                        printf("El forma de pago es efectivo.\n");
                    }
                    else
                    {
                        if(get_forma_de_pago(aux)==2)
                        {
                            printf("El forma de pago es debito.\n");
                        }
                        else
                        {
                                if(get_forma_de_pago(aux)==3)
                                {
                                    printf("El forma de pago es QR.\n");
                                }
                                else
                                {
                                    if(get_forma_de_pago(aux)==4)
                                    {
                                         printf("El forma de pago es QR.\n");

                                    }
                                }
                        }
                    }
                int k;
                for(k=0; k<10; k++)
                {
                    if(get_arreglo_para_combos(arreglo_aux[i],k)!=0)
                    {
                            printf("Pidio el combo %i: %i unidades\n", k+1,get_arreglo_para_combos(arreglo_aux[i]));
                    }
                }
                printf("El subtotal es: $%0.2f \n", get_subtotal(arreglo_aux[i]));
                printf("El total es: $%0.2f \n", get_total(arreglo_aux[i]));
                if(get_entregado(arreglo_aux[i])==1)
                {
                     printf("Entregado\n");

                }
                else
                {
                     printf("No esta entregado\n");
                }


            }
        }
    }
}

/**int  Busca_pedido(lista_pedido lista){
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
    printf("<21>Mostrar los pedidos.\n");
    scanf("%i", &opcion);
    switch(opcion)
    {
        case 1:
            ingresar_pedido(&la_lista, arreglo_combos);
        break;

        case 2:
                //Busca_pedido();
        break;
        case 4:
            buscar_ventas_mes(la_lista, 11);
        break;
        case 21:
            mostrar_lista(la_lista);
        break;

    };
    }while(opcion<=20 && opcion>=1);
    return 0;
}
