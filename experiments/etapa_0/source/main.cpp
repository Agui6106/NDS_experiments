// Librerias necesarias para desarrollo en Nintendo DS
#include <nds.h>
#include <stdio.h>
// Librerias de tercereros
// Librerias propias

int main(void) {
    consoleDemoInit();  // Initialize text console on top screen

    iprintf("Hello, Nintendo DS!\n");
    iprintf("Etapa 0 - First Test\n");

    while (1) {
        swiWaitForVBlank(); // Wait for next frame
        scanKeys();         // Update key input
        int keys = keysDown();
        if (keys & KEY_START) break; // Exit with START button
    }

    return 0;
}
