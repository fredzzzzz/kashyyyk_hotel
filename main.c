#include "header.h"

/* global variables (see data dictionary) */
int booking_info[4][6] = {};
char *customers[4][3][128] = {};
int rooms[4] = {0, 0, 0, 0};

/* let me know if there's other variables i missed in your program */
char *table7[3][2] = {{"E", "F"}, {"N", "F"}, {"T", "F"}};
char *table9[3][2] = {{"E", "F"}, {"N", "F"}, {"T", "F"}};
char freeTables7[4];
char freeTables9[3];

/* keep the room array but brute force for the booking id's, see ./get_room_index.c */
char r1_id[50] = "";
char r2_id[50] = "";
char r3_id[50] = "";
char r4_id[50] = "";

/* main program is an infinite loop calling the other subroutines */
int main()
{
    printf("==-== PROGRAM START ==-==");

    /* create infinite loop */
    while (1)
    {
        bool invalid_selection = false;
        int selection = 0;
        while (!invalid_selection)
        {
            printf("\n\nWelcome to the Kashyyyk Hotel! Please enter:\n\t1 - Check-in.\n\t2 - Book a table.\n\t3 - Check-out.\n\t4 - Get Room Number.\nSelection :");
            fflush(stdin);
            scanf("%d", &selection);

            if (selection < 1 || selection > 4)
            {
                printf("Invalid selection received, try again.");
                continue;
            }

            const char *selections[4] = {"Check-in", "Book a table", "Check-out", "Get Room Number"};
            printf("Received selection: - %s. Taking you there.\n\n", selections[selection - 1]);
            invalid_selection = true;
        }

        switch(selection)
        {
            case 1:
                checkin(booking_info, rooms, customers, r1_id, r2_id, r3_id, r4_id);
                break;

            case 2:
                book_table(booking_info, table7, table9, freeTables7, freeTables9, r1_id, r2_id, r3_id, r4_id);
                break;

            case 3:
                checkout(booking_info, rooms, customers, r1_id, r2_id, r3_id, r4_id);
                break;

            case 4:
                get_room_index(r1_id, r2_id, r3_id, r4_id);
                break;

            default:
                printf("Something went wrong. Starting again.");
        }
    }
}
