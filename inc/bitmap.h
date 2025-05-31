#ifndef BITMAP_H
#define BITMAP_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "mapping.h"


#define PHYSICAL_MEMORY_SIZE ( 16 * 1024 )
#define FRAME_SIZE ( 1024 )
#define PHYSICAL_NUM_FRAMES (PHYSICAL_MEMORY_SIZE / FRAME_SIZE)

extern uint8_t memory[PHYSICAL_NUM_FRAMES];

void pmm_init(void);
int pmm_alloc_frame(void);
int pmm_free_frame(size_t index);

void bitmap_init();
void bitmap_clear();
void bitmap_get_status(size_t index);
void bitmap_print();

int frame_alloc();
int frame_free(size_t index);




#endif
