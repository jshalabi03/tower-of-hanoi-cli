#include "diskstack.hpp"
#include "game.hpp"
#include "util.hpp"

#include <stdexcept>

DiskStack::DiskStack(int height) {
    disks_ = std::vector<int>();
    for (int i = height - 1; i >= 0; --i)
        disks_.push_back(i);
}

int DiskStack::TakeFromTop() {
    int top = disks_.at(Height() - 1);
    disks_.erase(disks_.begin() + Height() - 1);
    return top;
}

int DiskStack::Top() {
    return disks_.at(Height() - 1);
}

bool DiskStack::CanAccept(int other) {
    if (Height() == 0) return true;
    return disks_.at(Height() - 1) > other;
}

void DiskStack::Accept(int other) {
    if (!CanAccept(other)) throw BadMoveException();
    disks_.push_back(other);
}

void DiskStack::Move(DiskStack* other) {
    if (this->Height() == 0 || this == other) throw BadMoveException();
    int top = Top();
    if (!other->CanAccept(top)) throw BadMoveException();
    other->Accept(top);
    TakeFromTop();
}