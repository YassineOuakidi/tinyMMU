#ifndef MAP_H
#define MAP_H


#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitmap.h"


#define VIRTUAL_MEMORY_SIZE ( 64 * 1024 )
#define PAGE_SIZE ( 1024 )
#define VIRTUAL_NUM_FRAMES ( VIRTUAL_MEMORY_SIZE / PAGE_SIZE)

extern uint8_t PDBR[8][8] ;

uint16_t translate(uint16_t virt);
void map(uint16_t virt);
void unmap(uint16_t virt);

#endif
