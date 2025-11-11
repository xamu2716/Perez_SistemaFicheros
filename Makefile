#############################################################################################
# Pontificia Universidad Javeriana
#
# Materia Sistemas Operativos
# Docente: J. Corredor, PhD
# Autor: Xamuel perez
# Fecha: 11-11-2025
# Tema: Sistema de ficheros
#
# Descripción: Automatizacion para la ejecucion de los laboratorios
##############################################################################################
GCC = gcc
FLAGS = 

PROGRAMAS = lab01 lab02

lab01:
	$(GCC) $@.c -o $@ $(FLAGS)

lab02:
	$(GCC) $@.c -o $@ $(FLAGS)

clean:
	$(RM) $(PROGRAMAS)
