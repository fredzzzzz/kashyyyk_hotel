#ifndef KASHYYYK_HOTEL_2_HEADER_H
#define KASHYYYK_HOTEL_2_HEADER_H

/* you can include the libraries in the header file too */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/* main sub-routines */
int checkin(int booking_info[4][6], int *rooms, char *customers[4][3][128], char *r1_id, char *r2_id, char *r3_id, char *r4_id);
int book_table(int booking_info[4][6], char *table7[3][2], char *table9[3][2], char *freeTables7, char *freeTables9, char *r1_id, char *r2_id, char *r3_id, char *r4_id);
int checkout(int booking_info[4][6], int *rooms, char *customers[4][3][128], char *r1_id, char *r2_id, char *r3_id, char *r4_id);

/* other functions */
void remove_whitespace(char *str, int size);
int get_room_index(char *r1_id, char *r2_id, char *r3_id, char *r4_id);

#endif //KASHYYYK_HOTEL_2_HEADER_H
