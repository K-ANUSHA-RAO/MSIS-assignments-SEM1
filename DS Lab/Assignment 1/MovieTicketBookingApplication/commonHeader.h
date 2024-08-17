#ifndef COMMONHEADER_H_INCLUDED
#define COMMONHEADER_H_INCLUDED

#define MAX_SEAT_CLASS 5
#define NAME_SIZE 20
#define MOBILE_SIZE 11
#define ID_SIZE 8
#define CODE_SIZE 10
#define MAX_SEATS 20
#define SEAT_COUNT 100
#define MEM_ALLOC_FAIL NULL
#define SCREEN_COUNT 3
#define FULL -1
#define SUCCESS 1
#define MAX_BOOKINGS 100


struct _user_data_
{
    char mobile_number[MOBILE_SIZE];
    char user_name[NAME_SIZE];
    int screen_number;
    int selected_seat_numbers[MAX_SEATS];
    int total_booked_seats;
    char seat_class[NAME_SIZE];
    char promotion_code[CODE_SIZE];
    char selected_show_time;

};
typedef struct _user_data_ User;

struct _ticket_booking_
{
    char booking_id[ID_SIZE];
    User userData;
    double total_price;

};
typedef struct _ticket_booking_ Ticket;

struct _seat_
{
    int seat_number;
    char seat_status;// A-Available B-Booked
};
typedef struct _seat_ Seat;

struct _seat_class_
{
    char class_name[NAME_SIZE];
    Seat seats[SEAT_COUNT];
    int total_seat_count;
    int current_seat_count;
};
typedef struct _seat_class_ Seat_class;

struct _screen_
{
    Seat_class *seat_class[MAX_SEAT_CLASS];
    int total_no_of_seat_class;
    int current_seat_class;
    int total_seats_available;
};
typedef struct _screen_ Screen;

// Initialize data for seat class and count
Screen * intialize_screen(int no_of_seat_class);

// Insert seat class like VIP, Gold, Silver and assign seat numbers to each class
int insert_seat_class(Screen*, Seat_class data);

// Take input from user and return ticket
Ticket book_movie_ticket(Screen* screen, User user_data, Ticket* tickets, int* num_bookings);

// View available seats for booking
void display_available_seats(Screen*);

// Cancel booked seat
void cancel_booked_seat(char bookingId[ID_SIZE], Ticket* bookings, int* num_bookings, Screen screens[SCREEN_COUNT]);

#endif // COMMONHEADER_H_INCLUDED
