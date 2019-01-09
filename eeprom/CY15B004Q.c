/**************************************************************************//**
* Includes
 *****************************************************************************/
#include <SI_EFM8BB1_Register_Enums.h>
#include "CY15B004Q.h"

/**************************************************************************//**
* Pin Initialization
 *****************************************************************************/
SI_SBIT (FRAM_CS,   p0, 3);              // FRAM CS

/**************************************************************************//**
* Global Variables
 *****************************************************************************/
uint8_t i;

FRAM_PARAMS fram_params;

/**************************************************************************//**
* FRAM_Opcode_Write(uint8_t opcode)
*
* @param opcode		- Opcode commands to write (CY15B004Q.h)
*****************************************************************************/
void FRAM_Opcode_Write(uint8_t opcode) {
	FRAM_CS = 0;

	while (!SPI0CN0_TXBMT);
	SPI0DAT = opcode;

	for(i = 0; i < 50; i++);
	FRAM_CS = 1;
}
/**************************************************************************//**
* writeToFRAM(uint8_t writeData, uint8_t address)
*
* @param writeData	- Data to write
* @param address	- Location in memory. Range from:
* 	- 0x00 to 0xFF		(use SPI_FRAM_OPCODE_RANGE_L_WRITE)
* 	- 0x100 to 0x1FF	(use SPI_FRAM_OPCODE_RANGE_H_WRITE)
*****************************************************************************/
void writeToFRAM(uint8_t writeData, uint8_t address) {
	if(fram_params.address_range == 0) {
		fram_params.opcode_address = SPI_FRAM_OPCODE_RANGE_L_WRITE;
	} else {
		fram_params.opcode_address = SPI_FRAM_OPCODE_RANGE_H_WRITE;
	}

	FRAM_CS = 0;

	while (!SPI0CN0_TXBMT);
	SPI0DAT = fram_params.opcode_address;
	while (!SPI0CN0_TXBMT);
	SPI0DAT = address;
	while (!SPI0CN0_TXBMT);
	SPI0DAT = writeData;

	for(i = 0; i < 50; i++);
	FRAM_CS = 1;
}
/**************************************************************************//**
* readFromFRAM(uint8_t address)
*
* @param address	- Location in memory. Range from:
* 	- 0x00 to 0xFF		(use SPI_FRAM_OPCODE_RANGE_L_READ)
* 	- 0x100 to 0x1FF	(use SPI_FRAM_OPCODE_RANGE_H_READ)
* @return inputData - Read data from current address
*****************************************************************************/
uint8_t readFromFRAM(uint8_t address) {
	uint8_t inputData = 0;

	if(fram_params.address_range == 0) {
		fram_params.opcode_address = SPI_FRAM_OPCODE_RANGE_L_READ;
	} else {
		fram_params.opcode_address = SPI_FRAM_OPCODE_RANGE_H_READ;
	}

	FRAM_CS = 0;

	while (!SPI0CN0_TXBMT);
	SPI0DAT = fram_params.opcode_address;
	while (!SPI0CN0_TXBMT);
	SPI0DAT = address;
	while (!SPI0CN0_TXBMT);
	SPI0DAT = 0x00;

	for(i = 0; i < 50; i++);
	FRAM_CS = 1;

	inputData = SPI0DAT;

	return(inputData);
}
/**************************************************************************//**
* readRDSR()
*
* @return rdsrData  - Read Status Register
*****************************************************************************/
uint8_t readRDSR() {
	uint8_t rdsrData = 0;

	FRAM_CS = 0;

	while (!SPI0CN0_TXBMT);
	SPI0DAT = SPI_FRAM_OPCODE_RDSR;
	while (!SPI0CN0_TXBMT);
	SPI0DAT = 0x00;

	for(i = 0; i < 50; i++);
	FRAM_CS = 1;

	rdsrData = SPI0DAT;

	return(rdsrData);
}

