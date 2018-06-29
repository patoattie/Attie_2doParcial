#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "alumnos.h"
#include "../TP4/arraylist/examples/example_4/inc/ArrayList.h"

/*
1) Crear el archivo alumnos.csv, que va a contener la informacion de diez alumnos (Nombre, Edad, Legajo, Sexo),
   los cuales deben ser creados de manera dinamica y almacenados en un arraylist.
2) Listar los alumnos del arraylist ordenados por edad.
*/

int main()
{
    ArrayList* arrayAlumnos = al_newArrayList();
    int parseoAlumnos;
    char seguir = 's';
    int opcion;
    int listaAlumnos;
    /*int cargaEmpleado;
    int ordenaLista;
    int arrayEstaVacio;
    int borraEmpleado;
    int indiceDesde;
    int indiceHasta;*/

    if(arrayAlumnos != NULL)
    {
        while(seguir == 's')
        {
            system("cls");

            printf("1. Parse del archivo alumnos.csv\n");
            printf("2. Listar Alumnos\n");
            printf("3. Filtrar mayores a 30\n");
            /*printf("4. Agregar un elemento\n");
            printf("5. Elimina un elemento\n");
            printf("6. Listar Empleados (Desde/Hasta)\n\n");*/
            printf("7. Salir\n");

            scanf("%d", &opcion);

            switch(opcion)
            {
            case 1:
                parseoAlumnos = alumnos_cargarDesdeArchivo(NOMBRE_ARCHIVO_ALUMNOS, arrayAlumnos);
                if(parseoAlumnos == 0)
                {
                    printf("Parse del archivo OK\n");
                }
                else
                {
                    printf("ERROR en Parse\n");
                }
                break;

            case 2:
                listaAlumnos = alumno_listarOrdenado(arrayAlumnos);
                if(listaAlumnos < 0)
                {
                    printf("No hay Alumnos cargados\n");
                }
                break;

            case 3:
                listaAlumnos = alumno_listarFiltrado(arrayAlumnos);
                if(listaAlumnos < 0)
                {
                    printf("No hay Alumnos cargados\n");
                }
                break;
/*
            case 4:
                cargaEmpleado = employee_agregar(arrayEmpleados);
                if(cargaEmpleado == 1)
                {
                    printf("Alta de Empleado OK\n");
                }
                else
                {
                    printf("Error al cargar empleado\n");
                }
                break;

            case 5:
                listaEmpleados = employee_listar(arrayEmpleados);
                if(listaEmpleados < 1)
                {
                    printf("No hay Empleados cargados\n");
                }
                else
                {
                    borraEmpleado = employee_borrar(arrayEmpleados);
                    if(borraEmpleado == 1)
                    {
                        printf("Baja de Empleado OK\n");
                    }
                    else
                    {
                        printf("Error al borrar empleado\n");
                    }
                }
                break;

            case 6:
                arrayEstaVacio = al_isEmpty(arrayEmpleados);
                if(arrayEstaVacio == 0)
                {
                    do
                    {
                        indiceDesde = pedirEnteroSinValidar("Ingrese indice desde el cual listar Empleados: ");
                        if(indiceDesde < 0)
                        {
                            printf("El indice desde el cual listar no puede ser negativo\n");
                        }
                    } while(indiceDesde < 0);

                    do
                    {
                        indiceHasta = pedirEnteroSinValidar("Ingrese indice hasta el cual listar Empleados: ");
                        if(indiceHasta < 0)
                        {
                            printf("El indice hasta el cual listar no puede ser negativo\n");
                        }
                    } while(indiceHasta < 0);

                    if(indiceDesde <= indiceHasta)
                    {
                        listaEmpleados = employee_subConjunto(arrayEmpleados, indiceDesde, indiceHasta);
                        if(listaEmpleados < 1)
                        {
                            printf("No hay Empleados cargados\n");
                        }
                    }
                    else
                    {
                        printf("El indice desde no puede ser mayor al indice hasta\n");
                    }
                }
                else
                {
                    printf("No hay Empleados cargados\n");
                }
                break;
*/
            case 7:
                seguir = 'n';
                break;

            default:
                printf("Opcion incorrecta, opciones validas desde 1 hasta 7\n");
            }

            if(seguir == 's')
            {
                system("pause");
            }
        }

    }
    else
    {
        printf("ERROR. No se puede crear la lista de Alumnos en memoria\n");
    }

    return 0;
}
