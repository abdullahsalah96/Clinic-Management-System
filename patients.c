#include "patients.h"


node* head=NULL;
u8 reservations[5]={1,1,1,1,1}; // by default all the Reservations are not reserved, The value of a certain reservation is set to 0 when it has been reserved

void addPatient(u8 ID,u8 age,u8 name[15],u8 gender)
{
	// a function that adds new patient records by adding new node to the linked list
	u8 i=0;
	node *temp=(node*)malloc(sizeof(node)); //create new node
	temp->ID=ID;
	temp->age=age;
	temp->reservationNumber=0;
	for(i=0;i<15;i++){temp->Name[i]=name[i];}
	temp->gender=gender;
	temp->link=NULL; // set the link of the newly created node to NULL
	if(head==NULL){
		head=temp; //in case of first element
	}
	else{
		node* temp2 = head; //initialize node 2 with head of list address
		while(temp2->link!=NULL)
		{ //loop through list to reach last address
			temp2=temp2->link;
		}
		temp2->link=temp; //set last address to new element
	}
}

void printPatients()
{ // a function that prints every single node in the linked list
	u8 i=0,flag=0;
	node *temp=head;
	while(temp!=NULL){
		//while loop to loop through elements of the linked list until it reaches the last one
		flag++;
		printf("the ID of patient %u is %u \n", i,temp->ID);
		printf("the name of patient %u is %s ", i,temp->Name);
		printf("\nthe age of patient %u is %u \n", i,temp->age);
		printf("the gender of patient %u is %c \n", i,temp->gender);
		printf("\n\n");
		temp=temp->link;
		i++;
	}
	if(temp==NULL && flag==0){printf("\nNo patient IDs were entered.\n");}
}

void editPatientRecord(u8 ID,u8 age,u8 name[15],u8 gender){
	//a function that edits the content of a certain node by knowing the ID of the patient
	u8 i=0;
	node *temp =head;
	while(temp!=NULL){
		if(ID==temp->ID)
		{	//if this is the right ID, change the data
		temp->age=age;
		for(i=0;i<15;i++){temp->Name[i]=name[i];}
		temp->gender=gender;
		}
		temp=temp->link;
	}
}

u8 checkID(u8 ID){
	// a function that returns 0 when the ID already exists and returns 1 when the ID doesn't exist
	u8 flag=1,breakFlag=1;
	node *temp=head;
	while(temp!=NULL && breakFlag!=0){
		if(ID==temp->ID){flag=0; breakFlag=0;} // when the desired ID is found set breakFlag=0 so that we don't have to loop through the rest of the linked list
		else{flag=1; breakFlag=1;}
		temp=temp->link;
	}
	return flag;
}

void addReservations(u8 ID,u8 slot){
	// a function to add reservations to the patiens by entering their ID and the number of the reservation slot
	node *temp =head;
	u8 breakFlag=1;
	slot++;
	while(temp!=NULL && breakFlag!=0){
		if(ID==temp->ID)
		{
			temp->reservationNumber=slot;
			breakFlag=0;
		}

		else{breakFlag=1;}
		temp=temp->link;
	}
}

u8 checkForPreviousReservations(u8 ID){
	// a function that checks whether the patient has an existing reservation or not by retunring 0 if he has one and 1 if he didn't make any reservations
	node *temp =head;
	u8 breakFlag=1,flag=1;
	while(temp!=NULL && breakFlag!=0){
		if(ID==temp->ID)
		{
			if(temp->reservationNumber!=0){flag=0;}
			else{flag=1;}
			breakFlag=0;
		}
		else{breakFlag=1;}
		temp=temp->link;
	}
	return flag;
}

void viewReservations(){
	// a function that prints the ID of each patient and his reservation.
	node *temp =head;
	u8 flag=0;
	while(temp!=NULL){
		printf("\nID: %d",temp->ID);
		if(temp->reservationNumber==1){printf(" - Reservation: from 2:00PM to 2:30PM\n");flag++;}
		else if(temp->reservationNumber==2){printf(" - Reservation: from 2:30PM to 3:00PM\n");flag++;}
		else if(temp->reservationNumber==3){printf(" - Reservation: from 3:00PM to 3:30PM\n");flag++;}
		else if(temp->reservationNumber==4){printf(" - Reservation: from 4:00PM to 4:30PM\n");flag++;}
		else if(temp->reservationNumber==5){printf(" - Reservation: from 4:30PM to 5:00PM\n");flag++;}
		else {printf(" - No reservation\n");} // if the patient did not make any reservation.
		temp=temp->link;
	}
	if(temp==NULL && flag==0){printf("\nNo reservations are made yet\n");} // in case that no IDs are entered yet
}
void cancelReservations(u8 ID){
	// a function that cancels a certain reservation by entering a valid ID
	node *temp =head;
	u8 breakFlag=1;
	while(temp!=NULL && breakFlag!=0){
		if(ID==temp->ID)
		{
			if(temp->reservationNumber==0){printf("\nNo reservation to cancel.\n");}
			else{
			    printf("\nCancelling Reservation....\n");
				reservations[(temp->reservationNumber)-1]=1; //set the reservation[i] to 1 indicating that it is free and can be reserved by other patients
				temp->reservationNumber=0;  // set the reservation number to 0 indicating that this patient doesn't have any reservations yet
				breakFlag=0;
			}
		}
		else{breakFlag=1;}
		temp=temp->link;
	}
}
