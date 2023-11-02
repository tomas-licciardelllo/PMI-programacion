#include <stdio.h>
#include <time.h>
#include "lista.h"


void modifica_pago(Pedido *a, char modif[]){//incompleta
/** j) Modificar la forma de pago de un pedido según su idpedido */
    init(*a);//cual seria el error??
    ResetCursores(*a);
    while(!isOos){
        if(strcmp(get_id_pedido(a.),modif)==0)
        ForwardCursores(*a);
    }
    CopyLista()
    //modifico el nodo

}

void calcular_totales(Pedido *a, Combos todos[])
{
    int cuantos_de_cada;
    int i;
    float total_de_los_combos=0, descuentos=0;
    for(i=0; i<10; i++)
    {
         total_de_los_combos=total_de_los_combos+((*a).arreglo_para_combos[i]*todos[i].precio);
         if(get_descuento(todos[i])==1)
         {
             descuentos=descuentos+((get_precio(todos[i])*(*a).arreglo_para_combos[i])*15/100);
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

    int i,forma_de_pago, num_de_combo, cantCombos,opcion_de_comer, opcion_cargar;
    Pedido aux;
    init(&aux);
    printf("Inserte el nombre del cliente.\n");
    gets(aux.nombre);
    id(&aux);
    do{
            //en esta parte se pregunta si va a seguir cargando
            printf("Ingrese el combo que  va ingresar.\n");
            for(i=0; i<10; i++)
            {
                printf("%i_%s\n", get_id_combo(cms[i])+1, get_descipcion(cms[i]));
            }
            getchar();
            scanf("%i", &num_de_combo);
            printf("Ingrese la cantidad de combos.\n");
            scanf("%i", &cantCombos);
            if(get_stock(cms[num_de_combo-1])<cantCombos)
            {
                printf("No hay stock suficiente de ese tipo de combos.\n");
                printf("Hay %i combos de ese tipo.\n", get_stock(cms[num_de_combo-1]));
            }
            printf("Quiere seguir cargando combos?\n");
            printf("Ingrese 1: si quiere seguir cargando.\n");
            printf("Ingrese 2: si no quiere seguir cargando.\n");
            scanf("%i", &opcion_cargar);
    }while(get_stock(cms[num_de_combo-1])==0 && opcion_cargar==2);
    combo(&aux, num_de_combo,cantCombos);
    printf("Ingrese la forma de pago que va a utilizar.\n");
    printf("<1>Para efectivo.\n");
    printf("<2>Para debito.\n");
    printf("<3>Para QR\n");
    printf("<4>Para credito.\n");
    scanf("%i", &forma_de_pago);
    pago(&aux, forma_de_pago);
    printf("Ingrese donde consume.\n");
    printf("1: Para en el establecimiento.\n");
    printf("2: Para delivery.\n");
    scanf("%i", opcion_de_comer);
    lugar(&aux, opcion_de_comer);
    if(aux.donde_consume==2)
    {
        printf("El costo del delivery es $500\n");

    }
    else
    {
        printf("El costo del delivery es $0\n");
    }

    calcular_totales(&aux,cms);

    printf("El subtotal es: %f\n", aux.sub_total);
    printf("El total es : %f\n", aux.total);





    InsertarEnLista(&a, aux);



}

void iniciar_combos(Combos a[])
{
    int i;
    FILE *puntero_archivo;
    puntero_archivo=fopen("menu.txt", "r");
    for(i=0; i<10; i++)
    {
        inic_combo(&a[i]);
        fscanf(puntero_archivo,"%i", &(a[i].id_combo));
        fscanf(puntero_archivo, "%s", a[i].descripcion);
        fscanf(puntero_archivo, "%i", &(a[i].stock));
        fscanf(puntero_archivo, "%f", &(a[i].precio));
        fscanf(puntero_archivo, "%i", &(a[i].descuento));
    }
    fclose(puntero_archivo);
}


int main()
{
    lista_pedido la_lista;
    Combos arreglo_combos[10];
    iniciar_combos(arreglo_combos);
    InicializarLista(&la_lista);



    int opcion;



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
    ingresar_pedido(la_lista,arreglo_combos);


    return 0;
}
