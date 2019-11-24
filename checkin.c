#include "header.h"

int checkin(int booking_info[4][6], int *rooms, char *customers[4][3][128], char *r1_id, char *r2_id, char *r3_id, char *r4_id)
{
    // the most important var for linking the room, customer, and booking info.
    int room_index = 0;

    // Before they check in, first make sure there's an available room and then list the available rooms.
    int room_count = 0;

    for (int i = 0; i < 4; i++)
    {
        bool room_available = (rooms[i] == 0);
        if (room_available) {
            room_count++;
        }
    }

    if (room_count < 1)
    {
        printf("I'm afraid there are no available rooms right now. Please try again later.");
        return 1;
    } else {
        /* Determine which room they would like to stay in.
            Room 1 - £100, Room 2 - £85, Room 3 - &75, Room 4 - &50. */
        int room_prices[4] = {100, 85, 75, 50};

        printf("We have rooms available! Please choose from: \n");
        for (int i = 0; i < 4; i++)
        {
            if (rooms[i] == 1) continue;
            else
            {
                // & sign was being funky in console, \x means use hex value.
                int price = room_prices[i];
                printf("\tRoom %d [\x9C%d].\n", i + 1, price);
            }
        }

        printf("[PRICE PER DAY OF YOUR STAY]\n");
        int room_choice;
        char choice_input[5] = "";

        bool valid_room = false;
        while (!valid_room)
        {
            printf("Room Choice :");
            fflush(stdin);

            fgets(choice_input, sizeof(choice_input), stdin);

            // locate integer value with strtol, endpoint is throwaway.
            char *endpoint = "";
            room_choice = strtol(choice_input, &endpoint, 10);

            if (room_choice < 1 || room_choice > 4)
            {
                printf("Room choice must be between 1 and 4, try again.\n");
                continue;
            }

            bool room_open = rooms[room_choice - 1] == 0;
            if (!room_open)
            {
                printf("This room is not available at the moment, choose a different room or try again later.\n");
                continue;
            }

            printf("Selection: Room %d at price \x9C%d per day.", room_choice, room_prices[room_choice - 1]);
            room_index = room_choice - 1;

            /* declare the room as unavailable */
            rooms[room_index] = 1;
            valid_room = true;
        }
    }

    // There are available rooms, now we can start the check-in process:
    printf("\nFirstly please may we have your name and date of birth (mm/dd/yy).\n");

    // For the name, validation is only: length > 4, two words, (str type i slacked on).
    char first_name[50] = "";
    char last_name[50] = "";
    char booking_id[50] = "";
    bool valid_name = false;

    while (!valid_name)
    {
        printf("First Name :");
        fgets(first_name, 50, stdin);

        printf("Last Name :");
        fgets(last_name, 50, stdin);

        // checks if the length of each string is < 2, you subtract 1 to compromise the terminating character.
        bool invalid_length = ((strlen(first_name) - 1) < 2) || ((strlen(last_name) - 1) < 2);
        if (invalid_length)
        {
            printf("Your first & last name must be at least 2 characters, try again.\n");
            continue;
        }

        // check if there's any integers in the name, endpoint is throwaway.
        char *endpoint = "";
        int first_name_integers = strtol(first_name, &endpoint, 10);
        int last_name_integers = strtol(last_name, &endpoint, 10);

        if (first_name_integers != 0 || last_name_integers != 0)
        {
            printf("Your name cannot have only numerical values, please try again.\n");
            continue;
        }

        // because the length of the name was an arbitrary value of 50, there's gonna b whitespace after the value
        remove_whitespace(first_name, 50);
        remove_whitespace(last_name, 50);

        // concatenate the strings to make a fullname variable, not needed but a bit cleaner for output
        char full_name[100] = "\0";
        strcat(full_name, first_name);
        strcat(full_name, " ");
        strcat(full_name, last_name);

        // concat with last name to create the bookingid, make sure it's unique.
        bool unique_id = false;
        while (!unique_id)
        {
            /* create booking id with last name + random number */
            srand(time(NULL));
            int r = rand() % 10;

            // convert the random number to str format
            char random_number[5] = "";
            itoa(r, random_number, 10);

            remove_whitespace(random_number, 5);
            strcat(booking_id, last_name);
            strcat(booking_id, random_number);

            /* check every single booking id to see if it's unique */
            bool r1unique = r1_id == booking_id;
            bool r2unique = r2_id == booking_id;
            bool r3unique = r3_id == booking_id;
            bool r4unique = r4_id == booking_id;

            if (r1unique || r2unique || r3unique || r4unique)
            {
                // not unique booking id, try it again.
                continue;
            }

            /* this has been reached so unique_id is true, assign to the correct room. */
            switch(room_index)
            {
                case 0:
                    strcpy(r1_id, booking_id);
                    break;

                case 1:
                    strcpy(r2_id, booking_id);
                    break;

                case 2:
                    strcpy(r3_id, booking_id);
                    break;

                case 3:
                    strcpy(r4_id, booking_id);
                    break;

                default:
                    printf("Something went wrong..");
            }

            unique_id = true;
        }

        printf("Thank you for registering, %s! Your booking ID is %s.\n\tPlease may we now have your DOB:\n", full_name, booking_id);

        // see the data dictionary for a more detailed structure.
        strcpy((char *) customers[room_index][0], booking_id);
        strcpy((char *) customers[room_index][1], full_name);

        valid_name = true;
    }

    /* dob is next, it asked for dd/mm/yy but i'll consider them separate inputs because handing integers
        within strings is past me */

    char dob_input[15] = "";
    int dob_day;
    int dob_month;
    int dob_year;
    int age;

    bool valid_dob = false;
    while (!valid_dob)
    {
        // \t indicates a horizontal space (tab)
        printf("Your DOB (DD MM YYYY) \n\t*note - separate with whitespace e.g 18 06 2003 :");
        fgets(dob_input, sizeof(dob_input), stdin);
        char *endpoint = "";

        // Break down the DD/MM/YY 3 times using strtol.
        dob_day = strtol(dob_input, &endpoint, 10);
        dob_month = strtol(endpoint, &endpoint, 10);
        dob_year = strtol(endpoint, &endpoint, 10);

        // Now range check for each int value, these variables will be true if invalid.
        bool day_check = dob_day < 1 || dob_day > 31;
        bool month_check = dob_month < 1 || dob_month > 12;
        bool year_check = dob_year < 1900 || dob_year > 2019;

        if (day_check || month_check || year_check)
        {
            printf("Received invalid DOB data, check your input and try again.\n");
            continue;
        }

        age = 2019 - dob_year;
        printf("Received DOB as: %d/%d/%d (DD/MM/YY) [%dy], please now proceed to room details.\n\n", dob_day, dob_month, dob_year, age);

        /* convert int to string, you might have to convert string to int @ reuben */
        char age_string[5] = "";
        itoa(age, age_string, 10);

        strcpy((char *) customers[room_index][2], age_string);
        valid_dob = true;
    }

    /* moving away from customer info to the room info, starting with adults/children */
    int adults = 0;
    int children = 0;
    int total_people = 0;

    bool valid_people = false;
    while (!valid_people)
    {
        char adults_input[5] = "";
        printf("How many adults are staying? :");
        fgets(adults_input, 5, stdin);

        char children_input[5] = "";
        printf("How many children are staying? :");
        fgets(children_input, 5, stdin);

        // break down the input using strtol, as with dob, in this case endpoint is never used - throwaway value
        char *endpoint = "";
        adults = strtol(adults_input, &endpoint, 10);
        children = strtol(children_input, &endpoint, 10);
        total_people = adults + children;

        bool invalid_adults = adults < 1 || adults > 4;
        bool invalid_children = children < 1 || children > 4;
        bool invalid_total = total_people < 1 || total_people > 4;

        if (invalid_adults || invalid_children || invalid_total)
        {
            printf("Invalid amount of people. You may only have up to 4 people staying in a room. Try again.\n");
            continue;
        }

        printf("Received %d adults and %d children staying in the room.\n\n", adults, children);

        /* start filling booking_info - see data dictionary for more */
        booking_info[room_index][0] = room_index;
        booking_info[room_index][1] = adults;
        booking_info[room_index][2] = children;
        valid_people = true;
    }

    /* onto board type, the types are: 1 - FB, 2 - HB, 3 - B&B.
            validation: 1, 2, 3 only. */

    int board_type;
    char board_input[5] = "";

    bool valid_board = false;
    while (!valid_board)
    {
        printf("What board type would you like? Enter:\n\t1 - FB, 2 - HB, 3 - B&B :");
        fgets(board_input, 5, stdin);

        // break down using strtol, endpoint is just a throwaway here.
        char *endpoint = "";
        board_type = strtol(board_input, &endpoint, 10);

        /* invalid criteria: < 0, or not 1 or 2 or 3 */
        if (!(board_type == 1 || board_type == 2 || board_type == 3))
        {
            printf("Invalid board type received. Try again.\n");
            continue;
        }

        printf("Received board type %d.\n\n", board_type);

        booking_info[room_index][3] = board_type;
        valid_board = true;
    }

    /* find the duration of the stay, validation is easy - only > 0. */
    int duration;
    char duration_input[5] = "";

    bool valid_duration = false;
    while (!valid_duration)
    {
        printf("For how many days do you plan to stay at the hotel? \n\t(Note - Max 30 Days) :");
        fgets(duration_input, 5, stdin);

        // break down the input using strtol, as usual endpoint is a throwaway.
        char *endpoint;
        duration = strtol(duration_input, &endpoint, 10);

        if (duration < 1 || duration > 30)
        {
            printf("Invalid duration received, try again.");
            continue;
        }

        printf("Received duration as %d days.\n\n", duration);

        booking_info[room_index][4] = duration;
        valid_duration = true;
    }

    /* finally, the daily newspaper. validation is only 0 or 1, and assumes 0. */
    int daily_newspaper;
    char newspaper_input[5] = "";

    bool valid_newspaper = false;
    while (!valid_newspaper)
    {
        printf("Would you like a daily newspaper? Enter :\n\t0 - No, I would not like to receive a daily newspaper.\n\t1 - Yes, I would like to receive a daily newspaper.\nNewspaper Choice :");
        fgets(newspaper_input, 5, stdin);

        // break down input using strtol, endpoint still throwaway.
        char *endpoint = "";
        daily_newspaper = strtol(newspaper_input, &endpoint, 10);

        if (daily_newspaper != 1) daily_newspaper = 0;
        printf("Received daily newspaper input as %d.\n", daily_newspaper);

        booking_info[room_index][5] = daily_newspaper;
        valid_newspaper = true;
    }

    /* all of this is a final test, can be removed in final program */
    printf("==-== CHECKIN SUMMARY ==-==");

    /* customer details */
    printf("\nRoom Choice: %d.", room_index + 1);
    printf("\nBooking ID: %s.", customers[room_index][0]);
    printf("\nName: %s.", customers[room_index][1]);
    printf("\nAge: %s.", customers[room_index][2]);

    /* booking details */
    printf("\nAdults = %d.", booking_info[room_index][1]);
    printf("\nChildren = %d.", booking_info[room_index][2]);
    printf("\nBoard Type = %d. [1 - FB, 2 - HB, 3 - B&B]", booking_info[room_index][3]);
    printf("\nDuration = %d days.", booking_info[room_index][4]);
    printf("\nNewspaper = %d. [1 - YES, 0 - NO]", booking_info[room_index][5]);
}