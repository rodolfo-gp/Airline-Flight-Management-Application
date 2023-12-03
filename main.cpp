#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

#include "headers/airline.h"
#include "headers/flight.h"
#include "headers/passenger.h"
#include "headers/seat.h"
#include "SRC/extraction.cpp"
#include "headers/Globalfunctions.h"

int main(){
    
    std::ifstream readingstream("flight_info.txt");
    
    //read all data from file and turn it into objects, lists, ect. in the program
    // airline ptr
    if(!readingstream.is_open()){
        std::cout << "****************FILE ERROR****************\n";
    }
    std::string line = extract_the_line(readingstream); // reads first line

    Airline a1 = extract_airline(line); //makes airline object based on first line
    a1.set_num(1);
    Flight* f1 = extract_flight(line); //makes flight object on the heap based on first line
    
    FlightList* fl1 = new FlightList{*f1, nullptr}; //first flightlist struct 

    a1.set_list(fl1); // sets first flightlist struct as head of list

    ///////////////READING FILE THE FIRST TIME///////////////////////////////////////////
    while(!readingstream.eof()){
        std::string line = extract_the_line(readingstream);
        Passenger* new_pass = extract_passenger(line);
        PassengerList* p1 = new PassengerList{*new_pass, nullptr}; // first passengerlist struct
        
        p1->next = a1.get_list()->flight.get_pass_listH();
        a1.get_list()->flight.set_pass_listH(p1);
        p1 = nullptr;
        delete new_pass;
        new_pass = nullptr;
    }
    //////////////////////////////////////FIRST SETUP////////////////////////////////
    a1.get_list()->flight.update_FSmap(); //updating the seat map with all info
    printfirstmessege();
    int runprogram = 1; //bool logic to eventually exit the program
    char selection;
    ////////////////////////////////////////////////////////////////////////////////////////////
    if(pressreturntocontinue()){
        printoptions();
        ///////////////////////////////////////////MAIN PROGRAM LOOP///////////////////////////////////////////
        while(runprogram){ 
            std::cin >> selection;
            if(selection == '1'){
                a1.get_list()->flight.update_FSmap();
                DisplaySeatMap(a1.get_list()->flight); 
                pressreturntocontinue();
                printoptions();

            }else if (selection == '2'){
              
              a1.get_list()->flight.DisplayPassInfo();
                pressreturntocontinue();
                printoptions();
            }
            else if (selection == '3')
            {
                (a1.get_list()->flight).addpassenger(); //Add new passenger
                (a1.get_list()->flight).update_FSmap(); // update map
                pressreturntocontinue();
                printoptions();            
            }
            else if (selection == '4')
            {   int removeinput;
                cout<<"Enter PassengerID of Passenger you wish to remove"<<endl;
                while (!(std::cin >> removeinput)){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter an integer: ";
                   }
                a1.get_list()->flight.RemovePassengerById(removeinput);
                pressreturntocontinue();
                printoptions();
            }else if (selection == '5')
            {
                save_data(a1, f1); 
                pressreturntocontinue();
                printoptions();             

            }else if (selection == '6')
            {
                runprogram = 0;
            }
            else
            {
                std::cout << "Invalid input, please enter a number between 1 and 6\n";
                continue;
            }
        }
        std::cout<<"Program Terminated"<<std::endl;
    }
}
