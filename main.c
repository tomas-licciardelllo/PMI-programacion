#include <stdio.h>
#include <time.h>
#include "lista.h"



void modifica_pago(lista_pedido a, int modif, char id_buscado[])
{ /** j) Modificar la forma de pago de un pedido seg�n su idpedido */
    Pedido aux;
    ResetCursores(&a);
    while(isOos(a)==0){
        aux=CopyLista(a);
        if(strcmp(get_id_pedido(aux),id_buscado)==0)
        {
            SupressLista(&a);
            set_forma_de_pago(&aux, modif);
            InsertarEnLista(&a,aux);
        }
        ForwardCursores(&a);
    }
}



void ingresar_pedido(lista_pedido *a, Combos cms[])

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

void eliminar_pedido_por_id(lista_pedido a, char id_buscado[])
{
    int i;
    FILE *puntero_archivo;
    puntero_archivo=fopen("pedidoseliminados.txt", "w");

    Pedido aux;
    ResetCursores(&a);
    while(isOos(a)==0)
    {
        printf("ENTRA\n");
        aux=CopyLista(a);
        if(strcmp(get_id_pedido(aux),id_buscado)==0)
        {
            SupressLista(&a);
            fprintf(puntero_archivo, "Codigo %s.\n", get_id_pedido(aux));
            printf("ENTRA\n");
            fprintf(puntero_archivo, "Nombre: %s.\n", get_nombre_pedido(aux));
            if(get_id_pedido(aux)==1)
            {
                fprintf(puntero_archivo, "La forma de pago es efectivo\.n");
            }
            else
            {
                if(get_id_pedido(aux)==2)
                {
                    fprintf(puntero_archivo, "La forma de pago es debito.\n");
                }
                else
                {
                    if(get_id_pedido(aux)==3)
                    {
                        fprintf(puntero_archivo, "La forma de pago es QR.\n");
                    }
                    else
                    {
                        if(get_id_pedido(aux)==4)
                        {
                            fprintf(puntero_archivo, "La forma de pago es credito.\n");
                        }
                    }
                }
            }

            printf("ENTRA\n");
            fprintf(puntero_archivo, "El subtotal: $%0.2f\n", get_subtotal(aux));
            fprintf(puntero_archivo, "El total es: $%0.2f \n", get_total(aux));
            if(get_donde_consume(aux)==0)
            {
                fprintf(puntero_archivo, "Delivery\n");
            }
            else
            {
                fprintf(puntero_archivo, "Consume en el establecimiento.\n");
            }
            fprintf(puntero_archivo, "La fecha de la compra %i/%i/%i. \n", get_fecha(aux).dia, get_fecha(aux).mes, get_fecha(aux).ano );
            for(i=0; i<10; i++)
            {
                fprintf(puntero_archivo, "Pidio el combo %i %i unidades.\n", i+1 ,get_arreglo_para_combos(aux,i));
            }

            printf("ENTRA\n");
            fclose(puntero_archivo);

        }
        printf("AJJAJAJJAJ");
        ForwardCursores(&a);
    }
}


void mostrar_todos_los_combos(Combos cms[])
{
    int i;
    for(i=0; i<10; i++)
    {
        printf("Combo %i \n", get_id_combo(cms[i])+1);
        printf("%s\n", get_descipcion(cms[i]));
        printf("Stock %i\n", get_stock(cms[i]));
        printf("Precio $%0.2f\n", get_precio(cms[i]));
        if(get_descuento(cms[i])==1)
        {
            printf("Posee descuento.\n");
        }
        else
        {
            printf("No posee descuento.\n");
        }

    }
}

void modificar_precio_stock_combo(Combos cms[], int id_buscado)
{
    int i;
    float nuevo_precio;
    int nuevo_stock;
    for(i=0; i<10; i++)
    {
        if(get_id_combo(cms[i])==id_buscado-1)
        {
            printf("Ingrese el nuevo precio a ingresar.\n");
            scanf("%f", &nuevo_precio);
            set_precio(&cms[i], nuevo_precio);
            printf("Ingrese la nueva cantidad del stock del combo.\n");
            scanf("%i", &nuevo_stock);
            set_stock(&cms[i], nuevo_stock);;
        }
    }
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
        printf("El subtotal es: $%0.2f\n", get_subtotal(aux));
        printf("EL total es: $%0.2f\n", get_total(aux));
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
        if(get_entregado(aux)==1)
        {
            printf("El pedido esta entregado.\n");
        }
        else
        {
            printf("El pedido no esta entregado.\n");
        }
        ForwardCursores(&lista);
    }
}

void modificar_condicion (lista_pedido a, char id_buscado[])
{
    Pedido aux;
    ResetCursores(&a);
    while(isOos(a)==0)
    {
        aux=CopyLista(a);
        if(strcmp(get_id_pedido(aux), id_buscado)==0)
        {
            SupressLista(&a);
            set_entregado(&aux, 1);
            InsertarEnLista(&a,aux);
        }
        ForwardCursores(&a);
    }

}


