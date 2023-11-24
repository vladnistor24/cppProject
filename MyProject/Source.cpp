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

    int rows=0;
    int cols=0;

    static const int maxRows = 50; // Maximum rows
    static const int maxCols = 50; // Maximum columns
    int seatingChart2[maxRows][maxCols];

    void initializeSeatingChart(int rows, int cols) {
        seatingChart = new int* [rows];
        for (int i = 0; i < rows; i++) {
            seatingChart[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                seatingChart[i][j] = 1;
            }
        }
    }
    

    int** copySeatingChart(const int** source, int rows, int cols) {
        int** newChart = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            newChart[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                newChart[i][j] = source[i][j];
            }
        }
        return newChart;
    }


public:
    // Constructor for Venue class
    Venue(bool availability, const char* venueName, const char* venueLocation, seatCategory type, int totalSeatsSold, int** seatingChart,int rows, int cols) {
        this->seatAvailability = availability;
        strcpy_s(this->venueName, sizeof(this->venueName), venueName);
        strcpy_s(this->venueLocation, venueLocation);
        this->seatType = type;
        this->totalSeatsSold = totalSeatsSold;
        this->seatingChart = seatingChart;

        if (rows >= 0 || rows<maxRows||cols >= 0 || cols<maxCols) {

            this->rows = rows;
            this->cols = cols;
        }
        else {
            throw invalid_argument("Invalid dimension");
        }
        
        //initializeSeatingChart(rows, cols);
    }

    //copy constructor
    Venue(const Venue& other) {
        seatAvailability = other.seatAvailability;
        seatType = other.seatType;
        totalSeatsSold = other.totalSeatsSold;

        strncpy_s(venueName, sizeof(venueName), other.venueName, sizeof(venueName) - 1);
        strncpy_s(venueLocation, sizeof(venueLocation), other.venueLocation, sizeof(venueLocation) - 1);

        //Copy the seating chart
        if (other.seatingChart != nullptr) {
            //Assuming seatingChart dimensions are known
            seatingChart = copySeatingChart((const int**)other.seatingChart, rows, cols);
        }
    }



    // Getters and setters for seatAvailability 
    bool getSeatAvailability() {
        return this->seatAvailability;
    }

    void setSeatAvailability(bool availability) {
        if (availability == 1 || availability == 0) {
            this->seatAvailability = availability;
        }
        else {
            throw invalid_argument("Invalid seat availability value");
        }
        
    }
    // Getters and setters for venueName
    string getVenueName() {
        return this->venueName;
    }

    void setVenueName(const string& name) {
        if (sizeof(name) < 3 && sizeof(name) > 50) {
            throw invalid_argument("Venue name is invalid");
        }
        strcpy_s(this->venueName, name.c_str());
    }

    // Getters and setters for venueLocation
    string getVenueLocation() {
        return this->venueLocation;
    }

    void setVenueLocation(const string& location) {
        if (sizeof(location) < 3 && sizeof(location) > 50) {
            throw invalid_argument("Venue Location is invalid");
        }
        
        strcpy_s(this->venueLocation, location.c_str());
    }
    //Getters and display for seatType
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


    //getters and setters for totalSeatsSold
    int getTotalSeatsSold() {
        return this->totalSeatsSold;
    }

    void setTotalSeatsSold(int totalSold) {
        if (totalSold <0 || totalSold > maxNoOfSeats) {
            throw invalid_argument("Seats sold input is invalid");
        }
        
        this->totalSeatsSold = totalSold;
    }

    const int getMaxNoOfSeats() {
        return this->maxNoOfSeats;
    }


    // Getter for seatingChart
    int** getSeatingChart() {
        return this->seatingChart;
    }

    //second constructor
    Venue(int rows, int cols) {
        if (rows <= 0 || cols <= 0) {
            throw invalid_argument("Invalid dimension");
        }

        initializeSeatingChart(rows, cols);
    }
    //destructor
    ~Venue() {
        if (seatingChart != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] seatingChart[i];
            }
            delete[] seatingChart;
        }
    }
    //overloaded assignment operator =
    Venue& operator=(const Venue& other) {
        if (this != &other) { // Self-assignment check
            seatAvailability = other.seatAvailability;
            seatType = other.seatType;
            totalSeatsSold = other.totalSeatsSold;

            strncpy_s(venueName, sizeof(venueName), other.venueName, sizeof(venueName) - 1);
            strncpy_s(venueLocation, sizeof(venueLocation), other.venueLocation, sizeof(venueLocation) - 1);

            //clean up existing seatingChart if any
            if (seatingChart != nullptr) {
                //properly deallocate existing memory
                //assuming rows and cols are known dimensions
                for (int i = 0; i < rows; ++i) {
                    delete[] seatingChart[i];
                }
                delete[] seatingChart;
            }

            //copy the seating chart
            if (other.seatingChart != nullptr) {
                //assuming seatingChart dimensions are known
                seatingChart = copySeatingChart((const int**)other.seatingChart, rows, cols);
            }
            else {
                seatingChart = nullptr;
            }
        }
        return *this; //returns a reference to this object
    }

    void setSeatAvailability(int row, int col, bool availability) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            seatingChart[row][col] = (availability) ? 1 : 0; // 1 if available, 0 if occupied
        }
        //else {
          //  throw out_of_range("invalid seat input");
        //}
    }

};

int Venue::totalSeatsSold = 0;

int main() {
    bool availability = true;
    string name = "Ghencea";
    string location = "Bucuresti";
    seatCategory type = VIP;
    int totalSold = 10000;
    int** seatingChart = nullptr;
    int rows = 0;
    int cols = 0;
    int maxRows = 50;
    int maxCols = 50;


    // Creating an instance of Venue
    
    Venue myVenue(availability, name.c_str(), location.c_str(), type, totalSold, seatingChart,rows,cols);
    
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

    cout << " seat type :" << myVenue.displaySeatType(type)<<endl;
    
    cout << "type the number of sold seats :" << endl;
    cin >> totalSold;
    myVenue.setTotalSeatsSold(totalSold);
    cout << "The number of seats sold is :" << myVenue.getTotalSeatsSold() << endl;

    

    cout << "Enter the number of rows and columns" << endl;
    cin >> rows >> cols;

    if (rows <= 0 || rows >maxRows || cols <= 0 || cols >maxCols) {
        cout << "Invalid dimensions provided for seating chart" << endl;
        return 1; // Exit the program with an error code
    }

    myVenue.setSeatAvailability(rows, cols, 1);
    cout << myVenue.getSeatingChart();

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
