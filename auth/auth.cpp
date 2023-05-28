#include <iostream>
#include "../helpers/helpers.h"

using namespace std;

bool doesUserExist(const vector<User>& users, const string& email) {
    for (const auto& user : users) {
        if (user.email == email) {
            return true;
        }
    }
    return false;
}

User addNewUser(vector<User>& users) {
    User newUser;
    cout << "Sign Up\n";
    cout << "Enter name: ";
    getline(cin >> ws, newUser.name);
    cout << "Enter email: ";
    getline(cin >> ws, newUser.email);
    cout << "Enter password: ";
    getline(cin >> ws, newUser.password);
    newUser.isAdmin = false;
    newUser.assignedBooks.clear();
    cout << "Sign Up successful!\n";
    return newUser;
}

User signUp(vector<User>& users) {
    do {
        User newUser = addNewUser(users);
        if (!doesUserExist(users, newUser.email)) {
            users.emplace_back(newUser);
            return newUser;
        } else {
            cout << "User with this email already exists. Please try again.\n";
        }
    } while (true);
}

User signIn(const vector<User>& users) {
    string email, password;
    cout << "Sign In\n";
    cout << "Enter email: ";
    getline(cin >> ws, email);
    
    bool isValidPassword = false;
    User currentUser;

    while (!isValidPassword) {
        cout << "Enter password: ";
        getline(cin >> ws, password);

        for (const auto& user : users) {
            if (user.email == email && user.password == password) {
                cout << "Sign In successful!\n";
                currentUser = user;
                isValidPassword = true;
                break;
            }
        }

        if (!isValidPassword) {
            cout << "Invalid email or password. Please try again or enter 'q' to cancel.\n";
            string input;
            getline(cin >> ws, input);
            if (input == "q" || input == "Q") {
                break;
            }
        }
    }

    if (!isValidPassword) {
        cout << "Sign In failed.\n";
        return User();  // Return an empty user if sign in fails
    }

    return currentUser;
}
