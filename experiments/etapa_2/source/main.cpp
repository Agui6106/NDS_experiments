// Librerias requeridas de devkitPro/libnds
#include <nds.h>     
// Librerias de terceros
#include <stdio.h>   

// Inicializacion
int main(void) {
    // Configura una consola de texto en la pantalla superior
    consoleDemoInit();       
    // Mensaje de bienvenida/inicio
    iprintf("================================\n");
    iprintf("Etapa 2 - Load of sprites\n");
    iprintf("By Azuki Ind.     1-Oct-2025\n");
    iprintf("================================\n");
    iprintf("Presiona cualquier boton de la consola.\n\n");

    // Bucle principal (game loop)
    while (1) {
        // Leer entrada
        scanKeys();                  
        uint32_t down = keysDown(); 
        uint32_t held = keysHeld(); 
        uint32_t up   = keysUp();   

        //key_pressed(down, held, up);
        key_detector(held);
        key_hold_time(down, held, up);

        // Esperar al siguiente frame (sincronización VBlank)
        swiWaitForVBlank();
    }

    return 0; // Termina el programa
}   