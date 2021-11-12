/* File name : main.c
* Package name : SimpleRingBuffer
* Description: 
* This software implements the simple ring buffer (circular buffer/queue) 
* Also, a thin wrapper is built to visualize the ring buffer with user inputs
* To use the test mode : (mode, value) to be provided. 
* example write: w, 3 -> this indicates the write mode and the value to be written
* example read : r, 6 -> this indicates the read mode and the number of values to be read
* NOTE: for proper alignment, the single digit number must be used
*/

// Includes
#include <stdio.h>
#include <stdlib.h>         // for clear screen command
#include "ring_buffer.h"
#include "console.h"

// Definitions
#define DATA_BUFFER_SIZE                8   

// Global variables
uint8_t data_buff[DATA_BUFFER_SIZE];
ring_buffer_t g_ring_buffer;

const uint8_t program_title[] = "\n\r \n\r \n\r ****** SIMPLE RING BUFFER SOFTWARE PACKAGE ****** \n\r \n\r \n\r";

int main(int argc, char *argv[])
{
    // Initialize the test buffer
    buffer_init(&g_ring_buffer, &data_buff[0], DATA_BUFFER_SIZE);

    // print the program title
    printf("%s", program_title);
    printf("press any key to go into testing mode...");
    _getch();

    // Handle the user interaction
    console_task(&g_ring_buffer);

    return 0;
}
