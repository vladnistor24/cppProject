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
    //postfix
    Venue operator++(int) {
        Venue copy = *this;
        this->totalSeatsSold += 1;
        return *this;
    }
    //prefix
    Venue operator++() {
        this->totalSeatsSold += 1;
        return *this;
    }



};


class Ticket {
private:
    string eventName;
    string venueName;
    string seatNumber;
    float price;
    string* ticketDetails;//dynamically managed field
    static const int maxNoOfTicketsPerPerson = 0;// statically and constant field
    int ticketNumbers[maxNoOfTicketsPerPerson];//statically defined array

public:

    //default constructor
    Ticket() : eventName(""), venueName(""), seatNumber(""), price(0.0), ticketDetails(nullptr) {}

    //constructor
    Ticket(string& eventName, string& venueName, string& seatNumber, float price) {
        this->eventName = eventName;
        this->venueName = venueName;
        this->seatNumber = seatNumber;
        this->price = price;
    }

    Ticket(const string& details) {
        for (int i = 0; i < maxNoOfTicketsPerPerson; i++) {
            ticketNumbers[i]++;
        }

    }

    const int* getTicketNumbers() {
        return ticketNumbers;
    }

    void setTicketNumbers(int ticketsNumber) {
        for (int i = 0; i < maxNoOfTicketsPerPerson; i++) {
            this->ticketNumbers[i] = ticketsNumber;
        }
    }

    Ticket(string& details) {
        ticketDetails = new string(details);
    }

    //destructor

    ~Ticket() {
        delete[] ticketDetails;
    }

    string getTicketDetails() const {
        return *ticketDetails;
    }

    void setTicketDetails(const string& details) {
        if (!ticketDetails) {
            ticketDetails = new string(details);
        }
        else {
            *ticketDetails = details;
        }
    }
    //getters and setters

    void setEventName(const string& name) {
        if (name.length() < 3 || name.length() > 50) {
            throw invalid_argument("Event name length should be between 3 and 50 characters.");
        }
        eventName = name;
    }

    string getEventName() const {
        return eventName;
    }

    void setVenueName(const string& venue) {
        if (venue.length() < 3 || venue.length() > 50) {
            throw invalid_argument("Venue name length should be between 3 and 50 characters.");
        }
        venueName = venue;
    }

    string getVenueName() const {
        return venueName;
    }

    void setSeatNumber(const string& seat) {
        if (seat.empty()) {
            throw invalid_argument("Seat number cannot be empty.");
        }
        seatNumber = seat;
    }

    string getSeatNumber() const {
        return seatNumber;
    }

    void setPrice(float ticketPrice) {
        if (ticketPrice <= 0) {
            throw invalid_argument("Ticket price should be greater than zero.");
        }
        price = ticketPrice;
    }

    float getPrice() const {
        return price;
    }

    //copy constructor
    Ticket(const Ticket& other) {
        this->eventName = other.eventName;
        this->venueName = other.venueName;
        this->seatNumber = other.seatNumber;
        this->price = other.price;
    }
    //overloaded form of operator =
    Ticket& operator=(const Ticket& other) {
        if (this != &other) { // Check for self-assignment
            eventName = other.eventName;
            venueName = other.venueName;
            seatNumber = other.seatNumber;
            price = other.price;

            // Deep copy for dynamically managed field
            if (other.ticketDetails != nullptr) {
                if (ticketDetails == nullptr) {
                    ticketDetails = new string(*other.ticketDetails);
                }
                else {
                    *ticketDetails = *other.ticketDetails;
                }
            }
            else {
                delete ticketDetails;
                ticketDetails = nullptr;
            }
        }
        return *this;
    }

    //overloading << operator for output
    friend ostream& operator<<(ostream& os, const Ticket& ticket) {
        os << "Event Name: " << ticket.getEventName() << endl;
        os << "Venue Name: " << ticket.getVenueName() << endl;
        os << "Seat Number: " << ticket.getSeatNumber() << endl;
        os << "Price: $" << ticket.getPrice() << endl;
        os << "Ticket Details: " << ticket.getTicketDetails() << endl;
        return os;
    }

