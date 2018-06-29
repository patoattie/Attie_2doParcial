#ifndef ALUMNOS_H_INCLUDED
#define ALUMNOS_H_INCLUDED

#include "../TP4/arraylist/examples/example_4/inc/ArrayList.h"

#define NOMBRE_ARCHIVO_ALUMNOS "alumnos.csv"
#define TAM_NOMBRE 50
#define MASACARA_ARCHIVO_ALUMNOS "%[^,],%[^,],%[^,],%[^\n]\n"
#define CANTIDAD_CAMPOS_ARCHIVO_ALUMNOS 4
#define TIENE_ENCABEZADO_ARCHIVO_ALUMNOS 1
#define CANTIDAD_FILAS_ARCHIVO_ALUMNOS 10
#define SEXO_M 'M'
#define SEXO_F 'F'

typedef struct
{
    char nombre[TAM_NOMBRE];
    int edad;
    int legajo;
    char sexo;
} Alumno;

int alumnos_cargarDesdeArchivo(const char* nombreArchivo, ArrayList* arrayAlumnos);
int alumnos_parser(FILE* pFile, ArrayList* pArrayListAlumno);
Alumno* alumno_new(void);
int alumno_setEdad(Alumno* this, int edad);
int alumno_getEdad(Alumno* this);
int alumno_setLegajo(Alumno* this, int legajo);
int alumno_getLegajo(Alumno* this);
int alumno_setNombre(Alumno* this, const char* nombre);
char* alumno_getNombre(Alumno* this);
int alumno_setSexo(Alumno* this, const char sexo);
char alumno_getSexo(Alumno* this);
int charEdadToEdad(char* charEdad);
int charLegajoToLegajo(char* charLegajo);
char charSexoToSexo(char* charSexo);
void alumno_print(Alumno* this);
int alumno_listar(ArrayList* arrayAlumnos);

#endif // ALUMNOS_H_INCLUDED
