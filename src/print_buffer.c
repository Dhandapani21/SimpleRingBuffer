#include "print_buffer.h"


void print_buffer(ring_buffer_t *pbuff)
{
    uint8_t *pbuffer = (uint8_t*) pbuff->buff_data;
    uint32_t read_index = pbuff->read_index;
    uint32_t write_index = pbuff->write_index; 
    uint32_t buffer_size = pbuff->buff_size;
    uint32_t cnt;
    bool cond1,cond2,cond3;

    printf("\n\r\n\r");
    for (cnt = 0; cnt < buffer_size; cnt++)
    {
        cond1 = false; cond2 = false; cond3 = false;

        if (((cnt >= read_index) || (cnt < write_index)) && (read_index >= write_index))
        {
            cond1 = true;
        }

        if (((cnt >= read_index) && (cnt < write_index)) && (read_index < write_index))
        {
            cond2 = true;
        }

        if (pbuff->buff_count != 0)
        {
            cond3 = true;
        }

        if ( ((cond1 == true) || (cond2 == true)) && (cond3 == true) )
        {
            printf("  %d  ", pbuffer[cnt]);
        }
        else
        {
            printf("  _  ");
        }
    }
    printf("\n\r");
    for (cnt = 0; cnt < buffer_size; cnt++)
    {
        if ((cnt == read_index) && (cnt == write_index))
        {
            printf("  rw ");
        }
        else if (cnt == read_index)
        {
            printf("  r  ");
        }
        else if (cnt == write_index)
        {
            printf("  w  ");
        }
        else
        {
            printf("     ");
        }
    }
    printf("\n\r\n\r");
}



void clrscr()
{
    system("@cls||clear");
}

void clrscr_portable()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
