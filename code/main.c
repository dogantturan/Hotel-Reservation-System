#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define username "admin"												// this name will be used by recepsionist to enter the usarnanme of programme
#define password 12345													// this numbers will be used by recepsionist to enter the password of programme
#define SINGLE_ROOM 150													//this constant will be used for calculating single room cost 
#define DOUBLE_ROOM 250													//this constant will be used for calculating double room cost 
#define FAMILY_ROOM 350													//this constant will be used for calculating family room cost
#define SUITE_ROOM 750													//this constant will be used for calculating suite room cost
#define PRESIDENTAL_ROOM 1000											//this constant will be used for calculating presidental room cost
#define ask "yes"														//this constant will be used in functions to ask sure? 														
#define max 200															//this constant will used for arrays

#include "my_library.h"													//include our own library


int main() {
    char user[5];														
    int check;															//this will be used when we are looking for usarname is true or not
    int passwrd;														//this will be used when we are looking for password is true or not
    int button;															// this will be used for menu operations
    int option;															//this will be used for function returns and function operations
    
    
    printf("\n\n\n");
    printf("\t\t\t\t+--------------------------------------------------------+\n");
    printf("\t\t\t\t+---------------------ADMIN PANEL------------------------+\n");
    printf("\t\t\t\t+--------------------------------------------------------+\n");
    printf("\n\n\n");
    
	printf("\t\t\t\t\tEnter the user name:");
    scanf("%s",user);															//input the usarname
	
	printf("\t\t\t\t\tEnter the password:");
    scanf("%d",&passwrd);														//input the password
    printf("\n\n");
    
    check = strcmp(username,user);												//strcmp is int the header file of string.h (it is checking strings equal or not . if it is equal give us 0 value)
	
	if(check == 0 && passwrd==password ){										// check the password and surname is right if it is right , you are allowed to use programme
		printf("\t\t\t\t\tACCESS ALLOWED\n");
		system("cls");															//clean screen (this function in stdlib.h to use clean the screen )
		
		FILE *customerF;														//make file pointer to began use file
		customerF=fopen("customer.txt","a+");									// file open with "a+" to start end of the file and also we can write function
		
		menu:																	// this menu for go to function
		
		printf("\n\n\n");																			// display of programme screen with options
		printf("\t\t\t\t+--------------------------------------------------------+\n");
		printf("\t\t\t\t+---------------------MAIN MENU--------------------------+\n");
		printf("\t\t\t\t+--------------------------------------------------------+\n");
		printf("\n\n\t\t\t\t1. Add Reservation\n");
		printf("\t\t\t\t2. Delete reservation\n");
		printf("\t\t\t\t3. Show all reservations\n");
		printf("\t\t\t\t4. Show Budget");
		printf("\n\t\t\t\tyour choose:");
		scanf("%d",&button);																		// input the operation number
		
		if(button==1){																				
			system("cls");																			//clean screen
			printf("\n\n\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			printf("\t\t\t\t+------------------ADD RESERVATION-----------------------+\n");			
			printf("\t\t\t\t+--------------------------------------------------------+\n");
	
			option=makeRezervation(customerF);														// send the file pointer to function to make a reservation
			
			if(option==1){																			//if return is equal 1 go to menu again
				system("cls");
				goto menu;																			// go to label of menu
			}
			else{																					//else close the file and exit
				fclose(customerF);
				exit(0);
			}
			
		}
		
		
		else if(button==2){
			
			system("cls");																				//clean screen
			printf("\n\n\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			printf("\t\t\t\t+------------------CANCEL RESERVATION--------------------+\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			
			FILE *customerNew;																			//we open new file to copy the one file to another file when we need to delete a row in file
			customerNew=fopen("custom.txt","w");														//we need to open with "w" because this will be  the new file and we will use for writing
			
			cancelledReservation(customerF,customerNew);												//send the files pointers to function
			
			fclose(customerF);																			
			fclose(customerNew);																		// we need to close two file to rename and remove functions
			
			remove("customer.txt");																		// we remove this file because we copy the datas another file
        	rename("custom.txt","customer.txt");														// we rename the new file to make same name old file 
        	
        	printf("\t\t\t\t1.Do u wanna make another operation\n\t\t\t\t2.EXIT\n\t\t\t\tchoose:");		// we ask recepsionist what operations recepsionist wants
        	scanf("%d",&option);																		//input the operation
        	
        	if(option==1){
        		customerF=fopen("customer.txt","a+");													//we open file again to use in other operations with mode of "a+"
        		system("cls");
				goto menu;																				// go to label of menu 
			}
			
        	else{																						// else programme will exit. We are not closing files because we already closed the files
        		exit(0);
			}
		}
		
		else if(button==3){
			system("cls");
			printf("\n\n\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			printf("\t\t\t\t+------------------ALL RESERVATÝONS----------------------+\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			
			showReservations(customerF);																			// we send the pointer of file to function
			
			printf("\t\t\t\t1.Do u wanna make another operation\n\t\t\t\t2.Do u want to exit\n\t\t\t\tchoose:");	//ask the user operations
			scanf("%d",&option);																					//input the operation
			
			if(option==1){
				system("cls");																//clean the screen
				goto menu;																	// go to label of menu
			}
			else{
				fclose(customerF);															//close the file before exit
				exit(0);
			}
		}
		
		else if(button==4){
			system("cls");
			printf("\n\n\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			printf("\t\t\t\t+------------------SHOW BUDGET---------------------------+\n");
			printf("\t\t\t\t+--------------------------------------------------------+\n");
			
			option=show_budget(customerF);													//send the file pointer to function
			
			if(option==1){																	//if return of function equal 1, go to menu 
				system("cls");																//clean the screen
				goto menu;																	//goto label of menu
			}
			else{
				fclose(customerF);															//close the file before exit
				exit(0);
			}
		}
		
		else{
			printf("\t\t\t\tyou didnt give valid value.\n\t\t\t\tIf u wanna go make another option choose 1 ,else go enter different number to exit\n\t\t\t\tchoose:");
			scanf("%d",&option);															//ask the users if user didnt enter the right function number and input the operation
			
			if(option==1){
				system("cls");
				goto menu;																	//got label of menu
			}
			else{
				fclose(customerF);															//close the file before exit
				exit(0);
			}
		}
	}
 	else{
 		printf("\t\t\t\t\tYOU ARE NOT MY OWNER");											//if usarname and password is not true , display you are not my owner
 		exit(0);
	 }
	
	return 0;
}
