#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define username "admin"
#define password 12345
#define SINGLE_ROOM 150
#define DOUBLE_ROOM 250
#define FAMILY_ROOM 350
#define SUITE_ROOM 750
#define PRESIDENTAL_ROOM 1000
#define ask "yes"
#define max 200

#include "my_library.h"										//include our own library


int makeRezervation(FILE* fptr){							//the function of make a reservation

	customer stranger;										//define the new customer struct to use
	
	char check[3];											//this will be used for when we ask yes or no											
	int asking;												// this will be used when function returns and operations number
	int i=0;
	int j=0;
	
	reservation:											//the label of goto
	
	printf("\n\n\t\t\t\tPlease enter the customer name: ");
	scanf("%s",stranger.name);													//input the guest name
	
	printf("\n\t\t\t\tPlease enter the customer surname: ");
	scanf("%s",stranger.surname);												//input the guest surname
	
	printf("\n\t\t\t\tPlease enter the day of when making reservation: ");
	scanf("%d",&stranger.reservation_day);										//input the day of when reservations making 
	
	for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not		
		if(stranger.reservation_day>30 || stranger.reservation_day<=0){			
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&stranger.reservation_day);								//enter again
		}
		else{
			i=1;																//when the day will be among 0-30 , i will be 1 then loop end
		}
	}
	
	printf("\n\t\t\t\tPlease enter the month whem making reservation:");
	scanf("%d",&stranger.reservation_month);									//input the making reservation month
	
	for (i=0;i<1;){																//the loop of check if the month of reservation among 0-12 or not
		if(stranger.reservation_month>12 || stranger.reservation_month<=0){
			printf("\n\t\t\t\tWe are in season of January and February so Please enter among 1-12 values : ");
			scanf("%d",&stranger.reservation_month);							//enter the month again
		}
		else{
			i=1;																//when the month will be among 0-12 , i will be 1 then loop end
		}
	}
	
	printf("\n\t\t\t\tPlease enter the check in day: ");
	scanf("%d",&stranger.checkInDay);											//input the day when you will check in the hotel
	
	for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
		if(stranger.checkInDay>30 || stranger.checkInDay<=0){
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&stranger.checkInDay);
		}
		else{
			i=1;
		}
	}
	
	printf("\n\t\t\t\tPlease enter the check in month:");
	scanf("%d",&stranger.checkInMonth);											//input the month when you will check in the hotel
	
	for (i=0;i<1;){																//the loop of check if the month of reservation among 0-12 or not
		if(stranger.checkInMonth>12 || stranger.checkInMonth<=0){
			printf("\n\t\t\t\tWe are in season of January and February so Please enter among 1-12 values :");
			scanf("%d",&stranger.checkInMonth);
		}
		else{
			i=1;
		}
	}
	
	printf("\n\t\t\t\tPlease enter the check out day:");
	scanf("%d",&stranger.checkOutDay);											//input the day when you will check out the hotel
	
	for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
		if(stranger.checkOutDay>30 || stranger.checkOutDay<=0){
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&stranger.checkOutDay);
		}
		else{
			i=1;
		}
	}
	
	printf("\n\t\t\t\tPlease enter the check out month:");
	scanf("%d",&stranger.checkOutMonth);										//input the month when ou will check out the hotel
	
	for (i=0;i<1;){																//the loop of check if the month of reservation among 0-12 or not
		if(stranger.checkOutMonth>12 || stranger.checkOutMonth<=0){
			printf("\n\t\t\t\tWe are in season of January and February so Please enter among 1-12 values :");
			scanf("%d",&stranger.checkOutMonth);
		}
		else{
			i=1;
		}
	}
	
	asking=checkProperorNot(&stranger);											// send struct customer to function and take return (this will be compare the check out/in and reservation datas  to make sense the dates)
	
	if(asking==0){																// if returns of funciton equal zero , enter the datas again
		printf("\n\t\tPlease do not enter the date of check in  bigger than check out or reservation date. Please enter guest datas again\n");
		goto reservation;														//goto label of reservation to enter datas again
	}
	
	jump:																		//the label of goto

	stranger.roomNumber=lookAvalaibleRooms(&stranger,fptr);						//send the struct and file pointer to function of look avaliable rooms and enter the room number
	
	if(stranger.roomNumber==0){													//if returns of function equal zero , go to menu 
		return 1;
	}
	else{
		
		stranger.cost= room_cost(stranger.roomNumber,stranger.checkOutDay-stranger.checkInDay+(stranger.checkOutMonth-stranger.checkInMonth)*30);

		printf("\n\t\t\t\tThe reservation cost is %d.Do you want to make a reservation still?(yes/no): ",stranger.cost);
		scanf("%s",check);
		asking=strcmp(check,ask);
	
		if(asking==0){
			fprintf(fptr,"\n%s %s %d %d %d %d %d %d %d %d",stranger.name,stranger.surname,stranger.reservation_day,stranger.reservation_month,stranger.checkInDay,stranger.checkInMonth,stranger.checkOutDay,stranger.checkOutMonth,stranger.roomNumber,stranger.cost);
			output_Reservation(&stranger);
			printf("\t\t\t\t1.Do u wanna go to menu\n\t\t\t\t2.Do u wanna make another reservation addition\n\t\t\t\t3.Do u wanna exit the program\n\t\t\t\tchoose:");
        	scanf("%d",&asking);
        	
        	if(asking==1){
        		return 1;
			}
			else if(asking==2){
				goto reservation;
			}
       		else{
        		return 0;
			}
		}
		else{
			system("cls");
			printf("\t\t\t\t1.Do u wanna look another room type for reservation\n\t\t\t\t2.Do u wanna go to menu for another operation\n\t\t\t\t3.EXIT\n\t\t\t\t");
			scanf("%d",&asking);
			if(asking==1){
				goto jump;
			}
			else if(asking==2){
				return 1;
			}
			else{
				return 0;
			}
		}	
	}
	
}


