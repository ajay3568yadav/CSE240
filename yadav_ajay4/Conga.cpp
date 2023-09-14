#include <iostream>
#include "Conga.h"

//engine action adds the zombie to the front of the line
void Conga::engine_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        // add the zombie to the front of the line
        list.AddToFront(randomZomb);
}

//caboose action adds the zombie to the end of the line
void Conga::caboose_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        //add the zombie to the end of the line
        list.AddToEnd(randomZomb);
}

//jump in action adds the zombie to a random position in the line
void Conga::jump_in_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        //add the zombie at a random position in the line
        list.AddAtIndex(randomZomb, rand() % (list.Length()+1));
}

//everyone out action removes all the zombie of same color from the line; takes list reference and Zombie object as argument
void Conga::everyone_out_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        //removes all of the matching zombie
        list.RemoveAllOf(randomZomb);
}

//you out action removes the first matching zombie from the line
void Conga::you_out_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        //removes the first matching zombie
        list.RemoveTheFirst(randomZomb);
}

//brains action add a zombie to the front, end and to the middle of the conga line
void Conga::brains_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        //add the zombie at the middle
        list.AddAtIndex(randomZomb, (list.Length()) / 2);
        //add the zombie to the front of the line
        engine_action(list, randomZomb);
        //add the zombie to the end of the line
        caboose_action(list, randomZomb);
}

//rainbow action adds the zombie to the front of the line and add 6 zombies of different color in the order R,Y,G,B,C,M to the end of the list
void Conga::rainbow_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        // add the zombie to the front 
        engine_action(list, randomZomb);
        //create 6 zombies of different color in the given order
        Zombie red('R'), yellow('Y'), green('G'), blue('B'), cyan('C'), magenta('M');
        //perform caboose action on these zombies
        caboose_action(list, red);
        caboose_action(list, yellow);
        caboose_action(list, green);
        caboose_action(list, blue);
        caboose_action(list, cyan);
        caboose_action(list, magenta);
}

//friends action find a zombie of the randomZomb color, do a coin flip to decide if to insert the zombie beroe or after that zombie
//if no zombie of that color exist then it add that zombie to the end of the line
void Conga::friends_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        //checking if the zombie exists?
        if (list.ElementExists(randomZomb)) {
                //fliping a coin to decide insertion 
                int coin_flip = rand() % 2;
                if (coin_flip == 0) {
                        //insert before that matching zombie if flip is 0
                        list.AddBefore(list.Find(randomZomb), randomZomb);
                } else {
                        //insert after if flip is 1
                        list.AddAfter(list.Find(randomZomb), randomZomb);
                }
        } else {
                //else perform caboose action
                caboose_action(list, randomZomb);
        }
}