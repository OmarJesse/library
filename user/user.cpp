#include <iostream>
#include <limits>
#include "user.h"
#include "../helpers/helpers.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void viewAllUsers(const vector<User>& users) {
    cout << "All Users\n";
    for (const auto& user : users) {
        cout << "Name: " << user.name << "\n";
        cout << "Email: " << user.email << "\n";
        cout << "Password: " << user.password << "\n";
        cout << "Is Admin: " << (user.isAdmin ? "Yes" : "No") << "\n";
        cout << "Assigned Books: ";
        for (const auto& book : user.assignedBooks) {
            cout << book << ", ";
        }
        cout << "\n\n";
    }
}

vector<Book> getAssignedBooks(const vector<Book> &books, const User &user)
{
    vector<Book> assignedBooks;
    for (const string &bookId : user.assignedBooks)
    {
        for (const Book &book : books)
        {
            if (book.id == bookId)
            {
                assignedBooks.push_back(book);
            }
        }
    }
    return assignedBooks;
}

void editUserProfile(vector<User> &users, const User &currentUser)
{
    // Find the index of the current user in the users vector
    int index = -1;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].email == currentUser.email)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "User not found.\n";
        return;
    }

    User &user = users[index];

    cout << "Edit Profile:\n";
    cout << "1. Change Name\n";
    cout << "2. Change Password\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        string newName;
        cout << "Enter your new name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newName);
        user.name = newName;
        cout << "Name updated successfully.\n";
        break;
    }
    case 2:
    {
        string newPassword;
        cout << "Enter your new password: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newPassword);
        user.password = newPassword;
        cout << "Password updated successfully.\n";
        break;
    }
    default:
        cout << "Invalid option. Try again.\n";
        break;
    }

    // Update the user in the users vector
    users[index] = user;
}

void requestBook(const Book &book, const User &currentUser)
{
    // Check if the book is already assigned
    if (book.status == "assigned")
    {
        cout << "The book is already assigned.\n";
        return;
    }

    // Read existing assigned requests from assignRequests.csv
    vector<pair<string, string>> assignRequests;
    readAssignRequestsFromFile();

    // Add the new request
    assignRequests.emplace_back(currentUser.email, book.id);

    // Write the updated assigned requests to assignRequests.csv
    writeAssignRequestsToFile(assignRequests);

    cout << "Book request submitted successfully.\n";
}

void unassignBook(vector<User>& users, vector<Book>& books, const string& userEmail, const string& bookId) {
    // Find the user with the specified email
    auto userIter = find_if(users.begin(), users.end(), [&](const User& user) {
        return user.email == userEmail;
    });

    if (userIter != users.end()) {
        User& user = *userIter;

        // Remove the book from the user's assigned books
        auto bookIter = find(user.assignedBooks.begin(), user.assignedBooks.end(), bookId);
        if (bookIter != user.assignedBooks.end()) {
            user.assignedBooks.erase(bookIter);
            cout << "Book unassigned successfully from user: " << userEmail << endl;
        } else {
            cout << "Book not found in user's assigned books." << endl;
        }
    } else {
        cout << "User not found." << endl;
    }

    // Update the book status to "unassigned"
    auto bookIter = find_if(books.begin(), books.end(), [&](const Book& book) {
        return book.id == bookId;
    });

    if (bookIter != books.end()) {
        Book& book = *bookIter;
        book.status = "unassigned";
        cout << "Book status updated to unassigned: " << bookId << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

void getUserOptions(const User &currentUser, int &option)
{
    do
    {
        cout << "\nChoose an option:\n";
        cout << "1. View my assigned books\n";
        cout << "2. Request a book\n";
        cout << "3. Return a book\n";
        cout << "4. Edit my profile\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;
        Book selectedBook;
        vector<Book> assignedBooks;
        vector<User> users = readUsersFromFile();
        vector<Book> books = readBooksFromFile();
        switch (option)
        {
        case 1:
        {
            assignedBooks = getAssignedBooks(books, currentUser);
            cout << "Assigned Books:\n";
            viewBooks(assignedBooks);
            break;
        }
        case 2:
        {
            selectedBook = selectBook(books);
            requestBook(selectedBook, currentUser);
            break;
        }
        case 3:
            assignedBooks = getAssignedBooks(books, currentUser);
            selectedBook = selectBook(assignedBooks);
            unassignBook(users, books, currentUser.email, selectedBook.id);
            writeBooksToFile(books);
            writeUsersToFile(users);
            break;
        case 4:
            editUserProfile(users, currentUser);
            writeUsersToFile(users);
            break;
        case 5:
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (option != 5);
}
