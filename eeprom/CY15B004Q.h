#ifndef EEPROM_CY15B004Q_H_
#define EEPROM_CY15B004Q_H_

#include <SI_EFM8BB1_Register_Enums.h>

typedef enum PORT_DEF {
	p0			= SFR_P0,
    p1          = SFR_P1,
	p2			= SFR_P2
} PORT_DEF;

typedef struct {
	uint8_t 	address_range;		// address range 0 - > low, 1 -> high
									// low: 	use 0x00 to 0xFF
									// high: 	use 0x100 to 0x1FF
	uint8_t		opcode_address;		// opcode address for location
} FRAM_PARAMS;

extern FRAM_PARAMS fram_params;

/**************************************************************************//**
* 							Opcode commands
* WREN  - Set write enable latch   - 0000 0110
* WRDI  - Write disable 		   - 0000 0100
* RDSR  - Read Status Register     - 0000 0101
* WRSR  - Write Status Register    - 0000 0001
*****************************************************************************/
#define  SPI_FRAM_OPCODE_WREN    		 0x06
#define  SPI_FRAM_OPCODE_WRDI	 		 0x04
#define  SPI_FRAM_OPCODE_RDSR    		 0x05
#define  SPI_FRAM_OPCODE_WRSR	 		 0x01
/**************************************************************************//**
* For address range – 0x00 to 0xFF:
* WRITE – Write memory data		   - 0000 A010 = 0x0000 0010 (A = ‘0’)
* READ  – Read memory data		   - 0000 A011 = 0x0000 0011 (A = ‘0’)
*****************************************************************************/
#define  SPI_FRAM_OPCODE_RANGE_L_WRITE    0x02
#define  SPI_FRAM_OPCODE_RANGE_L_READ     0x03
/**************************************************************************//**
* For address range – 0x100 to 0x1FF:
* WRITE – Write memory data		   - 0000 A010 = 0x0000 1010 (A = ‘1’)
* READ  – Read memory data		   - 0000 A011 = 0x0000 1011 (A = ‘1’)
*****************************************************************************/
#define  SPI_FRAM_OPCODE_RANGE_H_WRITE    0x0A
#define  SPI_FRAM_OPCODE_RANGE_H_READ     0x0B

/**************************************************************************//**
* Function
*****************************************************************************/
void FRAM_Opcode_Write(uint8_t opcode);
void writeToFRAM(uint8_t writeData, uint8_t address);
uint8_t readFromFRAM(uint8_t address);
uint8_t readRDSR();

#endif /* EEPROM_CY15B004Q_H_ */
