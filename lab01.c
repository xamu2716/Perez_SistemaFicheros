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
 * pantalla el nombre y el tamaño de los ficheros que contiene
 *********************************************************************************************/
#include <sys/types.h>   
#include <sys/stat.h>    // Permite obtener información de archivos
#include <sys/mman.h>    // Proporciona funciones para manejo de memoria
#include <fcntl.h>       // Define constantes para control de archivos
#include <stdio.h>       
#include <unistd.h>     
#include <stdlib.h>      
#include <string.h>      // Funciones para manipulación de cadenas 
#include <dirent.h>      // Permite trabajar con directorios


int main() {
    DIR *d; // Puntero al directorio que se va a abrir
    char nomdir[90], nomfich[90]; // Variables para el nombre del directorio y del fichero
    struct stat datos; // Estructura para almacenar información del archivo
    struct dirent *direc; // Estructura para leer las entradas del directorio

    printf("Introduzca el Nombre de un Directorio: "); // Solicita al usuario el nombre del directorio
    fgets(nomdir, sizeof(nomdir), stdin); // Lee el nombre del directorio desde teclado
    nomdir[strlen(nomdir) - 1] = '\0'; // Elimina el salto de línea '\n' al final del nombre

    if ((d = opendir(nomdir)) == NULL) { // Intenta abrir el directorio; si falla, devuelve NULL
        printf("El directorio no existe\n"); // Mensaje de error si no existe
        return -1; // Termina el programa con código de error
    }

    while ((direc = readdir(d)) != NULL) { // Recorre todas las entradas del directorio
        strcpy(nomfich, nomdir); // Copia el nombre del directorio a la variable nomfich
        strcat(nomfich, "/"); // Añade una barra para formar la ruta completa
        strcat(nomfich, direc->d_name); // Añade el nombre del archivo 
        stat(nomfich, &datos); // Obtiene la información del archivo

        if (S_ISREG(datos.st_mode)) // Comprueba si es un archivo regular
            printf("Nombre: %s\t| Tamaño: %ld\n", direc->d_name, datos.st_size); // Muestra nombre y tamaño
    } /* Fin del while */

    closedir(d); // Cierra el directorio abierto
}


