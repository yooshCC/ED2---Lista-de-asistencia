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

// Función para crear un nuevo grupo, ahora devuelve un apuntador a Tcurso
Tcurso* new_grupo()
{
    Tcurso* cab = (Tcurso*)malloc(sizeof(Tcurso));
    if (cab == NULL)
    {
        printf("Error: No se pudo asignar memoria.\n");
        return NULL;
    }
    
    cab->curso = NULL;

    printf("Nombre del grupo: ");
    gets(cab->name_Curso);

    printf("Numero de alumnos: ");
    scanf("%d", &cab->no_Alumnos);
    
    printf("\tCreando el curso. . .\n");

    Lista* tem = NULL;
    for(int cont=0; cont<cab->no_Alumnos; cont++)
    {
        Lista* new_alumno = (Lista*)malloc(sizeof(Lista));
        if(new_alumno == NULL)
        {
            printf("Error");
            break;
        }

        printf("\tNombre del Alumno:");
        scanf(" %s", new_alumno->name_Alumno);
        new_alumno->total_Asistencia= 0;
        new_alumno->historial_Academico= NULL;
        new_alumno->sig= NULL;

        if(cab->curso==NULL)
        {
            cab->curso = new_alumno;
            tem = cab->curso;
        }else{
            tem->sig = new_alumno;
            tem = new_alumno;
        }
    }
    return cab;
}

void pasar_lista(Tcurso* curso)
{
    int d, m, n;
    // Obtener la fecha actual para el registro
    printf("INGRESA DIA: ");
    scanf("%d", &d);
    printf("INGRESA MES: ");
    scanf("%d", &m);
    printf("INGRESA ANO: ");
    scanf("%d", &n);

    Lista* temp_alumno = curso->curso;
    int asistencia;
    
    printf("\n- - - - - Pasando lista del curso: %s - - - - -\n", curso->name_Curso);

    while (temp_alumno != NULL)
    {
        printf("Asistencia de %s (1/ Si, 0/ No): ", temp_alumno->name_Alumno);
        scanf("%d", &asistencia);
        while (getchar() != '\n');

        // Crear un nuevo nodo de historial para este dia
        Historial* nuevo_historial = (Historial*)malloc(sizeof(Historial));
        if (nuevo_historial == NULL)
        {
            printf("Error\n");
            return;
        }

        nuevo_historial->dia = d;
        nuevo_historial->mes = m;
        nuevo_historial->ano = n;
        nuevo_historial->asistencia_to_day = asistencia;
        
        nuevo_historial->sig = temp_alumno->historial_Academico;
        temp_alumno->historial_Academico = nuevo_historial;

        if (asistencia == 1) {
            temp_alumno->total_Asistencia++;
        }

        temp_alumno = temp_alumno->sig;
    }
    printf("Lista completada.\n");
}


void menu(Tcurso** cab)
{
    int opt = 0;
    while (opt != 4)
    {
        printf("\n- - - - - Menu - - - - -\n");
        printf("1) Crear un curso nuevo\n");
        printf("2) Pasar lista\n");
        printf("3) Mostrar lista\n");
        printf("4) Salir\n"); 
        printf("Seleccione una opcion: ");
        
        scanf("%d", &opt);
        
        while (getchar() != '\n');

        switch (opt)
        {
            case 1:
                if (*cab != NULL)
                    printf("Ya existe un curso. Elimine el curso o seleccioanr otra opcion.\n");
                    else
                        *cab = new_grupo();
                
                break;
            case 2:
                if (*cab != NULL)
                    pasar_lista(*cab);
                    else
                        printf("No existe un curso.\n");
                break;
            case 3:
                if (*cab != NULL)
                    Mostrarlista(*cab);
                    else
                        printf("No existe un curso.\n");
            break;
            case 4:
                printf("Saliendo. . .\n");
                break;
            default:
                printf("Opcion invalida. Por favor, intente de nuevo.\n");
                break;
        }
    }
}

void Mostrarlista(Tcurso* curso)
{
    if (curso == NULL)
    {
        printf("No hay curso para mostrar.\n");
        return;
    }

    printf("\n- - - - - Curso: %s - - - - -\n", curso->name_Curso);
    Lista* temp_alumno = curso->curso;

    while (temp_alumno != NULL)
    {
        printf("Alumno: %s, Total Asistencias: %d\n", temp_alumno->name_Alumno, temp_alumno->total_Asistencia);
        
        Historial* temp_historial = temp_alumno->historial_Academico;
        while (temp_historial != NULL)
        {
            printf("  Fecha: %02d/%02d/%04d, Asistencia: %s\n", 
                   temp_historial->dia, 
                   temp_historial->mes, 
                   temp_historial->ano, 
                   temp_historial->asistencia_to_day ? "Presente" : "Ausente");
            temp_historial = temp_historial->sig;
        }
        temp_alumno = temp_alumno->sig;
    }
}


int main()
{
    Tcurso* grupo = NULL;
    
    menu(&grupo);

    if (grupo != NULL) {
        free(grupo);
        printf("Memoria liberada.\n");
    }
    printf("Programa finalizado :)\n");
    return 0;
}