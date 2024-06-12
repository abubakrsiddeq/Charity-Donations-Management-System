#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// MAIN MENU FUNCTIONS DECLARATIONS
void mainmenu() {
    cout << "\n\t -----------MAIN MENU------------";
    cout << "\n\t |                              |";
    cout << "\n\t |    1. Admin Panel            |";
    cout << "\n\t |    2. User Panel             |";
    cout << "\n\t |    3. Quit/Exit              |";
    cout << "\n\t |                              |";
    cout << "\n\t --------------------------------";
}

// Donor system
struct Donor {
    string name;
    string email;
    string phone;
    double donation;
};

Donor* donors = nullptr;
int donorCount = 0;
const string filename = "donors.txt";
double balance = 0; // Added balance variable here

void loadDonors() {
    ifstream inFile(filename); //read from file
    if (!inFile) {
        cout << "No existing donor data found." << endl;
        return;
    }

    inFile >> donorCount;
    inFile.ignore(); //skip newline characters
    donors = new Donor[donorCount];

    for (int i = 0; i < donorCount; ++i) {
        getline(inFile, donors[i].name);
        getline(inFile, donors[i].email);
        getline(inFile, donors[i].phone);
        inFile >> donors[i].donation;
        balance += donors[i].donation; // Update the balance when loading donors
        inFile.ignore();
    }

    inFile.close();
}

void saveDonors() {
    ofstream outFile(filename); //output file stream
    outFile << donorCount << endl;
    for (int i = 0; i < donorCount; ++i) {
        outFile << donors[i].name << endl;
        outFile << donors[i].email << endl;
        outFile << donors[i].phone << endl;
        outFile << donors[i].donation << endl;
    }
    outFile.close();
}

void registerDonor() {
    system("cls");
    Donor donor;
    cout << "Enter donor name: ";
    cin.ignore(); //clears the input buffer to ignore any leftover newline characters from previous input operations
    getline(cin, donor.name); // reads the entire line of input
    cout << "Enter donor email: ";
    getline(cin, donor.email);
    cout << "Enter donor phone: ";
    getline(cin, donor.phone);
    cout << "Enter donation amount: Rs ";
    cin >> donor.donation;

    Donor* newDonors = new Donor[donorCount + 1];
    for (int i = 0; i < donorCount; ++i) {
        newDonors[i] = donors[i];
    }

    newDonors[donorCount] = donor;
    ++donorCount;

    delete[] donors;
    donors = newDonors;

    balance += donor.donation; // Update the balance when a new donation is added

    saveDonors();

    cout << "Donation added successfully!" << endl;
}

// reciever system
struct Feedback {
    string name;
    string phone;
    double amount;
    string purpose;
    string remarks;
};

Feedback* feedbacks = nullptr;
int feedbackCount = 0;
const string feedbackFilename = "feedbacks.txt";

void loadFeedbacks() {
    ifstream inFile(feedbackFilename);
    if (!inFile) {
        cout << "No existing feedback data found." << endl;
        return;
    }

    inFile >> feedbackCount;
    inFile.ignore();
    feedbacks = new Feedback[feedbackCount];

    for (int i = 0; i < feedbackCount; ++i) {
        getline(inFile, feedbacks[i].name);
        getline(inFile, feedbacks[i].phone);
        inFile >> feedbacks[i].amount;
        inFile.ignore();
        getline(inFile, feedbacks[i].purpose);
        getline(inFile, feedbacks[i].remarks);
    }

    inFile.close();
}

void saveFeedbacks() {
    ofstream outFile(feedbackFilename);
    outFile << feedbackCount << endl;
    for (int i = 0; i < feedbackCount; ++i) {
        outFile << feedbacks[i].name << endl;
        outFile << feedbacks[i].phone << endl;
        outFile << feedbacks[i].amount << endl;
        outFile << feedbacks[i].purpose << endl;
        outFile << feedbacks[i].remarks << endl;
    }
    outFile.close();
}

void deductAmount(double amount) {
    balance -= amount;
    // Save the updated balance to the file if needed
}

