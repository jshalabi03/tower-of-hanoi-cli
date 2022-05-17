#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "diskstack.hpp"

class Game {
public:
    Game();
    Game(int size);
    void AcceptCommand(std::string cmd);
    void Play();
    bool HasWon();
    friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
    DiskStack* GetStackFromChar(char c);
    DiskStack* left_;
    DiskStack* middle_;
    DiskStack* right_;
    int num_disks_;
};

#endif