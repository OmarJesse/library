#include <iostream>
#include "admin.h"
#include "../helpers/helpers.h"
#include "../book/book.h"
#include "../user/user.h"

using namespace std;

void getAdminOptions(const User &currentUser, int &option)
{
  do
  {
  vector<User> users = readUsersFromFile();
  vector<Book> books = readBooksFromFile();
    cout << "\nChoose an option:\n";
    cout << "1. Create a book\n";
    cout << "2. Edit a book\n";
    cout << "3. Remove a book\n";
    cout << "4. View all books\n";
    cout << "5. View all users\n";
    cout << "6. View assign requests\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> option;
    Book selectedBook;
    vector<pair<string, string>> assignRequests = readAssignRequestsFromFile();
    switch (option)
    {
    case 1:
    {
      addBook(books);
      writeBooksToFile(books);
      break;
    }
    case 2:
    {
      selectedBook = selectBook(books);
      editBook(books, selectedBook);
      writeBooksToFile(books);
      break;
    }
    case 3:
      selectedBook = selectBook(books);
      deleteBook(books, selectedBook);
      writeBooksToFile(books);
      break;
    case 4:
      viewBooks(books);
      break;
    case 5:
      viewAllUsers(users);
      break;
    case 6:
      assignRequests = readAssignRequestsFromFile();
      manageAssignRequests(assignRequests, books, users);
      break;
    case 7:
      cout << "Exiting the program.\n";
      return;
    default:
      cout << "Invalid option. Try again.\n";
    }
  } while (option != 7);
}