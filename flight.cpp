#include <iostream>
#include <string>
#include "Globalfunctions.cpp"
#include"flight.h"

//Default ctor
Flight::Flight(){
    number_of_rows = 1;
    number_of_columns = 1;
    flight_id = "";
    pass_listH = nullptr;
    //FSmap is 0 matrix
}
//custom ctor
Flight::Flight(int rows, int columns, const std::string& id, PassengerList* passList) {
    number_of_rows = rows;
    number_of_columns = columns;
    flight_id = id;
    pass_listH = passList;

    FSmap.resize(rows);
    for(int i = 0; i < rows; i++){
        FSmap.at(i).resize(columns);
        for(int j = 0; j < columns; j++){
            FSmap.at(i).at(j) = 1;
        }
    }
}

//copy ctor
Flight::Flight(const Flight& rhs){
    number_of_rows = rhs.number_of_rows;
    number_of_columns = rhs.number_of_columns;
    flight_id = rhs.flight_id;
    if (rhs.pass_listH != nullptr) { //linked list copy
        pass_listH = new PassengerList(*rhs.pass_listH);
    } else {
        pass_listH = nullptr;
    }
    for (std::vector<int> row : rhs.FSmap) {
        // Copy each row (inner vector)
        FSmap.push_back(row);
    }
}  


//implementation

int Flight::get_number_of_rows()const{return number_of_rows;}
int Flight::get_number_of_columns()const{return number_of_columns;}
std::string Flight::get_flight_id()const{return flight_id;}
int Flight::get_seat_status(int row, int col){
    return FSmap.at(row).at(col);}
void Flight::set_number_of_rows(int r){number_of_rows=r;}
void Flight::set_number_of_columns(int c){number_of_columns=c;}
void Flight::set_flight_id(std::string f_id){flight_id=f_id;}
void Flight::set_FSmap(int rows, int columns){
    FSmap.resize(rows);
    for(int i = 0; i < rows;i++){
        FSmap.at(i).resize(columns, 1);
    }
}
void Flight::set_pass_listH(PassengerList* h){
    pass_listH = h;
}

PassengerList* Flight::get_pass_listH()const{
    return pass_listH;
}
void Flight::update_FSmap(){
    int r, c;
    
    for (PassengerList* p = pass_listH; p != nullptr; p = p->next) {  //run through list of passengers
        r = (p->Pass).get_seat()->get_row();
        c = int((p->Pass).get_seat()->get_column() - 'A');//convert char into int
        this->set_FSmap_seat(r, c, 0);  //setting seat to unavailable
    }
}
void Flight::set_FSmap_seat(int row, int column, int value){
    FSmap.at(row).at(column) = value;
}
void DisplaySeatMap(Flight f) {
    // Display column labels
    int r = f.get_number_of_rows();
    int c = f.get_number_of_columns();

    //displaying colum letters
    std::cout << "       ";
    for(int i = 0; i < c; i++){

        std::cout << char('A' + i);
        std::cout << "  ";
        
    }
    std::cout << "\n";
    for(int i = 0; i < r; i++){
        //print row num
        std::cout << i+1;
        if(i+1 <10){
            std::cout << "     ";
        }else if (i+1 > 9 && i+1<100)
        {
            std::cout << "    ";
        }else if (i+1 > 99 && i+1<1000)
        {
            std::cout << "   ";
        }
        
        
        //print seats
        for(int j = 0; j < c; j++){
            if(f.get_seat_status(i,j)){ //if seat is available
            std::cout << "[ ]";
            }else{
            std::cout << "[X]";  //if seat is not available
            }
            }
            std::cout << '\n';
        } 

        std::cout <<'\n'; //starts the next line
}
void Flight::DisplayPassInfo() {
    PassengerList* currentPassenger = pass_listH;

    if (currentPassenger == nullptr) {
        std::cout << "No passengers on this flight." << std::endl;
        return;
    }
    cout<<"\n\n\n+++++++++++++++++++++++++++++++++";
    std::cout << "\nPassenger Information for Flight " << get_flight_id() << ":" << std::endl;

    while (currentPassenger != nullptr) {
        Passenger* passenger = &(currentPassenger->Pass);

        std::cout << "Passenger ID: " << passenger->get_pass_id() << std::endl;
        std::cout << "Name: " << passenger->get_Fname() << " " << passenger->get_Lname() << std::endl;
        std::cout << "Phone: " << passenger->get_phone() << std::endl;
        std::cout << "Seat: Row " << passenger->get_seat()->get_row() << " Column " << passenger->get_seat()->get_column() << std::endl;
        cout<<"++++++++++++++++++++++++++++++++++\n\n\n";
        currentPassenger = currentPassenger->next;
    
        if (currentPassenger != nullptr) {
            std::cout << "---------------------" << std::endl;
        }
    }
}

