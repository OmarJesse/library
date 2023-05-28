#ifndef AUTH_H
#define AUTH_H

#include <vector>
#include "../helpers/helpers.h"

bool doesUserExist(const std::vector<User>& users, const std::string& email);
User addNewUser(std::vector<User>& users);
User signUp(std::vector<User>& users);
User signIn(const std::vector<User>& users);

#endif
