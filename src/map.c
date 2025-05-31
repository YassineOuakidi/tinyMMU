
#include "../inc/mapping.h"


void map(uint16_t virt)
{
	//Page Offset
	uint16_t PO = virt & 0x3FF; // page_size = 1KB -> offset = 10bits  
	
	//Page Table Index
	uint16_t PTI = (virt >> 10) & 0x7;
	
	//PAGE Directory Index
	uint16_t PDI = (virt >> 13) & 0x7;
	
	if(PDBR[PDI][PTI]!= 0xFF)
	{
		printf("the address %x is already mapped\n" , virt); 
		return ;
	}

	else 
	{
		int index = pmm_alloc_frame();
		if(index == -1)
		{
			printf("Error: Cannot allocate a frame\n");
		}
		else
		{
			printf("allocated 0x%04X to frame number: %d\n" , virt , index);
			PDBR[PDI][PTI] = index ;
		}
	}
	
}
