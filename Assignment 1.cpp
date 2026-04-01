#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> // 1/17/2026 is for this one and the ones above
#include <ctime>
#include <sstream> // 1/22/2026 is for this one and the one above

// UNCOMMENT the line below to run Tests. COMMENT it to run the Menu.
//#define TEST_MODE 

using namespace std;

//define an enum for Belt Ranks
enum BeltRank { White, Yellow, Green, Blue, Purple, Brown, Black };

//create a struct that holds all student info
struct StudentInfo {
    string name = "N/A";
    int age = 0; //will change this later to check if the age is above or equal to 6
    string startDate = "01/22/2026";
    int monthsEnrolled = 0;
    bool isReturning = false;
    BeltRank rank = White; //use the enum here
    double balance = 0.0;
    bool hasPaidCurrentMonth = false;
};


void Introduction();
void recommendLevel(StudentInfo& s); //pass Struct by reference to update it
void calculateSessionCount(StudentInfo& s);
string getRankName(BeltRank r);
void managePayments(StudentInfo& s);

int main()
{
    int choice;
    bool dataEntered = false;
    bool isReturning = false;
    BeltRank rank = White; //use the enum here
    bool hasPaidCurrentMonth = false;
    // create instance for Struct
    StudentInfo currentStudent; //might change the name of the value

    //present intro
    Introduction();

    //menu time with our do-while loop
    do {
        cout << "\n--- Dojo Management System (2026) ---" << endl;
        cout << "1. Register/Add Student Information" << endl;
        cout << "2. Recommend Level & Set Rank" << endl; //uses enum with if/else
        cout << "3. Generate and Save Record" << endl; //uses struct data
        cout << "4. Check Balance/Make Payments" << endl;
        cout << "5. Exit" << endl;
        cout << "Selection: ";
        //ensure cin is working right, ran into alot of errors with it yesterday and today
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting..." << endl;
            break;
        }

        switch (choice){
        case 1: //student info
            cout << "Are you a returning student? (1 for yes, 0 for no): ";
            cin >> currentStudent.isReturning;
            cout << "First and Last Name: ";
            cin.ignore(); //clears buffer
            getline(cin, currentStudent.name);
            cout << "Age: ";
            cin >> currentStudent.age;
            if (currentStudent.age < 5) {
                cout << "Invalid age! Resetting to 6.";
                currentStudent.age = 6;
            }
            cout << "Start Date: (ex: (MM / DD / YYYY)) ";
            cin.ignore();
            getline(cin, currentStudent.startDate);
            dataEntered = true;
            cout << "Information recorded successfully!" << endl;
            break;
        case 2: //belt level aka our enum
            if (!dataEntered) {
                cout << "Error: Please enter student info first (Option 1)" << endl;
            }
            else {
                // Ensure time is calculated first!
                calculateSessionCount(currentStudent);

                // Now recommend based on that time
                recommendLevel(currentStudent);

                // Display the result using your getRankName function
                cout << "System has assigned Rank: " << getRankName(currentStudent.rank) << endl;
            }
            break;
        case 3: //View/Save info
            if (!dataEntered) {
                cout << "Nothing to record yet." << endl;
            }
            else {
                ofstream outFile("record.txt"); //open text file record
                //use the struct fields directly
                cout << "Saving Record for: " << currentStudent.name << endl;
                outFile << "DOJO STUDENT RECORD 2026\n" << string(30, '=') << endl;
                outFile << "Name: " << currentStudent.name << "\nAge: " << currentStudent.age << endl;
                outFile << "Time in Training: " << currentStudent.monthsEnrolled << " month/s" << endl;
                outFile << "Rank: " << getRankName(currentStudent.rank) << endl;
                outFile << "Current Month Paid: " << (currentStudent.hasPaidCurrentMonth ? "Yes" : "No") << endl;
                outFile.close(); //should close the file
                cout << "Record saved and filed away" << endl;
            }
            break;
        case 4:
            cout << "Checking Records...." << endl;
            if (!dataEntered) {
                cout << "Error: No student record found. Please use Option 1." << endl;
            }
            else {
                // Ensure we have the latest enrollment time
                calculateSessionCount(currentStudent);
                // Run the payment system
                managePayments(currentStudent);
            }
            break;
        case 5:
            cout << "Exiting system... Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice. Please pick 1-4." << endl;
        }
    } while (choice != 5); // Loop continues as long as choice is not 4

    return 0;
}

void Introduction() {
    cout << "Welcome to Kelly's International Martial Arts Dojo!" << endl;
    cout << "Sadly our system lost all records. Please use our new menu." << endl;
    cout << string(45, '-') << endl;
}

