#ifndef SISTEMA_H
#define SISTEMA_H

#include <nds.h>
#include <fat.h>    // No olvides incluiarla en makefile (LIBS	:= -lfat -lnds9)
#include <time.h>
#include <stdio.h>

// Inicializa la FAT (SD) y muestra mensaje en caso de error
bool inicializarFAT();

// Muestra la hora actual de inicio del juego
void mostrarHoraActual();

#endif
