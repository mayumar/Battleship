#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Player{
    private:
        std::string username_;
        std::string password_;
        int socket_;
        bool isLogin_;
    
    public:
        inline Player(){}
        inline Player(std::string username, std::string password, int socket):
                      username_(username), password_(password), isLogin_(false), socket_(socket){}

        inline std::string getUsername(){return username_;}
        inline std::string getPassword(){return password_;}
        inline int getSocket(){return socket_;}
        inline bool isLogin(){return isLogin_;}
        
        inline void setUsername(std::string username){username_ = username;}
        inline void setPassword(std::string password){password_ = password;}
        inline void setSocket(int socket){socket_ = socket;}
        inline void setIsLogin(bool isLogin){isLogin_ = isLogin;}
};

#endif