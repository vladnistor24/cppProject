#include <iostream>
#include <cstring> 
#include <string>
#include <string.h>
using namespace std;

enum seatCategory { VIP, PREMIUM, GOLD, SILVER, REGULAR };

class Venue {
private:
    bool seatAvailability;
    char venueName[50];
    char venueLocation[50];
    seatCategory seatType;
    static int totalSeatsSold;
    static const int maxNoOfSeats = 63566;
    int** seatingChart; //dynamically defined field managed by a pointer
    int test;
public:
    // Constructor for Venue class
    Venue(bool availability, const char* venueName, const char* venueLocation, seatCategory seatType, int totalSeatsSold, int** seatingChart) {
        this->seatAvailability = availability;
        strcpy_s(this->venueName, sizeof(this->venueName), venueName);
        strcpy_s(this->venueLocation, venueLocation);
        this->seatType = seatType;
        this->totalSeatsSold = totalSeatsSold;
        this->seatingChart = seatingChart;
    }

    // Getters for the attributes
    bool getSeatAvailability() {
        return this->seatAvailability;
    }

    void setSeatAvailability(bool availability) {
        this->seatAvailability = availability;
    }

    string getVenueName() {
        return this->venueName;
    }

    void setVenueName(const string& name) {
        strcpy_s(this->venueName, name.c_str());
    }

    string getVenueLocation() {
        return this->venueLocation;
    }

    void setVenueLocation(const string& location) {
        strcpy_s(this->venueLocation, location.c_str());
    }

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
    string location = "ssss";
    seatCategory type = PREMIUM;
    int totalSold = 100;
    int** seatingChart = nullptr;
    int testNo;
    // Creating an instance of Venue
    //cin >> testNo;

    Venue myVenue(availability, name.c_str(), location.c_str(), type, totalSold, seatingChart);
    // Venue secondConstruct(testNo);
     //cout << secondConstruct.getTest() << endl;

    cout << "type seat availability";
    cin >> availability;
    myVenue.setSeatAvailability(availability);
    cout << " Seat is available :";

    cout << "type venue name:";
    cin >> name;
    myVenue.setVenueName(name);
    cout << "Venue Name: " << myVenue.getVenueName() << std::endl;



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
