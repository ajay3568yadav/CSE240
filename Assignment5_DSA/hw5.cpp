#include <iostream>
#include "Conga.cpp"
#include <cstring>
using namespace std;

void zombieConga();
void continueParty(LinkedList<Zombie>&);
void createLine(Conga, LinkedList<Zombie>&, Zombie&);
char* getAction(Conga, Zombie,LinkedList<Zombie>&);
Zombie createZombie();

void createLine(Conga line, LinkedList<Zombie>& list, Zombie& zom)
{
    line.rainbow_action(list, zom);
    line.brains_action(list, zom);
    line.brains_action(list, zom);
    line.brains_action(list, zom);
}

char* getAction(Conga line, Zombie zom,LinkedList<Zombie> &list)
{
    const int ACTION_LENGTH = 14;
    char* action = new char[ACTION_LENGTH];
    int choice = rand() % 8;
    switch (choice)
    {
    case 0:
        strcpy(action, "Engine!");
        line.engine_action(list,zom);
        break;
    case 1:
        strcpy(action, "Caboose!");
        line.caboose_action(list,zom);
        break;
    case 2:
        strcpy(action, "Jump In!");
        line.jump_in_action(list,zom);
        break;
    case 3:
        strcpy(action, "Everyone Out!");
        line.everyone_out_action(list,zom);
        break;
    case 4:
        strcpy(action, "You Out!");
        line.you_out_action(list,zom);
        break;
    case 5:
        strcpy(action, "Brains!");
        line.brains_action(list,zom);
        break;
    case 6:
        strcpy(action, "Rainbow!");
        line.rainbow_action(list,zom);
        break;
    case 7:
        strcpy(action, "New Friends!");
        line.friends_action(list,zom);
        break;
    }
    return action;
}

Zombie createZombie()
{
    int random = rand() % 6;
    char zombie;
    switch (random)
    {
    case 0:
        zombie = 'R';
        break;
    case 1:
        zombie = 'Y';
        break;
    case 2:
        zombie = 'G';
        break;
    case 3:
        zombie = 'B';
        break;
    case 4:
        zombie = 'M';
        break;
    case 5:
        zombie = 'C';
        break;
    }
    Zombie zom(zombie);
    return zom;
}

void continueParty(LinkedList<Zombie> &list)
{
    if(list.isEmpty())
    {
        cout<<"Party is over"<<endl;
        char response;
        std::cout<<"continue party or end(y/n): ";
        cin>>response;
        cout<<endl;
        if (response == 'y')
        {
            zombieConga();
        }
        else if(response == 'n')
        {
            cout<<"exited the party"<<endl;
        }
        else{
            cout<<"enter y or n"<<endl;
            continueParty(list);
        }
        
    }
}

void zombieConga()
{
    int rounds=0;
    Conga line;
    LinkedList<Zombie> list;
    std::cout<<"Enter the number of rounds: ";
    cin>>rounds;
    Zombie firstZom=createZombie();
    createLine(line,list,firstZom);
    int i=0;
    while(i<rounds&&!list.isEmpty())
    {
        if(i%5==0)
        {
            list.RemoveFromFront();
            list.RemoveFromEnd();
        }
        std::cout<<"Round: "<<i<<endl;
        std::cout<<"Size: "<<list.Length()<<" :: ";
        list.PrintList();
        Zombie zom=createZombie();
        char* action = getAction(line, zom,list);
        std::cout<<endl<<"New Zombie: "<< "["<<zom.getType()<<"]"<<" --Action: "<<"["<<action<<"]"<<endl;
        std::cout<<"The conga line is now:"<<endl;
        std::cout<<"Size: "<<list.Length()<<" :: ";
        list.PrintList();
        std::cout<<endl<<"**************************************************"<<endl;
        delete[] action;
        i++;
    }

    continueParty(list);
}
 
int main(int argc, char *argv[])
{
    if(argc==1)
    {
        srand(time(0));
    }
    else if(argc==3 && strcmp(argv[1],"-s")==0)
    {
        srand(atoi(argv[2]));
    }
    else{
        std::cout<<"invalid argument";
        return 0;
    }
    zombieConga();      
    return 0;
}

