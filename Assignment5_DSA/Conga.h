// conga.h file
#ifndef CONGA_H
#define CONGA_H
#include "linkedlist.hpp"
#include "Zombie.cpp"
#include <stdexcept>

class Conga : public LinkedList<Zombie>, public Zombie {
private:

public:
void engine_action(LinkedList<Zombie>& list, Zombie randomZomb);
void caboose_action(LinkedList<Zombie>& list, Zombie randomZomb);
void jump_in_action(LinkedList<Zombie>& list, Zombie randomZomb);
void everyone_out_action(LinkedList<Zombie>& list, Zombie randomZomb);
void you_out_action(LinkedList<Zombie>& list, Zombie randomZomb);
void brains_action(LinkedList<Zombie>& list, Zombie randomZomb);
void rainbow_action(LinkedList<Zombie>& list, Zombie randomZomb);
void friends_action(LinkedList<Zombie>& list, Zombie randomZomb);
};

#endif // CONGA_H