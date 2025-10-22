// Mini-Proyecto 1: Mover un sprite con el D-Pad y sistema de guardado FAT
// By Azuki Ind.     22-Oct-2025
#include <nds.h>
#include <fat.h>    // No olvides incluiarla en makefile (LIBS	:= -lfat -lnds9)
#include <stdio.h>
#include <time.h>
#include "sistema.h"


// Incluir Sprites y fondos
// #include "gfx/bg.h"
#include "casa.h" // Imagen que generaste por grit

// Definiciones de sprite
#define SPRITE_W 32
#define SPRITE_H 32
#define SCREEN_W 256
#define SCREEN_H 192

// Inicializacion
int main(void) {
    // Configura una consola de texto en la pantalla superior
    consoleDemoInit();       

    // Verificacion e inicializzacion de sistema de archivos
    if (!inicializarFAT()) {
        iprintf("[ERROR] Cant continue. Turn off.\n");
        while (1) swiWaitForVBlank();  // Se queda detenido mostrando el error
        return 1;
    }
    
    // Mensaje de bienvenida/inicio
    iprintf("|==============================|\n");
    iprintf("|        Mini Proyect 1        |\n");
    iprintf("| By Azuki Ind.    22-Oct-2025 |\n");
    iprintf("|==============================|\n");
    
    mostrarHoraActual(); // Muestra la hora de inicio del juego
    iprintf("\nUse el DPad para mover el sprite\n\n");
    
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

        // --- Limitar movimiento dentro de la pantalla ---
        if (x < 0)   x = 0;
        if (y < 0)   y = 0;
        if (x > SCREEN_W - SPRITE_W) x = SCREEN_W - SPRITE_W;
        if (y > SCREEN_H - SPRITE_H) y = SCREEN_H - SPRITE_H;

        // Actualizar sprite
        oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color,
               SPRITE_GFX, -1, false, false, false, false, false);
        oamUpdate(&oamMain);

        swiWaitForVBlank();
    }

    return 0; // Termina el programa
    
}   