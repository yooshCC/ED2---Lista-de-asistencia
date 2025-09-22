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

void menu(Tcurso** cab)
{
    int opt = 0;
    while (opt != 4)
    {
        printf("\n- - - - - Menu - - - - -\n");
        printf("1) Crear un curso nuevo\n");
        printf("2) Pasar lista (No implementado)\n");
        printf("3) Editar un grupo (No implementado)\n");
        printf("4) Salir\n"); 
        printf("Seleccione una opcion: ");
        
        scanf("%d", &opt);
        
        while (getchar() != '\n');

        switch (opt)
        {
            case 1:
                if (*cab != NULL)
                {
                    printf("Ya existe un curso. Elimine el curso o seleccioanr otra opcion.\n");
                }
                else{
                    *cab = new_grupo();
                }
                break;
            case 2:
                if (*cab != NULL)
                {
                    printf("Pasando lista del curso: %s\n", (*cab)->name_Curso);
                    // FUNCION PASAR LISTA
                }else{
                    printf("No existe un curso.\n");
                }
                break;
            case 3:
                    //FUNCION PARA EDITAR UN CURSO
                printf("Funcion de edicion aun no implementada.\n");
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


int main()
{
    Tcurso* grupo = NULL;
    
    menu(&grupo);

    if (grupo != NULL) {
        free(grupo);
        printf("Memoria liberada.\n");
    }

    return 0;
}