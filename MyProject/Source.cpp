#include <iostream>
#include <cstring> 
#include <string>
#include <string.h>
using namespace std;

enum seatCategory { VIP, PREMIUM, GOLD, SILVER, REGULAR };

class Venue {
private:
    bool seatAvailability; //1-if the seat is not occupied and 0- if the seat is occupied
    char venueName[50]; //name of venue ex:Arena Nationala
    char venueLocation[50]; // name of location ex :Bucharest
    seatCategory seatType; 
    static int totalSeatsSold; 
    static const int maxNoOfSeats = 63566;
    int** seatingChart; //dynamically defined field managed by a pointer
public:
    // Constructor for Venue class
    Venue(bool availability, const char* venueName, const char* venueLocation, seatCategory type, int totalSeatsSold, int** seatingChart) {
        this->seatAvailability = availability;
        strcpy_s(this->venueName, sizeof(this->venueName), venueName);
        strcpy_s(this->venueLocation, venueLocation);
        this->seatType = type;
        this->totalSeatsSold = totalSeatsSold;
        this->seatingChart = seatingChart;
    }

    // Getters and setters for seatAvailability 
    bool getSeatAvailability() {
        return this->seatAvailability;
    }

    void setSeatAvailability(bool availability) {
        this->seatAvailability = availability;
    }
    // Getters and setters for venueName
    string getVenueName() {
        return this->venueName;
    }

    void setVenueName(const string& name) {
        strcpy_s(this->venueName, name.c_str());
    }

    // Getters and setters for venueLocation
    string getVenueLocation() {
        return this->venueLocation;
    }

    void setVenueLocation(const string& location) {
        strcpy_s(this->venueLocation, location.c_str());
    }
    //Getters and setters for seatType
    seatCategory getSeatType() {
        return this->seatType;
    }

    string displaySeatType(seatCategory type) {
        switch (type) {
        case seatCategory::VIP:
            return "VIP";
        case seatCategory::PREMIUM:
            return "PREMIUM";
        case seatCategory::GOLD:
            return "GOLD";
        case seatCategory::SILVER:
            return "SILVER";
        case seatCategory::REGULAR:
            return "REGULAR";
        default:
            throw exception("Type not covered");
        }
    }



    int getTotalSeatsSold() {
        return this->totalSeatsSold;
    }

    const int getMaxNoOfSeats() {
        return this->maxNoOfSeats;
    }


    // Getter for seatingChart
    int** getSeatingChart() {
        return this->seatingChart;
    }
};

int Venue::totalSeatsSold = 0;

int main() {
    bool availability = true;
    string name = "Ghencea";
    string location = "Bucuresti";
    seatCategory type = PREMIUM;
    int totalSold = 100;
    int** seatingChart = nullptr;
    int testNo;
    // Creating an instance of Venue
    
    Venue myVenue(availability, name.c_str(), location.c_str(), type, totalSold, seatingChart);
    
    cout << "type seat availability :";
    cin >> availability;
    myVenue.setSeatAvailability(availability);
    if (myVenue.getSeatAvailability() == 1) {
        cout << "seat is available"<<endl;
    }
    else {
        cout << "seat is unavailable"<<endl;
    }
    //cout << " Seat is available :"<<myVenue.getSeatAvailability()<<endl;
   
    cout << "type location name :";
    cin >> location;
    myVenue.setVenueLocation(location);
    cout << "Venue location :" << myVenue.getVenueLocation()<<endl;
    
    cout << "type venue name :";
    cin >> name;
    myVenue.setVenueName(name);
    cout << "Venue Name : " << myVenue.getVenueName() << endl;

    cout << "input seat type(0 for VIP, 1 for PREMIUM, 2 for GOLD, 3 for SILVER, 4 for REGULAR) : ";
    int typeInput;
    cin >> typeInput;

    switch (typeInput) {
    case 0:
        type = seatCategory::VIP;
        break;
    case 1:
        type = seatCategory::PREMIUM;
        break;
    case 2:
        type = seatCategory::GOLD;
        break;
    case 3:
        type = seatCategory::SILVER;
        break;
    case 4:
        type = seatCategory::REGULAR;
        break;
    default:
        cout << "Invalid input" << endl;
        return 1; // Exit the program with an error code
    }

    cout << " seat type :" << myVenue.displaySeatType(type);
    


    //cout << myVenue.getVenueName();
    // Displaying the attributes
    //std::cout << "Seat Availability: " << myVenue.getSeatAvailability() << std::endl;
    //std::cout << "Venue Name: " << myVenue.getVenueName() << std::endl;
    //std::cout << "Venue Location: " << myVenue.getVenueLocation() << std::endl;
    //std::cout << "Seat Type: " << myVenue.getSeatType() << std::endl;
    //std::cout << "Seat Type: " << myVenue.displaySeatType(type) << std::endl;
    //std::cout << "Total Seats Sold: " << myVenue.getTotalSeatsSold() << std::endl;
    //std::cout << "Max No. of Seats: " << myVenue.getMaxNoOfSeats() << std::endl;

    return 0;
}
