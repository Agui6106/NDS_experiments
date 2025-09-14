// Librerias requeridas de devkitPro/libnds
#include <nds.h>     
// Librerias de terceros
#include <stdio.h>   
#include "keys.h"

// Constantes de lectura de teclas(botones)
#define TOTAL_KEYS 16   // La DS usa hasta 16 bits en la máscara de teclas

// Inicializacion
int main(void) {
    // Inicializa del sistema  
    int frameCount = 0;             // contador de frames
    int startFrames[TOTAL_KEYS];    // frame en el que se presionó cada tecla
    bool isHeld[TOTAL_KEYS];        // si la tecla está en seguimiento

    // Variables para controlar impresión (no imprimir cada frame)
    uint32_t prevHeld = 0;

    // Inicializar arrays vacios para la lectura de las teclas (16 bit)
    for (int i = 0; i < TOTAL_KEYS; i++) {
        startFrames[i] = 0;
        isHeld[i] = false;
    }
    
    // Configura una consola de texto en la pantalla superior
    consoleDemoInit();       
    // Mensaje de bienvenida/inicio
    iprintf("Etapa 1 - Input: Buttons demo\n");
    iprintf("=======================================\n");
    iprintf("Presiona A/B/X/Y/L/R/Start/Select/D-Pad. START para salir.\n\n");

    // Bucle principal (game loop)
    while (1) {
        // Leer entrada
        scanKeys();                  
        // Usa uint32_t para evitar warnings de conversion (Solo numeros enteros positivos)
        uint32_t down = keysDown(); // teclas presionadas en este frame
        uint32_t held = keysHeld(); // teclas mantenidas
        uint32_t up   = keysUp();   // teclas soltadas

        int cont= 0;

        /*
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

        // Detectar pulsaciones (evento "down")
        if (down & KEY_A)      iprintf("A pressed\n");
        if (down & KEY_B)      iprintf("B pressed\n");
        if (down & KEY_X)      iprintf("X pressed\n");
        if (down & KEY_Y)      iprintf("Y pressed\n");
        if (down & KEY_L)      iprintf("L pressed\n");
        if (down & KEY_R)      iprintf("R pressed\n");
        if (down & KEY_SELECT) iprintf("SELECT pressed\n");
        if (down & KEY_START)  iprintf("START pressed (will exit)\n");
        if (down & KEY_TOUCH)  iprintf("TOUCH pressed (stylus)\n");

        // Mostrar cambios en teclas mantenidas (held) — para evitar spam
        if (held != prevHeld) {
            iprintf("Held mask: 0x%04x\n", (unsigned int) held);
            prevHeld = held;
            cont++;
            if (prevHeld == up)  iprintf("Contador: %d\n", cont);
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
                float seconds = duration / 60.0f; // DS corre a ~60 fps
                iprintf("Tecla %d LIBERADA: %d frames (%.2f s)\n", 
                        i, duration, seconds);
            }
        }

        frameCount++;


        // Detectar release / up (ejemplo: mostrar cuando se suelta Start para salir)
        if (up & KEY_START) {
            iprintf("START released -> exiting\n");
            //break;
        }

        // Esperar al siguiente frame (sincronización VBlank)
        swiWaitForVBlank();
    }

    return 0; // Termina el programa
}   