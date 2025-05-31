

#include "../inc/mapping.h"


uint16_t translate(uint16_t virt)
{
	uint16_t PO = virt & 0x3FF;
	
	uint16_t PTI = (virt >> 10) & 0x7;

	uint16_t PDI = (virt >> 13) & 0x7;

	if(PDBR[PDI][PTI] == 0xFF)
		return (uint16_t) - 1;
	
	uint16_t phys = ( PDBR[PDI][PTI] * FRAME_SIZE ) + PO ;
	
	return phys;
}
