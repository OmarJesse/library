#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "helpers.h"
#include "../book/book.h"
#include "../admin/admin.h"
#include "../user/user.h"
#include <algorithm>

using namespace std;
void writeUsersToFile(const vector<User>& users) {
    ofstream file(USER_FILE_NAME);
    if (file.is_open()) {
        bool isFirstLine = file.tellp() == 0;  // Check if the file is empty
        if (isFirstLine) {
            file << "name,email,password,isAdmin,assignedBooks\n";  // Write the header line
        }
        for (const auto& user : users) {
            file << user.name << "," << user.email << "," << user.password << ","
                    << (user.isAdmin ? "true" : "false") << ",";
            if (!user.assignedBooks.empty()) {
                for (size_t i = 0; i < user.assignedBooks.size(); ++i) {
                    file << user.assignedBooks[i];
                    if (i != user.assignedBooks.size() - 1) {
                        file << ";";  // Use a delimiter to separate multiple assigned books
                    }
                }
            }
            file << "\n";
        }
        file.close();
        cout << "Users data saved to file: " << USER_FILE_NAME << "\n";
    } else {
        cerr << "Error: Unable to open file for writing: " << USER_FILE_NAME << "\n";
    }
}

vector<User> readUsersFromFile() {
    vector<User> users;

    ifstream file(USER_FILE_NAME);
    if (file.is_open()) {
        string line;
        getline(file, line);  // Read and discard the header line
        while (getline(file, line)) {
            istringstream iss(line);
            string name, email, password, isAdminStr, assignedBooksStr;
            if (getline(iss, name, ',') && getline(iss, email, ',') &&
                getline(iss, password, ',') && getline(iss, isAdminStr, ',')) {
                User user;
                user.name = name;
                user.email = email;
                user.password = password;
                user.isAdmin = (isAdminStr == "true");

                getline(iss, assignedBooksStr);  // Read the remaining line

                // Remove leading and trailing double quotes from assignedBooksStr
                if (!assignedBooksStr.empty() && assignedBooksStr.front() == '"') {
                    assignedBooksStr.erase(assignedBooksStr.begin());
                }
                if (!assignedBooksStr.empty() && assignedBooksStr.back() == '"') {
                    assignedBooksStr.pop_back();
                }

                // Split assignedBooksStr into individual books
                istringstream booksStream(assignedBooksStr);
                string book;
                while (getline(booksStream, book, ';')) {
                    // Trim leading and trailing spaces from each book string
                    book.erase(remove_if(book.begin(), book.end(), ::isspace), book.end());

                    user.assignedBooks.push_back(book);
                }

                users.push_back(user);
            }
        }
        file.close();
        cout << "Users read from file successfully.\n";
    } else {
        cout << "Unable to open the file.\n";
    }

    return users;
}

void writeBooksToFile(const vector<Book>& books) {
    ofstream file(BOOK_FILE_NAME);
    if (file.is_open()) {
        bool isFirstLine = file.tellp() == 0; // Check if the file is empty
        if (isFirstLine) {
            file << "id,title,author,status\n";
        }
        
        for (const auto& book : books) {
            file << book.id << "," << book.title << "," << book.author << "," << book.status << "\n";
        }
        file.close();
        cout << "Books data saved to file: " << BOOK_FILE_NAME << "\n";
    } else {
        cerr << "Error: Unable to open file for writing: " << BOOK_FILE_NAME << "\n";
    }
}

vector<Book> readBooksFromFile() {
    vector<Book> books;

    ifstream file(BOOK_FILE_NAME);
    if (file.is_open()) {
        string line;
        getline(file, line);  // Read and discard the header line
        while (getline(file, line)) {
            istringstream iss(line);
            string id, title, author, status;
            if (getline(iss, id, ',') && getline(iss, title, ',') &&
                getline(iss, author, ',') && getline(iss, status, ',')) {
                Book book;
                book.id = id;
                book.title = title;
                book.author = author;
                book.status = status;
                books.push_back(book);
            }
        }
        file.close();
        cout << "Books read from file successfully.\n";
    } else {
        cout << "Unable to open the file.\n";
    }

    return books;
}

vector<pair<string, string>> readAssignRequestsFromFile()
{
    vector<pair<string, string>> assignRequests;

    ifstream file(ASSIGN_REQUEST_FILE_NAME);
    if (!file.is_open())
    {
        cout << "Error opening assignRequests.csv\n";
        return assignRequests;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string userEmail, bookId;

        if (getline(ss, userEmail, ',') && getline(ss, bookId))
        {
            assignRequests.emplace_back(userEmail, bookId);
        }
    }

    file.close();

    return assignRequests;
}

void writeAssignRequestsToFile(const vector<pair<string, string>> &assignRequests)
{
    ofstream file(ASSIGN_REQUEST_FILE_NAME);
    if (!file.is_open())
    {
        cout << "Error opening assignRequests.csv\n";
        return;
    }

    for (const auto &request : assignRequests)
    {
        file << request.first << "," << request.second << "\n";
    }

    file.close();
}
