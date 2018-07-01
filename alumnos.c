#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "alumnos.h"
#include "../TP4/arraylist/examples/example_4/inc/ArrayList.h"

int alumnos_cargarDesdeArchivo(const char* nombreArchivo, ArrayList* arrayAlumnos)
{
    FILE* archivoAlumnos;
    int retorno = -1;
    int parseoArchivo;
    int cerroArchivo;
    int arrayEstaVacio = al_isEmpty(arrayAlumnos);
    char continua;
    int limpiaArray;
    int confirmaParseo = 1;

    if(arrayEstaVacio == 0)
    {
        do
        {
            printf("La carga de Alumnos desde archivo sobreescribira los Alumnos ya cargados. Continua? (S/N): ");
            fflush(stdin);
            scanf("%c", &continua);
            if(toupper(continua) != 'S' && toupper(continua) != 'N')
            {
                printf("Opcion no valida, debe ingresar S o N. Por favor reingrese\n");
            }
        } while(toupper(continua) != 'S' && toupper(continua) != 'N');

        if(toupper(continua) == 'S')
        {
            limpiaArray = al_clear(arrayAlumnos);
            if(limpiaArray < 0)
            {
                printf("Error al limpiar array list\n");
                confirmaParseo = 0; //Error al limpiar arrayList, se cancela
            }
        }
        else
        {
            printf("Parseo cancelado por el usuario\n");
            confirmaParseo = 0; //Cancelado por el usuario
        }
    }
    else if(arrayEstaVacio < 0)
    {
        printf("Array list apunta a NULL\n");
        confirmaParseo = 0; //Cancelado por el usuario
    }

    if(confirmaParseo == 1)
    {
        archivoAlumnos = fopen(nombreArchivo, "r");
        if(archivoAlumnos != NULL)
        {
            parseoArchivo = alumnos_parser(archivoAlumnos, arrayAlumnos);
            cerroArchivo = fclose(archivoAlumnos);

            if(parseoArchivo == 0 && cerroArchivo == 0)
            {
                retorno = 0;
            }
        }
    }

    return retorno;
}

int alumnos_parser(FILE* pFile, ArrayList* pArrayListAlumno)
{
    int retorno = -1;
    int cantidadFilasLeidas = 0;
    int cantidadDatosLeidos;
    Alumno* unAlumno;
    char charEdad[10];
    char charLegajo[10];
    char charSexo[10];
    int agregoAlumno;
    char cabecera[80];
    char nombre[TAM_NOMBRE];
    int guardoDato;

    if(pFile != NULL)
    {
        if(TIENE_ENCABEZADO_ARCHIVO_ALUMNOS == 1)
        {
            //descarto la lectura del encabezado
            fgets(cabecera, 80, pFile);
        }

        while(!feof(pFile))
        {
            unAlumno = alumno_new();
            if(unAlumno != NULL)
            {
                cantidadDatosLeidos = fscanf(pFile, MASACARA_ARCHIVO_ALUMNOS, nombre, charEdad, charLegajo, charSexo);
                if(cantidadDatosLeidos == CANTIDAD_CAMPOS_ARCHIVO_ALUMNOS)
                {
                    guardoDato = alumno_setNombre(unAlumno, nombre);
                    if(guardoDato < 0)
                    {
                        break;
                    }

                    guardoDato = alumno_setEdad(unAlumno, charEdadToEdad(charEdad));
                    if(guardoDato < 0)
                    {
                        break;
                    }

                    guardoDato = alumno_setLegajo(unAlumno, charLegajoToLegajo(charLegajo));
                    if(guardoDato < 0)
                    {
                        break;
                    }

                    guardoDato = alumno_setSexo(unAlumno, charSexoToSexo(charSexo));
                    if(guardoDato < 0)
                    {
                        break;
                    }

                    agregoAlumno = al_add(pArrayListAlumno, unAlumno);
                    if(agregoAlumno < 0) //Hubo error
                    {
                        break;
                    }

                    cantidadFilasLeidas++;
                }
                else //Fin de archivo u otro error
                {
                    break;
                }
            }
            else //Sin memoria
            {
                break;
            }
        }


        if(cantidadFilasLeidas == CANTIDAD_FILAS_ARCHIVO_ALUMNOS)
        {
            retorno = 0;
        }
    }

    return retorno;
}

Alumno* alumno_new(void)
{
    Alumno* returnAux;
    returnAux = (Alumno*)malloc(sizeof(Alumno));
    return returnAux;
}

int alumno_setEdad(Alumno* this, int edad)
{
    int retorno = -1;
    if(edad >= 18 && edad <= 100)
    {
        retorno = 0;
        this->edad = edad;
    }

    return retorno;
}

int alumno_getEdad(Alumno* this)
{
    int edad;
    edad = this->edad;

    return edad;
}

int alumno_setLegajo(Alumno* this, int legajo)
{
    int retorno = -1;
    if(legajo > 0)
    {
        retorno = 0;
        this->legajo = legajo;
    }

    return retorno;
}

int alumno_getLegajo(Alumno* this)
{
    int legajo;
    legajo = this->legajo;

    return legajo;
}

int alumno_setNombre(Alumno* this, const char* nombre)
{
    strcpy(this->nombre, nombre);

    return 0;
}

void alumno_getNombre(Alumno* this, char* nombre)
{
    strcpy(nombre, this->nombre);
}