// Admin login function
bool adminLogin() {
    string username, password;
    cout << "\nEnter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    // Predefined admin username and password
    string admin_username = "admin";
    string admin_password = "1234";

    if (username == admin_username && password == admin_password) {
        cout << "\nLogin Successful!\n";
        return true;
    }
    else {
        cout << "\nInvalid Username or Password. Please try again.\n";
        return false;
    }
}

// ADMIN PANEL FUNCTIONS DECLARATIONS
void displayadminmenu() {
    cout << "\n\t ----------ADMIN PANEL-----------";
    cout << "\n\t |                              |";
    cout << "\n\t |    1. Collections            |";
    cout << "\n\t |    2. Donors                 |";
    cout << "\n\t |    3. Receivers              |";
    cout << "\n\t |    4. Go To Main Menu        |";
    cout << "\n\t |                              |";
    cout << "\n\t --------------------------------";
}

void collections() {
    system("cls");
    cout << "\nTotal Collection is: " << balance << " Rupees" << endl;
}

void donoradminmenu() {
    cout << "\n\t -------DONORS DASHBOARD---------";
    cout << "\n\t |                              |";
    cout << "\n\t |    1. Display Donors         |";
    cout << "\n\t |    2. Delete Donor           |";
    cout << "\n\t |    3. Go To Admin Panel      |";
    cout << "\n\t |                              |";
    cout << "\n\t --------------------------------";
}

void displayDonors() {
    system("cls");
    cout << "Donors:" << endl;
    for (int i = 0; i < donorCount; ++i) {
        cout << "Name: " << donors[i].name << endl;
        cout << "Email: " << donors[i].email << endl;
        cout << "Phone: " << donors[i].phone << endl;
        cout << "Donation: Rs " << donors[i].donation << endl;
        cout << "------------------------" << endl;
    }
}

void deleteDonor() {
    system("cls");
    cout << "Enter the email of the donor to delete: ";
    string email;
    cin.ignore();
    getline(cin, email);

    int index = -1;
    for (int i = 0; i < donorCount; ++i) {
        if (donors[i].email == email) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Donor not found." << endl;
        return;
    }

    balance -= donors[index].donation; // Update the balance when a donor is deleted

    Donor* newDonors = new Donor[donorCount - 1];
    for (int i = 0, j = 0; i < donorCount; ++i) {
        if (i != index) {
            newDonors[j++] = donors[i];
        }
    }

    --donorCount;
    delete[] donors;
    donors = newDonors;

    saveDonors();

    cout << "Donor deleted successfully!" << endl;
}

void receiveradminmenu() {
    cout << "\n\t -------RECEIVER DASHBOARD-------";
    cout << "\n\t |                              |";
    cout << "\n\t |    1. Display Receivers      |";
    cout << "\n\t |    2. Delete Receivers       |";
    cout << "\n\t |    3. Go To Admin Panel      |";
    cout << "\n\t |                              |";
    cout << "\n\t --------------------------------";
}

void displayFeedbacks() {
    cout << "Receiver Feedbacks:" << endl;
    for (int i = 0; i < feedbackCount; ++i) {
        cout << "Name: " << feedbacks[i].name << endl;
        cout << "Phone: " << feedbacks[i].phone << endl;
        cout << "Amount Received: Rs " << feedbacks[i].amount << endl;
        cout << "Purpose: " << feedbacks[i].purpose << endl;
        cout << "Remarks: " << feedbacks[i].remarks << endl;
        cout << "------------------------" << endl;
    }
}

void deleteFeedback() {
    cout << "Enter the name of the feedback to delete: ";
    string name;
    cin.ignore();
    getline(cin, name);

    int index = -1;
    for (int i = 0; i < feedbackCount; ++i) {
        if (feedbacks[i].name == name) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Feedback not found." << endl;
        return;
    }

    Feedback* newFeedbacks = new Feedback[feedbackCount - 1];
    for (int i = 0, j = 0; i < feedbackCount; ++i) {
        if (i != index) {
            newFeedbacks[j++] = feedbacks[i];
        }
    }

    --feedbackCount;
    delete[] feedbacks;
    feedbacks = newFeedbacks;

    saveFeedbacks();

    cout << "Feedback deleted successfully!" << endl;
}

