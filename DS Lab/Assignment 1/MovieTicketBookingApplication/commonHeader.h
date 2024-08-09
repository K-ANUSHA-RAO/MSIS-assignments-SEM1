#ifndef COMMONHEADER_H_INCLUDED
#define COMMONHEADER_H_INCLUDED
#define MAX_SEAT_CLASS 5
#define NAME_SIZE 20
#define MOBILE_SIZE 11
#define ID_SIZE 8
#define CODE_SIZE 10


struct _user_data_
{
    char mobile_number[MOBILE_SIZE];
    char user_name[NAME_SIZE]
    int screen_number;
    int selected_seat_numbers[MAX_SEATS];
    int total_booked_seats;
    char seat_class;
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

struct _seat_class_
{
    char class_name[NAME_SIZE];
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

//initialize data for seat class and count
Screen * intialize_screen(int no_of_seat_class);

//insert seat class like VIP,Gold,Silver along
int insert_seat_class(Screen*, Seat_class data);


//take input from user and return ticket
Ticket book_movie_ticket(User user_data);

//view available seats for booking
void display_available_seats(Screen*);


//cancel booked seat
void cancel_booked_seat(char[ID_SIZE] bookingId);

#endif // COMMONHEADER_H_INCLUDED
