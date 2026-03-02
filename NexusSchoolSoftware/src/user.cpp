#include "../headers/user.h"
#include <iostream>

bool User::login() {
    string u, p;
    cout << "--- NSS LOGIN ---\nUsername: "; cin >> u;
    cout << "Password: "; cin >> p;

    if (u == "admin" && p == "1234") {
        username = u;
        return true;
    }
    cout << "Login failed!" << endl;
    return false;
}