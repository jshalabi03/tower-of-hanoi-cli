#ifndef DISKSTACK_H
#define DISKSTACK_H

#include <vector>
#include <iostream>

class Game;

class DiskStack {
public:
    DiskStack() = default;
    DiskStack(int height);
    int TakeFromTop();
    int Top();
    bool CanAccept(int other);
    void Accept(int other);
    void Move(DiskStack* other);
    size_t Height() { return disks_.size(); }
    friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
    std::vector<int> disks_;
};

#endif