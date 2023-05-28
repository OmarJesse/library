#ifndef USER_H
#define USER_H
#define USER_FILE_NAME "users.csv"

#include <string>
#include <vector>

struct User;
struct Book;

void viewAllUsers(const std::vector<User>& users);
void getUserOptions(const User& currentUser, int& option);

#include "../helpers/helpers.h"

struct User {
    std::string name;
    std::string email;
    std::string password;
    bool isAdmin;
    std::vector<std::string> assignedBooks;
};

#endif