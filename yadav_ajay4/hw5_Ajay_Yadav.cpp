/*
Name: Ajay Yadav
Date: 04/23/2023
Description: c++ assignment 3 Data structures
Usage: <executable> -s <int>

IMPORTANT:: need to install termcolor library to enable the color
refer to the following link for download instructions
 https://termcolor.readthedocs.io/

Add termcolor.hpp (grab it from include/termcolor/termcolor.hpp) to the project and use stream manipulators from the termcolor namespace.

You can also use vcpkg to install the library:

$ vcpkg install termcolor

Or if you are on macOS, you can use Homebrew for that purpose:

$ brew install termcolor

*/


#include <iostream>
#include "Conga.cpp"
#include <cstring>
using namespace std;

//funtion to start the Zombie conga  
void zombieConga();
//function to chek if the user wants to continue party
void continueParty(LinkedList<Zombie>&);
// function creates the intial conga line
void createLine(Conga, LinkedList<Zombie>&, Zombie&);
//determines the action to be perfomred
char* getAction();
//create a random zombie
Zombie createZombie();

//function creates the initial line for the conga party; take Conga object and templated linked list refernce as argument
void createLine(Conga line, LinkedList<Zombie>& list)
{
    //performs rainbow action
    line.rainbow_action(list, createZombie());
    //perfroms brains action 3 times
    line.brains_action(list, createZombie());

    line.brains_action(list, createZombie());

    line.brains_action(list, createZombie());
}
//determines the action to be perfomred
char* getAction()
{
    //set the max length of char array
    const int ACTION_LENGTH = 14;
    //create a char* to store the action 
    char* action = new char[ACTION_LENGTH];
    //generating a random number to choose action
    int choice = rand() % 8;
    switch (choice)
    {
        //for case 0 action will be Engine
    case 0:
        strcpy(action, "Engine!");
        break;
    case 1:
        //for case 1 action will be Caboose
        strcpy(action, "Caboose!");
        break;
    case 2:
        //for case 2 action will be Jump in
        strcpy(action, "Jump In!");
        break;
    case 3:
        //for case 3 action will be everyone out
        strcpy(action, "Everyone Out!");
        break;
    case 4:
        //for case 4 action will be you out
        strcpy(action, "You Out!");
        break;
    case 5:
        //for case 5 action will be brains
        strcpy(action, "Brains!");
        break;
    case 6:
        //for case 6 action will be rainbow
        strcpy(action, "Rainbow!");
        break;
    case 7:
        //for case 7 action will be New friends
        strcpy(action, "New Friends!");
        break;
    }
    //returns action
    return action;
}

//function to create a random zombie
Zombie createZombie()
{
    //random interger between 0 and 5 to select a zombie
    int random = rand() % 6;
    
    //char varaible to store the zombie type
    char zombie;
    switch (random)
    {
    case 0:
    // red zombie for case 0
        zombie = 'R';
        break;
    case 1:
    // yellow zombie for case 1
        zombie = 'Y';
        break;
    case 2:
    // green zombie for case 2
        zombie = 'G';
        break;
    case 3:
    // blue zombie for case 3
        zombie = 'B';
        break;
    case 4:
    // cyan zombie for case 4
        zombie = 'C';
        break;
    case 5:
    // magenta zombie for case 5
        zombie = 'M';
        break;
    }
    //creating a zombie of the choosen color
    Zombie zom(zombie);
    //returnin a zombie object
    return zom;
}

// function to check if the user wants to continue the party or not
void continueParty(LinkedList<Zombie> &list)
{
    //checking of the list is empty
    if(list.isEmpty())
    {
        //party over message
        cout<<"Party is over"<<endl;
        char response;
        //taking the user's response
        std::cout<<"continue party or end(y/n): ";
        cin>>response;
        cout<<endl;
        //is user said yess then continue
        if (response == 'y')
        {
            zombieConga();
        }
        //if user said no then exit the party
        else if(response == 'n')
        {
            cout<<"exited the party"<<endl;
        }
        //else the input is not valid so ask the user again with a warning
        else{
            cout<<"enter y or n"<<endl;
            continueParty(list);
        }
    }
}
//perform action on the list; receives action, linkedlist object refernence conga line object and Zombie object as arguments
void performAction(char* action,LinkedList<Zombie> &list,Conga line,Zombie zom)
{
    if(strcmp(action, "Engine!")==0)
    {
        line.engine_action(list,zom);
    }
    if(strcmp(action, "Caboose!")==0)
    {
        line.caboose_action(list,zom);
    }
    if(strcmp(action, "Jump In!")==0)
    {
        line.jump_in_action(list,zom);
    }
    if(strcmp(action, "Everyone Out!")==0)
    {
        line.everyone_out_action(list,zom);
    }
    if(strcmp(action, "You Out!")==0)
    {
        line.you_out_action(list,zom);
    }
    if(strcmp(action, "Brains!")==0)
    {
        line.brains_action(list,zom);
    }
    if(strcmp(action, "Rainbow!")==0)
    {
        line.rainbow_action(list,zom);
    }
    if(strcmp(action, "New Friends!")==0)
    {
        line.friends_action(list,zom);
    }
}

//funtion to start the Zombie conga  
void zombieConga()
{
    //number of rounds for which the conga will run
    int rounds=0;
    //conga class object
    Conga line;
    //linkedlist object
    LinkedList<Zombie> list;
    //getting the number of lines
    std::cout<<"How many rounds do you want to run?: ";
    cin>>rounds;
    //creating a conga line
    createLine(line,list);
    //counter for rounds
    int i=0;
    //runing the loop for conga party
    while(i<rounds&&!list.isEmpty())
    {
        //checking if the round is divisible by 5
        if(i%5==0)
        {
            //if divisible by 5 then remove from front and end
            list.RemoveFromFront();
            list.RemoveFromEnd();
        }
        //outputting in the terminal
        std::cout<<"Round: "<<i<<endl;
        std::cout<<"Size: "<<list.Length()<<" :: ";
        list.PrintList();
        //getting the action
        char* action = getAction();
        //creating a new random zombie
        Zombie zom=createZombie();
        //performing the choosen action
        performAction(action,list,line,zom);
        //printing the zombie
        std::cout<<endl<<"New Zombie: "<< zom <<" --Action: "<<"["<<action<<"]"<<endl;
        std::cout<<"The conga line is now:"<<endl;
        std::cout<<"Size: "<<list.Length()<<" :: ";
        list.PrintList();
        std::cout<<endl<<"**************************************************"<<endl;
        //delete the action string
        delete[] action;
        //incrementing the round
        i++;
    }
    continueParty(list);
}
 
int main(int argc, char *argv[])
{
    //checks for the number of arguments and "-s " flag
    if( argc==3 && strcmp(argv[1],"-s")==0)
    {
        //if seed is given the seed it to srand() function
        srand(atoi(argv[2]));
    }
    else if(argc==1)
    {
        //else use time(0) as seed value
        srand(time(0));
    }
    else{
        //else printout usage message
        std::cout<<"<exe> -s <int>"<<endl;
        return 0;
    }
    //run zombie conga
    zombieConga();      
    return 0;
}

