#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>
#include "book.h"
#include "../helpers/helpers.h"
#include "../user/user.h"

using namespace std;

void addBook(vector<Book> &books)
{
  Book newBook;
  cout << "Add Book\n";
  cout << "Enter the book title: ";
  getline(cin >> ws, newBook.title);
  cout << "Enter the author: ";
  getline(cin >> ws, newBook.author);
  newBook.id = books.empty() ? "1" : to_string(stoi(books.back().id) + 1);
  newBook.status = "unassigned";
  books.push_back(newBook);
  cout << "Book added successfully!\n";
}

void editBook(vector<Book>& books, Book& book)
{
  do
  {
    cout << "Choose an option:\n";
    cout << "1. Edit title\n";
    cout << "2. Edit author\n";
    cout << "3. Save changes\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
      case 1:
      {
        string newTitle;
        cout << "Enter the new title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newTitle);
        book.title = newTitle;
        cout << "Title updated successfully.\n";

        // Update the book in the vector
        for (Book& b : books)
        {
          if (b.id == book.id)
          {
            b.title = book.title;
            break;
          }
        }
        break;
      }
      case 2:
      {
        string newAuthor;
        cout << "Enter the new author: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newAuthor);
        book.author = newAuthor;
        cout << "Author updated successfully.\n";

        // Update the book in the vector
        for (Book& b : books)
        {
          if (b.id == book.id)
          {
            b.author = book.author;
            break;
          }
        }
        break;
      }
      case 3:
        return;
      default:
        cout << "Invalid option. Try again.\n";
    }
  } while (true);
}

void deleteBook(vector<Book> &books, Book &book)
{
  for (int i = 0; i < books.size(); i++)
  {
    if (books[i].id == book.id)
    {
      books.erase(books.begin() + i);
      cout << "Book deleted successfully!\n";
      return;
    }
  }
}

Book selectBook(vector<Book>& books)
{
  int choice;
  cout << "Choose a book:\n";
  for (int i = 0; i < books.size(); ++i)
  {
    cout << i + 1 << ". " << books[i].title << " by " << books[i].author << "\n";
  }

  do
  {
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > books.size())
    {
      cout << "Invalid choice. Try again.\n";
    }
  } while (choice < 1 || choice > books.size());

  return books[choice - 1];
}

void viewBooks(vector<Book>& books)
{
  for (int i = 0; i < books.size(); ++i)
  {
    cout << i + 1 << ". " << books[i].title << " by " << books[i].author << "\n";
  }
}

void viewAssignRequests(const vector<pair<string, string>>& assignRequests) {
  if (assignRequests.empty()) {
    cout << "No assign requests found.\n";
    return;
  }

  cout << "Assign Requests:\n";
  for (int i = 0; i < assignRequests.size(); ++i) {
    cout << i + 1 << ". " << assignRequests[i].first << " - " << assignRequests[i].second << "\n";
  }
}

void assignBook(vector<User> &users, const string &currentUserEmail, vector<Book> &books, const string &bookId)
{
  User currentUser;
  for (const auto &user : users)
  {
    if (user.email == currentUserEmail)
    {
      currentUser = user;
      break;
    }
  }
  Book book;
  for (const auto &b : books)
  {
    if (b.id == bookId)
    {
      book = b;
      break;
    }
  }
  currentUser.assignedBooks.push_back(bookId);
  book.status = "assigned";
  for (int i = 0; i < users.size(); ++i)
  {
    if (users[i].email == currentUserEmail)
    {
      users[i] = currentUser;
      break;
    }
  }
  for (int i = 0; i < books.size(); ++i)
  {
    if (books[i].id == bookId)
    {
      books[i] = book;
      break;
    }
  }
  
  cout << "Book assigned successfully.\n";
}

void manageAssignRequests(vector<pair<string, string>>& assignedRequests, vector<Book>& books, vector<User>& users) {
    do {
        cout << "\n";
        // Display the list of assign requests
        viewAssignRequests(assignedRequests);

        // Prompt the admin to select a request
        char choice;
        cout << "\n" << "Enter the index of the request to manage (or E to exit): ";
        cin >> choice;

        // Validate the choice and perform corresponding actions
        if (isdigit(choice)) {
            int index = choice - '0';
            if (index > 0 && index <= assignedRequests.size()) {
                pair<string, string> selectedRequest = assignedRequests[index - 1];

                // Display the details of the selected request
                cout << "Selected request:\n";
                cout << "User: " << selectedRequest.first << "\n";
                cout << "Book: " << selectedRequest.second << "\n";

                // Prompt the admin to accept or reject the request
                cout << "Enter 'A' to accept or 'R' to reject (or 'E' to exit): ";
                char decision;
                cin >> decision;

                // Process the admin's decision
                if (decision == 'A' || decision == 'a') {
                    // Assign the book to the user
                    for (User& user : users) {
                        if (user.name == selectedRequest.first) {
                            user.assignedBooks.push_back(selectedRequest.second);
                            break;
                        }
                    }

                    // Remove the request from the assignedRequests vector
                    assignedRequests.erase(assignedRequests.begin() + index - 1);

                    // Update the books and users files
                    assignBook(users, selectedRequest.first, books, selectedRequest.second);
                    writeBooksToFile(books);
                    writeUsersToFile(users);
                    writeAssignRequestsToFile(assignedRequests);

                    cout << "Book assigned to the user.\n";
                } else if (decision == 'R' || decision == 'r') {
                    // Remove the request from the assignedRequests vector
                    assignedRequests.erase(assignedRequests.begin() + index - 1);

                    // Update the assignedRequests file
                    writeAssignRequestsToFile(assignedRequests);

                    cout << "Request rejected.\n";
                } else {
                    cout << "Invalid decision. Try again.\n";
                }
            } else {
                cout << "Invalid index. Try again.\n";
            }
        } else if (choice == 'E' || choice == 'e') {
            // Exit the loop if the admin chooses to exit
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}



