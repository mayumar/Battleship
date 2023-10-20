#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Player{
    private:
        std::string username_;
        std::string password_;
    
    public:
        inline Player(){}
        inline Player(std::string username, std::string password):
                      username_(username), password_(password){}

        inline std::string getUsername(){return username_;}
        inline std::string getPassword(){return password_;}
        
        inline void setUsername(std::string username){username_ = username;}
        inline void setPassword(std::string password){password_ = password;}
};

#endif