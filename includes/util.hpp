#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <exception>

struct InvalidInputException : public std::exception {

    const char* what() const throw() {
        return "Invalid Input.";
    }

};

struct BadMoveException : public std::exception {

    const char* what() const throw() {
        return "Bad move.";
    }

};

std::ostream& PrintMultipleTimes(std::ostream& os,
                                 char ch,
                                 unsigned freq);

#endif