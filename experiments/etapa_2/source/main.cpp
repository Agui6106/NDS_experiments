// Librerias requeridas de devkitPro/libnds
#include <nds.h>     
// Librerias de terceros
#include <stdio.h>   

// Incluir Sprites y fondos
// #include "gfx/bg.h"
#include "casa.h"

/*
NOTA: Recuerde que los archivos .h y .c generados por grit
deben estar en un directorio declarado en makefile.

Usa el comando: 
grit casa.png -gt -gB8 -gT -p -o casa
para generar los archivos casa.h y casa.c
El flag -gB8 indica 8 bits por pixel (256 colores)
El flag -gT indica que se generen tiles (sprites)
El flag -p indica que se genere la paleta
El flag -o indica el prefijo de los archivos generados

*/

// Inicializacion
int main(void) {
    // Configura una consola de texto en la pantalla superior
    consoleDemoInit();       
    // Mensaje de bienvenida/inicio
    iprintf("================================\n");
    iprintf("Etapa 2 - Load/Control of sprites\n");
    iprintf("By Azuki Ind.     1-Oct-2025\n");
    iprintf("================================\n");
    iprintf("Presiona cualquier boton de la consola.\n\n");

    // Configurar video en la pantalla superior (main) para sprites
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_SPRITE);  

    // Inicializar sistema de sprites
    oamInit(&oamMain, SpriteMapping_1D_32, false);

    // Copiar gráficos de la casa a memoria de sprites
    dmaCopy(casaTiles, SPRITE_GFX, casaTilesLen);
    dmaCopy(casaPal, SPRITE_PALETTE, casaPalLen);

    // Crear sprite
    int x = 100, y = 80;
    oamSet(&oamMain, 
        0,       // ID del sprite
        x, y,    // posición
        0,       // prioridad
        0,       // paleta
        SpriteSize_32x32, 
        SpriteColorFormat_256Color,
        SPRITE_GFX, 
        -1, false, false, false, false, false);

    // Loop principal
    while (1) {
        scanKeys();
        u16 keys = keysHeld();

        if(keys & KEY_LEFT)  x--;
        if(keys & KEY_RIGHT) x++;
        if(keys & KEY_UP)    y--;
        if(keys & KEY_DOWN)  y++;

        // Actualizar sprite
        oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color,
               SPRITE_GFX, -1, false, false, false, false, false);
        oamUpdate(&oamMain);

        swiWaitForVBlank();
    }

    return 0; // Termina el programa
    
}   