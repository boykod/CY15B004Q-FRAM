// USER INCLUDES			
#include <main.h>
#include <SI_EFM8BB1_Register_Enums.h>

//-----------------------------------------------------------------------------
// SPI0_ISR
//-----------------------------------------------------------------------------
// SPI0 ISR Content goes here. Remember to clear flag bits:
// SPI0CN0::SPIF (SPI# Interrupt Flag)
//-----------------------------------------------------------------------------

//SI_INTERRUPT (SPI0_ISR, SPI0_IRQn) {
//   static uint8_t array_index = 0;
//   static char state = 0;
//
//   IE_ESPI0 = 0;
//
//   if(state == 0) {
//	   switch(Command) {
//	   case SPI_WRITE:
//		   while (!SPI0CN0_TXBMT);
//		   SPI0DAT = SPI_Data;
//		   break;
//
//	   case SPI_READ:
//		   SPI_Data = SPI0DAT;     // Read the data from the slave
//		   break;
//
//	   case SPI_READ_BUFFER:
//		   array_index = 0;        // Clear the data counter
//
//		   state = 1;
//		   break;
//	   }
//   } else if(state == 1) {
//	   switch(Command) {
//	   case SPI_READ_BUFFER:
//		   SPI_Data_Array[array_index] = SPI0DAT;
//		   SPI0DAT = 0xFF;
//
//		   array_index++;
//		   break;
//
//	   default:
//		   state = 0;
//	   }
//   }
//
//   SPI0CN0_SPIF = 0;                 // Clear the SPIF0 flag
//}
