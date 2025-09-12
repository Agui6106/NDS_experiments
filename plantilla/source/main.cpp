// ===============================
// Nintendo DS - Plantilla Basica de Programa (Chat GPT Generated. Modified by Owner)
// ===============================
// Este archivo muestra la estructura básica de un programa homebrew
// para Nintendo DS usando devkitPro/libnds.
// Incluye inicialización, bucle principal y puntos clave comentados.

// Librerias requeridas de devkitPro/libnds
#include <nds.h>     // Librería principal de libnds

// Librerias de terceros
#include <stdio.h>   // Para usar iprintf (texto en consola)

// Librerias propias
#include "logic.h"  // Tu archivo de lógica del juego (si tienes uno)

// Función principal (punto de entrada)
int main(void) {
    // -----------------------------
    // 1. Inicialización de IRQs
    // -----------------------------
    //irqInit();               // Inicializa el sistema de interrupciones
    //irqEnable(IRQ_VBLANK);   // Habilita interrupción de VBlank (sincronización de pantalla)

    // -----------------------------
    // 2. Inicialización de pantalla/consola
    // -----------------------------
    consoleDemoInit();       // Configura una consola de texto en la pantalla superior
    iprintf("Nintendo DS Homebrew Template\n");
    iprintf("============================\n");

    // -----------------------------
    // 3. Inicialización de subsistemas opcionales
    // -----------------------------
    // Ejemplos:
    // - Configurar modos de video: videoSetMode(), videoSetModeSub()
    // - Configurar VRAM para sprites: vramSetBankA()
    // - Inicializar OAM: oamInit(&oamMain, SpriteMapping_1D_32, false);
    // - Inicializar audio (ej. maxmod)

    // -----------------------------
    // 4. Bucle principal (game loop)
    // -----------------------------
    while (1) {
        // 4.1 Leer entrada
        scanKeys();                  // Actualiza estado de teclas
        int keys = keysDown();       // Teclas presionadas en este frame
        int held = keysHeld();       // Teclas mantenidas

        // Ejemplo: reaccionar a teclas
        if (keys & KEY_A) {
            iprintf("Tecla A presionada\n");
        }
        if (held & KEY_B) {
            iprintf("Tecla B mantenida\n");
        }
        if (keys & KEY_START) {
            iprintf("Saliendo del programa...\n");
            break; // Terminar bucle
        }

        // 4.2 Actualizar lógica del juego (Tu programas esta parte)
        showMessage();

        // 4.3 Preparar gráficos (sprites/fondos)
        // drawSprites();
        // oamUpdate(&oamMain);

        // 4.4 Sincronizar con VBlank
        swiWaitForVBlank(); // Espera al siguiente frame para evitar tearing
    }

    // -----------------------------
    // 5. Limpieza antes de salir
    // -----------------------------
    // Aquí podrías guardar datos, detener música, liberar recursos...
    // En la mayoría de programas de DS no se hace nada especial.

    return 0;
}
