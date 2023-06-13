/**********************************************************************************************************************
 * \file SPI_CPU.h
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

#ifndef QSPI_CPU_H_
#define QSPI_CPU_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxQspi_SpiMaster.h"
#include "IfxQspi_SpiSlave.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define SPI_BUFFER_SIZE     5                       /* Buffers size                  */

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/
typedef struct
{
    uint8 spiMasterTxBuffer[SPI_BUFFER_SIZE];       /* QSPI Master Transmit buffer   */
    uint8 spiMasterRxBuffer[SPI_BUFFER_SIZE];       /* QSPI Master Receive buffer    */
    uint8 spiSlaveTxBuffer[SPI_BUFFER_SIZE];        /* QSPI Slave Transmit buffer    */
    uint8 spiSlaveRxBuffer[SPI_BUFFER_SIZE];        /* QSPI Slave Receive buffer     */
} qspiBuffers;

typedef struct
{
    qspiBuffers               spiBuffers;           /* Buffers instance              */
    IfxQspi_SpiMaster         spiMaster;            /* QSPI Master handle            */
    IfxQspi_SpiMaster_Channel spiMasterChannel;     /* QSPI Master Channel handle    */
    IfxQspi_SpiSlave          spiSlave;             /* QSPI Slave handle             */
} qspiComm;

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initPeripherals(void);
void transferData(void);
void setupLedMatrix (void);
void setRow (uint8 row, uint8 val, uint8 state);
void printLedMatrix(int range);
void turnOff(void);

#endif /* QSPI_CPU_H_ */
