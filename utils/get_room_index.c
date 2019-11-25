#include "../header.h"

/* take a booking id and return the associated room_index (if one), otherwise return 0. */
int get_room_index(char *r1_id, char *r2_id, char *r3_id, char *r4_id)
{
    char booking_id[50] = "";
    bool valid_booking_id = false;
    int room_index = 0;

    while (!valid_booking_id)
    {
        printf("\nFind your associated room by entering your booking id here :\n");
        fflush(stdin);

        fgets(booking_id, 50, stdin);
        remove_whitespace(booking_id, 50);

        /* little bit of code to let the user cancel */
        int cancel = strcmp("c", booking_id);
        if (cancel == 0)
        {
            printf("Cancelling function.");
            return -1;
        }

        /* strings in c aaa, resorted to this. */
        int r1 = strcmp(r1_id, booking_id);
        int r2 = strcmp(r2_id, booking_id);
        int r3 = strcmp(r3_id, booking_id);
        int r4 = strcmp(r4_id, booking_id);

        /* note that the room_index variable is the same as the array index, so it's 1 less than the actual room_index number */
        if (r1 == 0)
        {
            room_index = 0;
            valid_booking_id = true;
        } else if (r2 == 0)
        {
            room_index = 1;
            valid_booking_id = true;
        } else if (r3 == 0)
        {
            room_index = 2;
            valid_booking_id = true;
        } else if (r4 == 0)
        {
            room_index = 3;
            valid_booking_id = true;
        } else
        {
            // booking id wasn't valid, go again;
            printf("Could not find an associated booking id, please try again.");
            continue;
        }
    }

    /* the room_index variable is actually the index */
    printf("Your associated room_index is: #%d! Room check finished. Press any key to return. :", room_index + 1);

    char throwaway;
    scanf("%c", &throwaway);

    return room_index;
}

