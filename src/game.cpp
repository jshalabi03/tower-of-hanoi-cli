#include "game.hpp"
#include "diskstack.hpp"
#include "util.hpp"

#include <iostream>
#include <algorithm>
#include <list>

Game::Game(): Game(5) {}

Game::Game(int size) {
    num_disks_ = size;
    left_ = new DiskStack(num_disks_);
    middle_ = new DiskStack();
    right_ = new DiskStack();
}

DiskStack* Game::GetStackFromChar(char c) {
    switch (c) {
        case 'l':
            return left_;
        case 'm':
            return middle_;
        case 'r':
            return right_;
        default:
            throw std::runtime_error("bad char.");
    }
}

void Game::AcceptCommand(std::string cmd) {

    if (!IsValidCommand(cmd)) throw InvalidInputException();

    char from_char = cmd.at(0);
    char to_char = cmd.at(2);

    DiskStack* from_stack = GetStackFromChar(from_char);
    DiskStack* to_stack = GetStackFromChar(to_char);

    from_stack->Move(to_stack);
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    std::vector<int> left_copy(g.left_->disks_);
    std::vector<int> middle_copy(g.middle_->disks_);
    std::vector<int> right_copy(g.right_->disks_);
    std::list<std::vector<int>*> stacks
     {&left_copy, &middle_copy, &right_copy};

    size_t max_height = std::max(left_copy.size(),
                        std::max(middle_copy.size(),
                                 right_copy.size()));

    for (int curr_height = max_height; 
         curr_height > 0; 
         --curr_height) {

        for (std::vector<int>* stack : stacks) {
            if (stack->size() < curr_height) PrintMultipleTimes(os, ' ', g.num_disks_);
            else {
                PrintMultipleTimes(os, 'a', stack->at(curr_height - 1) + 1);
                PrintMultipleTimes(os, ' ', g.num_disks_ - (stack->at(curr_height - 1) + 1) );
            }
            if (stack != &right_copy) os << ' ';
        }
        os << '\n';
    }

    PrintMultipleTimes(os, '-', g.num_disks_);
    os << ' ';
    PrintMultipleTimes(os, '-', g.num_disks_);
    os << ' ';
    PrintMultipleTimes(os, '-', g.num_disks_);

    return os;

}

bool Game::HasWon() {
    return right_->Height() == num_disks_;
}

void Game::Play() {
    std::cout << *this << std::endl;
    std::string cmd;
    while (true) {
        std::cout << "COMMAND: ";
        std::getline(std::cin, cmd);
        try {
            AcceptCommand(cmd);
            std::cout << "_________________________________\n";
            std::cout << std::endl << *this << std::endl;
            if (HasWon()) {
                std::cout << "Congratulations, you win!" << std::endl;
                break;
            }
        } catch (InvalidInputException& e) {
            std::cout << "Invalid command." << std::endl;
        } catch (BadMoveException& e) {
            std::cout << "Invalid move." << std::endl;
        }
    }
}

bool IsValidCommand(std::string cmd) {
    std::vector<std::string> valid_options
        {"lr", "lm", "ml", "mr", "rl", "rm"};

    if (cmd.length() != 3) return false;

    std::string res;
    res.push_back(cmd.at(0));
    res.push_back(cmd.at(2));

    return cmd.at(1) == ' ' && 
        std::find(valid_options.begin(), valid_options.end(), res) 
        != valid_options.end();
}