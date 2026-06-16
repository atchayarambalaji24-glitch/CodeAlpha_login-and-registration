#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct User {
    char username[20];
    char password[20];
};

void registerUser() {
    User u;
    cout << "Enter username: ";
    cin >> u.username;
    cout << "Enter password: ";
    cin >> u.password;

    // check duplicate
    ifstream fin("users.dat", ios::binary);
    User temp;
    while (fin.read((char*)&temp, sizeof(User))) {
        if (strcmp(temp.username, u.username) == 0) {
            cout << "Username already exists!\n";
            fin.close();
            return;
        }
    }
    fin.close();

    ofstream fout("users.dat", ios::binary | ios::app);
    fout.write((char*)&u, sizeof(User));
    fout.close();
    cout << "Registration successful!\n";
}

void loginUser() {
    char uname[20], pass[20];
    cout << "Enter username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pass;

    ifstream fin("users.dat", ios::binary);
    User temp;
    while (fin.read((char*)&temp, sizeof(User))) {
        if (strcmp(temp.username, uname) == 0 && strcmp(temp.password, pass) == 0) {
            cout << "Login successful!\n";
            fin.close();
            return;
        }
    }
    fin.close();
    cout << "Invalid username or password!\n";
}

int main() {
    int choice;
    cout << "1. Register\n2. Login\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
        registerUser();
    else if (choice == 2)
        loginUser();
    else
        cout << "Invalid choice!\n";

    return 0;
}
