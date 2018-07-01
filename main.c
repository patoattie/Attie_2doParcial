#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "alumnos.h"
#include "../TP4/arraylist/examples/example_4/inc/ArrayList.h"

int main()
{
    ArrayList* arrayAlumnos = al_newArrayList();
    int parseoAlumnos;
    char seguir = 's';
    int opcion;
    int listaAlumnos;

    if(arrayAlumnos != NULL)
    {
        while(seguir == 's')
        {
            system("cls");

            printf("1. Parse del archivo alumnos.csv\n");
            printf("2. Listar Alumnos\n");
            printf("3. Filtrar mayores a 30\n");
            printf("4. Exportar mayores a 30\n\n");
            printf("5. Salir\n");

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

            case 4:
                parseoAlumnos = alumnos_guardarEnArchivo(NOMBRE_ARCHIVO_SALIDA, arrayAlumnos);
                if(parseoAlumnos == 0)
                {
                    printf("Exportacion al archivo OK\n");
                }
                else
                {
                    printf("ERROR en Exportacion\n");
                }
                break;

            case 5:
                seguir = 'n';
                break;

            default:
                printf("Opcion incorrecta, opciones validas desde 1 hasta 5\n");
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
