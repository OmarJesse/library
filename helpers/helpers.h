#ifndef HELPERS_H
#define HELPERS_H
#define ASSIGN_REQUEST_FILE_NAME "assignRequests.csv"
#include <string>
#include <vector>
#include <iostream>
#include "../book/book.h"
#include "../user/user.h"

void writeUsersToFile(const std::vector<User>& users);
std::vector<User> readUsersFromFile();
void writeBooksToFile(const std::vector<Book>& books);
std::vector<Book> readBooksFromFile();
std::vector<std::pair<std::string, std::string>> readAssignRequestsFromFile();
void writeAssignRequestsToFile(const std::vector<std::pair<std::string, std::string>> &assignRequests);

#endif
