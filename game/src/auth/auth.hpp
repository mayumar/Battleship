#ifndef AUTH_HPP
#define AUTH_HPP

#include <string>
#include "../classes/player/Player.hpp"

bool loginUsername(std::string user);
bool loginPass(std::string password);
Player signup(std::string username, std::string password, int socket);

#endif