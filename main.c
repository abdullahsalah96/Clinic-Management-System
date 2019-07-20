#include <stdio.h>
#include "std_types.h"
#include "patients.h"

int main(void)
{
	// declaring some variables
	u8 mode,adminModeFlag=0,passwordFlag=0,adminModes,userModes,quitAdminModeFlag=1,quitSoftwareFlag=1,i=0,scannedSlot;
	u16 enteredPassword,password=1234;
	u8 ID=0,age,gender;
	u8 editedID=0,editedAge,editedGender;
	u8 name[15];
	u8 editedName[15];
	printf("\n\n------------------------\n\nCLINIC MANAGEMENT SYSTEM\n\n------------------------\n\n");
	while(quitSoftwareFlag!=0 && passwordFlag<3){
		//scaning modes from user
		printf("\nPress 1 for Admin mode\nPress 2 for User mode\nPress 0 to quit\n");
		scanf("%hhu",&mode);
		// printf("password = %u\n",password); //shit happens
		if(mode==1)
		{
			//Admin mode code
			enteredPassword=0;
			passwordFlag=0;
			adminModeFlag=0;
			quitAdminModeFlag=1;
			while(enteredPassword!=password && passwordFlag<3)
			{
				// a while loop to prevent user from entering an invalid password for more than 3 times
				printf("\nPlease enter the password: ");
				scanf("%hu",&enteredPassword);
				passwordFlag++;
				if(passwordFlag==3 && enteredPassword!=password){printf("You exceeded the maximum number of trials\n");adminModeFlag=1;}
				else{adminModeFlag=0;}
			}
			if(adminModeFlag!=1){ // if the password is entered correctly
				while(quitAdminModeFlag!=0){ // a while loop to keep the software running in the admin mode unless the user enters 0 to quit it
					printf("\nPress 1 to add new record\nPress 2 to Edit patient record\nPress 3 to reserve a slot with the doctor\nPress 4 to cancel reservation\nPress 0 to quit Admin mode\n");
					scanf("%hhu",&adminModes);
					if(adminModes==1){
						//add new record
						printf("\nEnter ID: ");
						scanf("%hhu",&ID);
						if(checkID(ID)){ //check if the entered ID already exists.
							printf("Enter Name: ");
							scanf("%s",name);
							printf("Enter Gender: ");
							scanf(" %c",&gender);
							printf("Enter Age: ");
							scanf("%hhu",&age);
							addPatient(ID,age,name,gender);
						}
						else{printf("\nID NOT AVAILABLE\n");} // if the ID already exists this message is prompted to the user.
					}

					else if(adminModes==2){
						//edit patient record
						printf("\nEnter ID: ");
						scanf("%hhu",&editedID);
						if(checkID(editedID)==0){ // check if this is a valid ID
							printf("Enter Name: ");
							scanf("%s",editedName);
							printf("Enter Gender: ");
							scanf(" %c",&editedGender);
							printf("Enter Age: ");
							scanf("%hhu",&editedAge);
							editPatientRecord(editedID,editedAge,editedName,editedGender);
						}
						else{printf("\nIncorrect ID\n");}
					}
					else if(adminModes==3){
						//reserve a slot
						printf("\nAvailable slots are....\n");
						for(i=0;i<5;i++){
							if(reservations[i]==1){ //if reservations[i]==1 then this slot is not reserved
								if(i==0){printf("\n%d) 2:00PM to 2:30PM\n",i);}
								else if(i==1){printf("\n%d) 2:30PM to 3:00PM\n",i);}
								else if(i==2){printf("\n%d) 3:00PM to 3:30PM\n",i);}
								else if(i==3){printf("\n%d) 4:00PM to 4:30PM\n",i);}
								else if(i==4){printf("\n%d) 4:30PM to 5:00PM\n",i);}
							}
							else{printf("\n%d) Slot unavailable\n",i);} //else this slot is already reserved.
						}
						printf("\nEnter your ID: ");
						scanf("%hhu",&ID);
						if(checkID(ID)==0){
							if(checkForPreviousReservations(ID)){ //check that this ID doesn't have a previous registration
								printf("\nType the number of slot required: ");
								scanf("%hhu",&scannedSlot);
								if(scannedSlot>4 || reservations[scannedSlot]==0){printf("\nInvalid input\n");} //if number entered is > than the number of available slots-->Invalid
								else{
									addReservations(ID,scannedSlot);
									reservations[scannedSlot]=0;
								}
							}
							else{printf("\nThis ID already has a registration. Please cancel it first!\n");}
						}
						else{printf("\nInvalid ID\n");}

					}
					else if(adminModes==4){
						//cancel reservation
						printf("\nEnter you ID: ");
						scanf("%hhu",&ID);
						if(checkID(ID)==0){
							cancelReservations(ID); //cancel reservation of this ID
						}
						else{printf("\nInvalid ID\n");}
					}
					else if(adminModes==0){quitAdminModeFlag=0;}
					else{printf("\n Invalid Input.");}
				}
			}

		}
		else if(mode==2)
		{
			//User mode code
			printf("\nPress 1 to view patient record\nPress 2 to view today's reservations.\n");
			scanf("%hhu",&userModes);
			if(userModes==1){
				//view patient record
				printf("\n");
				printPatients(); //print patient records
			}
			else if(userModes==2){
				//view today's reservations
				viewReservations(); // view reservations
			}
			else{printf("\nInvalid input\n");}
		}
		else if(mode==0){quitSoftwareFlag=0;} // quit software
		else{printf("\nInvalid input\n");} // if the input is not from the options --> invalid option
	}
}
