#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include <conio.h>

using namespace std;

const int MAX_ROOMS = 100 ;
int count_rooms = 0 ;

// Customer Class
class Customer{

private:
string name ;
string address ;
string phone ;
string arrival ;
string departure ;
float payed ;

public:

Customer(string name, string address, string phone, string arrival, string departure, float payed){
    this->name = name ;
    this->address = address ;
    this->phone = phone ;
    this->arrival = arrival ;
    this->departure = departure ; 
    this->payed = payed ;
}

string getname(){
    return name ;
}

string getphone(){
    return phone ;
}

int days(){
    return stoi(departure)-stoi(arrival) ;
}

float advpay(){
    return payed ;
}

void info(){
    cout<<"Customer Name : "<< name << "\n" ;
    cout<<"Customer Phone Number : "<< phone << "\n" ;
    cout<<"Customer Arrival Date : "<< arrival << "\n" ;
    cout<<"Customer Departure Date : "<< departure << "\n" ;
    cout<<"Advance Payment : " << payed << "$" ;
}

};

bool is_valid_type(const string& type);
bool is_used_number(const int& number);
bool iequals(const string& a, const string& b);

class Room{

private:
Customer* customer ;
int number ;
bool status ;
int rent_price ;
string type ;

public:
//Room Constructor
Room(int number, int rent_price, string type){
    if (count_rooms >= MAX_ROOMS){
        cout << "Maximum number of rooms reached" ;
        getch() ;
        return ;
    }
    if (!is_valid_type(type)){
        cout << "Invalid room type" ;
        getch() ;
        return ;
    }
    if (is_used_number(number)){
        cout << "Used room number" ;
        getch() ;
        return ;
    }
    this->number = number ;
    this->status = false ;
    this->rent_price = rent_price ;
    this->type = type ;
    this->customer = nullptr ;
    count_rooms++ ;
    cout << "Successfuly added room !\n" ;
}

//Customer Destructor
~Room(){
    delete customer ;
}

int room_number(){
    return number ;
}

int room_rent_price(){
    return rent_price ;
}

bool room_status(){
    return status ;
}

string room_type(){
    return type ;
}

void setstatus(bool value){
    status = value ;
}

string custname(){
    return this->customer->getname() ;
}

string custphone(){
    return this->customer->getphone() ;
}

float total(){
    return this->customer->days()*rent_price - this->customer->advpay() ;
}


void displayroom();
void addroom();
void assignCustomer(string name, string address, string phone, string arrival, string departure, float payed) {
    customer = new Customer(name, address, phone, arrival, departure, payed);
    cout << customer->getname() ;
    cout << "Successfully Assigned Customer \n" ;
}
void printinfo(){
    this->customer->info() ;
}
};

vector<Room> rooms;

void Room::displayroom(){
    cout << "Room Number : " << this->room_number() << "\n" ;
    cout << "Room Type  : " << this->room_type() << "\n" ;
    cout << "Room Status : " << this->room_status() << "\n" ;
    cout << "Room Rent-Price : " << this->room_rent_price() << "\n" ;
}

void Room::addroom(){
    int number,rent_price ;
    string type ;

    cout << "Room Number ? : \n" ;
    cin >> number ;
    cout << "Room type ? : \n" ;
    cout << "Single || Double || Deluxe \n" ;
    cin >> type ;
    cout << "Room Rent Price : \n" ;
    cin >> rent_price ;

    if (cin.fail()) {
    cout << "Invalid input." << endl;
    cin.clear(); // reset the stream state
    return ;
    }

    rooms.emplace_back(number,rent_price,type) ; //The arguments passed to emplace_back are used to initialize the Room object using the constructor.
    getch();
    system("cls") ;
    return ;
};


bool is_valid_type(const string& type){
    const vector<string> allowed_types = {"Single", "Double", "Deluxe" } ;
    for (auto& t : allowed_types){
        if (iequals(type,t)) 
        return true ;
    }

    return false ;
}

bool is_used_number(const int& number){
    for (auto& room : rooms) {
        if (room.room_number() == number) {
            return true ;
            break;
        }   
    }
    return false ;
}

