#ifndef my_library
#define my_library

typedef struct customer{
	char name[30];
	char surname[30];
	int reservation_day;
	int reservation_month;
	int checkInDay;
	int checkInMonth;
	int checkOutDay;
	int checkOutMonth;
	int roomNumber;
	int cost;
}customer;

int makeRezervation(FILE* fptr);
int lookAvalaibleRooms(customer *person,FILE* fptr2);
void output_Reservation(customer *human);
int room_cost(int room,int day);
void cancelledReservation(FILE* fptr3,FILE* fptr4);
void showReservations(FILE* fptr5);
int show_budget(FILE* fptr6);
int checkValidorNot(int *array,int size);
int checkProperorNot(customer *human2);

#endif
