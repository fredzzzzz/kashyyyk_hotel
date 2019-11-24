#include "header.h"

int checkout(int booking_info[4][6], int *rooms, char *customers[4][3][128], char *r1_id, char *r2_id, char *r3_id, char *r4_id) {
    /* use the external function to get the room index, rest of program is all yours. */
    printf("==--== START OF CHECKOUT ==-==");
    int room = get_room_index(r1_id, r2_id, r3_id, r4_id);

    //local variables
    double roomcost = 0.0;
    double mealscost = 0.0;
    double totalcost = 0.0;
    double roomprices[4] = {100.0, 85.0, 75.0, 50.0};
    double boardcost = 0.0;

    int newspaper = booking_info[room][5];
    int children = booking_info[room][2];
    int adults = booking_info[room][1];
    int x = 0;

    /* endpoint is throwaway */
    char *endpoint;
    int mainage = strtol((char *) customers[room][2], &endpoint, 10);

    int duration = booking_info[room][4];
    int boardtype = booking_info[room][3];

    /* altered values slightly to change for the room index */
    for (x = 0; x < 4; x++)                //This simple for loop identifies the room cost
    {
        if (room == x) {
            roomcost = roomprices[x];
        }
    }

    /* altered to use int values as given in the checkin */
    switch (boardtype) {
        case 1:
            boardcost = 20.0;
            break;
        case 2:
            boardcost = 15.0;
            break;
        case 3:
            boardcost = 5.0;
            break;
        default:
            printf("\n[Invalid board type(?), assumed as B&B]");
            boardcost = 5.0;
    }


    mealscost =(boardcost * adults * duration) + ((boardcost * children * duration) / 2);    //This equation calculates
    roomcost =roomcost * duration;                                                 // the mealscost for the wholeparty

    if (mainage > 65) {
        roomcost = roomcost * 0.9;
    }

    /* changed to use int value as given in checkin */
    if (newspaper == 1)    //only adds price to bill if they bought paper
    {
        totalcost = totalcost + 5.50;
    }
    totalcost = totalcost + roomcost + mealscost;  //more calculations - for the total cost


    printf("\nBookingID:\tMain name:\n%s\t%s", (char *) customers[room][0], (char *) customers[room][1]);   //prints the receipt
    printf("\n\nFinal bill: \t\x9C%1.2f\n-Room cost: \t\x9C%1.2f\n-Meals cost: \t\x9C%1.2f\n", totalcost, roomcost, mealscost);
    if (newspaper == 1) //only prints if they bought a paper
    {
        printf("Newspaper cost:  \x9C%1.2f", 5.50);
    }
    printf("\n");

    /* will have to add the removing of elements, will do tmrw ? could always make a function for it. */
    printf("The checkout was successful, press any key to return to the main menu. :");

    char throwaway;
    scanf("%c", &throwaway);

    return 0;
}