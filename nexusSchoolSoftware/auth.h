#ifndef AUTH_H
#define AUTH_H

#include <string>

struct UserAccount
{
    std::string username;
    std::string password;
    bool used;
};

const int maxAccounts = 10;

void initializeAccounts(UserAccount accounts[], int size);
bool handleAuthentication(UserAccount accounts[], int size, std::string& loggedInUser);

#endif


