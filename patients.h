#ifndef patients_header
#define patients_header
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
typedef struct node_list{ //linked list with 5 data variables
	u8 ID;
	u8 Name[15];
	u8 age;
	u8 gender;
	u8 reservationNumber;
	struct node_list * link;
}node;

extern u8 reservations[5]; //an array that determines the available slots
//prototyping of functions
void addPatient(u8 ID,u8 age,u8 name[15],u8 gender);
void printPatients();
u8 checkID(u8 ID);
void editPatientRecord(u8 ID,u8 age,u8 name[15],u8 gender);
void addReservations(u8 ID,u8 slot);
u8 checkForPreviousReservations(u8 ID);
void viewReservations();
void cancelReservations(u8 ID);

#endif
