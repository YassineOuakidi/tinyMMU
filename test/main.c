// test/main.c

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/bitmap.h"
#include "../inc/mapping.h"

#define TEST_MEM_DUMP()  \
    do {                                         \
        printf("Current PDBR state:\n");         \
        for (int i = 0; i < 8; i++) {            \
            for (int j = 0; j < 8; j++){         \
                printf("%3d ", PDBR[i][j]);      \
            }                                    \
            printf("\n");                        \
        }                                        \
        printf("\n");                            \
    } while (0)

int main(void) {
    printf("=== Physical Memory Manager & Two-Level Paging Test Suite ===\n\n");

    // ------------------------------------------------------------------------
    // 1) Initialize PMM and Paging Structures
    // ------------------------------------------------------------------------
    printf("[1] Initializing PMM and Paging Structures...\n");
    pmm_init();          // Initialize the physical memory manager
    // Initialize all PDBR entries to -1 (unmapped)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            PDBR[i][j] = 0xFF; //UNMAPPED
        }
    }
    TEST_MEM_DUMP();
    printf("    PMM & PDBR initialized.\n\n");

    // ------------------------------------------------------------------------
    // 2) Test frame_alloc() until exhaustion
    // ------------------------------------------------------------------------
    printf("[2] Allocating all physical frames one by one...\n");
    int allocated_frames[PHYSICAL_NUM_FRAMES];
    for (int i = 0; i < PHYSICAL_NUM_FRAMES; i++) {
        int f = pmm_alloc_frame();
        allocated_frames[i] = f;
        if (f >= 0) {
            printf("    frame_alloc() -> frame %d allocated\n", f);
        } else {
            printf("    frame_alloc() -> ERROR: no free frames (iteration %d)\n", i);
        }
    }

    // Attempt one more allocation (should fail)
    int f_extra = pmm_alloc_frame();
    if (f_extra == -1) {
        printf("    frame_alloc() after exhaustion -> returned -1 as expected\n\n");
    } else {
        printf("    frame_alloc() after exhaustion -> ERROR: returned %d\n\n", f_extra);
    }
    TEST_MEM_DUMP();
    // ------------------------------------------------------------------------
    // 3) Free one frame and re-allocate it
    // ------------------------------------------------------------------------
    if (PHYSICAL_NUM_FRAMES > 0) {
        int idx_to_free = allocated_frames[PHYSICAL_NUM_FRAMES - 1];
        printf("[3] Freeing frame %d and re-allocating...\n", idx_to_free);
        int ret = frame_free(idx_to_free);
        if (ret == 0) {
            printf("    frame_free(%d) succeeded\n", idx_to_free);
        } else {
            printf("    frame_free(%d) FAILED\n", idx_to_free);
        }
        int f_realloc = frame_alloc();
        if (f_realloc == idx_to_free) {
            printf("    frame_alloc() -> re-allocated frame %d as expected\n\n", f_realloc);
        } else {
            printf("    frame_alloc() -> ERROR: re-allocated frame %d (expected %d)\n\n",
                   f_realloc, idx_to_free);
        }
    }
    printf("Freeing all the frames ...\n\n");
    for(size_t i = 0 ; i <= 15 ; i++)
	
	pmm_free_frame(i);
    
    TEST_MEM_DUMP();
    // ------------------------------------------------------------------------
    // 4) Test map(), translate(), and unmap()
    // ------------------------------------------------------------------------
    printf("[4] Testing map(), translate(), and unmap()...\n");

    // Helper lambda to attempt translation and print result
    #define TRY_TRANSLATE(addr)                                                       \
        do {                                                                          \
            uint16_t phys;                                                            \
            uint16_t ret = translate(addr);                                           \
            if (ret == (uint16_t)-1) {                                                \
                printf("    translate(0x%04X) -> ERROR: unmapped\n", addr);           \
            } else {                                                                  \
                phys = ret;                                                           \
                printf("    translate(0x%04X) -> 0x%04X (decimal %u)\n",              \
                       addr, phys, phys);                                             \
            }                                                                         \
        } while (0)

    // 4a) Attempt to translate an unmapped address
    printf("    [4a] Translating unmapped virtual address 0x0005...\n");
    TRY_TRANSLATE(0x0005);
    printf("\n");

    // 4b) Map a few virtual addresses
    uint16_t test_addrs[] = { 0x0000, 0x03FF, 0x0400, 0x1000, 0x1ABC, 0x3FFF };
    size_t num_test_addrs = sizeof(test_addrs) / sizeof(test_addrs[0]);

    for (size_t i = 0; i < num_test_addrs; i++) {
        uint16_t v = test_addrs[i];
        printf("    map(0x%04X)...\n", v);
        map(v);
    }
    printf("\n");

    // 4c) Dump the PDBR after mapping
    printf("    [4c] PDBR After Initial Mapping:\n");
    TEST_MEM_DUMP();

    // 4d) Translate the addresses we just mapped
    printf("    [4d] Translating addresses after mapping:\n");
    for (size_t i = 0; i < num_test_addrs; i++) {
        TRY_TRANSLATE(test_addrs[i]);
    }
    printf("\n");

    // 4e) Attempt to map a virtual address twice (should indicate already mapped)
    uint16_t duplicate_vaddr = test_addrs[2]; // 0x0400
    printf("    [4e] Attempting to map 0x%04X again...\n", duplicate_vaddr);
    map(duplicate_vaddr);
    printf("\n");

    // 4f) Unmap a couple of virtual addresses
    uint16_t to_unmap1 = 0x0000;
    uint16_t to_unmap2 = 0x1000;
    printf("    [4f] Unmapping 0x%04X and 0x%04X...\n", to_unmap1, to_unmap2);
    unmap(to_unmap1);
    unmap(to_unmap2);
    printf("\n");

    // 4g) Dump PDBR after unmapping
    printf("    [4g] PDBR After Unmapping:\n");
    TEST_MEM_DUMP();

    // 4h) Translate the unmapped addresses (should error) and some still mapped
    printf("    [4h] Translating after unmapping:\n");
    TRY_TRANSLATE(to_unmap1);
    TRY_TRANSLATE(to_unmap2);
    // Translate an address that should still be mapped (e.g., 0x1ABC)
    TRY_TRANSLATE(0x1ABC);
    printf("\n");

    // 4i) Re-map an unmapped address and translate again
    printf("    [4i] Re-mapping 0x%04X and translating...\n", to_unmap1);
    map(to_unmap1);
    TRY_TRANSLATE(to_unmap1);
    printf("\n");

    // ------------------------------------------------------------------------
    // 5) Test full physical memory exhaustion through mapping
    // ------------------------------------------------------------------------
    printf("[5] Testing exhaustion of physical memory via map() calls...\n");
    // First, unmap all previously mapped pages so frames become free
    for (size_t i = 0; i < num_test_addrs; i++) {
        unmap(test_addrs[i]);
    }
    for (size_t i = 0; i < PHYSICAL_NUM_FRAMES; i++) {
        // If frame was allocated by map, free it here (some may already be free)
        frame_free(i);
    }
    // Reset PDBR
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            PDBR[i][j] = -1;

    // Now call map() repeatedly on unique virtual pages until frames run out
    printf("    Mapping unique virtual pages until physical memory is exhausted:\n");
    // We'll pick virtual addresses with different L1/L2 indices to use up all 16 frames.
    int mapped_count = 0;
    for (uint16_t vpage = 0; vpage < VIRTUAL_NUM_FRAMES; vpage++) {
        uint16_t virt_addr = vpage * PAGE_SIZE; // use offset=0 for simplicity
        map(virt_addr);
        int pdi = (virt_addr >> 13) & 0x7;
        int pti = (virt_addr >> 10) & 0x7;
        if (PDBR[pdi][pti] != -1) {
            mapped_count++;
        }
        if (mapped_count == PHYSICAL_NUM_FRAMES) {
            printf("    %d frames mapped. Next map() should fail.\n", mapped_count);
            break;
        }
    }
    // One more map call should fail
    printf("    Attempting one more map() (should fail):\n");
    map(0x5000);  // Arbitrary new virtual address
    printf("\n");

    // ------------------------------------------------------------------------
    // 6) Test invalid translations and clean up
    // ------------------------------------------------------------------------
    printf("[6] Testing invalid translate() on completely unmapped address 0x7FFF...\n");
    TRY_TRANSLATE(0x7FFF);
    printf("\n");

    printf("=== Test Suite Completed ===\n");
    return 0;
}

