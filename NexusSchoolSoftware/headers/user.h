#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

class User {
private:
    string username;
public:
    bool login();
    string getUsername() { return username; }
};

#endif