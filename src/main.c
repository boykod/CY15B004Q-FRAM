/*
 * SPI:
 * 		P0.6 - SPI SCK    			(digital output, push-pull)
 *		P0.7 - SPI MISO   			(digital, open drain I/O)
 * 		P1.0 - SPI MOSI				(digital output, push-pull)
 * 		P0.3 - SPI CS				(Low Active)
 * */

/**************************************************************************//**
* Includes
 *****************************************************************************/
#include <main.h>
#include <SI_EFM8BB1_Register_Enums.h>
#include "InitDevice.h"
#include "../eeprom/CY15B004Q.h"

/**************************************************************************//**
* Pin Initialization
 *****************************************************************************/
SI_SBIT (DISP_EN, SFR_P0, 0);          // Display Enable
#define DISP_BC_DRIVEN   0             // 0 = Board Controller drives display
#define DISP_EFM8_DRIVEN 1             // 1 = EFM8 drives display

/**************************************************************************//**
* Global Variables
 *****************************************************************************/
uint8_t k;
uint8_t readStatusRegister = 0;

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void delay(void);

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
//-----------------------------------------------------------------------------
void SiLabs_Startup (void) {
  // Disable the watchdog here
}
 
/**************************************************************************//**
* main
 *****************************************************************************/
void main(void) {
   uint8_t fram_address[MAX_BUFFER_SIZE] = {0x00,0x01,0x02,0x03,0x04,0x05};
   uint8_t fram_read_data[MAX_BUFFER_SIZE] = {0};

   enter_DefaultMode_from_RESET();

   DISP_EN = DISP_BC_DRIVEN;           			// Display not driven by EFM8

   IE_EA = 0;                          			// Disable global interrupts

/**************************************************************************//**
* Write/Read test
*****************************************************************************/
   fram_params.address_range = 0;				// explanation CY15B004Q.h

   /*FRAM_Opcode_Write(SPI_FRAM_OPCODE_WREN);		// Set write enable latch
   writeToFRAM(15, 0x00);						// Write the value 15
   	   	   	   	   	   	   	   	   	   	   	    // to location 0x00
   delay();

   FRAM_Opcode_Write(SPI_FRAM_OPCODE_WREN);		// Set write enable latch
   writeToFRAM(95, 0x01);						// Write the value 95
	   	   	   	   	    						// to location 0x01
   delay();

   FRAM_Opcode_Write(SPI_FRAM_OPCODE_WREN);		// Set write enable latch
   writeToFRAM(125, 0x02);						// Write the value 125
												// to location 0x02
   delay();

   FRAM_Opcode_Write(SPI_FRAM_OPCODE_WREN);		// Set write enable latch
   writeToFRAM(85, 0x03);						// Write the value 85
												// to location 0x03
   delay();

   FRAM_Opcode_Write(SPI_FRAM_OPCODE_WREN);		// Set write enable latch
   writeToFRAM(64, 0x04);						// Write the value 64
												// to location 0x04
   delay();

   FRAM_Opcode_Write(SPI_FRAM_OPCODE_WREN);		// Set write enable latch
   writeToFRAM(212, 0x05);						// Write the value 212
												// to location 0x05
   delay();*/

   // Read the values from locations 0x00 - 0x05
   for(k = 0; k < MAX_BUFFER_SIZE; k++) {
	   fram_read_data[k] = readFromFRAM(fram_address[k]);
	   delay();
   }
/**************************************************************************//**
* End test
*****************************************************************************/

   while (1) {
	   readStatusRegister = readRDSR();			// Read the values from RDSR
	   delay();
   }
}

//-----------------------------------------------------------------------------
// Support Routines
//-----------------------------------------------------------------------------
/**************************************************************************//**
* Delay
*****************************************************************************/
void delay(void) {
   uint32_t count;

   for (count = 100000; count > 0; count--);
}