    //overloading >> operator for input
    friend istream& operator>>(istream& is, Ticket& ticket) {
        string eventName, venueName, seatNumber, details;
        float price;

        cout << "Enter Event Name: ";
        is >> eventName;
        ticket.setEventName(eventName);

        cout << "Enter Venue Name: ";
        is >> venueName;
        ticket.setVenueName(venueName);

        cout << "Enter Seat Number: ";
        is >> seatNumber;
        ticket.setSeatNumber(seatNumber);

        cout << "Enter Ticket Price: ";
        is >> price;
        ticket.setPrice(price);

        cout << "Enter Ticket Details: ";
        is >> details;
        ticket.setTicketDetails(details);

        return is;
    }

    //overloading indexing operator []
    string& operator[](int index) {
        if (index >= 0 && index < maxNoOfTicketsPerPerson) {
            return ticketDetails[index];
        }
        else {
            throw out_of_range("Index out of range");
        }
    }



    //overloading addition operator +
    Ticket operator+(const Ticket& other) {
        Ticket result(*this); // Make a copy
        result.price += other.price;
        return result;
    }

    //overloading prefix increment operator ++
    Ticket& operator++() {
        ++price;
        return *this;
    }

    //overloading postfix increment operator ++
    Ticket operator++(int) {
        Ticket temp(*this); // Make a copy
        ++(*this);
        return temp;
    }

    //overloading cast operator to float
    explicit operator float() const {
        return price;
    }

    //overloading negation operator !
    bool operator!() const {
        return price == 0.0f;
    }

    //overloading less than operator <
    bool operator<(const Ticket& other) const {
        return price < other.price;
    }

    //overloading equality operator ==
    bool operator==(const Ticket& other) const {
        return (eventName == other.eventName &&
            venueName == other.venueName &&
            seatNumber == other.seatNumber &&
            price == other.price);
    }
    //method for displaying the details of the ticket
    void displayTicket() {
        cout << "Event Name: " << eventName << endl;
        cout << "Venue Name: " << venueName << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Price: " << price << endl;
    }
};

class User {
private:
    string userID;
    string familyName;
    string firstName;
    string userPhoneNumber;
    string* additionalInfo;// dynamically managed field
    static const int maxFirstNames = 5;// static and const field
    string maxFirstNamesArray[maxFirstNames];//statically defined array


public:
    //constructor
    User(string& userID, string& familyName, string& firstName, string userPhoneNumber, const string additionalInfo) {
        this->userID = userID;
        this->familyName = familyName;
        this->firstName = firstName;
        this->userPhoneNumber = userPhoneNumber;
        this->additionalInfo = new string(additionalInfo);
    }

    //destructor
    ~User() {
        delete[] additionalInfo;
    }

    //constructor for maxFirstNames and the array

    User(const string maxFirstNamesArray[], int maxFirstNames) {
        //initializing maxFirstNamesArray with the given values
        for (int i = 0; i < maxFirstNames; ++i) {
            this->maxFirstNamesArray[i] = maxFirstNamesArray[i];
        }
    }

    //getters 

    const string& getUserID() const {
        return userID;
    }

    const string& getFamilyName() const {
        return familyName;
    }

    const string& getFirstName() const {
        return firstName;
    }

    string getUserPhoneNumber() const {
        return userPhoneNumber;
    }

    const string getAdditionalInfo() const {
        if (additionalInfo != nullptr) {
            return *additionalInfo;
        }
        return "";
    }

    const string& getMaxFirstName(int index) const {
        if (index >= 0 && index < maxFirstNames) {
            return maxFirstNamesArray[index];
        }
        else {
            // Handle out of range error
            throw out_of_range("Index out of range for maxFirstNamesArray");
        }
    }

    int getMaxFirstNames() const {
        return maxFirstNames;
    }

    //setters

    void setUserID(const string& newUserID) {
        if (sizeof(newUserID) < 6) {
            throw invalid_argument("id must be at least 6 characters long");
        }
        userID = newUserID;
    }

    void setFamilyName(const string& newFamilyName) {
        if (newFamilyName.empty()) {
            throw invalid_argument("Family name cannot be empty.");
        }
        familyName = newFamilyName;
    }

    void setFirstName(const string& newFirstName) {
        if (newFirstName.empty()) {
            throw invalid_argument("First name cannot be empty.");
        }
        firstName = newFirstName;
    }

