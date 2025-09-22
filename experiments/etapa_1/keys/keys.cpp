/*
    keys.cpp
    By Azuki Industries, 2025
    License: Free Source.

    Funciones para manejo de entrada de botones (keys)
    - key_pressed(): Detecta pulsaciones (evento "down")
    - hold_more_keys(): Muestra cuando 2 o más teclas están siendo mantenidas
    - key_hold_time(): Detecta el tiempo que una tecla ha sido mantenida
    Cada función puede ser llamada desde el main loop.


    NOTA DEL DESAROLALDOR:
    Las funciones de entrada: keysDown, keysHeld y keysUp. Regresan una máscara de bits
    donde cada bit representa una tecla. Puedes usar operadores AND (&) para verificar.

    Cada mascara representa:
    KEY_A        0x0001
    KEY_B        0x0002
    KEY_SELECT   0x0004
    KEY_START    0x0008
    KEY_RIGHT    0x0010
    KEY_LEFT     0x0020
    KEY_UP       0x0040
    KEY_DOWN     0x0080
    KEY_R        0x0100
    KEY_L        0x0200
    KEY_X        0x0400
    KEY_Y        0x0800
    KEY_TOUCH    0x1000 (stylus)

    Dependiendo de tu logica, puedes usar cualquiera de las 3 funciones.
    IMPORTANTE: Cadda funcion solo detecta un evento por frame.
*/

// Librerias
#include <nds.h>
#include <stdio.h>
#include "keys.h"

// Variables globales
// Nombres de teclas para debug (Diccioanario)
const char* keyNames[] = {
    "A", "B", "SELECT", "START",
    "RIGHT", "LEFT", "UP", "DOWN",
    "R", "L", "X", "Y",
    "TOUCH", "LID", "DEBUG", "UNKNOWN"
};

// Variables estáticas que persisten entre llamadas
static int frameCount = 0;
static int startFrames[TOTAL_KEYS];
static bool isHeld[TOTAL_KEYS];
static uint32_t prevHeld = 0;
static bool initialized = false;

// Detecta cuando una tecla es presionada (evento "down")
void key_pressed(uint32_t down, uint32_t held, uint32_t up) {
    // Puedes cambiarlo a un return para obtener la tecla que fue presionada
    if (down & KEY_A)      iprintf("A pressed\n");
    if (down & KEY_B)      iprintf("B pressed\n");
    if (down & KEY_X)      iprintf("X pressed\n");
    if (down & KEY_Y)      iprintf("Y pressed\n");
    if (down & KEY_L)      iprintf("L pressed\n");
    if (down & KEY_R)      iprintf("R pressed\n");
    if (down & KEY_SELECT) iprintf("SELECT pressed\n");
    if (down & KEY_START)  iprintf("START pressed\n");
    if (down & KEY_TOUCH)  iprintf("TOUCH pressed (stylus)\n");
    if (down & KEY_UP)     iprintf("UP pressed\n");
    if (down & KEY_DOWN)   iprintf("DOWN pressed\n");
    if (down & KEY_LEFT)   iprintf("LEFT pressed\n");
    if (down & KEY_RIGHT)  iprintf("RIGHT pressed\n");
        
}

// Mostrar cuando 2 o más teclas están siendo mantenidas
void key_detector(uint32_t held) {
    // --- Mostrar cuando 2 o más teclas están siendo mantenidas ---
    if (held != prevHeld) {
        // Imprimir tecla en hexadecimal
        iprintf("Held mask: 0x%04x\n", (unsigned int) held);

        // Contar e imprimir teclas activas cuántas teclas están siendo mantenidas (Recorrer el array)
        for (int i = 0; i < 16; i++) {
            if (held & (1 << i)) {
                iprintf("Teclas presionadas: [%s]\n", keyNames[i]);
            }
        }

        prevHeld = held;
        }
    
}

// Detecta el tiempo que UNA SOLA tecla ha sido mantenida
void key_hold_time(uint32_t down, uint32_t held, uint32_t up) {
    //iprintf("--- key_hold_time() ---\n");
    // Inicializar arrays contadores
    if (!initialized) {
        for (int i = 0; i < TOTAL_KEYS; i++) {
            startFrames[i] = 0;
            isHeld[i] = false;
        }
        initialized = true;
        iprintf("Array created succesfully :D\n\n");
    }
          /*  
    // Solo imprimir la máscara si cambió (evita spam)
    if (held != prevHeld) {
        //iprintf("Held mask: 0x%04x    ", (unsigned int) held);
        // Imprimir nombres de teclas actualmente mantenidas
        iprintf("Teclas: ");
        int count = 0;
        // Recorrer el array de teclas y contar cuántas están siendo mantenidas
        for (int i = 0; i < TOTAL_KEYS; i++) {
            if (held & (1u << i)) {
                iprintf("[%s] ", keyNames[i]);
                count++;
            }
        }
        iprintf(" (count=%d)\n", count);
        prevHeld = held;
    }*/

    // Para cada tecla: registrar inicio en 'down', medir duración en 'up'
    for (int i = 0; i < TOTAL_KEYS; i++) {
        uint32_t mask = (1u << i);

        if (down & mask) { // Si es presionada...
            // Guarda el frame actual
            isHeld[i] = true;
            startFrames[i] = frameCount;
            // Si quieres ver el frame donde se presionod:
            // iprintf("Tecla %s PRESIONADA en frame %d\n", keyNames[i], frameCount);
        }

        if ((up & mask) && isHeld[i]) { // Si es soltada...
            // Calcular duración de esta pulsación solamente
            isHeld[i] = false;
            int duration = frameCount - startFrames[i];
            //float seconds = duration / 60.0f; // ~60 fps
            int ms = (int)((duration * 1000) / 60); // milisegundos
            iprintf("[%s] hold by: %d frames\nAprox: %d ms)\n",
                    keyNames[i], duration, ms);

            // Reiniciar contador de ese botón (preparado para próxima pulsación)
            startFrames[i] = 0;
        }
    }

    // aumentar contador global de frames (llamar cada frame desde main)
    frameCount++;

}
// Fin de keys.cpp