#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Function prototypes
void registration();
bool login();
void changePassword();
void mainMenu();
void clearScreen();
string getPasswordInput();

int main() {
    int choice;
    
    while (true) {
        clearScreen();
        cout << "\n\t\t==============================" << endl;
        cout << "\t\t| SECURITY SYSTEM PROJECT   |" << endl;
        cout << "\t\t==============================" << endl;
        cout << "\t\t|                           |" << endl;
        cout << "\t\t| 1. Register              |" << endl;
        cout << "\t\t| 2. Login                 |" << endl;
        cout << "\t\t| 3. Exit                  |" << endl;
        cout << "\t\t|                           |" << endl;
        cout << "\t\t==============================" << endl;
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;
        
        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\t\tInvalid input. Please enter a number." << endl;
            cout << "\n\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                registration();
                break;
            case 2:
                if (login()) {
                    mainMenu();
                }
                break;
            case 3:
                cout << "\n\t\tThank you for using our system!" << endl;
                return 0;
            default:
                cout << "\n\t\tInvalid choice. Press Enter to try again...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
        }
    }
    
    return 0;
}

void clearScreen() {
    // Cross-platform clear screen
    cout << string(50, '\n');
}

string getPasswordInput() {
    string password;
    // For simplicity, we're not hiding input in this cross-platform version
    // In a real application, you'd use platform-specific code or a library for this
    cout << "\n\t\t(Note: Password will be visible as you type)" << endl;
    cout << "\t\t";
    cin >> password;
    return password;
}

void registration() {
    string username, password;
    
    clearScreen();
    cout << "\n\t\t==============================" << endl;
    cout << "\t\t|      REGISTRATION         |" << endl;
    cout << "\t\t==============================" << endl;
    
    cout << "\n\t\tEnter Username: ";
    cin >> username;
    
    // Check if username already exists
    ifstream checkFile("users.txt");
    string line;
    bool userExists = false;
    
    while (getline(checkFile, line)) {
        if (line.substr(0, line.find(':')) == username) {
            userExists = true;
            break;
        }
    }
    checkFile.close();
    
    if (userExists) {
        cout << "\n\t\tUsername already exists! Please try a different username." << endl;
        cout << "\n\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    
    cout << "\t\tEnter Password: ";
    password = getPasswordInput();
    
    // Save the user details to file
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << ":" << password << endl;
        file.close();
        cout << "\n\n\t\tRegistration Successful!" << endl;
    }
    else {
        cout << "\n\n\t\tError opening file!" << endl;
    }
    
    cout << "\n\t\tPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool login() {
    string username, password;
    string storedUsername, storedPassword;
    bool loginSuccess = false;
    
    clearScreen();
    cout << "\n\t\t==============================" << endl;
    cout << "\t\t|         LOGIN             |" << endl;
    cout << "\t\t==============================" << endl;
    
    cout << "\n\t\tEnter Username: ";
    cin >> username;
    
    cout << "\t\tEnter Password: ";
    password = getPasswordInput();
    
    // Check if username and password match
    ifstream file("users.txt");
    string line;
    
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            storedUsername = line.substr(0, pos);
            storedPassword = line.substr(pos + 1);
            
            if (username == storedUsername && password == storedPassword) {
                loginSuccess = true;
                break;
            }
        }
    }
    file.close();
    
    if (loginSuccess) {
        cout << "\n\n\t\tLogin Successful!" << endl;
        cout << "\n\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return true;
    }
    else {
        cout << "\n\n\t\tInvalid Username or Password!" << endl;
        cout << "\n\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return false;
    }
}

void changePassword() {
    string username, oldPassword, newPassword;
    bool found = false;
    
    clearScreen();
    cout << "\n\t\t==============================" << endl;
    cout << "\t\t|     CHANGE PASSWORD       |" << endl;
    cout << "\t\t==============================" << endl;
    
    cout << "\n\t\tEnter Username: ";
    cin >> username;
    
    cout << "\t\tEnter Old Password: ";
    oldPassword = getPasswordInput();
    
    // Read the file content
    ifstream inFile("users.txt");
    string line;
    string fileContent = "";
    
    while (getline(inFile, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string storedUsername = line.substr(0, pos);
            string storedPassword = line.substr(pos + 1);
            
            if (username == storedUsername && oldPassword == storedPassword) {
                found = true;
                
                cout << "\n\t\tEnter New Password: ";
                newPassword = getPasswordInput();
                
                fileContent += storedUsername + ":" + newPassword + "\n";
            }
            else {
                fileContent += line + "\n";
            }
        }
    }
    inFile.close();
    
    if (found) {
        // Write the updated content back to the file
        ofstream outFile("users.txt");
        outFile << fileContent;
        outFile.close();
        
        cout << "\n\n\t\tPassword changed successfully!" << endl;
    }
    else {
        cout << "\n\n\t\tInvalid Username or Password!" << endl;
    }
    
    cout << "\n\t\tPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mainMenu() {
    int choice;
    
    while (true) {
        clearScreen();
        cout << "\n\t\t==============================" << endl;
        cout << "\t\t|        MAIN MENU          |" << endl;
        cout << "\t\t==============================" << endl;
        cout << "\t\t|                           |" << endl;
        cout << "\t\t| 1. Change Password       |" << endl;
        cout << "\t\t| 2. Logout                |" << endl;
        cout << "\t\t|                           |" << endl;
        cout << "\t\t==============================" << endl;
        cout << "\n\t\tEnter your choice: ";
        cin >> choice;
        
        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\t\tInvalid input. Please enter a number." << endl;
            cout << "\n\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            continue;
        }
        
        switch (choice) {
            case 1:
                changePassword();
                break;
            case 2:
                cout << "\n\t\tLogging out..." << endl;
                cout << "\n\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                return;
            default:
                cout << "\n\t\tInvalid choice. Press Enter to try again...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
        }
    }
}