/**
  @file ring_buffer.c
  @internal
  Author: Dhandapani Rajabathar
  Date: 10/oct/2021
  @endinternal
  @brief generic ring buffer implementation

  Detailed Description:
  this ring buffer can be used on both embedded and desktop software.


  */

#include "ring_buffer.h"


/** @addtogroup ring_buffer RingBuffer
 *  @{
 */


/**
 *  @brief buffer_put_data
 *  @param buff
 *  @return status
 *
 *
*/

bool buffer_full(ring_buffer_t *buff)
{
    if(buff->buff_count >= buff->buff_size)
    {
        return true;
    }

    return false;
}



bool buffer_empty(ring_buffer_t *buff)
{
    if(buff->buff_count == 0)
    {
        return true;
    }

    return false;
}

/**
 *
 *   buffer_put_data
 *
 *
*/
int buffer_put_data(ring_buffer_t *buff, uint8_t *in_data, uint32_t count)
{
    uint32_t i;
    //uint8_t *ptr = (uint8_t *)in_data;

    if(buff == NULL)  return BUFFER_ERROR;

    if((count + buff->buff_count) <= buff->buff_size)
    {
        // the buffer has enough room, insert stream of data
        for(i = 0; i<count; i++)
        {
          //buff->buff_data[buff->write_index] = *ptr++;
          buff->buff_data[buff->write_index] = in_data[i];
          //buff->write_index =  (buff->write_index + 1) % buff->buff_size;   // if write index reaches end of buffer, restart from zero
          buff->write_index++;
          if(buff->write_index >= buff->buff_size)
          {
             buff->write_index=0;
          }
          buff->buff_count++;
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

/**
 *
 *  @brief buffer empty
 *
 *
*/
int buffer_get_data(ring_buffer_t *buff, uint8_t *out_data, uint32_t count)
{
    uint32_t i, actual_bytes_read=0;
    //uint8_t *ptr = (uint8_t *)out_data;

    if(buff == NULL)  return BUFFER_ERROR;

    if(count >= buff->buff_count)
    {
        actual_bytes_read = buff->buff_count;
    }
    else
    {
        actual_bytes_read = count;
    }

    /* if the size requested fits on current contents, extract the data stream */
    for(i = 0; (i<actual_bytes_read); i++)
    {
        //*ptr++ = buff->buff_data[buff->read_index];
        out_data[i] = buff->buff_data[buff->read_index];
        buff->buff_data[buff->read_index] = 0;                              // clearing read place holders with zero for easy debugging
        //buff->read_index =  (buff->read_index + 1) % buff->buff_size;       // if read index reaches end of buffer, restart from zero
        buff->read_index++;
        if(buff->read_index >= buff->buff_size)
        {
           buff->read_index=0;
        }
        buff->buff_count--;
    }

    if(actual_bytes_read != count)
    {
        return (int)actual_bytes_read;
    }

    return 0;
}

/**
 *
 *  @brief buffer empty
 *
 *
*/
int buffer_put_byte(ring_buffer_t *buff, uint8_t *in_byte)
{
    if(buff == NULL)  return BUFFER_ERROR;

    // Check buffer is full and then insert new byte
    if(buff->buff_count != buff->buff_size)
    {
        buff->buff_data[buff->write_index] = in_byte[0];
        buff->buff_count++;
        buff->write_index++;
        if(buff->write_index >= buff->buff_size)
        {
           buff->write_index=0;
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

/**
 *
 *  @brief buffer empty
 *
 *
*/
int buffer_get_byte(ring_buffer_t *buff, uint8_t *out_byte)
{
    if(buff == NULL)  return BUFFER_ERROR;

    // Check buffer is not empty and then extract byte
    if (buff->buff_count != 0)
    {
        out_byte[0] =  buff->buff_data[buff->read_index];
        buff->buff_data[buff->read_index] = 0;  // clearing the read place holder for testing
        buff->buff_count--;
        buff->read_index++;
        if(buff->read_index >= buff->buff_size)
        {
           buff->read_index=0;
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

/**
 *
 *  @brief buffer empty
 *
 *
*/
uint32_t buffer_remaining_bytes(ring_buffer_t *buff)
{
    return buff->buff_count;
}

/**
 *
 *  @brief buffer empty
 *
 *
*/
int buffer_flush(ring_buffer_t *buff)
{
    if(buff == NULL) return BUFFER_ERROR;

    memset(buff->buff_data,0,buff->buff_size);
    buff->read_index=0;
    buff->write_index=0;
    buff->buff_count=0;

    return 0;
}

/**
 *
 *  @brief buffer empty
 *
 *
*/
int buffer_init(ring_buffer_t *buff, uint8_t *data_ptr, uint32_t size)
{
    buff->buff_data = data_ptr;
    buff->buff_size = size;
    buff->read_index = 0;
    buff->write_index = 0;
    buff->buff_count = 0;

    return 0;
}

/** @}*/
