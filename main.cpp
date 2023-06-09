#include <iostream>
#include <limits>
#include "./helpers/helpers.h"
#include "./auth/auth.h"
#include "./book/book.h"
#include "./admin/admin.h"
#include "./user/user.h"

using namespace std;

void authenticationFlow(vector <User> & users, vector <Book> & books) {
  bool isLoggedIn = false;
  User currentUser;

  do {
    cout << "Choose an option:\n";
    cout << "1. Sign Up\n";
    cout << "2. Sign In\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    while (!(cin >> choice)) {
      cout << "Invalid choice. Try again.\n";
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }

    switch (choice) {
    case 1:
      currentUser = signUp(users);
      isLoggedIn = true;
      break;
    case 2:
      currentUser = signIn(users);
      if (!currentUser.name.empty()) {
        isLoggedIn = true;
      }
      break;
    case 3:
      cout << "Exiting the program.\n";
      return;
    default:
      cout << "Invalid choice. Try again.\n";
    }
  } while (!isLoggedIn);

  cout << "Logged in as: " << currentUser.name << endl;

  writeUsersToFile(users);

  int option;
  if (currentUser.isAdmin) {
    getAdminOptions(currentUser, option);
    if (option == 4) {
    }
  } else {
    getUserOptions(currentUser, option);
  }

  authenticationFlow(users, books); // Recursive call to go back to authentication flow
}

int main() {
  vector <User> users = readUsersFromFile();
  vector <Book> books = readBooksFromFile();

  authenticationFlow(users, books);

  return 0;
}