#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#define TAM 5

typedef struct{int dia,mes,anio;}fecha;
typedef struct{char sectorEmpleado;}sector;

typedef struct
{
    int legajo;
    char nombre[20];
    char sexo;
    float sueldo;
    int ocupado;
    fecha fn;
    sector sc;

} eEmpleado;

int menu();
void inicializarEmpleados(eEmpleado vec[], int tam);
int buscarLibre(eEmpleado vec[], int tam);
int buscarEmpleado(eEmpleado vec[], int tam, int legajo);
void mostrarEmpleado(eEmpleado emp);
void mostrarEmpleados(eEmpleado vec[], int tam);
void altaEmpleado(eEmpleado vec[], int tam);
void bajaEmpleado(eEmpleado vec[], int tam);
void ModificacionEmpleado(eEmpleado vec[], int tam);
void hardcoreo(eEmpleado vec [], int tam);
void empleadoXanio(eEmpleado vec [], int tam, int anio);
void empleadoXsector(eEmpleado vec[], int tam, char sector);

int main()
{
    char seguir = 's';
    char confirma;
    char auxSector;
    int anios;
    eEmpleado lista[TAM];
    inicializarEmpleados(lista, TAM); // llamada
    hardcoreo(lista, 0);
    do
    {
        switch(menu())
        {

        case 1:
            // printf("\nAlta empleado\n\n");
            altaEmpleado(lista, TAM);
            system("pause");
            break;

        case 2:
            //printf("\nBaja empleado\n\n");
            bajaEmpleado(lista, TAM);
            system("pause");
            break;

        case 3:
            //printf("\nModificacion empleado\n\n");
            ModificacionEmpleado(lista,TAM);
            system("pause");
            break;

        case 4:
            printf("\nOrdenar empleados\n\n");
            system("pause");
            break;

        case 5:
            //printf("\nListar empleados\n\n");
            mostrarEmpleados(lista, TAM);
            system("pause");
            break;

        case 6:
            printf("Informe\n\nIngrese anio a buscar: ");
            scanf("%d",&anios);
            empleadoXanio(lista, TAM,anios);
            system("pause");
            break;
        case 7:
            printf("Informe\n\nSector a buscar: ");
            fflush(stdin);
            scanf("%c",&auxSector);
            auxSector = toupper(auxSector);
            empleadoXsector(lista, TAM,auxSector);
            system("pause");
            break;


        case 8:
            printf("\nConfirma salida s/n?: ");
            fflush(stdin);
            confirma = getche();

            if( tolower(confirma) == 's')
            {
                seguir = 'n';
            }
            break;

        default:
            printf("\n Opcion invalida\n\n");
            system("break");
        }
    }
    while(seguir == 's');

    return 0;
}

void inicializarEmpleados(eEmpleado vec[], int tam)
{

    for(int i=0; i < tam; i++)
    {
        vec[i].ocupado = 0;
    }
}