// USER PANEL FUNCTIONS DECLARATIONS
void displayuserpanel() {
    system("cls");
    cout << "\n\t ----------USER PANEL-----------";
    cout << "\n\t |                               |";
    cout << "\n\t |   1. Donor Dashboard          |";
    cout << "\n\t |   2. Receiver Dashboard       |";
    cout << "\n\t |   3. Go To Main Menu          |";
    cout << "\n\t |                               |";
    cout << "\n\t ---------------------------------";
}

void donormainmenu() {
    cout << "\n\t --------DONAR ACCOUNT----------";
    cout << "\n\t |                             |";
    cout << "\n\t |   1. LOGIN                  |";
    cout << "\n\t |   2. REGISTRATION           |";
    cout << "\n\t |   3. FORGOT                 |";
    cout << "\n\t |   4. Go To User Panel       |";
    cout << "\n\t |                             |";
    cout << "\n\t -------------------------------";
}

void donordashboard() {
    cout << "\n\t --------DONAR DASHBOARD--------";
    cout << "\n\t |                             |";
    cout << "\n\t |   1. Add Donation           |";
    cout << "\n\t |   2. Logout                 |";
    cout << "\n\t |                             |";
    cout << "\n\t -------------------------------";
}

void receiverdashboardmenu() {
    cout << "\n\t --------receiverdashboard-------";
    cout << "\n\t |                             |";
    cout << "\n\t |   1. Get Donations          |";
    cout << "\n\t |   2. Go to Main menu        |";
    cout << "\n\t |                             |";
    cout << "\n\t -------------------------------";
}

bool donorlogin() {
    system("cls");
    int count = 0;
    string userId, password, id, pass;

    cout << "Please enter the username and password :" << endl;
    cout << "USERNAME: ";
    cin >> userId;
    cout << "PASSWORD: ";
    cin >> password;
    ifstream input("records.txt");
    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
            break;
        }
    }
    input.close();
    if (count == 1) {
        cout << userId << "\nYour LOGIN is successful\nThanks for logging in!\n";
        return true; // Login successful
    }
    else {
        system("cls");
        cout << "\nLOGIN ERROR\nPlease check your username and password\n";
        return false; // Login failed
    }
}

void donorregistration() {
    system("cls");
    string ruserId, rpassword;
    system("cls");
    cout << "Enter the username: ";
    cin >> ruserId;
    cout << "Enter the password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << endl;
    system("cls");
    cout << "Registration is successful!\n";
}

void forgot() {
    system("cls");
    int option;
    system("cls");
    cout << "You forgot the password? No worries\n";
    cout << "Press 1 to search your id by username\n";
    cout << "Press 2 to go back to the main menu\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
    case 1: {
        int count = 0;
        string suserId, sId, spass;
        cout << "Enter the username which you remembered: ";
        cin >> suserId;

        ifstream f2("records.txt");
        while (f2 >> sId >> spass) {
            if (sId == suserId) {
                count = 1;
                break;
            }
        }
        f2.close();
        if (count == 1) {
            cout << "Your account is found!\n";
            cout << "Your password is: " << spass << endl;
        }
        else {
            cout << "Account not found. Please try again.\n";
        }
        break;
    }
    case 2: {
        mainmenu();
        break;
    }
    default:
        cout << "Wrong choice! Please try again\n";
        forgot();
        break;
    }
}

void receiverdashboard() {
    int choice;
    do {
        receiverdashboardmenu();
        cout << endl << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
        {
            Feedback feedback;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, feedback.name);
            cout << "Enter your phone number: ";
            getline(cin, feedback.phone);
            cout << "Enter the amount received: Rs ";
            cin >> feedback.amount;
            deductAmount(feedback.amount); // Deduct the amount received
            cout << "Enter the purpose: ";
            cin.ignore();
            getline(cin, feedback.purpose);
            cout << "Enter any remarks: ";
            getline(cin, feedback.remarks);

            Feedback* newFeedbacks = new Feedback[feedbackCount + 1];
            for (int i = 0; i < feedbackCount; ++i) {
                newFeedbacks[i] = feedbacks[i];
            }

            newFeedbacks[feedbackCount] = feedback;
            ++feedbackCount;

            delete[] feedbacks;
            feedbacks = newFeedbacks;

            saveFeedbacks();

            cout << "\nYour Request has been approved, You got Rs " << feedback.amount << endl << endl;
            break;
        }
        case 2:
            cout << "Exiting user panel..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 2);
}