    void setUserPhoneNumber(const string& newUserPhoneNumber) {
        if (newUserPhoneNumber.length() != 10) {
            throw invalid_argument("Phone number must be 10 digits long.");
        }
        userPhoneNumber = newUserPhoneNumber;
    }

    void setAdditionalInfo(const string& info) {
        if (additionalInfo == nullptr) {
            additionalInfo = new string(info);
        }
        else {
            *additionalInfo = info;
        }
    }

    void setMaxFirstName(int index, const string& value) {
        if (index >= 0 && index < maxFirstNames) {
            maxFirstNamesArray[index] = value;
        }
        else {
            // Handle out of range error
            throw out_of_range("Index out of range for maxFirstNamesArray");
        }
    }
    //method to display the attributes
    template<typename T>
    void displayAttribute(const T& attribute) const {
        cout << "Attribute: " << attribute << endl;
    }
    //method to display all attributes
    void displayAttributes() const {
        displayAttribute(userID);
        displayAttribute(familyName);
        displayAttribute(firstName);
        displayAttribute(userPhoneNumber);
        displayAttribute(getAdditionalInfo());

        for (int i = 0; i < maxFirstNames; ++i) {
            displayAttribute(maxFirstNamesArray[i]);
        }
    }

    //copy constructor
    User(const User& other) {
        userID = other.userID;
        familyName = other.familyName;
        firstName = other.firstName;
        userPhoneNumber = other.userPhoneNumber;
        if (other.additionalInfo != nullptr) {
            additionalInfo = new string(*other.additionalInfo);
        }
        else {
            additionalInfo = nullptr;
        }
        for (int i = 0; i < maxFirstNames; ++i) {
            maxFirstNamesArray[i] = other.maxFirstNamesArray[i];
        }
    }

    //overloaded form of the operator =
    User& operator=(const User& other) {
        if (this != &other) {
            userID = other.userID;
            familyName = other.familyName;
            firstName = other.firstName;
            userPhoneNumber = other.userPhoneNumber;

            // Deallocate existing additionalInfo if it exists
            delete additionalInfo;
            if (other.additionalInfo != nullptr) {
                additionalInfo = new string(*other.additionalInfo);
            }
            else {
                additionalInfo = nullptr;
            }

            // Copy maxFirstNamesArray
            for (int i = 0; i < maxFirstNames; ++i) {
                maxFirstNamesArray[i] = other.maxFirstNamesArray[i];
            }
        }
        return *this;
    }

    //overloaded << operator for output
    friend ostream& operator<<(ostream& os, const User& user) {
        os << "User ID: " << user.userID << endl
            << "Family Name: " << user.familyName << endl
            << "First Name: " << user.firstName << endl
            << "Phone Number: " << user.userPhoneNumber << endl
            << "Additional Info: " << (user.additionalInfo != nullptr ? *user.additionalInfo : "") << endl
            << "First Names: ";
        for (int i = 0; i < user.maxFirstNames; ++i) {
            os << user.maxFirstNamesArray[i] << " ";
        }
        return os;
    }
    //overloaded >> operator for input
    friend istream& operator>>(istream& is, User& user) {
        cout << "Enter User ID: ";
        is >> user.userID;

        cout << "Enter Family Name: ";
        is >> user.familyName;

        cout << "Enter First Name: ";
        is >> user.firstName;

        cout << "Enter Phone Number: ";
        is >> user.userPhoneNumber;

        cout << "Enter Additional Info: ";
        string additional;
        is >> additional;
        user.additionalInfo = new string(additional);

        cout << "Enter First Names (up to " << user.maxFirstNames << " names): ";
        for (int i = 0; i < user.maxFirstNames; ++i) {
            is >> user.maxFirstNamesArray[i];
        }
        return is;
    }
    //overloading indexing operator []
    string& operator[](int index) {
        if (index == 0) {
            return userID;
        }
        else if (index == 1) {
            return familyName;
        }
        else if (index == 2) {
            return firstName;
        }
        //handle other indices or throw an exception for out-of-bounds access
        throw out_of_range("Index out of bounds");
    }

    //overloading addition operator +
    User operator+(const User& other) const {
        User result(*this);
        //define addition logic here (if needed)
        return result;
    }

    //overloading prefix increment operator ++
    User& operator++() {
        //define prefix increment logic here
        return *this;
    }

