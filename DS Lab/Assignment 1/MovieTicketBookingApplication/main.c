#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "operations.c"
int main()
{
    Ticket tickets[MAX_BOOKINGS];
    int num_bookings = 0;
    // Assume 3 screens
    // First screen seating capacity is 150, second and third screen has seatings of 120 each.
    Screen *screen[SCREEN_COUNT];
    int count = 0;
    while(count < SCREEN_COUNT){
        screen[count] = intialize_screen(3);// 3 seat_class VIP, GOLD and SILVER.
        count++;
    }

    screen[0]->total_seats_available = 150;
    screen[1]->total_seats_available = screen[2]->total_seats_available = 120;
    // Screen_class data
    // Inserting Seat_class for each screen
    // Screen 1
    Seat_class seat_class_data1, seat_class_data2, seat_class_data3;
    strcpy(seat_class_data1.class_name,"VIP");
    seat_class_data1.current_seat_count = 0;
    seat_class_data1.total_seat_count = 30;
    insert_seat_class(screen[0],seat_class_data1);
    assert(screen[0]->seat_class[0]->total_seat_count == 30);

    strcpy(seat_class_data2.class_name,"GOLD");
    seat_class_data2.current_seat_count = 0;
    seat_class_data2.total_seat_count = 80;
    insert_seat_class(screen[0],seat_class_data2);
    assert(screen[0]->seat_class[1]->total_seat_count == 80);

    strcpy(seat_class_data3.class_name,"SILVER");
    seat_class_data3.current_seat_count = 0;
    seat_class_data3.total_seat_count = 40;
    insert_seat_class(screen[0],seat_class_data3);
    assert(screen[0]->seat_class[2]->total_seat_count == 40);

    //Screen 2 and 3
    Seat_class seat_class_data4, seat_class_data5, seat_class_data6;
    strcpy(seat_class_data4.class_name,"VIP");
    seat_class_data4.current_seat_count = 0;
    seat_class_data4.total_seat_count = 20;
    insert_seat_class(screen[1],seat_class_data4);
    insert_seat_class(screen[2],seat_class_data4);
    assert(screen[1]->seat_class[0]->total_seat_count == 20);

    strcpy(seat_class_data5.class_name,"GOLD");
    seat_class_data5.current_seat_count = 0;
    seat_class_data5.total_seat_count = 60;
    insert_seat_class(screen[1],seat_class_data5);
    insert_seat_class(screen[2],seat_class_data5);
    assert(screen[1]->seat_class[1]->total_seat_count == 60);

    strcpy(seat_class_data6.class_name,"SILVER");
    seat_class_data6.current_seat_count = 0;
    seat_class_data6.total_seat_count = 40;
    insert_seat_class(screen[1],seat_class_data6);
    insert_seat_class(screen[2],seat_class_data6);
    assert(screen[1]->seat_class[2]->total_seat_count == 40);

    char bookingId[ID_SIZE];
    User user_data;
    int choice;

    do {
        printf("\n*********\n");
        printf("\nMenu:\n");
        printf("\n*********\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Booking\n");
        printf("3. Display Available Seats\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n**************************************************************\n");

        switch(choice) {
            case 1:
                // Book a ticket
                printf("Enter user name: ");
                scanf("%s", user_data.user_name);
                printf("Enter mobile number: ");
                scanf("%s", user_data.mobile_number);
                printf("Enter screen number (0-%d): ", SCREEN_COUNT-1);
                scanf("%d", &user_data.screen_number);
                printf("Enter seat class: (VIP,GOLD,SILVER) ");
                scanf("%s", user_data.seat_class);
                printf("Enter total seats to book: ");
                scanf("%d", &user_data.total_booked_seats);
                printf("Enter seat numbers (space-separated): ");
                for(int i = 0; i < user_data.total_booked_seats; i++) {
                    scanf("%d", &user_data.selected_seat_numbers[i]);
                }

                Ticket new_ticket = book_movie_ticket(screen[user_data.screen_number], user_data, tickets, &num_bookings);
                printf("Ticket booked successfully with Booking ID: %s\n", new_ticket.booking_id);
                break;

            case 2:
                // Cancel a booking
                printf("Enter Booking ID to cancel: ");
                scanf("%s", bookingId);
                cancel_booked_seat(bookingId, tickets, &num_bookings, screen[user_data.screen_number]);
                break;

            case 3:
                // Display available seats
                printf("Enter screen number (0-%d): ", SCREEN_COUNT-1);
                int screen_number;
                scanf("%d", &screen_number);
                if (screen_number >= 0 && screen_number < SCREEN_COUNT) {
                    display_available_seats(screen[screen_number]);
                } else {
                    printf("Invalid screen number.\n");
                }
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
    return 0;
}
