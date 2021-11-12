/**
  @file Console.c
  @brief Console implementation.
  this is the generic console implementation which can be used with any ports like
  serial or ethernet ports.
  this is based on the buffered string output meaning a dedicated ring buffer is
  used for this console

  */


#include "console.h"
#include "print_buffer.h"

// static variables
static uint8_t u8_input_value[CONSOLE_TX_BUFFER_SIZE];
static uint8_t u8_output_value[CONSOLE_RX_BUFFER_SIZE];

/**
 * @brief this provides initialization of console
 *  @param none
 *  @return none
 */
void console_init()
{
    
}

/**
 *  @brief This is the main console task function
 *  @param pbuff
 *  @return none
 */
void console_task(ring_buffer_t* pbuff)
{
    uint32_t u32_input_value;
    //static uint8_t u8_input_value;
    //static char mode, out_value;
    static char mode;
    char c;
    char inp_value_string[8];
    uint32_t num_bytes=0;

    while (1)
    {
        clrscr();
        printf("------------ Ring Buffer data ---------\n\r\n\r");
        //print_buffer(pbuff->buff_data,pbuff->buff_size, 'H');
        //print_buffer(pbuff, pbuff->read_index, pbuff->write_index, pbuff->buff_size);
        print_buffer(pbuff);
        printf("\n\r-------- Buffer Read/Write Input ------\n\r\n\r");

        printf("read index : %d \n\r", pbuff->read_index);
        printf("write index : %d \n\r", pbuff->write_index);
        printf("buffer count : %d \n\r", pbuff->buff_count);

        printf("Enter the values (mode, value): ");
        scanf("%c %s", &mode, inp_value_string);
        u32_input_value = atoi(inp_value_string);
//        printf(" the input value string is %d\n", u32_input_value);
//        _getch();

        /* empty remaining chars from input buffer */
        while ((c = getchar()) != '\n' && c != EOF) {}

        //printf("the user inputs are %c and %c \n\r", mode, inp_value);

        if (mode == 'w')
        {
            if ((buffer_full(pbuff)) == false)
            {
                u8_input_value[0] = (uint8_t) u32_input_value;  // only 8 bit values are supported
                buffer_put_byte(pbuff, u8_input_value);     // inp_value is actual data to be written here
                //printf("size of buffer count is %d", pbuff->buff_count);
                //printf("write mode \n\r");
                //_getch();
            }
            else
            {
                printf("Buffer is Full \n\r");
                //_getch();
            }
        }
        else if (mode == 'r')
        {
            if ((buffer_empty(pbuff)) == false)
            {
                num_bytes = u32_input_value;
                buffer_get_data(pbuff, u8_output_value, num_bytes);
//                printf("size of buffer count is %d \n\r", pbuff->buff_count);
//                printf("num of bytes to read : %d \n\r", num_bytes);
//                printf("read mode \n\r");
//                _getch();
            }
            else
            {
                printf("Buffer is Empty \n\r");
                //_getch();
            }
        }
        else
        {
            printf("error in mode \n\r");
            //_getch();
        }
    }

}