    //overloading postfix increment operator ++
    User operator++(int) {
        User temp(*this);
        //define postfix increment logic here
        return temp;
    }

    //overloading casting operator
    explicit operator string() const {
        //define casting logic to string
        return userID + " " + familyName + " " + firstName;
    }

    //overloading negation operator !
    bool operator!() const {
        //define negation logic here
        return userID.empty() && familyName.empty() && firstName.empty();
    }

    //overloading relational operator <
    bool operator<(const User& other) const {
        //define less-than comparison logic here
        return userID < other.userID;
    }

    //overloading equality operator ==
    bool operator==(const User& other) const {
        //define equality comparison logic here
        return (userID == other.userID) && (familyName == other.familyName) && (firstName == other.firstName);
    }


};




int Venue::totalSeatsSold = 0;

int main() {
    //CLASS VENUE

    //declared variables for class Venue
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
    
    cout << "CLASS VENUE" << endl;

    cout << "type seat availability(1 if the seat is available and 0 if the seat is occupied :";
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
    cout << myVenue.getSeatingChart()<<endl;
    
    //CLASS TICKET

    string eventName, venueName, seatNumber;
    float price = 0;
    string details;

    Ticket myTicketDetails(details);

    cout << "CLASS TICKET" << endl;

    cout << "enter ticket details :" << endl;
    cin >> details;
    myTicketDetails.setTicketDetails(details);
    cout << myTicketDetails.getTicketDetails() << endl;

    //creating a ticket object
    Ticket myTicket(eventName, venueName, seatNumber, price);

    // Reading ticket attributes from the user
    cout << "Enter Event Name: " << endl;
    cin >> eventName;
    myTicket.setEventName(eventName);
    cout << "Event Name: " << myTicket.getEventName() << endl;

    cout << "Enter Venue Name: " << endl;
    cin >> venueName;
    myTicket.setVenueName(venueName);
    cout << "Venue Name: " << myTicket.getVenueName() << endl;

    cout << "Enter Seat Number: " << endl;
    cin >> seatNumber;
    myTicket.setSeatNumber(seatNumber);
    cout << "Seat Number: " << myTicket.getSeatNumber() << endl;

    cout << "Enter Ticket Price: " << endl;
    cin >> price;
    myTicket.setPrice(price);
    cout << "Price: $" << myTicket.getPrice() << endl;

    Ticket t1, t2;

    // Usage examples
    t1[0] = "VIP Seat";
    t1[1] = "Premium Seat";

    Ticket result = t1 + t2;
    ++t1;
    t2++;

    float priceValue = float(t1);
    bool isNotZero = !t2;
    bool isLessThan = t1 < t2;
    bool isEqual = (t1 == t2);

    t1.displayTicket();

    //CLASS USER
    string userID, familyName, firstName;
    string phoneNumber;
    string additioanlInfo;
    string maxFirstNamesArray[5];// an array that can hold up to 5 names of the same person

    User user1(userID, familyName, firstName, phoneNumber, additioanlInfo);

    cout << "CLASS USER" << endl;

    cout << "enter user id:" << endl;
    cin >> userID;
    user1.setUserID(userID);
    cout << "user id is:" << user1.getUserID() << endl;

    cout << "enter family name:" << endl;
    cin >> familyName;
    user1.setFamilyName(familyName);
    cout << "family name is: " << user1.getFamilyName() << endl;

    cout << "enter first name:" << endl;
    cin >> firstName;
    user1.setFirstName(firstName);
    cout << "first name is:" << user1.getFirstName() << endl;

    cout << "enter phone number:" << endl;
    cin >> phoneNumber;
    user1.setUserPhoneNumber(phoneNumber);
    cout << "phone number of the user is:" << user1.getUserPhoneNumber() << endl;

    cout << "enter additional info" << endl;
    cin >> additioanlInfo;
    user1.setAdditionalInfo(additioanlInfo);
    cout << "additional info is :" << user1.getAdditionalInfo() << endl;

    cout << "Enter up to 5 first names:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "First Name " << i + 1 << ": ";
        cin >> maxFirstNamesArray[i];
    }

    cout << "Names entered:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "First Name " << i + 1 << ": " << maxFirstNamesArray[i] << endl;
    }




    return 0;
}
