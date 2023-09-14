#include <iostream>

#include "Conga.h"

void Conga::engine_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        list.AddToFront(randomZomb);
}

void Conga::caboose_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        list.AddToEnd(randomZomb);
}

void Conga::jump_in_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        list.AddAtIndex(randomZomb, rand() % list.Length());
}

void Conga::everyone_out_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        list.RemoveAllOf(randomZomb);
}

void Conga::you_out_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        list.RemoveTheFirst(randomZomb);
}

void Conga::brains_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        list.AddAtIndex(randomZomb, (list.Length() - 1) / 2);
        engine_action(list, randomZomb);
        caboose_action(list, randomZomb);
}

void Conga::rainbow_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        engine_action(list, randomZomb);
        Zombie red('R'), yellow('Y'), green('G'), blue('B'), cyan('C'), magenta('M');
        caboose_action(list, red);
        caboose_action(list, yellow);
        caboose_action(list, green);
        caboose_action(list, blue);
        caboose_action(list, cyan);
        caboose_action(list, magenta);
}

void Conga::friends_action(LinkedList < Zombie > & list, Zombie randomZomb) {
        if (list.ElementExists(randomZomb)) {
                int coin_flip = rand() % 2;
                if (coin_flip == 0) {
                        list.AddBefore(list.Find(randomZomb), randomZomb);
                } else {
                        list.AddAfter(list.Find(randomZomb), randomZomb);
                }
        } else {
                caboose_action(list, randomZomb);
        }
}