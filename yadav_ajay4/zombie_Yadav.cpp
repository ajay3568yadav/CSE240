#include <iostream>
#include "zombie_Yadav.h"
#include "termcolor.hpp"
using namespace std;

Zombie::Zombie() {} //default constructor for zombie class

Zombie::Zombie(char c) { // parametried constructor for zombie class
type = c;
}

// function returns the type of zombie
char Zombie::getType() const { 
return type;
}

// overloading the == operator to comapre two zombie objects
bool Zombie::operator==(const Zombie& zombie) { 
return this->type == zombie.type;
}

// overloading the == operator to comapre two zombie objects
bool Zombie::operator!=(const Zombie& zombie) {
    // returns true if the "type" of two zombie is same else false
return this->type != zombie.type; 
}

//friend function to print the zombie object
ostream& operator<<(ostream& out, const Zombie& zombie) { 
    //used termcolor to color the Zombie
    //checking if zombie is red 
    if(zombie.getType()=='R')
    {
        out << "[" << termcolor::red << zombie.getType()<< termcolor::reset <<"]";
    }
    //checking if zombie is yellow 
    if(zombie.getType()=='Y')
    {
        out << "[" << termcolor::yellow << zombie.getType()<< termcolor::reset <<"]";
    }
    //checking if zombie is green 
    if(zombie.getType()=='G')
    {
        out << "[" << termcolor::green << zombie.getType()<< termcolor::reset <<"]";
    }
    //checking if zombie is blue 
    if(zombie.getType()=='B')
    {
        out << "[" << termcolor::blue << zombie.getType()<< termcolor::reset <<"]";
    }
    //checking if zombie is cyan 
    if(zombie.getType()=='C')
    {
        out << "[" << termcolor::cyan << zombie.getType()<< termcolor::reset <<"]";
    }
    //checking if zombie is magenta 
    if(zombie.getType()=='M')
    {
        out << "[" << termcolor::magenta << zombie.getType()<< termcolor::reset <<"]";
    }
    
return out;
}