void recommendLevel(StudentInfo& s) { 
    // 1. First, always check the minimum age requirement
    if (s.age < 6) {
        cout << "Notice: Student is under 6. Limited to 'Little Ninjas' program." << endl;
        s.rank = White;
        return;
    }

    // 2. Recommend Rank based on monthsEnrolled (calculated in getSessionCount)
    cout << "Analyzing " << s.monthsEnrolled << " months of training..." << endl;

    if (s.monthsEnrolled < 6) {
        cout << "Recommendation: Beginner (White Belt)." << endl;
        s.rank = White;
    }
    else if (s.monthsEnrolled >= 6 && s.monthsEnrolled < 12) {
        cout << "Recommendation: Intermediate Beginner (Yellow Belt)." << endl;
        s.rank = Yellow;
    }
    else if (s.monthsEnrolled >= 12 && s.monthsEnrolled < 18){
        cout << "Recommendation: Intermediate (Green Belt)." << endl;
        s.rank = Green;
    }
    else if (s.monthsEnrolled >= 18 && s.monthsEnrolled < 24) {
        cout << "Recommendation: Intermediate Pro (Blue Belt)." << endl;
        s.rank = Blue;
    }
    else if (s.monthsEnrolled >= 24 && s.monthsEnrolled < 30) {
        cout << "Recommendation: Advanced Beginner (Purple Belt)." << endl;
        s.rank = Purple;
    }
    else if (s.monthsEnrolled >= 30 && s.monthsEnrolled < 36) {
        cout << "Recommendation: Advanced (Brown Belt)." << endl;
        s.rank = Brown;
    }
    else if (s.monthsEnrolled >= 36 && s.monthsEnrolled < 42) {
        cout << "Recommendation: Candidate for Black Belt testing." << endl;
        s.rank = Brown;
    }
    else if (s.monthsEnrolled >= 42) {
        cout << "Recommendation: Master." << endl;
        s.rank = Black;
    }
}

void calculateSessionCount(StudentInfo& s) {
    // 1. Get current date safely for 2026
    time_t t = time(0);
    struct tm now;

    // Using the 'safe' version for modern debuggers
    #ifdef _WIN32
        localtime_s(&now, &t);
    #else
        now = *localtime(&t);
    #endif

    int currentYear = now.tm_year + 1900;
    int currentMonth = now.tm_mon + 1; // tm_mon is 0-11

    // 2. Parse the date string (MM / DD / YYYY)
    int startM, startD, startY;
    char slash1, slash2;
    stringstream ss(s.startDate);

    if (ss >> startM >> slash1 >> startD >> slash2 >> startY) {
        int totalMonths = ((currentYear - startY) * 12) + (currentMonth - startM);

        // Update the struct (This requires StudentInfo& s to be a modifiable lvalue)
        if (totalMonths < 0) {
            s.monthsEnrolled = 0;
        }
        else {
            s.monthsEnrolled = totalMonths;
        }
    }
}

string getRankName(BeltRank r) {
    switch (r) {
    case White:  return "White";
    case Yellow: return "Yellow";
    case Green:  return "Green";
    case Blue:   return "Blue";
    case Purple: return "Purple";
    case Brown:  return "Brown";
    case Black:  return "Black";
    default:     return "White";
    }
}

void managePayments(StudentInfo& s) {
    double monthlyRate;

    // 1. Determine rate based on Age (Youth vs Adult)
    if (s.age < 16) {
        monthlyRate = 80.00; // Youth Rate
        cout << "Class Type: Youth (2-3 sessions/week)" << endl;
    }
    else {
        monthlyRate = 120.00; // Adult Rate
        cout << "Class Type: Adult (2-3 sessions/week)" << endl;
    }

    // 2. Calculate Lifetime Investment (Total months * rate)
    s.balance = s.monthsEnrolled * monthlyRate;

    cout << "Monthly Rate: $" << fixed << setprecision(2) << monthlyRate << endl;
    cout << "Total Tuition over " << s.monthsEnrolled << " months: $" << s.balance << endl;

    // 3. Check current month status
    char paidChar;
    cout << "Has the current month (January 2026) been paid? (y/n): ";
    cin >> paidChar;

    if (paidChar == 'y' || paidChar == 'Y') {
        s.hasPaidCurrentMonth = true;
        cout << "Payment recorded. Thank you!" << endl;
    }
    else {
        s.hasPaidCurrentMonth = false;
        cout << "Balance Due: $" << monthlyRate << " for the current session." << endl;
    }
}
