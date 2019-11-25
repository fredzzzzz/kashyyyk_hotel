cmake_minimum_required(VERSION 3.15)
project(kashyyyk_hotel_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(kashyyyk_hotel_2 main.c header.h utils/remove_whitespace.c utils/get_room_index.c subroutines/book_table.c subroutines/checkin.c subroutines/checkout.c)