void output_Reservation(customer *human){ 		//the function of output the new reservation

	printf("\t\t\t\t%s %-10s %d.%d/%d.%d %dTL \n",human->name,human->surname,human->checkInDay,human->checkInMonth,human->checkOutDay,human->checkOutMonth,human->cost);

}


int room_cost(int room,int day){				//the function of calculating room cost
	
	if(room<1006 && room>1000){					// if room number among these values, the return will the value of room cost
		return day*SINGLE_ROOM;					//calculate the how much money will be room cost
	}
	else if(room<2006 && room>2000){
		return day*DOUBLE_ROOM;
	}
	else if(room<3006 && room>3000){
		return day*FAMILY_ROOM;
	}
	else if(room<4006 && room>4000){
		return day*SUITE_ROOM;
	}
	else if(room<5006 && room>5000){
		return day*PRESIDENTAL_ROOM;
	}
	
}

int checkProperorNot(customer *human2){						// this function will be used for compare the value of reservation datas and check in datas and check out datas to see there is any meaningless . For example if reservation day will be after the checkin day,the programme will not accept that
	
	if(human2->reservation_month==human2->checkInMonth){			//if reservation day will be after the check in day ,the programme will not ignore that
		if(human2->checkInDay<human2->reservation_day){
			return 0;												//return 0 value to enter datas again
		}
	}
	
	else if(human2->reservation_month>human2->checkInMonth){		//if reservation month will be after check in month , the programme will not ignore that
		return 0;													//return 0 value to enter datas again
	}
	
	
	if(human2->checkInMonth==human2->checkOutMonth){				//if check out day will be before the check in day ,the programme will not acceppt that
		if(human2->checkInDay>human2->checkOutDay){
			return 0;												//return 0 value to enter datas again
		}
		else{
			return 1;												//return 1 value to keep going the other operations . It is cool for programme . there is no problem.
		}
	}
	
	else if(human2->checkInMonth<human2->checkOutMonth){			//if check in month before check out month , it is cool.
		return 1;													//return 1 value to keep going the other operations . It is cool for programme . there is no problem.
	}
	
	else{															// the else situtations says us the check out month before the check in day. So the programme mustnt ignore that
		return 0;													// return 0 value to enter the datas again
	}
	
}


