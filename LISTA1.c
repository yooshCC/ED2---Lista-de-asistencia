#include <stdio.h>
#include <stdlib.h>

//Estructura para el registro de las asistencias de C/u de los Alumnos
    typedef struct History
    {
        int dia, mes, ano;
        int asistencia_to_day;
        struct History* sig;
    }Historial;

//Estrcutura para cada alumno
    typedef struct Lista_A
    {
        char name_Alumno[50];
        int total_Asistencia;
        Historial* historial_Academico;
        struct Lista_A* sig; 
    }Lista;

//Estructura Principal
    typedef struct
    {
        int no_Alumnos;
        char name_Curso[50];
        struct Lista* curso;
    }Tcurso;