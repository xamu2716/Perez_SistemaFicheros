/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Autor: Xamuel perez
 * Fecha: 11/11/2025
 * Tema: Sistema de ficheros
 *
 * Descripción:Programa en C que lea del teclado el nombre de un directorio y muestre en 
 * pantalla los permisos/directorio, ademas, muestra los ficheros del directorio y su
 * fecha de modificacion.
 *********************************************************************************************/
#include <stdio.h>       
#include <string.h>      
#include <time.h>        
#include <dirent.h>      // Funciones para trabajar con directorios
#include <fcntl.h>       // Control de archivos
#include <unistd.h>      
#include <sys/stat.h>    // Información sobre archivos
#include <sys/types.h>   
int main() {
    int er;                      // Variable para almacenar el resultado de la función stat
    char nomdir[100], nomfich[200]; // Arreglos para el nombre del directorio y del archivo completo
    struct stat atr;              // Estructura para guardar los atributos del archivo
    DIR *d;                       // Puntero al directorio que se va a abrir
    struct dirent *rdl;           // Estructura que representa una entrada del directorio
    time_t fecha;                 // Variable para almacenar la fecha y hora actuales

    printf("Nombre directorio:\n");  // Solicita el nombre del directorio
    fgets(nomdir, sizeof(nomdir), stdin); // Lee el nombre del directorio 

    /* Quita el salto de línea final del nombre introducido */
    nomdir[strlen(nomdir) - 1] = '\0';
    fecha = time(&fecha); // Obtiene la hora y fecha actuales del sistema

    /* Intenta abrir el directorio especificado */
    if ((d = opendir(nomdir)) == NULL) {
        printf("No existe ese directorio\n"); // Si no se puede abrir, muestra un mensaje de error
        return -1; // Termina el programa con código de error
    }

    /* Recorre todas las entradas dentro del directorio */
    while ((rdl = readdir(d)) != NULL) {
       
        if ((strcmp(rdl->d_name, ".") != 0) && (strcmp(rdl->d_name, "..") != 0)) {
            strcpy(nomfich, nomdir); // Copia el nombre del directorio base
            strcat(nomfich, "/");    // Añade "/"
            strcat(nomfich, rdl->d_name); // Añade el nombre del archivo actual

            printf("Fichero: %s\n", nomfich); // Muestra la ruta completa del archivo

            er = stat(nomfich, &atr); // Obtiene la información del archivo
            printf("Modo: %o\n", atr.st_mode); // Muestra el modo

            /* Verifica si el propietario tiene permiso de lectura */
            if ((atr.st_mode & 0400) != 0)
                printf("→ Permiso R para propietario\n");//muestra si tiene permisos de propietario
            else
                printf("→ No permiso R para propietario\n");//muestra si tiene permisos de propietario

            /* Comprueba si es un directorio o un archivo regular */
            if (S_ISDIR(atr.st_mode))
                printf("→ Es un directorio\n");//muestra si es un directorio
            else if (S_ISREG(atr.st_mode))//si no es un directorio

            /* Comprueba si el archivo fue modificado en los últimos 10 días */
            if ((fecha - 10 * 24 * 60 * 60) < atr.st_mtime) {
            	//muestra el fichero y la fecha de modificacion
                printf("→ FICHERO: %s - Fecha modificación: %s\n",
                       rdl->d_name, ctime(&atr.st_mtime));
            }
        }
    }

    closedir(d); // Cierra el directorio abierto
    return 0;    // Finaliza el programa 
}