int menu()
{
    int opcion;

    system("cls");
    printf("  *** ABM Empleados ***\n\n");
    printf("1- Alta Empleado\n");
    printf("2- Baja Empleado\n");
    printf("3- Modificacion Empleado\n");
    printf("4- Ordenar Empleados\n");
    printf("5- Listar Empleados\n");
    printf("6- EmpleadosXanio\n");
    printf("7- EmpleadosXsector\n");
    printf("8- Salir\n\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}

int buscarLibre(eEmpleado vec[], int tam)
{

    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if(vec[i].ocupado == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

int buscarEmpleado(eEmpleado vec[], int tam, int legajo)
{

    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if( vec[i].legajo == legajo && vec[i].ocupado == 1)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

void mostrarEmpleado(eEmpleado emp)
{

    printf("  %d   %s    %c     %.2f    Fecha de ingreso: %02d/%02d/%d Sector: %c\n", emp.legajo, emp.nombre, emp.sexo, emp.sueldo,emp.fn.dia,emp.fn.mes,emp.fn.anio, emp.sc.sectorEmpleado);

}

void mostrarEmpleados(eEmpleado vec[], int tam)
{
    int cont= 0;

    for(int i=0; i < tam; i++)
    {
        if(vec[i].ocupado == 1)
        {

            mostrarEmpleado(vec[i]);
            cont++;
        }
    }
    if(cont == 0)
    {
        printf("No hay empleados que mostrar\n\n");
    }
}

void altaEmpleado(eEmpleado vec[], int tam)
{
    int indice;
    int legajo;
    int esta;

    indice = buscarLibre(vec, tam);

    if(indice == -1)
    {
        printf("No hay lugar\n");
    }
    else
    {

        printf("Ingrese legajo: ");
        scanf("%d", &legajo);

        esta = buscarEmpleado(vec, tam, legajo);

        if( esta == -1)
        {
            vec[indice].legajo = legajo;

            printf("Ingrese nombre: ");
            fflush(stdin);
            gets(vec[indice].nombre);

            printf("Ingrese sexo: ");
            fflush(stdin);
            scanf("%c", &vec[indice].sexo);

            printf("Ingrese sueldo: ");
            scanf("%f", &vec[indice].sueldo);

            printf("Ingrese dia de ingreso: ");
            scanf("%i",&vec[indice].fn.dia);

            printf("Ingrese mes de ingreso: ");
            scanf("%i",&vec[indice].fn.mes);

            printf("Ingrese anio de ingreso: ");
            scanf("%i",&vec[indice].fn.anio);

            printf("Ingrese sector del empleado (A B o C): ");
            fflush(stdin);
            scanf("%c", &vec[indice].sc.sectorEmpleado);
            vec[indice].sc.sectorEmpleado = toupper(vec[indice].sc.sectorEmpleado);



            vec[indice].ocupado = 1;

            printf("\nEl empleado/a ha sido registrado con exito!!!\n\n");

        }
        else
        {

            printf("Ya existe un empleado/a con el legajo %d\n", legajo);

            mostrarEmpleado(vec[esta]);
        }
    }
}

void bajaEmpleado(eEmpleado vec[], int tam){

    int legajo;
    char confirma;
    int esta;

    printf("Ingrese legajo: ");
    scanf("%d", &legajo);

    esta = buscarEmpleado(vec, tam, legajo);

    if( esta == -1){

        printf("\nEl legajo %d no esta registrado en el sistema\n", legajo);
    }
    else{
        mostrarEmpleado(vec[esta]);

        printf("\nConfirma la eliminacion? s/n: ");
        fflush(stdin);
        confirma = tolower(getche());

        if(confirma == 's'){
            vec[esta].ocupado = 0;
        }
        else{
            printf("\nLa eliminacion ha sido cancelada\n");
        }

    }





}

void ModificacionEmpleado(eEmpleado vec[], int tam){

    int legajo;
    char confirma;
    float nuevoSueldo;
    int esta;

    printf("Ingrese legajo: ");
    scanf("%d", &legajo);

    esta = buscarEmpleado(vec, tam, legajo);

    if( esta == -1){

        printf("\nEl legajo %d no esta registrado en el sistema\n", legajo);
    }
    else{
        mostrarEmpleado(vec[esta]);

        printf("\nQuiere cambiar el sueldo? s/n: ");
        fflush(stdin);
        confirma = tolower(getche());

        if(confirma == 's'){
            printf("\nIngrese nuevo sueldo: ");
            scanf("%f", &nuevoSueldo);
            //valido sueldo
            vec[esta].sueldo = nuevoSueldo;
            printf("Sueldo modificado\n");
        }
        else{
            printf("\nNo se ha modificado el sueldo\n");
        }

    }





}

void hardcoreo(eEmpleado vec [], int tam){

    eEmpleado empleado[5] = {
                            {100225, "Alejandro", 'm', 75000, 1, {10,3,1990}},
                            {114521, "Sonia", 'f', 36000, 1, {24,5,2002}},
                            {134529, "Eve",'f', 32000, 1, {19,2,2015}},
                            {201458, "Facu",'m', 16000, 1, {21,10,2014}},
                            {985241, "Rocio",'f', 52000, 1, {4,5,2002}},
                            };
    for(int i = 0; i<tam; i++){
        vec[i] = empleado[i];
        }

}

void empleadoXanio(eEmpleado vec [], int tam, int anio){
    int cont= 0;

    for(int i=0; i < tam; i++)
    {
        if(vec[i].ocupado == 1 && vec[i].fn.anio == anio)
        {

            mostrarEmpleado(vec[i]);
            cont++;
        }
    }
    if(cont == 0)
    {
        printf("No hay empleados que ese anio\n\n");
    }

}

void empleadoXsector(eEmpleado vec[], int tam, char sector){
    int cont= 0;

    for(int i=0; i < tam; i++)
    {
        if(vec[i].ocupado == 1 && vec[i].sc.sectorEmpleado == sector)
        {

            mostrarEmpleado(vec[i]);
            cont++;
        }
    }
    if(cont == 0)
    {
        printf("No hay empleados en ese sector\n\n");
    }



}