int alumno_setSexo(Alumno* this, const char sexo)
{
    int retorno = -1;

    if(toupper(sexo) == SEXO_M || toupper(sexo) == SEXO_F)
    {
        retorno = 0;
        this->sexo = toupper(sexo);
    }

    return retorno;
}

char alumno_getSexo(Alumno* this)
{
    char retorno;
    retorno = this->sexo;

    return retorno;
}

int charEdadToEdad(char* charEdad)
{
    int edad;
    edad = atoi(charEdad);

    return edad;
}

int charLegajoToLegajo(char* charLegajo)
{
    int legajo;
    legajo = atoi(charLegajo);

    return legajo;
}

char charSexoToSexo(char* charSexo)
{
    char sexo = toupper(*charSexo);

    if(sexo != SEXO_M && sexo != SEXO_F)
    {
        sexo = ' ';
    }

    return sexo;
}

void alumno_print(Alumno* this)
{
    printf("%s - %d - %d - %c\n", this->nombre, this->edad, this->legajo, this->sexo);
}

int alumno_listar(ArrayList* arrayAlumnos)
{
    int i;
    int retorno = -1;
    Alumno* unAlumno = NULL;

    for(i = 0; i < al_len(arrayAlumnos); i++)
    {
        unAlumno = (Alumno*)al_get(arrayAlumnos, i);
        if(unAlumno != NULL)
        {
            alumno_print(unAlumno);
            retorno = 0;
        }
    }

    return retorno;
}

int alumno_compare(void* pAlumnoA, void* pAlumnoB)
{
    int retorno = 0;
    Alumno* alumnoA = (Alumno*) pAlumnoA;
    Alumno* alumnoB = (Alumno*) pAlumnoB;

    if(alumnoA != NULL && alumnoB != NULL)
    {
        if(alumnoA->edad < alumnoB->edad)
        {
            retorno = -1;
        }
        else if(alumnoA->edad > alumnoB->edad)
        {
            retorno = 1;
        }
    }

    return retorno;
}

int alumno_listarOrdenado(ArrayList* arrayAlumnos)
{
    int retorno = -1;
    ArrayList* arrayCopia;

    if(al_isEmpty(arrayAlumnos) == 0)
    {
        arrayCopia = al_clone(arrayAlumnos);
        al_sort(arrayCopia, alumno_compare, 1);
        retorno = alumno_listar(arrayCopia);
        al_deleteArrayList(arrayCopia);
    }

    return retorno;
}

int alumno_filtrar(void* item)
{
    int retorno = 0;
    Alumno* unAlumno;

    if(item != NULL)
    {
        unAlumno = (Alumno*) item;
        if(alumno_getEdad(unAlumno) > 30)
        {
            retorno = 1;
        }
    }

    return retorno;
}

int alumno_listarFiltrado(ArrayList* arrayAlumnos)
{
    int retorno = -1;
    ArrayList* arrayCopia;

    if(al_isEmpty(arrayAlumnos) == 0)
    {
        arrayCopia = al_filter(arrayAlumnos, alumno_filtrar);
        al_sort(arrayCopia, alumno_compare, 1);
        retorno = alumno_listar(arrayCopia);
        al_deleteArrayList(arrayCopia);
    }

    return retorno;
}

int alumnos_guardarEnArchivo(const char* nombreArchivo, ArrayList* arrayAlumnos)
{
    FILE* archivoAlumnos;
    int retorno = -1;
    int cerroArchivo;
    char salida[80];
    char charEdad[10];
    char charLegajo[10];
    char charSexo[10];
    char nombre[TAM_NOMBRE];
    int i;
    Alumno* unAlumno = NULL;
    int cantidadGuardada;
    int longitudCadena;
    int huboError = 0;
    ArrayList* arrayCopia;

    if(al_isEmpty(arrayAlumnos) == 0)
    {
        arrayCopia = al_filter(arrayAlumnos, alumno_filtrar);
        al_sort(arrayCopia, alumno_compare, 1);
        archivoAlumnos = fopen(nombreArchivo, "w");
        if(archivoAlumnos != NULL)
        {
            for(i = 0; i < al_len(arrayCopia); i++)
            {
                unAlumno = (Alumno*)al_get(arrayCopia, i);

                alumno_getNombre(unAlumno, nombre);
                sprintf(charEdad, "%d", alumno_getEdad(unAlumno));
                sprintf(charLegajo, "%d", alumno_getLegajo(unAlumno));
                sprintf(charSexo, "%c", alumno_getSexo(unAlumno));

                strcpy(salida, nombre);
                strcat(salida, SEPARADOR_ARCHIVO_SALIDA);
                strcat(salida, charEdad);
                strcat(salida, SEPARADOR_ARCHIVO_SALIDA);
                strcat(salida, charLegajo);
                strcat(salida, SEPARADOR_ARCHIVO_SALIDA);
                strcat(salida, charSexo);
                strcat(salida, "\n");

                longitudCadena = strlen(salida);
                cantidadGuardada = fwrite(salida, sizeof(char), longitudCadena, archivoAlumnos);
                if(cantidadGuardada != longitudCadena)
                {
                    huboError = 1;
                    break;
                }
            }

            cerroArchivo = fclose(archivoAlumnos);
            al_deleteArrayList(arrayCopia);

            if(cerroArchivo == 0 && huboError == 0)
            {
                retorno = 0;
            }
        }
    }

    return retorno;
}
