// zombie.h file
//contains the methods for the Zombie class
#ifndef ZOMBIE_H
#define ZOMBIE_H

using namespace std;

class Zombie { // zombie class defination
private:
char type; // type of zombie represented by the char data type
public:
Zombie(); //default constructor
Zombie(char c); // parametrized constructor, taking a char(type of zombie as argument
char getType() const; //returns the type of zombie/ zombie's color
bool operator == (const Zombie& zombie); //overloaded == operater comparing the char type of the zombie
bool operator != (const Zombie& zombie); //overloaded != operator comparing the char type of the zombie
friend ostream& operator<<(ostream& out, const Zombie& zombie); // friend function prints the char type of the zombie
};
// overloaded out function to print zombie object
ostream& operator<<(ostream& out, const Zombie& zombie);

#endif 
