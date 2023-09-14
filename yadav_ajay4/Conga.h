// conga.h file
#ifndef CONGA_H
#define CONGA_H
#include "linkedlist_Yadav.hpp"
#include "zombie_Yadav.cpp"


class Conga{
private:

public:
//engine action adds the zombie to the front of the line
void engine_action(LinkedList<Zombie>& list, Zombie randomZomb);
//caboose action adds the zombie to the end of the line
void caboose_action(LinkedList<Zombie>& list, Zombie randomZomb);
//jump in action adds the zombie to a random position in the line
void jump_in_action(LinkedList<Zombie>& list, Zombie randomZomb);
//everyone out action removes all the zombie of same color from the line; takes list reference and Zombie object as argument
void everyone_out_action(LinkedList<Zombie>& list, Zombie randomZomb);
//you out action removes the first matching zombie from the line
void you_out_action(LinkedList<Zombie>& list, Zombie randomZomb);
//brains action add a zombie to the front, end and to the middle of the conga line
void brains_action(LinkedList<Zombie>& list, Zombie randomZomb);
//rainbow action adds the zombie to the front of the line and add 6 zombies of different color in the order R,Y,G,B,C,M to the end of the list
void rainbow_action(LinkedList<Zombie>& list, Zombie randomZomb);
//friends action find a zombie of the randomZomb color, do a coin flip to decide if to insert the zombie beroe or after that zombie
//if no zombie of that color exist then it add that zombie to the end of the line
void friends_action(LinkedList<Zombie>& list, Zombie randomZomb);
};

#endif // CONGA_H