// sistema.cpp
// Funciones para manejo del sistema FAT y hora
#include "sistema.h"

// Inicializa la FAT (SD) y muestra mensaje en caso de error
bool inicializarFAT() {
    if (!fatInitDefault()) {
        iprintf("[ERROR]: No se pudo inicializar el sistema FAT.\n");
        iprintf("Inserta una tarjeta SD válida y reinicia la consola.\n");
        return false;
    }
    return true;
}

// Muestra la hora actual (Interna de la consola) de inicio del juego
void mostrarHoraActual() {
    time_t rawTime;
    time(&rawTime);
    struct tm* timeInfo = localtime(&rawTime);

    if (timeInfo != NULL) {
        iprintf("Started on: %02d/%02d/%04d %02d:%02d:%02d\n",
            timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900,
            timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    } else {
        iprintf("[WARN]: No se pudo obtener la hora actual.\n");
    }
}
