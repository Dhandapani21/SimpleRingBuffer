/**
  @file ring_buffer.h
  @brief this file provides the generic ring buffer implementation

  */


#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/** \addtogroup ring_buffer RingBuffer
 *  @{
 */


// Definitions
#define BUFFER_ERROR                (-1)

// Buffer structure
typedef struct
{
    uint8_t *buff_data;
    uint32_t read_index;
    uint32_t write_index;
    uint32_t buff_count;
    uint32_t buff_size;

} ring_buffer_t;


// Buffer API
bool buffer_full(ring_buffer_t *buff);
bool buffer_empty(ring_buffer_t *buff);
int buffer_put_data(ring_buffer_t *buff, uint8_t *in_data, uint32_t count);
int buffer_get_data(ring_buffer_t *buff, uint8_t *out_data, uint32_t count);
int buffer_put_byte(ring_buffer_t *buff, uint8_t *in_byte);
int buffer_get_byte(ring_buffer_t *buff, uint8_t *out_byte);
uint32_t buffer_remaining_bytes(ring_buffer_t *buff);
int buffer_flush(ring_buffer_t *buff);
int buffer_init(ring_buffer_t *buff, uint8_t *data_ptr, uint32_t size);

/** @}*/

#endif // RING_BUFFER_H