// Case insensitive string Comparison
bool iequals(const string& a, const string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

Room searchroom(int num) {
    for (auto& room : rooms) {
        if (room.room_number() == num) {
            cout << "--------------------\n" ;
            return room ;
        }
    }
    cout << "Room " << num << " Not Found" << "\n";
    cout << "Invalid Room Number\n" ;
    getch() ;
}

template <typename T>
T getinput(){
    T input ;
    cin >> input ;
    if (cin.fail()) {
    cout << "Invalid input." << endl;
    cin.clear(); // reset the stream state
    getch() ;
    }
    return input ;
}


class HotelManagement{
    public:
    void Checkin() ;
    void AvailableRooms() ;
    void SearchCustomer(string) ;
    void Checkout(int) ;
};

void HotelManagement::Checkin(){
    int room_num ;
    string name ;
    string address ;
    string phone ;
    string arrival ;
    string departure;
    float payed ;
    cout << "Enter Room Number\n" ;
    cin >> room_num ;
    if (searchroom(room_num).room_status()){
        cout << "Room Already Booked\n" ;
        getch() ;
        return ;
    }
    cout<<"\nEnter Customer Name (First Name) :\n ";
    name = getinput<string>() ;
    cout<<"\nEnter Address :\n ";
    address = getinput<string>() ;
    cout<<"\nEnter Phone :\n ";
    phone = getinput<string>() ;
    cout<<"\nEnter Arrival Date :\n ";
    arrival = getinput<string>() ;
    cout<<"\nEnter Departure Date :\n";
    departure = getinput<string>() ;
    cout<<"\nEnter Advance Payment :\n ";
    payed = getinput<float>() ;
    rooms[room_num].assignCustomer(name, address, phone, arrival, departure, payed);
    rooms[room_num].setstatus(true) ;
    cout << "Successfully Checked in :\n" ;
    getch() ;
    return ;
}

void HotelManagement::AvailableRooms(){
    bool foundone = false ;
    for(auto& room : rooms){
        if(!room.room_status()){
            room.displayroom() ;
            cout<<"\nPress Any button for the next room \n";
            getch() ;
            foundone = true ;
        }
    }
    if (!foundone){
        cout << "All rooms are Reserved" ;
        getch() ;
    }
}

void HotelManagement::SearchCustomer(string name){
    bool foundone = false ;
    for (auto& room : rooms){
        if (room.room_status() && room.custname().compare(name) == 0 ){
            cout << "Customer Name : " << name << "\n";
            cout << "Room Number : " << room.room_number() << "\n" ;
            cout << "Phone Number : " << room.custphone() << "\n" ;
            foundone = true ;
            getch() ;
        }
    }
    if (!foundone){
        cout << "Person with name : " << name << " Not found" << "\n" ;
        getch() ;
    }
}

void HotelManagement::Checkout(int roomnum){
    bool foundone = false ;
    for (auto& room : rooms){
        if(room.room_status() && room.room_number() == roomnum  ){
           foundone = true ;
           room.printinfo() ;
           cout << "Total Payment : " << room.total() << "\n" ;
           room.setstatus(false) ;
           break ;
        }
    }
    getch() ;
}

void Managerooms(){
    int operation,roomnum ;
    do{
        cout << "------ Rooms Management ------\n" ;
        cout << "1. Add Room \n" ;
        cout << "2. Search in Rooms \n" ;
        cout << "3. Back To Main Menu \n" ;
        cin >> operation ;
        system("cls") ;
        switch (operation)
        {
        case 1:
            rooms[count_rooms].addroom() ;
            break;

        case 2:
            cout << "Enter Room Number \n" ;
            cin >> roomnum ;
            searchroom(roomnum).displayroom() ;
            getch() ;
            system("cls") ;
            break ;

        case 3:
            break ;

        default:
            cout << "Please Enter A Valid Option" ;
            break ;
        }

    }while(operation != 3) ;
}


int main()
{
    HotelManagement hotel ;
    int operation,roomnum ;
    string sname ;
    do
    {
        system("cls") ;
        cout<<"######## Hotel Management #########\n";
        cout<<"1. Manage Rooms\n";
        cout<<"2. Do Check-in\n";
        cout<<"3. Available Rooms\n";
        cout<<"4. Search Customer\n";
        cout<<"5. Do Check-Out\n";
        cout<<"6. Exit\n";
        cout<<"Enter Option: \n";
        cin >> operation ;

        switch (operation)
        {
        case 1 :
            system("cls") ;
            Managerooms() ;
            break;
        
        case 2:
            system("cls") ;
            hotel.Checkin() ;
            break ;
        
        case 3:
            system("cls") ;
            hotel.AvailableRooms() ;
            break;
        
        case 4: 
            system("cls") ;
            cout << "Enter The Name of Customer\n" ;
            cin >> sname ;
            hotel.SearchCustomer(sname) ;
            break ;
        
        case 5:
            system("cls") ;
            cout << "Enter Number Of Room to be Checked-out\n" ;
            cin >> roomnum ;
            hotel.Checkout(roomnum) ; 
            break ;

        case 6: 
            system("cls") ;
            cout << "Thank you for using our Program" ;
            break ;
        
        default:
            cout << "Please Enter A Valid Option\n" ;
            break ;
        }

    } while (operation != 6);
    getch() ;
}