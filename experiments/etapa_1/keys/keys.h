#ifndef KEYS_H
#define KEYS_H
#include <nds.h>

// Constantes de lectura de teclas(botones)
#define TOTAL_KEYS 16   // La DS usa hasta 16 bits en la máscara de teclas

// Prototipos de funciones
void key_pressed(uint32_t down, uint32_t held, uint32_t up);
void key_detector(uint32_t held);
void key_hold_time(uint32_t down, uint32_t held, uint32_t up);

#endif