#include <stdio.h>
#include <time.h>
#include "lista.h"
int VENDEDOR_1;


void modifica_pago(lista_pedido a, int modif, char id_buscado[])
{ /** j) Modificar la forma de pago de un pedido según su idpedido */
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
    set_vendedor(&aux, VENDEDOR_1);
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
            printf("Cant de combos %i\n", cantCombos);
            printf("combo stock %i\n",get_stock(cms[num_de_combo-1]));
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

void mostrar_pedidos_no_entregados(lista_pedido *a)
{
    int i;
    Pedido aux;
    ResetCursores(a);
    while(!isOos(*a))
    {
        aux=CopyLista(*a);
        if(get_entregado(aux)==0)
        {
                printf("Nombre del cliente: %s \n", get_nombre_pedido(aux));
                printf("ID del pedido: %s \n", get_id_pedido(aux));
                if(get_forma_de_pago(aux)==1)
                {
                    printf("El forma de pago es: efectivo.\n");
                }
                else
                {
                    if(get_forma_de_pago(aux)==2)
                    {
                        printf("El forma de pago es: debito.\n");
                    }
                    else
                    {
                            if(get_forma_de_pago(aux)==3)
                            {
                                printf("El forma de pago es: QR.\n");
                            }
                            else
                            {
                                if(get_forma_de_pago(aux)==4)
                                {
                                     printf("El forma de pago es: QR.\n");

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
                    if(get_arreglo_para_combos(aux, i)>0)
                    {
                        printf("Pidio el combo %i : %i unidades.\n", i+1 ,get_arreglo_para_combos(aux,i));
                    }
                }
                if(get_entregado(aux)==1)
                {
                    printf("El pedido esta entregado.\n");
                }
                else
                {
                    printf("El pedido no esta entregado.\n");
                }
        }
        ForwardCursores(a);
    }
}

void eliminar_pedido_por_id(lista_pedido *a, char id_buscado[], Combos arreglo[])
{
    int i;
    FILE *puntero_archivo;
    puntero_archivo=fopen("pedidoseliminados.txt", "a+");

    Pedido aux;
    ResetCursores(a);
    while(isOos(*a)==0)
    {

        aux=CopyLista(*a);
        if(strcmp(get_id_pedido(aux),id_buscado)==0 && get_entregado(aux)==0)
        {
            SupressLista(a);
            fprintf(puntero_archivo, "Codigo %s.\n", get_id_pedido(aux));
            fprintf(puntero_archivo, "Nombre: %s.\n", get_nombre_pedido(aux));
            if(get_forma_de_pago(aux)==1)
            {
                fprintf(puntero_archivo, "La forma de pago es efectivo.\n");
            }
            else
            {
                if(get_forma_de_pago(aux)==2)
                {
                    fprintf(puntero_archivo, "La forma de pago es debito.\n");
                }
                else
                {
                    if(get_forma_de_pago(aux)==3)
                    {
                        fprintf(puntero_archivo, "La forma de pago es QR.\n");
                    }
                    else
                    {
                        if(get_forma_de_pago(aux)==4)
                        {
                            fprintf(puntero_archivo, "La forma de pago es credito.\n");
                        }
                    }
                }
            }

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
                set_stock(&arreglo[i],get_stock(arreglo[i])+get_arreglo_para_combos(aux,i));
                fprintf(puntero_archivo, "Pidio el combo %i %i unidades.\n", i+1 ,get_arreglo_para_combos(aux,i));
            }
            fprintf(puntero_archivo, "\n");
            printf("Se elimino exitosamente.\n");

        }
        else
        {
            if(strcmp(get_id_pedido(aux),id_buscado)==0)
            {
                printf("El id ingresado no esta dentro de la lista.\n");
            }
            else
            {
                if(get_entregado(aux)==0)
                {
                    printf("El pedido que solicita no se encuentra en la lista.\n");
                }
            }

        }
        if(!isOos(*a))
        {
            ForwardCursores(a);
        }
    }
    fclose(puntero_archivo);
}
void guardar_forma_pago(lista_pedido *a, int forma_pago)
{
    Pedido aux;
    int suma=0, i;
    FILE *pa;
    pa=fopen("forpago.txt", "a+");

    ResetCursores(a);
    while(!isOos(*a))
    {
        aux=CopyLista(*a);
        if(get_forma_de_pago(aux)==forma_pago)
        {
                suma=suma+1;
                fprintf(pa, "Codigo %s. \n", get_id_pedido(aux));
                printf("ENTRA\n");
                fprintf(pa, "Nombre: %s. \n", get_nombre_pedido(aux));
                if(get_forma_de_pago(aux)==1)
                {
                    fprintf(pa, "La forma de pago es efectivo.\n");
                }
                else
                {
                    if(get_forma_de_pago(aux)==2)
                    {
                        fprintf(pa, "La forma de pago es debito.\n");
                    }
                    else
                    {
                        if(get_forma_de_pago(aux)==3)
                        {
                            fprintf(pa, "La forma de pago es QR.\n");
                        }
                        else
                        {
                            if(get_forma_de_pago(aux)==4)
                            {
                                fprintf(pa, "La forma de pago es credito.\n");
                            }
                        }
                    }
                }

                printf("ENTRA\n");
                fprintf(pa, "El subtotal: $%0.2f\n", get_subtotal(aux));
                fprintf(pa, "El total es: $%0.2f \n", get_total(aux));
                if(get_donde_consume(aux)==0)
                {
                    fprintf(pa, "Delivery\n");
                }
                else
                {
                    fprintf(pa, "Consume en el establecimiento.\n");
                }
                fprintf(pa, "La fecha de la compra %i/%i/%i. \n", get_fecha(aux).dia, get_fecha(aux).mes, get_fecha(aux).ano );
                for(i=0; i<10; i++)
                {
                    fprintf(pa, "Pidio el combo %i %i unidades.\n", i+1 ,get_arreglo_para_combos(aux,i));
                }

            }
            if(!isOos(*a))
            {
                ForwardCursores(a);
            }
        }


    printf("Se cargaron %i. \n", suma);
    fclose(pa);
}
void cargar_historial(lista_pedido *a)
{
    Pedido aux;
    int i,x,z, dia, mes, ano, forma_pago,donde_consume, entregado, vendedor, arreglo_combos[10];
    char nombre[31], id[11], basura[30];
    float total,sub_total;

    ResetCursores(a);
    FILE *pa;
    pa=fopen("historial.txt", "r");

    if(isFull(*a)==1)
    {
        printf("La lista esta llena.\n");
    }
    else
    {

        for(i=0; i<10; i++)
        {
            init(&aux);
            fscanf(pa, "%s\n", nombre);
            fscanf(pa,"%s\n", id);
            fscanf(pa, "%d\n", &vendedor);
            for(x=0; x<10; x++)
            {
                fscanf(pa, "%d\n", &arreglo_combos[x]);
                set_arreglo_para_combo(&aux,x,arreglo_combos[x]);
            }
            fscanf(pa, "%d\n", &forma_pago);
            fscanf(pa, "%f\n", &sub_total);
            fscanf(pa, "%d\n", &donde_consume);
            fscanf(pa, "%f\n", &total);
            fscanf(pa, "%d\n", &dia);
            fscanf(pa, "%d\n", &mes);
            fscanf(pa, "%d\n", &ano);
            fscanf(pa, "%d\n", &entregado);
            fscanf(pa, "%s\n", &basura);

            set_nombre_pedido(&aux, nombre);
            set_id_pedido(&aux,id);
            set_vendedor(&aux, vendedor);
            /*for(z=0; z<10; z++)
            {
                set_arreglo_para_combo(&aux,i,arreglo_combos[z]);
            }*/
            set_forma_de_pago(&aux, forma_pago);
            set_subtotal_carga_historial(&aux,sub_total);
            set_donde_consume(&aux,donde_consume);
            set_total_historial(&aux, total);
            set_fecha_dia(&aux,dia);
            set_fecha_mes(&aux,mes);
            set_fecha_ano(&aux,ano);
            set_entregado(&aux, entregado);
            InsertarEnLista(a,aux);
            ForwardCursores(a);
    }

    printf("Se cargaron los pedidos exitosamente.\n");
    fclose(pa);
   }
}
int pedidos_realizados_x_vendedor_total_ID(lista_pedido *a, int codigo)
{

    if(isOos(*a)==1)
    {
        return 0;
    }
    else
    {
        if(get_vendedor(CopyLista(*a))==codigo)
        {
            printf("El id es %s \n", get_id_pedido(CopyLista(*a)));
            printf("Total: $%0.2f \n", get_total(CopyLista(*a)));
        }
        ForwardCursores(a);
        pedidos_realizados_x_vendedor_total_ID(a, codigo);
        return 1;
    }
}
/**<19>Mostrar cual es el vendedor que realizo mas ventas en el mes.*/
int vendedor_de_mes(lista_pedido a){
    Pedido aux;
    int vendedor1=0, vendedor2=0, vendedor3=0;
    ResetCursores(&a);
    while(!isOos(a)){
        aux=CopyLista(a);

        if(get_vendedor(aux)==1){
            vendedor1= vendedor1 + 1;
        }
        if(get_vendedor(aux)==2){
            vendedor2= vendedor2 + 1;
        }
        if(get_vendedor(aux)==3){
            vendedor3= vendedor3 + 1;
        }
        ForwardCursores(&a);
    }
    if(vendedor1>=vendedor2 && vendedor1>=vendedor3){
        return 1;
    }else{
        if(vendedor2>=vendedor1 && vendedor2>=vendedor3){
            return 2;
        }else{
            if(vendedor3>=vendedor1 && vendedor3>=vendedor2){
                return 3;
            }
        }
    }
}
int pedidos_realizados_x_vendedor(lista_pedido *a, int codigo, int acum)
{
    if(isOos(*a)==1)
    {
        return acum;
    }
    else
    {
        if(get_vendedor(CopyLista(*a))==codigo)
        {
            acum++;
        }
        ForwardCursores(a);
        pedidos_realizados_x_vendedor(a,codigo,acum);
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
        printf("\n");

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
    if(isEmpty(lista)==1)
    {
        printf("La lista esta vacia.\n");
    }
    else
    {


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
                                     printf("El forma de pago es credito.\n");

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

                    if(get_arreglo_para_combos(aux,i)>0)
                    {
                        printf("Pidio el combo %d: %d unidades.\n", i+1 ,get_arreglo_para_combos(aux,i));
                    }
                }
                if(get_entregado(aux)==1)
                {
                    printf("El pedido esta entregado.\n");
                }
                else
                {
                    printf("El pedido no esta entregado.\n");
                }
                printf("Codigo del pedido del vendedor %d.\n", get_vendedor(aux));
                 printf("\n");
                ForwardCursores(&lista);
            }
    }
}

void modificar_condicion (lista_pedido a, char id_buscado[])
{
    Pedido aux;
    int control=0;
    ResetCursores(&a);
    while(isOos(a)==0)
    {
        aux=CopyLista(a);
        if(strcmp(get_id_pedido(aux), id_buscado)==0)
        {
            SupressLista(&a);
            set_entregado(&aux, 1);
            InsertarEnLista(&a,aux);
            printf("Se a cambiado el estado del pedido a entregado.\n");
            control=1;
        }
        else
        {
            if(control==1)
            {
                printf("El id del pedido que solicita no se encuentra en la lista.\n");
            }
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
            printf("Se cambio existosamente.\n");
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
    while(isOos(lista)==0)
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
    printf("la suma es %i\n",suma);
    int n=0;
    ResetCursores(&lista);
    while(n!=suma)
    {
        aux=CopyLista(lista);
        fecha_aux=get_fecha(aux);
        if(CopyLista(lista).fecha_pedido.mes==mes_pedido)
        {
            arreglo_aux[n]=aux;
            n++;
        }
        ForwardCursores(&lista);

    }
    int i,x, basura;
    //revisa en cada pedido el mes si es igual del 1 al 12 y muestra los datos de menor a mayor
    ResetCursores(&lista);
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
                            printf("Pidio el combo %i: %i unidades\n", k+1, get_arreglo_para_combos(arreglo_aux[i],k));
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
        printf("\n");
    }
}


int Busca_pedido(lista_pedido lista, char id_buscado[]){

    Pedido var_pedido;
    ResetCursores(&lista);

    int x=0;
            while(!isOos(lista)){
                var_pedido=CopyLista(lista);
                ForwardCursores(&lista);
                if(strcmp(get_id_pedido(var_pedido),id_buscado)==0)
                {
                    x=1;
                }
            }

            if(x==1)
            {

                return 1;
            }
            else
            {
                return 0;
            }
    }


//Mostrar Pedido de id buscado
void MostrarPedido_id(lista_pedido *lista, char id_busqueda[])
{
    int i, encontrado=0;
    Pedido var_pedido;
    ResetCursores(lista);
    while(!isOos(*lista))
    {
            var_pedido=CopyLista(*lista);
            if(strcmp(get_id_pedido(var_pedido),id_busqueda)==0)
            {

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

                                for(i=0; i<10; i++)
                                {
                                    if(get_arreglo_para_combos(var_pedido,i)!=0)
                                    {
                                        printf("Pidio el combo %i: %i unidades.\n", i+1 ,get_arreglo_para_combos(var_pedido,i));
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
                    encontrado=1;
                }
        ForwardCursores(lista);
        if(encontrado==0)
        {
            printf("El pedido no esta en la lista.\n");
        }
    }
}

//Mostrar pedidos sin stock

void Mostar_SinStock(Combos arreglo_combos[]){
    int i;
        printf("Pedidos sin stock: \n");
        for(i=0;i<10;i++){
                if((get_stock(arreglo_combos[i]))==0){

                printf("id combo = %d\n",get_id_combo(arreglo_combos[i]));

                printf("id descripcion = %s\n",get_descipcion(arreglo_combos[i]));

            }
    }
}

 //Mostrar precio y stock de combo pasado por id
void Mostrar_PrecyStock(Combos arreglo_combos[],int id_combo){
int i, suma=0;
    printf("Precio y stock del pedido:");
        for(i=0;i<10;i++){
                if((get_id_combo(arreglo_combos[i]))==id_combo-1){

                printf("El precio del combo es $ %0.2f\n",get_precio(arreglo_combos[i]));


                printf("El stock del combo es: %i\n",get_stock(arreglo_combos[i]));
                }
                else
                {
                    suma++;
                }

            }
            if(suma==10)
            {
                printf("No se ha encontrado el id que solicitado");
            }
}

///Mostrar los pedidos por nombre, paginar la muestra de los datos. Función (e). Menu <4>.
void mostrar_aux(lista_pedido l){
        printf("Nombre del cliente: %s\n",get_nombre_pedido(CopyLista(l)));
        printf("El id del cliente: %s\n", get_id_pedido(CopyLista(l)));
        printf("\nFecha de compra: %d/%d/%d\n",get_fecha(CopyLista(l)).dia,get_fecha(CopyLista(l)).mes,get_fecha(CopyLista(l)).ano);
        printf("Forma de pago: ");
            switch(get_forma_de_pago(CopyLista(l))){
            case 1:
                printf("Debito\n");
                break;
            case 2:
                printf("Credito\n");
                break;
            case 3:
                printf("QR\n");
                break;
            case 4:
                printf("Efectivo\n");
                break;
            }
            if(get_donde_consume(CopyLista(l))==1){
                printf("Consume en el local\n");
            }
            else{
                printf("No consume en el local\n");
            }
        printf("Subtotal pagado: %.2f\n",get_subtotal(CopyLista(l)));
        printf("Total pagado: %.2f\n\n",get_total(CopyLista(l)));
}

void mostrar_pedidos_nombre(lista_pedido l,char nom_pasado[]){
    Pedido aux;
    int mostrar_mas=0,se_muestra=0;
    char letra;
    system("cls");
    ResetCursores(&l);
    while(!isOos(l)){
        aux = CopyLista(l);
        if(strcmp(get_nombre_pedido(aux),nom_pasado)==0){
            mostrar_aux(l);
            se_muestra++;
            mostrar_mas++;
       }
        ForwardCursores(&l);
        if(mostrar_mas==4){
            do{
                printf("Presione (M) si desea ver mas pedidos. Presione (S) si no lo desea\n");
                scanf(" %c",&letra);
                if(letra == 's'){
                        system("cls");
                    return 0;
                }

                if(letra!= 'm'){
                    printf("\nel valor ingresado no esta en los parametros\n");
                }

            }while(letra!= 'm');
            mostrar_mas=0;
            system("cls");
        }

    }

    do{
        if(se_muestra==0){
            printf("\nNo se encontró ningún pedido con el nombre pasado\n");
        }
       else  {
            printf("Se mostraron todos los pedidos exitosamente\n\n");
       }
        printf("Presione (V) para volver al menu\n");
        scanf(" %c",&letra);
        if(letra!= 'v'){
            printf("\nel valor ingresado no esta en los parametros\n");
        }
    }while(letra!= 'v');

    system("cls");
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
    int validacion=0,carga_completada=0,opcion, opcion_volver,nueva_opcion_de_pago, id_opcion_17, vendedor_opcion_20, mes_opcion_4, codigo_vendedor_opcion_6, codigo_vendedor_opcion_7, acum_opcion_7=0, forma_pago_opcion_12, opcion_id_combo_17;
    char nombre_buscaus[31], validacion_char, id_buscado[11], id_buscado_opcion_9[11], id_buscado_opcion_8[11], id_pedido_opcion_10[10], nombre_opcion_10[11], id_pedido_opcion_11[11];

    printf("Ingrese el codigo del vendedor de 1 a 3.\n");
    do{
        scanf("%i", &VENDEDOR_1);
        if(VENDEDOR_1<1 || VENDEDOR_1>3)
        {
            printf("El codigo ingresado no es valido, ingrese un codigo valido.\n");
        }
    }while(VENDEDOR_1<1 || VENDEDOR_1>3);
    do{
    system("cls");
    printf("------------------Menu---------------------------\n");
    printf("<1>Ingresar un pedido.\n");
    printf("<2>Mostrar los datos del pedido buscado por ID.\n");
    printf("<3>Mostrar los pedidos de un mes ordenados por fecha.\n");
    printf("<4>Mostrar los pedidos por nombre.\n");
    printf("<5>Mostrar los pedidos realizados por un vendedor, solo el idpedido y el total.\n");//es una recursiva muestra el idpedido total
    printf("<6>Contar los pedidos realizados por un vendedor.\n");
    printf("<7>Modificar el estado del pedido a entregado por idpedido.\n");
    printf("<8>Modificar la forma de pago de un pedido \n");
    printf("<9>Modificar nombre de un pedido segun su idpedido.\n");
    printf("<10>Anular un pedido por idpedido.\n");
    printf("<11>Almacenar los datos de los pedidos pagados de un tipo de forma de pago.\n");
    printf("<12>Historial de los pedidos.\n");
    printf("<13>Mostrar los pedidos no entregados\n");
    printf("<14>Modificar precio y stock del combo segun idcombo.\n");
    printf("<15>Mostrar todos los combos.\n");
    printf("<16>Mostrar precio y stock de un combo por idcombo.\n");
    printf("<17>Mostrar los combos sin stock.\n");
    printf("<18>Mostrar cual es el vendedor que realizo mas ventas en el mes.\n");
    printf("<19>Cambiar el vendedor,\n");
    printf("<20>Mostrar los pedidos.\n");
    printf("<21>Salir.\n");
    printf("Ingrese una opcion del menu INGRESE UN NUMERO, NO CARACTERES.\n");
    scanf("%d", &opcion);

    switch(opcion)
    {
        case 1:
            if(isFull(la_lista)==1)
            {
                printf("La lista esta llena ya no se pueden agregar mas pedidos.\n");
            }
            else
            {
                ingresar_pedido(&la_lista, arreglo_combos);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 2:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, por lo tanto no se pudo bucar ningun pedido aun.\n");
            }
            else
            {
                printf("Ingrese el id que esta buscando.\n");
                getchar();
                gets(id_buscado);

                if(Busca_pedido(la_lista, id_buscado)==1)
                {
                    MostrarPedido_id(&la_lista, id_buscado);
                }
                else
                {
                    printf("El pedido no esta en la lista.\n");
                }
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 3:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede buscar ningun pedido por mes hasta que al menos se ingrese uno.\n");
            }
            else
            {
                printf("Ingrese el mes el cual quiere ver los pedidos.\n");
                fflush(stdin);
                scanf("%i", &mes_opcion_4);
                buscar_ventas_mes(la_lista, mes_opcion_4);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 4:

            printf("Cual es el nombre del usuario que desea buscar?\n");
            fflush(stdin);
            gets(nombre_buscaus);
            printf("%s", nombre_buscaus);
            mostrar_pedidos_nombre(la_lista,nombre_buscaus);
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 5:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede buscar ningun vendedor ya que no se a guardado nada aun.\n");
            }
            else
            {
                printf("Ingrese el codigo del vendedor que esta buscando (del 1 al 3).\n");
                do{
                    scanf("%i", &codigo_vendedor_opcion_6);
                    if(codigo_vendedor_opcion_6>3 || codigo_vendedor_opcion_6<1)
                    {
                        printf("Ingrese un codigo valido.\n");
                    }
                }while(codigo_vendedor_opcion_6<1 || codigo_vendedor_opcion_6>3);
                if(codigo_vendedor_opcion_6==1)
                {
                    printf("El empleado Juan Carlos realizo los pedidos.\n");
                }
                else
                {
                    if(codigo_vendedor_opcion_6==2)
                    {
                        printf("El empleado Jose Maria realizo los pedidos.\n");
                    }
                    else
                    {
                        if(codigo_vendedor_opcion_6==3)
                        {
                            printf("El empleado Nilda Juarez realizo los pedidos.\n");
                        }
                    }
                }
                ResetCursores(&la_lista);
                pedidos_realizados_x_vendedor_total_ID(&la_lista,codigo_vendedor_opcion_6);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 6:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede buscar ningun pedido ya que ningun vendedor vendio algo aun.\n");
            }
            else
            {
                    printf("Ingrese el id del vendedor al cual que esta busacando (del 1 al 3).\n");
                    do{
                        scanf("%d", &codigo_vendedor_opcion_7);
                    }while(codigo_vendedor_opcion_7<1 || codigo_vendedor_opcion_7>3);
                    if(codigo_vendedor_opcion_7==1)
                    {
                        printf("El empleado Juan Carlos realizo");
                    }
                    else
                    {
                        if(codigo_vendedor_opcion_7==2)
                        {
                            printf("El empleado Jose Maria realizo");
                        }
                        else
                        {
                            if(codigo_vendedor_opcion_7==3)
                            {
                                printf("El empleado Nilda Juarez realizo");
                            }
                        }
                    }
                    ResetCursores(&la_lista);

                    printf(" %d pedidos.\n", pedidos_realizados_x_vendedor(&la_lista,codigo_vendedor_opcion_7, acum_opcion_7));
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 7:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
                    printf("Ingrese el id que esta buscando.\n");
                    getchar();
                    gets(id_buscado_opcion_8);
                    modificar_condicion(la_lista, id_buscado_opcion_8);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 8:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
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
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 9:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
                printf("Ingrese el id del pedido buscado.\n");
                getchar();
                scanf("%s", id_pedido_opcion_10);
                printf("Ingrese el nuevo nombre que quiere ingressar.\n");
                getchar();
                gets(nombre_opcion_10);
                modificar_nombre(la_lista,nombre_opcion_10, id_pedido_opcion_10);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 10:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
                printf("Ingrese el id del pedido que quiere anular.\n");
                getchar();
                gets(id_pedido_opcion_11);
                eliminar_pedido_por_id(&la_lista, id_pedido_opcion_11, arreglo_combos);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 11:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
                printf("Ingrese la forma de pago.\n");
                printf("<1>Para efectivo.\n");
                printf("<2>Para debito.\n");
                printf("<3>Para QR.\n");
                printf("<4>Para credito.\n");
                scanf("%i", &forma_pago_opcion_12);
                guardar_forma_pago(&la_lista, forma_pago_opcion_12);
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 12:
            if(carga_completada==0)
            {
                cargar_historial(&la_lista);
                carga_completada=1;
            }
            else
            {
                printf("Ya se cargo el historial.\n");
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 13:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
                mostrar_pedidos_no_entregados(&la_lista);
            }
            do{
                printf("Inngrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 14:

                printf("Ingrese el id del combo que quiere modificar.\n");
                scanf("%i", &id_opcion_17);
                modificar_precio_stock_combo(arreglo_combos,id_opcion_17);

            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 15:
            mostrar_todos_los_combos(arreglo_combos);
            do{
                printf("Igrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 16:
               printf("Ingrese el id del combo del 1 al 10.\n");
               scanf("%i", &opcion_id_combo_17);
               Mostrar_PrecyStock(arreglo_combos, opcion_id_combo_17);
               do{
                printf("Igrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 17:
                Mostar_SinStock(arreglo_combos);
                do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 18:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {
                printf("El vendedor con mas pedidos realizados fue el vendedor de codigo: %i, Nombre:",vendedor_de_mes(la_lista));
                if(vendedor_de_mes(la_lista)==1)
                {
                    printf("Juan Carlos\n");
                }
                else
                {
                    if(vendedor_de_mes(la_lista)==2)
                    {
                        printf("Jose Maria\n");
                    }
                    else
                    {
                        if(vendedor_de_mes(la_lista)==3)
                        {
                            printf("Nilda Juarez\n");
                        }
                    }
                }
            }
            do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 19:
                printf("Ingrese el codigo del vendedor al cual va a cambiar.\n");
                do{
                    scanf("%i",&vendedor_opcion_20);
                }while(vendedor_opcion_20<1 && vendedor_opcion_20>3);

                VENDEDOR_1=vendedor_opcion_20;
                printf("Se a cambiado el codigo correctamente.\n");
                do{
                printf("Ingrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        case 20:
            if(isEmpty(la_lista)==1)
            {
                printf("La lista esta vacia, no se puede hacer ningun cambio hasta que se cargue al menos un pedido.\n");
            }
            else
            {

                mostrar_lista(la_lista);
            }
            do{
                printf("Igrese 1 si quiere volver al MENU.\n");
                scanf("%d",&opcion_volver);
            }while(opcion_volver!=1);
        break;
        default:
            printf("La eleccion no esta dentro de las opciones, ingrese una eleccion correcta.\n");
            printf("Presione cualquier tecla para continuar.\n");
            system("pause");
    }

    }while(opcion!=21);
    return 0;
}


