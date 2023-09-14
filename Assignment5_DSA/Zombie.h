// zombie.h file
#ifndef ZOMBIE_H
#define ZOMBIE_H

//#include <iostream>
//#include <stdexcept>

using namespace std;

class Zombie {
private:
char type;
public:
Zombie();
Zombie(char c);
char getType() const;
bool operator == (const Zombie& zombie);
bool operator != (const Zombie& zombie);
friend ostream& operator<<(ostream& out, const Zombie& zombie);
};

ostream& operator<<(ostream& out, const Zombie& zombie);

#endif // ZOMBIE_H
