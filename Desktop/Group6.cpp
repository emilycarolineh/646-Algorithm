#include <iostream>       // std::cin, std::cout
#include <queue> 
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <list>
#include <cstdlib>



 
class Bottle {
	public: int amount;
	public: int expiryDate;
};

class Baby {
    public: std::queue<Bottle> bottles; 
    public: int roomNumber;
    public: bool enteral;
    public: int feedingSchedule;
    public: char* name;
    
    void set_room (int);
};

class Output {
	public: 
	char* babyname;
	int room;
	int num2exp;
	int timeToThaw;
	
	//Functions.
	void set_room_output (int);
	void set_babyname(char*);
	void set_num2exp(int);
	void set_timeToThaw(int);
	char* get_babyname();
	
};
void Output::set_babyname(char* a)
 {
     babyname = a;
 }
 char* Output::get_babyname()
 {
     return babyname;
 }
 void Baby::set_room(int a)
 {
    roomNumber = a;
 }
  void Output::set_room_output(int a)
 {
    room = a;
 }
void Output::set_num2exp(int a) {
    num2exp = a;
}
void Output::set_timeToThaw(int a) {
    timeToThaw = a;
}

int roomNumbers[20] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119};


Output doesTheWork(int bottlesAdded, char* stringName, int month, int day, Baby babies[]) {
    
    
	time_t     now = time(0);
    struct tm  nowtm;
    nowtm = *localtime(&now);

	int today = (nowtm.tm_mon + 1) * 100 + nowtm.tm_mday;
	
	int numberOfExpired = 0;
    int numberToThaw = 0;

    //Iterate through every baby’s bottle set.
	for(int i = 0; i < 54; i++) {
		//If we need to add bottles, add them.
		//If we need to add bottles, add them.
		if(bottlesAdded > 0) {
			bool match = false;
		    for(int j = 0; j < strlen(babies[i].name); j++) {
		        if((babies[i].name)[j] != stringName[j]) {
		            break;		
			}
			else if(j == strlen(babies[i].name))
				match = true;
		    }

		        
		    if(match) {
		        //Add every new bottle.
		        for(int j = 0; j < bottlesAdded; j++) {
			        Bottle newBottle;
				    newBottle.amount = 100;
				    newBottle.expiryDate = month* 10 + 01;
					babies[i].bottles.push(newBottle);

				}
		    }
		}
		//Check that none of the bottles need to be tossed out.
		//While the bottle in the front of the queue is expired, remove it. 
		//While expiryDate < today’s date:
			//If there are any bottles that have expired, toss them.
    while(!babies[i].bottles.empty() && babies[i].bottles.front().expiryDate < today) {

		//Report this data as a bottle that needs to be tossed.
		numberOfExpired++;

		//Remove the bottle at the front of the queue.
		babies[i].bottles.pop();
	}
	
    //If a baby’s schedule is enteral, consider the 
	if(babies[i].enteral) {
	    if(babies[i].bottles.front().amount - babies[i].feedingSchedule < babies[i].feedingSchedule) {
			//Toss the top bottle.
			babies[i].bottles.pop();
			//Feed the next bottle to the baby.
			babies[i].bottles.front().amount -= babies[i].feedingSchedule;

		}
					
	}


	//Check that none of the bottles need to be thawed. 
	int hoursInFridge;
	int bottlesLeft = 0;

	std::queue<Bottle> tempQueue;

	//Find the number of bottles in a baby’s part of the fridge.
	while(!babies[i].bottles.empty()) {
		bottlesLeft++;
		Bottle tempBottle = babies[i].bottles.front();
		tempQueue.push(tempBottle);
        babies[i].bottles.pop();

	}
	babies[i].bottles = tempQueue;

	int hoursLeft;

	if(babies[i].enteral) {
		hoursLeft = (bottlesLeft * 100)/babies[i].feedingSchedule;
	} else {
		if(babies[i].feedingSchedule > 50)
			hoursLeft = bottlesLeft;
		else
			hoursLeft = bottlesLeft * 2;
	}
			
			
			
	//Report number to toss and number to thaw.
    Output result;
    result.set_babyname(babies[i].name);
    result.set_room_output(babies[i].roomNumber);
    result.set_num2exp(numberOfExpired);
    result.set_timeToThaw((nowtm.tm_hour + 1) * 10 + nowtm.tm_min);
    return result;


	numberOfExpired = 0;
	}
}


int main() { 

	int bottlesAdded = 0;
	char stringName[10] = "Baby Name";
	int month = 10;
	int day = 04;

	//Initialize test data.
    int expiryDate = 1009;

	Baby babies[55];
    for(int i = 0; i < 55; i++) {
        Baby newBaby;
        newBaby.set_room(roomNumbers[(rand()%19)+1]);
	    babies[i] = newBaby;
	    Bottle newBottle;
	    newBaby.bottles.push(newBottle);
    }

    int testyVariable = 0;
    
    while(testyVariable < 5) {
        Output result = doesTheWork(bottlesAdded, stringName, month, day, babies);
        testyVariable++;
    }

}


