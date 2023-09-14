#include <iostream>
#include "Zombie.h"
//#include "linkedlist.hpp"
//#include <stdexcept>
using namespace std;

Zombie::Zombie() {}

Zombie::Zombie(char c) {
type = c;
}

char Zombie::getType() const {
return type;
}

bool Zombie::operator==(const Zombie& zombie) {
return this->type == zombie.type;
}

bool Zombie::operator!=(const Zombie& zombie) {
return this->type != zombie.type;
}

ostream& operator<<(ostream& out, const Zombie& zombie) {
out << zombie.getType();
return out;
}

