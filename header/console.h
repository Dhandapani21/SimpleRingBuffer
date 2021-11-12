/**
  @file Console.h
  @brief prototypes for console file

  */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ring_buffer.h"

/** \addtogroup console Console Module
 *  @{
 */


// console file definitions and initializations
#define CONSOLE_TX_BUFFER_SIZE             16
#define CONSOLE_RX_BUFFER_SIZE             32


// function prototypes
void console_task(ring_buffer_t* pbuff);
void console_init();


/** @}*/

#endif // CONSOLE_H
