#ifndef AUTH_H
#define AUTH_H
#include <string>
using namespace std;

struct UserAccount
{
    string username;
    string password;
    bool used;
};

const int maxAccounts = 10;

void initializeAccounts(UserAccount accounts[], int size);
bool handleAuthentication(UserAccount accounts[], int size, string& loggedInUser);

#endif