void modificar_nombre(lista_pedido a, char nombre_cambio[], char id_buscado[])
{
    Pedido aux;
    ResetCursores(&a);
    while(isOos(a)==0){
        aux=CopyLista(a);
        if(strcmp(get_id_pedido(aux),id_buscado)==0)
        {
            SupressLista(&a);
            set_nombre_pedido(&aux, nombre_cambio);
            InsertarEnLista(&a,aux);
        }
        ForwardCursores(&a);
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
                            printf("Pidio el combo %i: %i unidades\n", k+1,get_arreglo_para_combos(arreglo_aux[i],i));
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


int  Busca_pedido(lista_pedido lista, char id_buscado[]){

    Pedido var_pedido;
    ResetCursores(&lista);
    do{
        var_pedido=CopyLista(lista);
        ForwardCursores(&lista);
    }
    while(strcmp(get_id_pedido(var_pedido),id_buscado)!=0 || isOos(lista)==0);

    if(strcmp(get_id_pedido(var_pedido),id_buscado)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Mostrar Pedido de id buscado
void MostrarPedido_id(lista_pedido lista, char id_busqueda[])
{
    Pedido var_pedido;

    Busca_pedido(lista, id_busqueda);

    var_pedido=CopyLista(lista);

    printf("El nombre del clinte es:%s\n",get_nombre_pedido(var_pedido));
    printf("El id del pedido es: %s \n", get_id_pedido(var_pedido));

    if(get_forma_de_pago(var_pedido)==1)
                    {
                        printf("El forma de pago es efectivo.\n");
                    }
                    else
                    {
                        if(get_forma_de_pago(var_pedido)==2)
                        {
                            printf("El forma de pago es debito.\n");
                        }
                        else
                        {
                                if(get_forma_de_pago(var_pedido)==3)
                                {
                                    printf("El forma de pago es QR.\n");
                                }
                                else
                                {
                                    if(get_forma_de_pago(var_pedido)==4)
                                    {
                                         printf("El forma de pago es QR.\n");

                                    }
                                }
                        }
                    }
    if(get_donde_consume(var_pedido)==0)
    {
        printf("Consume en el establecimiento.\n");
    }
    else
    {
        printf("Delivery\n");
    }
    printf("El sub total es: $%0.2f\n",get_subtotal(var_pedido));
    printf("El total es:$%0.2f \n",get_total(var_pedido));
    printf("Fecha %i/%i/%i. \n", get_fecha(var_pedido).dia, get_fecha(var_pedido).mes, get_fecha(var_pedido).ano);
}

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
    int opcion, nueva_opcion_de_pago, id_opcion_17;
    char id_buscado[11], id_buscado_opcion_9[11], id_buscado_opcion_8[11], id_pedido_opcion_10[10], nombre_opcion_10[11], id_pedido_opcion_11[11];
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

            printf("Ingrese el id que esta buscando.\n");
            getchar();
            gets(id_buscado);
            Busca_pedido(la_lista, id_buscado);
            if(Busca_pedido(la_lista, id_buscado)==1)
            {
                printf("El pedido esta en la lista.\n");
            }
            else
            {
                printf("El pedido no esta en la lista.\n");
            }
        break;
        case 3:
            printf("Ingrese el id que esta buscando.\n");
            getchar();
            gets(id_buscado);
            MostrarPedido_id(la_lista, id_buscado);
        break;
        case 4:
            buscar_ventas_mes(la_lista, 11);
        break;
        case 8:
            printf("Ingrese el id que esta buscando.\n");
            getchar();
            gets(id_buscado_opcion_8);
            modificar_condicion(la_lista, id_buscado_opcion_8);
        break;
        case 9:
            printf("Ingrese el id del pedido buscado.\n");
            getchar();
            gets(id_buscado_opcion_9);
            printf("Ingrese la nueva forma de pago que quiere ingresar.\n");
            printf("<1>Para efectivo.\n");
            printf("<2>Para debito.\n");
            printf("<3>Para QR\n");
            printf("<4>Para credito.\n");
            scanf("%i", &nueva_opcion_de_pago);
            modifica_pago(la_lista, nueva_opcion_de_pago, id_buscado_opcion_9);
        break;
        case 10:
            printf("Ingrese el id del pedido buscado.\n");
            getchar();
            gets(id_pedido_opcion_10);
            printf("Ingrese el nuevo nombre que quiere ingressar.\n");
            getchar();
            gets(nombre_opcion_10);
            modificar_nombre(la_lista,nombre_opcion_10, id_pedido_opcion_10);
        break;
        case 11:
            printf("Ingrese el id del pedido que quiere eliminar.\n");
            getchar();
            gets(id_pedido_opcion_11);
            eliminar_pedido_por_id(la_lista, id_pedido_opcion_11);
        break;
        case 15:
            printf("Ingrese el id del combo que quiere modificar.\n");
            scanf("%i", &id_opcion_17);
            modificar_precio_stock_combo(arreglo_combos,id_opcion_17);
        break;
        case 16:
            mostrar_todos_los_combos(arreglo_combos);
        break;
        case 21:
            mostrar_lista(la_lista);
        break;

    };
    }while(opcion<=21 && opcion>=1);
    return 0;
}
