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

#include <nds.h>
#include <stdio.h>
#include "keys.h"

// Detecta cuando una tecla es presionada (evento "down")
void key_pressed(uint32_t down, uint32_t held, uint32_t up) {
    // Detectar pulsaciones (evento "down")
    if (down & KEY_A)      iprintf("A pressed\n");
    if (down & KEY_B)      iprintf("B pressed\n");
    if (down & KEY_X)      iprintf("X pressed\n");
    if (down & KEY_Y)      iprintf("Y pressed\n");
    if (down & KEY_L)      iprintf("L pressed\n");
    if (down & KEY_R)      iprintf("R pressed\n");
    if (down & KEY_SELECT) iprintf("SELECT pressed\n");
    if (down & KEY_START)  iprintf("START pressed\n");
    if (down & KEY_TOUCH)  iprintf("TOUCH pressed (stylus)\n");
        
/*
    // --- Detectar pulsaciones (evento "down") ---
    for (int i = 0; i < TOTAL_KEYS; i++) {
        uint32_t mask = 1 << i;   // bitmask de la tecla i

        if (down & mask) {
            iprintf("Tecla %d PRESIONADA en frame %d\n", i, frameCount);
        }
    }

    frameCount++;*/
}

// Mostrar cuando 2 o más teclas están siendo mantenidas
void key_detector(uint32_t held) {
    // --- Mostrar cuando 2 o más teclas están siendo mantenidas ---
    // Nombres de teclas para debug (Diccioanario)
    const char* keyNames[] = {
        "A", "B", "SELECT", "START",
        "RIGHT", "LEFT", "UP", "DOWN",
        "R", "L", "X", "Y",
        "TOUCH", "LID", "DEBUG", "UNKNOWN"
    };

    if (held != prevHeld) {
        // Imprimir tecla en hexadecimal
        iprintf("Held mask: 0x%04x\n", (unsigned int) held);

        // Contar e imprimir teclas activas cuántas teclas están siendo mantenidas (Recorrer el array)
        iprintf("Teclas presionadas: ");
        for (int i = 0; i < 16; i++) {
            if (held & (1 << i)) {
                iprintf("[%s] ", keyNames[i]);
            }
        }
        iprintf("\n");


        prevHeld = held;
        }
    
}

// Detecta el tiempo que UNA SOLA tecla ha sido mantenida
void key_hold_time(void) {
    iprintf("--- key_hold_time() ---\n");
    /*
    // Inicializar arrays solo la primera vez
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < TOTAL_KEYS; i++) {
            startFrames[i] = 0;
            isHeld[i] = false;
        }
        initialized = true;
        iprintf("Inicialización de arrays completada.\n");
    }

    // Leer entrada
    scanKeys();                  
    //uint32_t down = keysDown(); 
    //uint32_t held = keysHeld(); 
    //uint32_t up   = keysUp();   

    // --- Mostrar cambios en teclas mantenidas ---
    if (held != prevHeld) {
        iprintf("Held mask: 0x%04x\n", (unsigned int) held);
        prevHeld = held;
    }

    // --- detectar tiempo de teclas presionadas ---
    for (int i = 0; i < TOTAL_KEYS; i++) {
        uint32_t mask = 1 << i;   // bitmask de la tecla i

        if (down & mask) {
            isHeld[i] = true;
            startFrames[i] = frameCount;
            iprintf("Tecla %d PRESIONADA en frame %d\n", i, frameCount);
        }

        if (up & mask && isHeld[i]) {
            isHeld[i] = false;
            int duration = frameCount - startFrames[i];
            float seconds = duration / 60.0f; 
            iprintf("Tecla %d LIBERADA: %d frames (%.2f s)\n", 
                    i, duration, seconds);
        }
    }

    frameCount++; */
}
// Fin de keys.cpp