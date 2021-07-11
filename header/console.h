#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>   
#include "ring_buffer.h"

// console file definitions and initializations
#define CONSOLE_TX_BUFFER_SIZE             16
#define CONSOLE_RX_BUFFER_SIZE             32

void console_task(ring_buffer_t* pbuff);
void console_init();



#endif // CONSOLE_H
