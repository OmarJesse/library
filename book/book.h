#ifndef BOOK_H
#define BOOK_H
#define BOOK_FILE_NAME "books.csv"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "book.h"
#include "../user/user.h"

struct Book
{
  std::string id;
  std::string title;
  std::string author;
  std::string status;
};

void addBook(std::vector<Book> &books);
void deleteBook(std::vector<Book> &books, Book &book);
void editBook(std::vector<Book>& books, Book& book);
Book selectBook(std::vector<Book> &books);
void viewBooks(std::vector<Book> &books);
void viewAssignRequests(const std::vector<std::pair<std::string, std::string>>& assignRequests);
void manageAssignRequests(std::vector<std::pair<std::string, std::string>>& assignedRequests, std::vector<Book>& books, std::vector<User>& users);

#endif