int main() {
    int mainmenuchoice, adminchoice, donoradminchoice, receiveradminchoice, userchoice, donoruserchoice;

    cout << "WELCOME TO A & F DONOR MANAGEMENT SOFTWARE" << endl;

    // MAIN PROGRAM
    do {
        mainmenu();
        cout << "\n\nEnter your choice: ";
        cin >> mainmenuchoice;

        switch (mainmenuchoice) {
        case 1:
            if (adminLogin())
            {
                // ADMIN PANEL CODES
                cout << "Admin Panel Dashboard\n";
                do {
                    displayadminmenu(); // menu display calling

                    cout << "\n\nEnter your choice: ";
                    cin >> adminchoice;

                    switch (adminchoice) {
                    case 1:
                        collections();
                        break;
                    case 2:
                        do {
                            donoradminmenu(); // donor menu display calling
                            cout << "\n\nEnter your choice: ";
                            cin >> donoradminchoice;

                            switch (donoradminchoice) {
                            case 1:
                                displayDonors();
                                break;
                            case 2:
                                deleteDonor();
                                break;
                            case 3:
                                cout << "Going back to Admin Panel...\n";
                                break;
                            default:
                                cout << "Invalid choice! Please try again.\n";
                                break;
                            }
                        } while (donoradminchoice != 3);
                        break;
                    case 3:
                        do {
                            receiveradminmenu(); // receiver menu display calling
                            cout << "\n\nEnter your choice: ";
                            cin >> receiveradminchoice;

                            switch (receiveradminchoice) {
                            case 1:
                                displayFeedbacks();
                                break;
                            case 2:
                                deleteFeedback();
                                break;
                            case 3:
                                cout << "Going back to Admin Panel...\n";
                                break;
                            default:
                                cout << "Invalid choice! Please try again.\n";
                                break;
                            }
                        } while (receiveradminchoice != 3);
                        break;
                    case 4:
                        cout << "\nGoodbye!" << endl;
                        break;
                    default:
                        cout << "\nInvalid choice! Please put correct choice.\n";
                        break;
                    }
                } while (adminchoice != 4);
            }
            break;
        case 2:
            // USER PANEL CODES
            do {
                displayuserpanel();
                cout << "\n\nEnter your choice: ";
                cin >> userchoice;
                switch (userchoice) {
                case 1:
                    do {
                        donormainmenu();
                        cout << "\n\nEnter your choice: ";
                        cin >> donoruserchoice;

                        switch (donoruserchoice) {
                        case 1:
                            if (donorlogin()) {
                                int dashboardChoice;
                                do {
                                    donordashboard();
                                    cout << "\n\nEnter your choice: ";
                                    cin >> dashboardChoice;
                                    switch (dashboardChoice) {
                                    case 1:
                                        registerDonor();
                                        break;
                                    case 2:
                                        cout << "Logging out...\n";
                                        break;
                                    default:
                                        cout << "Invalid choice! Please try again.\n";
                                        break;
                                    }
                                } while (dashboardChoice != 2);
                                donoruserchoice = 4; // Force exit to the main user panel after logging out
                            }
                            break;
                        case 2:
                            donorregistration();
                            break;
                        case 3:
                            forgot();
                            break;
                        case 4:
                            cout << "Exiting...\n";
                            break;
                        default:
                            cout << "Invalid choice! Please try again.\n";
                            break;
                        }
                    } while (donoruserchoice != 4);
                    break;
                case 2:
                    receiverdashboard();
                    break;
                case 3:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (userchoice != 3);
            break;
        case 3:
            cout << "Thank You!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

    } while (mainmenuchoice != 3);

    return 0;
}