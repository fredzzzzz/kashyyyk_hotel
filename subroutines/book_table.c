#include "../header.h"

/* book table - jackson */
int book_table(int booking_info[4][6], char *table7[3][2], char *table9[3][2], char *freeTables7, char *freeTables9, char *r1_id, char *r2_id, char *r3_id, char *r4_id)
{
    int guestCheck = 0, tableCheck = 0, timeChoice = 0, tableChoice = 0, room = 0, x = 0; //declares all integer variables

    printf("==-== START OF TABLE BOOK ==-==\n");
    printf("To help serve you tonight, we'll start by asking for your booking id.");

    /* use the external function to get the room index, booking id input is included in that. */
    room = get_room_index(r1_id, r2_id, r3_id, r4_id);
    guestCheck = (room == -1 ? 0 : 1);

    if (guestCheck == 1) {//only happens if guest is staying at hotel
        if (booking_info[room][3] == 3) { //checks to see board type
            printf("Cannot book you a table if you are not staying full/half board.\n");
        } else {
            for (x = 0; x < 3; x++) { //loops around the whole table list to check free tables
                if ((strcmp(table7[x][1], "F")) == 0) {
                    tableCheck = 1;
                }
                if ((strcmp(table9[x][1], "F")) == 0) {
                    tableCheck = 1;
                }
            }
        }
        if (tableCheck == 1) { //checks if there is a free table
            printf("Would you like to view options at 7pm or 9pm: \n");
            scanf("%d", &timeChoice);
            switch (timeChoice) { //sees which time user would like to book for
                case (7):
                    printf("These tables are free:\n");
                    for(x=0;x<3;x++){ //for loop to print any free tables
                        if((strcmp(table7[x][1], "F")) == 0){
                            printf("%s, ", table7[x][0]);
                        }
                    }
                    printf("\nWhich table would you like? (0 for E, 1 for N, 2 for T):\n");
                    scanf("%d", &tableChoice);
                    if((strcmp(table7[tableChoice][1], "N")) == 0){ //checks to see if input table is free
                        printf("You cannot book that table");
                    } else{
                        printf("Table %s booked\n", table7[tableChoice][0]);
                        table7[tableChoice][1] = "N";
                        printf("Thank you for booking with us");
                    }
                    break;
                case (9):
                    printf("These tables are free:\n");
                    for(x=0;x<3;x++){
                        if((strcmp(table9[x][1], "F")) == 0){
                            printf("%s, ", table9[x][0]);
                        }
                    }
                    printf("Which table would you like? (0 for E, 1 for N, 2 for T):\n");
                    scanf("%d", &tableChoice);
                    if((strcmp(table9[tableChoice][1], "N")) == 0){ //checks to see if input table is free
                        printf("You cannot book that table");
                    } else{
                        printf("Table %s booked\n", table7[tableChoice][0]);
                        table9[tableChoice][1] = "N";
                        printf("Thank you for booking with us");
                    }
                    break;
                default:
                    printf("Invalid time");
                    break;
            }
        } else {
            printf("No available tables.");
        }
    }
    return 1;
}