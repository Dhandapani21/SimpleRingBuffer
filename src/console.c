#include "console.h"

void console_init()
{

}

void console_task(ring_buffer_t* pbuff)
{
    uint32_t u32_temp;
    static uint8_t u8_input_value;
    static char mode, out_value;
    char* temp = 0, c;
    char inp_value_string[8];

    while (1)
    {
        clrscr();
        printf("------------ Ring Buffer data ---------\n\r\n\r");
        //print_buffer(pbuff->buff_data,pbuff->buff_size, 'H');
        print_buffer(pbuff, pbuff->read_index, pbuff->write_index, pbuff->buff_size);
        printf("\n\r-------- Buffer Read/Write Input ------\n\r\n\r");

        printf("read index : %d \n\r", pbuff->read_index);
        printf("write index : %d \n\r", pbuff->write_index);
        printf("buffer count : %d \n\r", pbuff->buff_count);

        printf("Enter the values \(mode, value\): ");
        scanf("%c %s", &mode, inp_value_string);
        u8_input_value = (uint8_t)atoi(inp_value_string);
        //printf("the converted value is %d\n\r", u8_input_value);
        //getch();

        /* empty remaining chars from input buffer */
        while ((c = getchar()) != '\n' && c != EOF) {}

        //printf("the user inputs are %c and %c \n\r", mode, inp_value);

        if (mode == 'w')
        {
            if ((buffer_full(pbuff)) == false)
            {
                buffer_put_byte(pbuff, &u8_input_value);     // inp_value is actual data to be written here
                //printf("size of buffer count is %d", pbuff->buff_count);
                //printf("write mode \n\r");
                //getch();
            }
            else
            {
                printf("Buffer is Full \n\r");
                getch();
            }
        }
        else if (mode == 'r')
        {
            if ((buffer_empty(pbuff)) == false)
            {
                //buffer_get_byte(pbuff, &out_value);
                buffer_get_data(pbuff, &out_value, (uint32_t)u8_input_value);  // inp value is count here
                //printf("size of buffer count is %d", pbuff->buff_count);
                //printf("read mode \n\r");
                //getch();
            }
            else
            {
                printf("Buffer is Empty \n\r");
                getch();
            }
        }
        else
        {
            printf("error in mode \n\r");
            getch();
        }
    }

}


