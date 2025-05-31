
#include "../inc/mapping.h"


void unmap(uint16_t virt)
{
	uint16_t PO = virt & 0x3FF ;

	uint16_t PTI = (virt >> 10) & 0x7;

	uint16_t PDI = (virt >> 13) & 0x7;

	if(PDBR[PDI][PTI]==-1)
		return ;
	
	int status = frame_free(PDBR[PDI][PTI]);	 
	
	if(status==-1)
	{
		printf("Error: An error occured\n");
		return;
	}
	
	PDBR[PDI][PTI] = 0xFF;
}
