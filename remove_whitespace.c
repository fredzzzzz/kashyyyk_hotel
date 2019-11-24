#include "header.h"

/* used in the checkin subroutine */
void remove_whitespace(char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
    }
}

