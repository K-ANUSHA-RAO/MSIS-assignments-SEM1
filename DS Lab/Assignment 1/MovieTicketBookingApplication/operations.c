#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "commonHeader.h"

// Initialize data for seat class and count
Screen * intialize_screen(int no_of_seat_class)
{
    Screen *my_screen;

    my_screen = (Screen *)malloc(sizeof(Screen));
    if(NULL == my_screen) return MEM_ALLOC_FAIL;


    my_screen->total_no_of_seat_class = no_of_seat_class;
    my_screen->current_seat_class = 0;
    my_screen->total_seats_available = 0;

    //Allocate memory for each Seat_class
    for(int i=0; i<no_of_seat_class;i++)
    {
        my_screen->seat_class[i] = (Seat_class *)malloc(sizeof(Seat_class));
        if(NULL == my_screen->seat_class[i]) return MEM_ALLOC_FAIL;
    }

    return my_screen;

}

// Insert seat class like VIP,Gold,Silver
int insert_seat_class(Screen *my_screen, Seat_class seat_class_data)
{
    if(my_screen->current_seat_class == my_screen->total_no_of_seat_class) return FULL;

    Seat_class *new_class = (Seat_class *)malloc(sizeof(Seat_class));
    if(NULL == new_class) return MEM_ALLOC_FAIL;

    memcpy(new_class, &seat_class_data, sizeof(Seat_class));

     // Determine the starting seat number for this seat class
    int starting_seat_number = 1;
    for(int i = 0; i < my_screen->current_seat_class; i++) {
        starting_seat_number += my_screen->seat_class[i]->total_seat_count;
    }

    // Initialize seats within the seat class
    for(int i = 0; i < new_class->total_seat_count; i++) {
        new_class->seats[i].seat_number = starting_seat_number + i;
        new_class->seats[i].seat_status = 'A'; // Mark all seats as Available initially
    }

    new_class->current_seat_count = 0;

    my_screen->seat_class[my_screen->current_seat_class] = new_class;
    my_screen->current_seat_class++;
    my_screen->total_seats_available += new_class->total_seat_count;

    return SUCCESS;

}

// Function to generate a random booking ID
void generate_booking_id(char *booking_id) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int length = sizeof(characters) - 1;

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate random booking ID
    for (int i = 0; i < ID_SIZE - 1; ++i) {
        booking_id[i] = characters[rand() % length];
    }
    booking_id[ID_SIZE - 1] = '\0'; // Null-terminate the string
}

int add_ticket_booking(Ticket* tickets, int* num_bookings, Ticket new_ticket) {
    if(*num_bookings >= MAX_BOOKINGS) {
        printf("Error: Maximum number of bookings reached.\n");
        return FULL; // No space left
    }

    tickets[*num_bookings] = new_ticket;
    (*num_bookings)++;

    printf("Ticket booking added successfully.\n");
    return 0;
}

// Take input from user and return ticket
Ticket book_movie_ticket(Screen* screen, User user_data, Ticket* tickets, int* num_bookings) {
    Ticket new_ticket;
    generate_booking_id(new_ticket.booking_id); // Generate unique booking ID
    new_ticket.userData = user_data;
    new_ticket.total_price = 0.0;

    Seat_class* seat_class = NULL;

    // Find the seat class based on the user's selection
    for (int i = 0; i < screen->total_no_of_seat_class; i++) {
        seat_class = screen->seat_class[i];
        if (strcmp(seat_class->class_name, user_data.seat_class) == 0) {
            // Attempt to book each seat selected by the user
            for (int j = 0; j < user_data.total_booked_seats; j++) {
                int seat_num = user_data.selected_seat_numbers[j];
                for (int k = 0; k < seat_class->total_seat_count; k++) {
                    if (seat_class->seats[k].seat_number == seat_num) {
                        if (seat_class->seats[k].seat_status == 'A') {
                            seat_class->seats[k].seat_status = 'B'; // Mark seat as booked
                            seat_class->current_seat_count++;
                            screen->total_seats_available--;
                            break;
                        } else {
                            printf("Seat number %d in class %s is already booked.\n", seat_num, user_data.seat_class);
                        }
                    }
                }
            }
            break;
        }
    }

    // Calculate the price based on seat class
    if (strcmp(user_data.seat_class, "VIP") == 0) {
        new_ticket.total_price = user_data.total_booked_seats * 300.0;
    } else if (strcmp(user_data.seat_class, "GOLD") == 0) {
        new_ticket.total_price = user_data.total_booked_seats * 200.0;
    } else if (strcmp(user_data.seat_class, "SILVER") == 0) {
        new_ticket.total_price = user_data.total_booked_seats * 150.0;
    }

    // Add the ticket to the array
    if (add_ticket_booking(tickets, num_bookings, new_ticket) != 0) {
        printf("Failed to add the ticket.\n");
    }

    return new_ticket;
}


// View available seats for booking
void display_available_seats(Screen *my_screen)
{
    for(int i = 0; i < my_screen->current_seat_class; i++) {
        Seat_class *seat_class = my_screen->seat_class[i];
        printf("Seat Class: %s\n", seat_class->class_name);

        for(int j = 0; j < seat_class->total_seat_count; j++) {
            Seat seat = seat_class->seats[j];
            printf("Seat Number: %d, Status: %c\n", seat.seat_number, seat.seat_status);
        }
        printf("\n");
    }
}

// Find a booking by ID
Ticket* find_booking(Ticket* bookings, int num_bookings, const char* booking_id) {
    for(int i = 0; i < num_bookings; i++){
        if(strcmp(bookings[i].booking_id, booking_id) == 0) {
            return &bookings[i];
        }
    }
    return NULL;
}

// Cancel booked seat
void cancel_booked_seat(char bookingId[ID_SIZE], Ticket* bookings, int* num_bookings, Screen *screens)
{
    Ticket* booking = find_booking(bookings, *num_bookings, bookingId);

    if(booking) {
        // Locate the corresponding screen
        int screen_number = booking->userData.screen_number;
        if(screen_number >= 0 && screen_number < SCREEN_COUNT) {
            Screen* screen = &screens[screen_number];
            Seat_class* seat_class = NULL;

            // Find the corresponding seat class
            for(int i = 0; i < screen->total_no_of_seat_class; i++) {
                    printf("%s,",screen->seat_class[i]->class_name);
                if(strcmp(screen->seat_class[i]->class_name, booking->userData.seat_class) == 0) {
                    seat_class = screen->seat_class[i];
                    break;
                }
            }

            if(seat_class) {
                // Cancel booked seats
                for(int i = 0; i < booking->userData.total_booked_seats; i++) {
                    int seat_number = booking->userData.selected_seat_numbers[i];
                    for(int j = 0; j < seat_class->total_seat_count; j++) {
                        if (seat_class->seats[j].seat_number == seat_number) {
                            seat_class->seats[j].seat_status = 'A'; // Mark as available
                            screen->total_seats_available++;
                            break;
                        }
                    }
                }

                // Remove booking from the list
                for(int i = 0; i < *num_bookings; i++) {
                    if(strcmp(bookings[i].booking_id, bookingId) == 0) {
                        for(int j = i; j < *num_bookings - 1; j++) {
                            bookings[j] = bookings[j + 1];
                        }
                        (*num_bookings)--;
                        break;
                    }
                }

                printf("Booking with ID %s has been canceled.\n", bookingId);
            } else {
                printf("Seat class %s not found.\n", booking->userData.seat_class);
            }
        } else {
            printf("Screen number %d is invalid.\n", screen_number);
        }
    } else {
        printf("Booking ID %s not found.\n", bookingId);
    }

}