int lookAvalaibleRooms(customer *person,FILE* fptr2){
	int number;																//this will be used for input values of operations
	
	lookingOtherType:														//the label of go to
	
	printf("\t\t\t\t1.Single room 150$ for one night \n\t\t\t\t2.Double room 250$ for one night\n\t\t\t\t3.Family room 350$ for one night\n\t\t\t\t4.Suite room 750$ for one night \n\t\t\t\t5.Presidental room 1000$ for one night\n");
	printf("\t\t\t\tPlease enter the type of room:");
	scanf("%d",&number);													//input the number of operation
	
	customer stranger2;														//define new customer struct not to confuse other struct datas 
	
	int i,j=0;
	int day,day2,day3,day4;
	

	int arr1[5]={1001,1002,1003,1004,1005};									//make an array which include single room number
	int arr2[5]={2001,2002,2003,2004,2005};									//make an array which include double room number
	int arr3[5]={3001,3002,3003,3004,3005};									//make an array which include family room number
	int arr4[5]={4001,4002,4003,4004,4005};									//make an array which include suite room number
	int arr5[5]={5001,5002,5003,5004,5005};									//make an array which include presidental room number
	
	fseek(fptr2, 0, SEEK_SET);												//we need to come the start of file . Because we did open the file with "a+" MODE (This mode make stay us the end of the file)
	
	if(number==1){															//choosen the single room type
		while(!feof(fptr2)){
    		fscanf(fptr2, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    		// we are reading file with fscanf with all datas . And we make the assignment to new struct to compare person struct
    		if(stranger2.roomNumber<1006&&stranger2.roomNumber>1000){		//we will compare the datas in this if. Because we need to see there is any available room when we enter the hotel
									
    			day=((stranger2.checkInMonth-1)*30)+stranger2.checkInDay;						// we need to make sense for compare values for example if the day 2 mont 2 , the check in day w,ll be 32
    			day2=((stranger2.checkOutMonth-1)*30)+stranger2.checkOutDay;
    			day3=((person->checkInMonth-1)*30)+person->checkInDay;
    			day4=((person->checkOutMonth-1)*30)+person->checkOutDay;
    			
    			
    			if(day3-1<day){																	//if the room is occupied among the check in date - check out date of guest , we make the room number 0 to not use room twice time
    				if(day2<day4+1){
    					for(i=0;i<5;i++){
    						if(arr1[i]==stranger2.roomNumber){
    						arr1[i]=0;
							}
						}
					}
				}
				if(day4+1>day){																	//if check out day of person among the occupied room, we make room number 0 to not use room twice time
					if(day2+1>day4){
						for(i=0;i<5;i++){
    						if(arr1[i]==stranger2.roomNumber){
    						arr1[i]=0;
							}
						}
					}
				}
				if(day3>day-1){																	//if check in day of person among the occupied room,we make room number 0 to not use room again
					if(day2+1>day3){
    					for(i=0;i<5;i++){
    						if(arr1[i]==stranger2.roomNumber){
    						arr1[i]=0;
							}
						}
					}
				}
				
			}
		}
		
		stranger2.roomNumber= checkValidorNot(&arr1[0],5);					//we send arrays to function , show the available rooms or say there is no available room number. then you will choose the room number
		
		if(stranger2.roomNumber==2){
			goto lookingOtherType;											//if return is equal 2 , this mean there is no available room that dates in this room type. So you will go to choose another room type
		}
		else{																//else it is cool or the programme will return menu
			return stranger2.roomNumber;
		}
		
	}
			
	

	
	
	else if(number==2){
		while(!feof(fptr2)){
    		fscanf(fptr2, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    	
    		if(stranger2.roomNumber<2006&&stranger2.roomNumber>2000){
    			day=((stranger2.checkInMonth-1)*30)+stranger2.checkInDay;
    			day2=((stranger2.checkOutMonth-1)*30)+stranger2.checkOutDay;
    			day3=((person->checkInMonth-1)*30)+person->checkInDay;
    			day4=((person->checkOutMonth-1)*30)+person->checkOutDay;
    			
    			if(day3-1<day){
    				if(day2<day4+1){
    					for(i=0;i<5;i++){
    						if(arr2[i]==stranger2.roomNumber){
    						arr2[i]=0;
							}
						}
					}
				}
				
				if(day4+1>day){
					if(day2+1>day4){
						for(i=0;i<5;i++){
    						if(arr2[i]==stranger2.roomNumber){
    						arr2[i]=0;
							}
						}
					}
				}
				
				if(day3>day-1){
					if(day2+1>day3){
    					for(i=0;i<5;i++){
    						if(arr2[i]==stranger2.roomNumber){
    						arr2[i]=0;
						}
					}
				}
				}
			}
		}
		
		stranger2.roomNumber= checkValidorNot(&arr2[0],5);
		
		if(stranger2.roomNumber==2){
			goto lookingOtherType;
		}
		else{
			return stranger2.roomNumber;
		}
		
	}
	
	else if(number==3){
		while(!feof(fptr2)){
    		fscanf(fptr2, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    	
    		if(stranger2.roomNumber<3006&&stranger2.roomNumber>3000){
    					day=((stranger2.checkInMonth-1)*30)+stranger2.checkInDay;
    					day2=((stranger2.checkOutMonth-1)*30)+stranger2.checkOutDay;
    					day3=((person->checkInMonth-1)*30)+person->checkInDay;
    					day4=((person->checkOutMonth-1)*30)+person->checkOutDay;
    					
    					if(day3-1<day){
    					if(day2<day4+1){
    						for(i=0;i<5;i++){
    							if(arr3[i]==stranger2.roomNumber){
    							arr3[i]=0;
								}
							}
						}
						}
						if(day4+1>day){
							if(day2+1>day4){
								for(i=0;i<5;i++){
    								if(arr3[i]==stranger2.roomNumber){
    								arr3[i]=0;
									}
								}
							}
						}
				
						if(day3>day-1){
							if(day2+1>day3){
    							for(i=0;i<5;i++){
    								if(arr3[i]==stranger2.roomNumber){
    								arr3[i]=0;
							}
						}
						}
					
			}
		}
	}
		stranger2.roomNumber= checkValidorNot(&arr3[0],5);
		
		if(stranger2.roomNumber==2){
			goto lookingOtherType;
		}
		else{
			return stranger2.roomNumber;
		}
		
		
	}
	
	else if(number==4){
		while(!feof(fptr2)){
    		fscanf(fptr2, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    	
    		if(stranger2.roomNumber<4006&&stranger2.roomNumber>4000){
    			day=((stranger2.checkInMonth-1)*30)+stranger2.checkInDay;
    			day2=((stranger2.checkOutMonth-1)*30)+stranger2.checkOutDay;
    			day3=((person->checkInMonth-1)*30)+person->checkInDay;
    			day4=((person->checkOutMonth-1)*30)+person->checkOutDay;
    			
    			
    			if(day3-1<day){
    				if(day2<day4+1){
    					for(i=0;i<5;i++){
    						if(arr4[i]==stranger2.roomNumber){
    						arr4[i]=0;
							}
						}
					}
				}
				
				if(day4+1>day){
					if(day2+1>day4){
						for(i=0;i<5;i++){
    						if(arr4[i]==stranger2.roomNumber){
    						arr4[i]=0;
							}
						}
					}
				}
				
				if(day3>day-1){
					if(day2+1>day3){
    					for(i=0;i<5;i++){
    						if(arr4[i]==stranger2.roomNumber){
    						arr4[i]=0;
						}
					}
				}
				}
			}
		}
		
		stranger2.roomNumber= checkValidorNot(&arr4[0],5);
		
		if(stranger2.roomNumber==2){
			goto lookingOtherType;
		}
		else{
			return stranger2.roomNumber;
		}
		
	}
	
	else if(number==5){
		while(!feof(fptr2)){
    		fscanf(fptr2, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    	
    		if(stranger2.roomNumber<5006&&stranger2.roomNumber>5000){
    			day=((stranger2.checkInMonth-1)*30)+stranger2.checkInDay; 
    			day2=((stranger2.checkOutMonth-1)*30)+stranger2.checkOutDay; 
    			day3=((person->checkInMonth-1)*30)+person->checkInDay;	
    			day4=((person->checkOutMonth-1)*30)+person->checkOutDay; 
    			
    			
    			if(day3-1<day){			
    				if(day2<day4+1){
    					for(i=0;i<5;i++){
    						if(arr5[i]==stranger2.roomNumber){
    						arr5[i]=0;
							}
						}
					}
				}
				if(day4+1>day){
					if(day2+1>day4){
						for(i=0;i<5;i++){
    						if(arr5[i]==stranger2.roomNumber){
    						arr5[i]=0;
							}
						}
					}
				}
				if(day3>day-1){
					if(day2+1>day3){
    					for(i=0;i<5;i++){
    						if(arr5[i]==stranger2.roomNumber){
    						arr5[i]=0;
						}
					}
					}
				}
			}
		}
		
		stranger2.roomNumber= checkValidorNot(&arr5[0],5);
		
		if(stranger2.roomNumber==2){
			goto lookingOtherType;
		}
		else{
			return stranger2.roomNumber;
		}
	}
}


int checkValidorNot(int *array,int size){									//this function will display available rooms or display all rooms are occupied and also this function will enter the room available room
	int i=0;
	int j=0;
	int arr[size];															//assignment array to pointer arrays datas shared with this array
	int option;																//operation  number 
	customer stranger;														
	
	for(i=0;i<5;i++){														//the loop of share the pointer arrays datas to new array
		arr[i]=*(array+i);
	}
	
	i=0;
	for(j=0;j<5;j++){														//the loop of display available rooms except 0 values(0 values show the occupied rooms)
		if(arr[j]!=0){
			printf("\t\t\t\t%d.Available Room number %d\n",j+1,arr[j]);
		}
		else{
			i++;															//we increase the i number when room is occupied
		}
	}
	
	if(i==5){																//if occupied rooms number 5 , this means all rooms occupied so displaying for another operation

		printf("\t\t\t\tPlease choose another room type(enter 1) or go exit(enter number except 1):");
		scanf("%d",&option);
			
		if(option==1){
			return 2;
		}
		else{
			return 0;
		}
	}	
	
	printf("\n\t\t\t\tPlease enter the room number:");		
	scanf("%d",&stranger.roomNumber);
		
	for(i=0;i<1;){																//the loop of checking the input room number is right or not
		for(j=0;j<5;j++){
			if(arr[j]==stranger.roomNumber){
				i=1;
				return stranger.roomNumber;
			}
		}
		if(i==0){
			printf("\n\t\t\t\tPlease enter the valid number room:");
			scanf("%d",&stranger.roomNumber);
		}
	}		
}


void cancelledReservation(FILE* fptr3,FILE* fptr4){											//the function of cancel the reservation
	fseek(fptr3, 0, SEEK_SET);																//we need to come the start of file . Because we did open the file with "a+" MODE (This mode make stay us the end of the file)
	
	customer stranger;																		//this will be used for input name and surname
	customer stranger2;																		//this will be used for reading file values and assignments
	int check,check2;																		//this will be use for compare strings
	int line=0;
	int i=0;								
	int cancel_line;
	
	printf("\t\t\t\tPlease enter the guest name to cancelled the reservation:");			//input the datas of guest who will cancel reservation
	scanf("%s",stranger.name);
	
	printf("\t\t\t\tSurname:");
	scanf("%s",stranger.surname);
	
	while(!feof(fptr3)){
    		fscanf(fptr3, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    		//reading datas and make these assignments to struct
			line++;
			
			check=strcmp(stranger2.name,stranger.name);
			check2=strcmp(stranger2.surname,stranger.surname);
			
    		if(check==0 && check2==0){													//if name and surname matched, this function will look for the today date to cancel reservation is cool or not
    			printf("\t\t\t\tPlease enter the date of today . Day (1-30):");
    			scanf("%d",&stranger.reservation_day);
    			for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
					if(stranger.reservation_day>30 || stranger.reservation_day<=0){
						printf("\n\t\t\t\tPlease enter among 1-30 values : ");
						scanf("%d",&stranger.reservation_day);
					}
				else{
					i=1;
				}
			}
    			printf("\t\t\t\tMonth(1-12):");
    			scanf("%d",&stranger.reservation_month);
    			for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
					if(stranger.reservation_month>12 || stranger.reservation_month<=0){
						printf("\n\t\t\t\tPlease enter among 1-30 values : ");
						scanf("%d",&stranger.reservation_month);
					}
				else{
					i=1;
				}
			}
    			
    			if(stranger2.checkInMonth==stranger.reservation_month){
    				if(stranger2.checkInDay-1<=stranger.reservation_day){					// in these ifs, we are looking for cancel day is before one day or after check in day . If cancel day before at least two days check in day , it is cool.
    					printf("\t\t\t\tWe are sorry not to cancelled because it is not proper our hotel reservation rules\n ");
					}
    				else{ 
    					cancel_line=line;
					}
				}
				else if(stranger2.checkInMonth>stranger.reservation_month){
					cancel_line=line;
				}
				else{
					printf("\t\t\t\tWe are sorry not to cancelled because it is not proper our hotel reservation rules\n ");
				}
			}
		}
		
	fseek(fptr3, 0, SEEK_SET);														// we turn back the start of file, for scanning again
	line = 1;
	
	 while (!feof(fptr3)) 
        {
            fscanf(fptr3, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    		//scan datas
            if (!feof(fptr3)) {
                if (line != cancel_line) {											//if the scanf data is not equal  cancel line , we will the datas write other file 
                	if(line==1){													// if line is 1, we dont write \n
                		fprintf(fptr4,"%s %s %d %d %d %d %d %d %d %d",stranger2.name,stranger2.surname,stranger2.reservation_day,stranger2.reservation_month,stranger2.checkInDay,stranger2.checkInMonth,stranger2.checkOutDay,stranger2.checkOutMonth,stranger2.roomNumber,stranger2.cost);
						//write datas other file
					}
					else{
						fprintf(fptr4,"\n%s %s %d %d %d %d %d %d %d %d",stranger2.name,stranger2.surname,stranger2.reservation_day,stranger2.reservation_month,stranger2.checkInDay,stranger2.checkInMonth,stranger2.checkOutDay,stranger2.checkOutMonth,stranger2.roomNumber,stranger2.cost);
						//write datas other file
					}
                }
                line++;
            }
            
        } 
        
}


void showReservations(FILE* fptr5){										//the function of show reservation day  to the recepsionist 
	int option,day,month;
	int i;
	customer stranger2;
	
	fseek(fptr5, 0, SEEK_SET);											// we turn back the start of file, for scanning again
	
	
	jump:																//the label of goto
	
	printf("\t\t\t\t1.Show expected reservations\n\t\t\t\t2.Show all reservations in this season\n\t\t\t\tchoose:");
	scanf("%d",&option);
	
	if(option==1){														//if input value equal 1, we will show the soon reservations date
		
		printf("\t\t\t\tPlease enter the today day(1-30):");
		scanf("%d",&day);												//enter today date datas
		for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
		if(day>30 || day<=0){
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&day);
		}
		else{
			i=1;
		}
	}
		printf("\t\t\t\tPlease enter the this month(1-12):");
		scanf("%d",&month);
		for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
		if(month>12 || month<=0){
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&month);
		}
		else{
			i=1;
		}
	}
		
		printf("\t\t\t\tSoon reservations in same month\n");
		printf("\t\t\t\tNAME       SURNAME CHECK IN/CHECK OUT   ROOM NUMBER COST\n");
		
		while(!feof(fptr5)){											//the loop of scan the same month reservations
		
    		fscanf(fptr5, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    		
    		if(stranger2.checkInMonth==month){
    			if(stranger2.checkInDay>day){
    				printf("\t\t\t\t%-10s %-10s %d.%d/%d.%-10d %-10d %d\n\n",stranger2.name,stranger2.surname,stranger2.checkInDay,stranger2.checkInMonth,stranger2.checkOutDay,stranger2.checkOutMonth,stranger2.roomNumber,stranger2.cost);
					//display same month reservations
				}
			}
			
		}
	}
	
	else if(option==2){													//the loop of scan all reservations
		printf("\t\t\t\tAll reservations in this season\n");
		printf("\t\t\t\tNAME       SURNAME CHECK IN/CHECK OUT   ROOM NUMBER COST\n");
		
		while(!feof(fptr5)){
    		
			fscanf(fptr5, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
    		//read datas
			printf("\t\t\t\t%-10s %-10s %d.%d/%d.%-10d %-10d %d\n\n",stranger2.name,stranger2.surname,stranger2.checkInDay,stranger2.checkInMonth,stranger2.checkOutDay,stranger2.checkOutMonth,stranger2.roomNumber,stranger2.cost);
			//display datas
		}
	}
	
	else{																		//if input number is not valid,show another operations
		printf("\t\t\t\tPlease 1.enter valid value \n\t\t\t\t2.go exit(enter number except 1)");
		scanf("%d",&option);
		
		if(option==1){
			goto jump;															//go to label of jump make another operation
		}
		else{
			fclose(fptr5);														//close the file and exit
			exit(0);
		}
	}
	
}


int show_budget(FILE* fptr6){													//this function will show the how much money earned till toady or how much money you will earn this season
	
	int costsArray[200];
	int todayday,todaymonth;
	int option;
	int weWillEarn=0;
	int weEarnedTillToday=0;
	int i=0;
	
	fseek(fptr6, 0, SEEK_SET);													// we turn back the start of file, for scanning again
	
	customer stranger2;
	
	printf("\t\t\t\t1.Do u wanna see how much you earned till today\n\t\t\t\t2.Do u wanna see how much you will have earned end of this season\n\t\t\t\t3.Do u wanna go menu or exit\n\t\t\t\tchoose:");
	scanf("%d",&option);														//input operation number
	
	if(option==2){																//if number is equal 2
		
		while(!feof(fptr6)){
			
    		fscanf(fptr6, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);        
			//read datas
			
			costsArray[i]=stranger2.cost;										//make an assignment cost to array
			
			weWillEarn= weWillEarn+costsArray[i];								//sum the costs for learn how much we will earn
			
			i++;	
		}
		printf("\t\t\t\tHow much we will earn this season: %d", weWillEarn);
		
		printf("\n\t\t\t\t1.Do you wanna make another operation\n\t\t\t\t2.Do you wanna exit\n\t\t\t\tchoose:");
		scanf("%d",&option);
		
		if(option==1){
			return 1;															//return to menu
		}
		else{
			return 0;															//exit in main c
		}	
	}
	
	else if(option==1){															
		i=0;	
		printf("\n\t\t\t\t\tenter today day\n\t\t\t");
		scanf("%d",&todayday);													//enter the today to learn how much you have earned  till toady
		for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
		if(todayday>30 || todayday<=0){
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&todayday);
		}
		else{
			i=1;
		}
	}
		printf("\t\t\t\t\tenter today month\n\t\t\t");
		scanf("%d",&todaymonth);
		for (i=0;i<1;){																//the loop of check if the day of reservation among 0-30 or not
		if(todaymonth>12 || todaymonth<=0){
			printf("\n\t\t\t\tPlease enter among 1-30 values : ");
			scanf("%d",&todaymonth);
		}
		else{
			i=1;
		}
	}
	
		while(!feof(fptr6)){
			
    		fscanf(fptr6, "%s%s%d%d%d%d%d%d%d%d",stranger2.name, stranger2.surname, &stranger2.reservation_day, &stranger2.reservation_month, &stranger2.checkInDay, &stranger2.checkInMonth, &stranger2.checkOutDay, &stranger2.checkOutMonth, &stranger2.roomNumber, &stranger2.cost);
				//read datas
				
    		if(stranger2.checkInMonth==todaymonth){								//if the datas match in same month
    			if(stranger2.checkInDay<todayday){								//if the day lower than today day
    				costsArray[i]=stranger2.cost;
    				weEarnedTillToday=weEarnedTillToday+costsArray[i];			//sum the datas
    				i++;
					}
				}
			else if(stranger2.checkInMonth<todaymonth){							//if the month smaller than today month
				costsArray[i]=stranger2.cost;
    			weEarnedTillToday=weEarnedTillToday+costsArray[i];				// sum the datas
    			i++;
			}
		}
		
		printf("\t\t\t\tHow much we have earned: %d",weEarnedTillToday);
		
		printf("\n\t\t\t\t1.Do you wanna make another operation\n\t\t\t\t2.Do you wanna exit\n\t\t\t\tchoose:");
		scanf("%d",&option);
		
		if(option==1){
			return 1;															// go to menu
		}
		else{
			return 0;															// exit in main c
		}
	}
	else{
		printf("\t\t\t\t1.Do you wanna make another operation\n\t\t\t\t2.Do you wanna exit\n\t\t\t\tchoose:");
		scanf("%d",&option);
		
		if(option==1){
			return 1;																//go to menu
		}
		else{
			return 0;																//exit in main c
		}
	}
}
