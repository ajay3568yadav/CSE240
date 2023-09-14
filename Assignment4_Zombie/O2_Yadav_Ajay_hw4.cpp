/*
Name: Ajay Yadav
Date: 03/30/2023
Description: c++ assignment
Usage: 

<executable> -s <int>

IMPORTANT:: need to install termcolor library to enable the color
refer to the following link for download instructions
 https://termcolor.readthedocs.io/

Add termcolor.hpp (grab it from include/termcolor/termcolor.hpp) to the project and use stream manipulators from the termcolor namespace.

You can also use vcpkg to install the library:

$ vcpkg install termcolor

Or if you are on macOS, you can use Homebrew for that purpose:

$ brew install termcolor

*/
#include <string.h>

#include <iostream>

#include<algorithm>

#include <stdlib.h>

#include <fstream>

#include <cstdlib>

#include "termcolor.hpp"

using namespace std;

class Subject { //Subject of the Apocalypse
        private: char state; //Human
        //' . ': human ; ' * ':Infected ; ' # ':zombie ; ' O ':Bezerk Zombie; 'I': intermediate; 'H': Hunter Human; 'D': Doctor
        int strength;
        public:
                //constructor set the default state to Human ('.')
                Subject() {
                        state = '.';
                        strength = 0;
                }
        //return state of the Subject {*, ., O, H, D}
        char getState() {
                return state;
        }
        //changes to the state of the Subject
        void setState(char c) {
                state = c;
        }
        // returns the strength of the Zombie
        int getStrength() {
                return strength;
        }
        //sets the strength
        void setStrength(int s) {
                strength = s;
        }
        //increase strength by one
        void increaseStrength() {
                strength++;
        }

};

// run itration for apocalypse
int run_iteration(Subject ** , int, int, float, float, float);

//make the zombie bite its neighbour
int valid_bite(Subject ** , int, int, float);

//prints the map/array
void print_map(Subject ** , int, int);

//make the zombie to bite left if the bite is valid
int bite_left(Subject ** , int, int, float, float, int);

//make the zombie to bite right if the bite is valid
int bite_right(Subject ** , int, int, float, float, int);

//make the zombie to bite top if the bite is valid
int bite_top(Subject ** , int, int, float, float, int);

//make the zombie to bite bottom if the bite is valid
int bite_bottom(Subject ** , int, int, float, float, int);

//create an angry human 'H' or 'D' on coin flip(0,1)
int makeAngryHuman(Subject ** , float);

//creates a beserker zombie if the conditions are met
bool is_berserker(float);

//checks if all the subjects on the map are humans
bool allHumans(Subject ** , int, int);

//check if all the subjects on the map are zombies
bool allZombies(Subject ** , int, int);

//make hunter to act: shoot all the zombie in the direction with most zombies
int hunt(Subject ** , int, int);

//returns the number of zombies in the north direction to the hunter
int zombiesNorth(Subject ** , int, int);

//returns the number of zombies in the south direction to the hunter
int zombiesSouth(Subject ** , int, int);

//returns the number of zombies in the east direction to the hunter
int zombiesEast(Subject ** , int, int);

//returns the number of zombies in the west direction to the hunter
int zombiesWest(Subject ** , int, int);

//make the doctor to act: add strength 7 to the surrounding zombies
int cure(Subject ** , int, int);

//boolean for using max function of algorithm
bool cmp(int, int);

//add 7 to the bottom zombie's strength
int cureBottom(Subject ** , int, int);

//add 7 to the right zombie's strength
int cureRight(Subject ** , int, int);

//add 7 to the bottom-right zombie's strength
int cureBottomRight(Subject ** , int, int);

//add 7 to the bottom-left zombie's strength
int cureBottomLeft(Subject ** , int, int);

//add 7 to the top-right zombie's strength
int cureTopRight(Subject ** , int, int);

//add 7 to the top-left zombie's strength
int cureTopLeft(Subject ** , int, int);

//add 7 to the left zombie's strength
int cureLeft(Subject ** , int, int);

//add 7 to the top zombie's strength
int cureTop(Subject ** , int, int);

//width of the map
int x = 0;

//height of the map
int y = 0;

//bite accuracy of zombie
float bite_accuracy = 0.0f;

//probablity to become a beserker zombie
float bz_probablity = 0.0f;

//probablity to become angry human
float angry_human_probability = 0.0f;

//number of iterations
int iteration = 0;
//main function

int main(int argc, char ** argv) {

        int seed = 0; //seed value
        if (argc == 3) { //condition to check "-s" flag
                if (strcmp(argv[1], "-s") == 0) {
                        seed = atoi(argv[2]); //assigns the 3rd argument to the seed
                        cout << "seed value given: " << seed << endl;
                }
                srand(seed); // if seed is given then use seed for generating random numbers
        }
        else if(argc>3){ //display error message if the number of arguments are more than 3
                cout<<"Error: incorrect Usage"<<endl<<"Usage: <executable> -s <int>"<<endl;
                return 0;
        }
        else{
                srand(time(0)); // if no seed is given then use time(0) as seed
        }

        //termcolor file for using colored output
        cout << termcolor::red << "hello" << endl;
        cout << termcolor::magenta << "Welcome to ze apocalypse!" << endl << endl;
        cout << termcolor::bright_grey << "Enter map width (between 4 and 40): ";
        cin >> x;
        cout << endl;
        cout << "Enter map height (between 4 and 40): ";
        cin >> y;
        cout << endl;
        cout << "Enter zombie bit accuracy (float between 0 and 1): ";
        cin >> bite_accuracy;
        cout << endl;
        cout << "Enter berserker probability (float between 0 and 1):";
        cin >> bz_probablity;
        cout << endl;
        cout << "Enter angry Human probability (float between 0 and 1):";
        cin >> angry_human_probability;
        cout << endl << endl;

        //created a dynamic 2D array of the subject objects
        Subject ** array = new Subject * [x];
        for (int i = 0; i < x; i++) {
                array[i] = new Subject[y];
        }

        //coordinates of randon x and y value to drop the strain
        int rand_x = 0;
        int rand_y = 0;

        //checking the validity of the inputs
        if (x < 5 || y < 5 || x > 40 || y > 40 || bite_accuracy > 1 || bz_probablity > 1 || angry_human_probability > 1 || x < 0 || y < 0 || bite_accuracy < 0 || bz_probablity < 0 || angry_human_probability < 0) {
                cout << termcolor::cyan << "enter valid values" << endl;
                return 0;
        }
        //assigning random values to the x and y
        rand_x = rand() % x;
        rand_y = rand() % y;
        //printing the drop point information
        cout << termcolor::bright_green << "Strain dropped at coordinate (" << rand_x << "," << rand_y << "). Zombie of Strength 5 spawned" << endl;

        array[rand_x][rand_y].setState('#');
        array[rand_x][rand_y].setStrength(5);

        //iterating till the end of the apocalyspe 
        while (true) {

                if (allZombies(array, x, y)) {

                        cout << endl << "Zombies Won" << endl;
                        print_map(array, x, y);
                        //breaking the loop when there are no humans left
                        break;
                }
                if (allHumans(array, x, y)) {

                        cout << endl << "Humans Won" << endl;
                        //breaking the loop when no zombies are left
                        print_map(array, x, y);
                        break;
                }
                run_iteration(array, x, y, bite_accuracy, bz_probablity, angry_human_probability);

        }
        //dealocating the memory
        for (int i = 0; i < x; i++) {
                delete[] array[i];
        }
        delete[] array;

        return 0;

}
//checks if there are all zombies on the map and return false if not
bool allZombies(Subject ** array, int x, int y) {
        int numZombies = 0;
        for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) { //checking for zombies
                        if (array[i][j].getState() == '#' || array[i][j].getState() == 'O') {
                                numZombies++;
                        }
                }
        }
        //returns true if each subject is a zombie
        return numZombies == x * y;
}
//checks of there are all humans on the map and return false if not
bool allHumans(Subject ** array, int x, int y) {
        int numZombies = 0;
        for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) { //checking for zombies and infecteds
                        if (array[i][j].getState() == '#' || array[i][j].getState() == 'O' || array[i][j].getState() == '*') {
                                numZombies++;
                        }
                }
        }
        //returns true if the number of zombies are 0
        return numZombies == 0;
}

//<-------------------------------------------------------------/*bite functions*///-------------------------------------------------------------------------->//

int bite_left(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //left
{
        //checks if there is ahuman to bite left to the zombie's position
        if (array[i][j - 1].getState() == '.' || array[i][j - 1].getState() == 'D' || array[i][j - 1].getState() == 'H') {
                if (bite_attempt < success_bite) { //check if the bite will be successful or not
                        array[i][j - 1].setState('*'); //set the state to infected if the bite is successful
                        array[i][j - 1].setStrength(new_strength);
                }
        } else {
                //if there is no human to bite in the left then the zombie to should look to TRY to bite at least one human each round thus return to valid bite function
                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

int bite_top(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //top
{
        //checks if there is a human to bite top of the zombie's position
        if (array[i - 1][j].getState() == '.' || array[i - 1][j].getState() == 'D' || array[i - 1][j].getState() == 'H') {
                if (bite_attempt < success_bite) { //check if the bit will be successful

                        array[i - 1][j].setState('*'); //set the state to infected if the bite is successful
                        array[i - 1][j].setStrength(new_strength); //passes the new strength to the infected
                }
        } else {
                //if there is no human to bite in the left then the zombie to should look to TRY to bite at least one human each round thus return to valid bite function
                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

int bite_right(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //right
{
        //checks if there is ahuman to bite right to the zombie's position
        if (array[i][j + 1].getState() == '.' || array[i][j + 1].getState() == 'D' || array[i][j + 1].getState() == 'H') {
                if (bite_attempt < success_bite) {

                        //sets an intermediate state as the run_iteration loops skips the infected state if the zombie bites its' right person

                        array[i][j + 1].setState('I');
                        array[i][j + 1].setStrength(new_strength);
                }
        } else {
                //if there is no human to bite in the left then the zombie to should look to TRY to bite at least one human each round thus return to valid bite function
                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}
int bite_bottom(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //bottom
{
        //checks if there is ahuman to bite bottom to the zombie's position
        if (array[i + 1][j].getState() == '.' || array[i + 1][j].getState() == 'D' || array[i + 1][j].getState() == 'H') {
                if (bite_attempt < success_bite) {

                        //sets an intermediate state as the run_iteration loops skips the infected state if the zombie bites its' bottom person

                        array[i + 1][j].setState('I');
                        array[i + 1][j].setStrength(new_strength);

                }
        } else {
                //if there is no human to bite in the left then the zombie to should look to TRY to bite at least one human each round thus return to valid bite function         
                valid_bite(array, i, j, bite_accuracy);
        }
        return 0;
}

//<----------------------------------------------------------------bite functions-END---------------------------------------------------------------------------->

int valid_bite(Subject ** array, int i, int j, float bite_accuracy) {

        //getting a random direction to attack
        int direction = rand() % 4;
        // 0 ----> left
        // 1 ----> top
        // 2 ----> right
        // 3 ----> bottom
        //calculating probability of successful bite
        float success_bite = bite_accuracy * float(array[i][j].getStrength()) / 10;
        //random bite_attempt to compare with probaility of success
        float bite_attempt = (float) rand() / RAND_MAX;
        //new strength of the zombie/infected created
        int new_strength = int(bite_attempt * 10);
        //<----------------------------------------------------------checking for non-boundry cases---------------------------------------------------------------------->

        //           . . . . . . . . .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . . . . . . . . .

        if (i != 0 && j != 0 && i != (x - 1) && j != (y - 1)) {

                //possible directions to attack 
                char right = array[i][j + 1].getState();
                char bottom = array[i + 1][j].getState();
                char top = array[i - 1][j].getState();
                char left = array[i][j - 1].getState();

                //if there are all zombies and infecteds
                if (left != '.' && right != '.' && top != '.' && bottom != '.') {
                        return 0;
                } else if (direction == 0) //left
                {
                        bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                } else if (direction == 1) //top
                {
                        bite_top(array, i, j, bite_attempt, success_bite, new_strength);
                } else if (direction == 2) //right
                {
                        bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                } else if (direction == 3) //bottom
                {
                        bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                }
        } //checking for boundary conditions

        //<--------------------------------------------------------------boundry for i=0 and i=x-1 ------------------------------------------------------------------------>
        else if ((i == 0 || i == x - 1) && (j > 0 && j < y - 1)) {

                //           . * * * * * * * .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . * * * * * * * .

                //there is always a possibility for zombies in this case to attack right and left
                char right = array[i][j + 1].getState();
                char left = array[i][j - 1].getState();

                if (i == 0) {
                        char bottom = array[i + 1][j].getState();

                        //zombie at i=0 can only go left right and bottom
                        if (left != '.' && bottom != '.' && right != '.') {
                                return 0;
                        }
                } else {
                        char top = array[i - 1][j].getState();

                        //zombie at i=x-1 can only go left right and top
                        if (left != '.' && top != '.' && right != '.') {
                                return 0;
                        }
                }

                if (direction == 0) //left
                {
                        bite_left(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 2) //right
                {
                        bite_right(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 3 && i == 0) { //bottom

                        bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 1 && i == x - 1) { //top

                        bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                } else { //if the bite is not valid then try again to bite
                        valid_bite(array, i, j, bite_accuracy);
                }

        }
        //<--------------------------------------------------------------checking for y boundary-------------------------------------------------------------->//
        else if ((j == 0 || j == y - 1) && (i > 0 && i < x - 1)) {

                //           . . . . . . . . .
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           . . . . . . . . .

                //alwasys possible to attack top and bottom for zombies in this case
                char bottom = array[i + 1][j].getState();
                char top = array[i - 1][j].getState();

                if (j == 0) { //checking if there are zombies surrounding the subject that itself is a zombie

                        char right = array[i][j + 1].getState();
                        if (right != '.' && bottom != '.' && top != '.') {
                                return 0;
                        }
                } else {
                        char left = array[i][j - 1].getState();
                        if (left != '.' && top != '.' && bottom != '.') {
                                return 0;
                        }
                }

                if (direction == 1) { //top

                        bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 3) { //bottom

                        bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 0 && j == y - 1) //left 
                {
                        bite_left(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 2 && j == 0) //right
                {

                        bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                } else {
                        //if the bite is not valid then try again to bite
                        valid_bite(array, i, j, bite_accuracy);
                }
        }

        //<------------------------------------------------------------ setting conditions for corners----------------------------------------------------------------->
        else {

                //         1 * . . . . . . . * 2
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //         3 * . . . . . . . * 4

                if (i == 0 && j == 0) //right and bottom
                {
                        //zombie in the top left corner

                        char right = array[i][j + 1].getState();
                        char bottom = array[i + 1][j].getState();

                        if (bottom != '.' && right != '.') {
                                return 0;
                        }

                        if (direction == 2) //right
                        {
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 3) //bottom
                        {
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                //if the bite is not valid then try again to bite
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == 0 && j == y - 1) //bottom and left
                {

                        //zombie in the top right corner

                        char bottom = array[i + 1][j].getState();
                        char left = array[i][j - 1].getState();

                        if (bottom != '.' && left != '.') {
                                return 0;
                        }

                        if (direction == 3) //bottom
                        {
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 0) //left
                        {
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == x - 1 && j == 0) //top and right
                {

                        //zombie in the bottom left corner

                        char right = array[i][j + 1].getState();
                        char top = array[i - 1][j].getState();

                        if (right != '.' && top != '.') {
                                return 0;
                        } else if (direction == 1) //top
                        {
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 2) //right
                        {
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == x - 1 && j == y - 1) //top and left
                {
                        //zombie in the bottom right corner

                        char left = array[i][j - 1].getState();
                        char top = array[i - 1][j].getState();

                        if (left != '.' && top != '.') {
                                return 0;
                        } else if (direction == 1) //top
                        {
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 0) //left
                        {
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {

                                //try to looking in another valid direction for the zombie at that point by trying to bite again

                                valid_bite(array, i, j, bite_accuracy);
                        }
                }
        }
        return 0;
}

bool is_berserker(float p_of_berserk) { //returns the possibility of the spawning of beserker zombie
        return (((float) rand() / RAND_MAX) <= p_of_berserk) ? true : false;
}

int zombiesNorth(Subject ** array, int i, int j) { // rerturn the number of zombies in the north to the hunter

        //number of Zombies in north direction
        int numZombies = 0;
        int row = i;
        int col = j;

        while (row >= 0) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') { //checking for a zombie
                        numZombies++;
                }
                row--;
        }
        return numZombies;
}

int zombiesSouth(Subject ** array, int i, int j) { // rerturn the number of zombies in the south to the hunter

        //number of Zombies in south direction
        int numZombies = 0;
        int row = i;
        int col = j;

        while (row <= x - 1) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') { //checking for a zombie
                        numZombies++;
                }
                row++;
        }
        return numZombies;
}

int zombiesEast(Subject ** array, int i, int j) { // rerturn the number of zombies in the east to the hunter

        //number of Zombies in east direction
        int numZombies = 0;
        int row = i;
        int col = j;

        while (col <= y - 1) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') { //checking for a zombie
                        numZombies++;
                }
                col++;
        }
        return numZombies;
}

int zombiesWest(Subject ** array, int i, int j) { // rerturn the number of zombies in the west to the hunter

        //number of Zombies in west direction
        int numZombies = 0;
        int row = i;
        int col = j;

        while (col >= 0) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') { //checking for a zombie
                        numZombies++;
                }
                col--;
        }
        return numZombies;
}
bool cmp(int x, int y) { // supporting function to make the max function of algorithm library work
        return (x < y);
}

//make the hunter to shoot all the zombies in the direction with maximum zombies
int hunt(Subject ** array, int i, int j) {

        //get the number of zombies in the north
        int north = zombiesNorth(array, i, j);

        //get the number of zombies in the west
        int west = zombiesWest(array, i, j);

        //get the number of zombies in the east
        int east = zombiesEast(array, i, j);

        //get the number of zombies in the south
        int south = zombiesSouth(array, i, j);

        int row = i;
        int col = j;

        //return the direction with the maiximum zombies
        int maxDirection = max({
                north,
                south,
                east,
                west
        }, cmp);

        //if north has the most zombies then shoot in the north
        if (north == maxDirection && north!=0) {
                while (row - 1 >= 0) { //moving in the north direction
                        if (array[row - 1][col].getState() == '#' || array[row - 1][col].getState() == 'O') {
                                array[row - 1][col].setState('.');
                                //turning zombies back to human after hunter's action
                                array[row - 1][col].setStrength(0);
                                //resetting the strength
                        }
                        row--;
                }
                array[i][j].setState('.'); //return to normal human state after shooting
        } 
        //if west has the most zombies then shoot in the west
        else if (west == maxDirection && west!=0) {
                while (col - 1 >= 0) { //moving in the west direction
                        if (array[row][col - 1].getState() == '#' || array[row][col - 1].getState() == 'O') {
                                array[row][col - 1].setState('.');
                                //turning zombies back to human after hunter's action
                                array[row][col - 1].setStrength(0);
                                //resetting the strength
                        }

                        col--;
                }
                array[i][j].setState('.');//return to normal human state after shooting
        } 
        //if east has the most zombies then shoot in the east
        else if (east == maxDirection && east!=0) {
                while (col + 1 <= y - 1) { //moving in the east direction
                        if (array[row][col + 1].getState() == '#' || array[row][col + 1].getState() == 'O') {
                                array[row][col + 1].setState('.');
                                //turning zombies back to human after hunter's action
                                array[row][col + 1].setStrength(0);
                                //resetting the strength
                        }
                        col++;
                }    
                array[i][j].setState('.');//return to normal human state after shooting
        } 
        //if south has the most zombies then shoot in the south
        else if (south == maxDirection && south!=0) {
                while (row + 1 <= x - 1) { //moving in the south direction
                        if (array[row + 1][col].getState() == '#' || array[row + 1][col].getState() == 'O') {
                                array[row + 1][col].setState('.');
                                //turning zombies back to human after hunter's action
                                array[row + 1][col].setStrength(0);
                                //resetting the strength
                        }
                        row++;
                }
                array[i][j].setState('.');//return to normal human state after shooting
        }

        return 0;

}

int run_iteration(Subject ** array, int width, int height, float bite_accuracy, float bz_probablity, float angry_human_probability) {

        //number of zombies in the apocalypse
        int num_Zombies = 0;

        cout << "Iteration: " << iteration << endl;

        //counting the numbe rof zombies
        for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                        if (array[i][j].getState() == '#' || array[i][j].getState() == 'O') {
                                num_Zombies++;
                        }
                }
        }

        //print the number of Zombies
        cout << "Number of Zombies: " << num_Zombies << endl;
        //printing the map of the apocalypse
        print_map(array, width, height);

        //iterating through each subject in the apocalypse
        for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {

                        //get the current state if the subject
                        char current_state = array[i][j].getState();
                        if (current_state == '#') {
                                //if the subject is a zombie attemp to bite its neighbour in a cardinal direction

                                valid_bite(array, i, j, bite_accuracy);
                                if (array[i][j].getStrength() >= 10) { //if the strength of the zombie is more than or equal to 10 then change it to human state

                                        array[i][j].setStrength(0); //reset the strength of the subject
                                        array[i][j].setState('.'); //reset the state
                                } else {
                                        array[i][j].increaseStrength();
                                        //the strength is less than 10 then increase the strength by 1
                                }

                        } else if (current_state == 'O') {

                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);

                                if (array[i][j].getStrength() == 10) {
                                        array[i][j].setStrength(0); //reset the strength of the subject
                                        array[i][j].setState('.'); //reset the state
                                } else {
                                        array[i][j].increaseStrength();
                                        //the strength is less than 10 then increase the strength by 1
                                }

                        } else if (current_state == '*') {
                                //randomly will become beserk or bitey based on the output of is is_berserker function
                                is_berserker(bz_probablity) ? array[i][j].setState('O') : array[i][j].setState('#');
                                //a beserker zombie gets to bite 3 people
                                if (array[i][j].getState() == 'O') {
                                        valid_bite(array, i, j, bite_accuracy);
                                        valid_bite(array, i, j, bite_accuracy);
                                        valid_bite(array, i, j, bite_accuracy);
                                } else {

                                        //if a bitey zombie then bites once
                                        valid_bite(array, i, j, bite_accuracy);
                                }
                                //strength wont increase
                        } else if (current_state == 'I') {
                                //itermediate state to correct the state of the human bitten by the zombies at theor left or top as 
                                //their state of infected gets skipped as run_iteration reaches them 
                                array[i][j].setState('*');
                        } else if (current_state == 'H') {
                                //make the hunter to hunt
                                hunt(array, i, j);
                        } else if (current_state == 'D') {
                                //make the doctor to cure its neighbours
                                cure(array, i, j);
                        }
                }
        }
        makeAngryHuman(array, angry_human_probability); //checks if an angary huamn will spawn in the next apocalyspe
        iteration++; //increase the iteration
        return 0;
}

int cure(Subject ** array, int i, int j) {

        if (i != 0 && j != 0 && i != (x - 1) && j != (y - 1)) {

                //doctor not on the boundries can cure all 8 of its neighbours
                cureLeft(array, i, j);
                cureRight(array, i, j);
                cureBottom(array, i, j);
                cureTop(array, i, j);
                cureTopLeft(array, i, j);
                cureTopRight(array, i, j);
                cureBottomLeft(array, i, j);
                cureBottomRight(array, i, j);

                array[i][j].setState('.');

        } //checking for boundary conditions
        //<--------------------------------------------------------boundry for i=0 and i=x-1 --------------------------------------------->
        else if ((i == 0 || i == x - 1) && (j > 0 && j < y - 1)) {

                //           . * * * * * * * .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . * * * * * * * .

                //doctor in the first and the last row and not in the forst and last column can cure left and right zombie
                cureLeft(array, i, j);
                cureRight(array, i, j);

                if (i == 0) {

                        //doctor in the first row can cure in the following directions
                        //bottom left
                        //bottom right
                        //bottom
                        cureBottom(array, i, j);
                        cureBottomLeft(array, i, j);
                        cureBottomRight(array, i, j);
                } else {
                        //doctor in the last row can cure in the following directions
                        //top left
                        //top right
                        //top
                        cureTop(array, i, j);
                        cureTopLeft(array, i, j);
                        cureTopRight(array, i, j);
                }

        }
        //<--------------------------------------------------------------checking for y boundary------------------------------------------>
        else if ((j == 0 || j == y - 1) && (i > 0 && i < x - 1)) {

                //           . . . . . . . . .
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           * . . . . . . . *
                //           . . . . . . . . .

                //doctor in the first and the last column and not in the first and last row can cure top and bottom zombies
                cureTop(array, i, j);
                cureBottom(array, i, j);

                if (j == 0) {

                        //doctor in the first column can cure in the following directions
                        //bottom right
                        //top right
                        //right
                        cureRight(array, i, j);
                        cureTopRight(array, i, j);
                        cureBottomRight(array, i, j);

                } else {

                        //doctor in the last column can cure in the following directions
                        //bottom left
                        //top left
                        //left
                        cureLeft(array, i, j);
                        cureTopLeft(array, i, j);
                        cureBottomLeft(array, i, j);

                }

        }

        //<--------------------------------------------------- setting conditions for corners--------------------------------------------->
        else {

                //         1 * . . . . . . . * 2
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //           . . . . . . . . .
                //         3 * . . . . . . . * 4

                if (i == 0 && j == 0) //right and bottom
                {

                        cureRight(array, i, j);
                        cureBottom(array, i, j);
                        cureBottomRight(array, i, j);;

                } else if (i == 0 && j == y - 1) //bottom and left
                {

                        cureBottom(array, i, j);
                        cureLeft(array, i, j);
                        cureBottomLeft(array, i, j);

                } else if (i == x - 1 && j == 0) //top and right
                {

                        cureTop(array, i, j);
                        cureRight(array, i, j);
                        cureTopRight(array, i, j);;

                } else if (i == x - 1 && j == y - 1) //top and left
                {

                        cureTop(array, i, j);
                        cureLeft(array, i, j);;
                        cureTopLeft(array, i, j);

                }

        }

        return 0;
}

int makeAngryHuman(Subject ** array, float angry_human_probability) { //make an angry human in the next apocalypse at a random location with a huamn at it

        //generating random coordinates to drop angry human
        int rand_x = rand() % x;
        int rand_y = rand() % y;
        //fliping a coin to decide between doctor and hunter
        int coinSide = rand() % 2;
        float specialHuman = (float) rand() / RAND_MAX;
        //chance of spwaning a special human
        if (specialHuman < angry_human_probability) {
                //chekcing if an angry human will spawn
                if (coinSide == 0) { //hunter
                        if (array[rand_x][rand_y].getState() == '.') { //checking of a human is present at that random location
                                array[rand_x][rand_y].setState('H'); //setting state to hunter
                        } else {
                                makeAngryHuman(array, angry_human_probability);
                                //if there is no human then try again to find a location by recalling the function
                        }
                } else { //Doctor
                        if (array[rand_x][rand_y].getState() == '.') { //checking of a human is present at that random location
                                array[rand_x][rand_y].setState('D'); //setting state to doctor
                        } else {
                                makeAngryHuman(array, angry_human_probability);
                                //if there is no human then try again to find a location by recalling the function
                        }
                }
        }

        return 0;

}

void print_map(Subject ** array, int width, int heigth) { //print the map of each apocalypse

        for (int i = 0; i < width; i++) {
                for (int j = 0; j < heigth; j++) {
                        cout << array[i][j].getState() << " ";
                }
                cout << endl;
        }
}
int cureLeft(Subject ** array, int i, int j) { //cure the zombie at the left

        //i,j-1
        //check for the presence of the zombie in the left 
        if (array[i][j - 1].getState() == '#' || array[i][j - 1].getState() == 'O') {
                array[i][j - 1].setStrength(array[i][j - 1].getStrength() + 7);
                if (array[i][j - 1].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i][j - 1].setState('.');
                }
                array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureRight(Subject ** array, int i, int j) { //cure the zombie at the right

        //i,j+1
        //check for the presence of the zombie in the right 
        if (array[i][j + 1].getState() == '#' || array[i][j + 1].getState() == 'O') {
                array[i][j + 1].setStrength(array[i][j + 1].getStrength() + 7);
                if (array[i][j - 1].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i][j - 1].setState('.');
                }
                array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureTop(Subject ** array, int i, int j) { //cure the zombie at the top

        //i-1 , j
        //check for the presence of the zombie in the top 
        if (array[i - 1][j].getState() == '#' || array[i - 1][j].getState() == 'O') {
                array[i - 1][j].setStrength(array[i - 1][j].getStrength() + 7);
                if (array[i - 1][j].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i - 1][j].setState('.');
                }
                array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureBottom(Subject ** array, int i, int j) { //cure the zombie at the bottom

        //i+1 ,j
        //check for the presence of the zombie in the bottom 
        if (array[i + 1][j].getState() == '#' || array[i + 1][j].getState() == 'O') {
                array[i + 1][j].setStrength(array[i + 1][j].getStrength() + 7);
                if (array[i + 1][j].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i + 1][j].setState('.');
                }
                array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureTopLeft(Subject ** array, int i, int j) { // cure the zombie at the top left

        //i-1 ,j-1
        //check for the presence of the zombie in the top left 
        if (array[i - 1][j - 1].getState() == '#' || array[i - 1][j - 1].getState() == 'O') {
                array[i - 1][j - 1].setStrength(array[i - 1][j - 1].getStrength() + 7);
                if (array[i - 1][j - 1].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i - 1][j - 1].setState('.');
                }
        array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureBottomLeft(Subject ** array, int i, int j) { //cure the zombie at the bottom left

        //i+1,j-1
        //check for the presence of the zombie in the bottom left 
        if (array[i + 1][j - 1].getState() == '#' || array[i + 1][j - 1].getState() == 'O') {
                array[i + 1][j - 1].setStrength(array[i + 1][j - 1].getStrength() + 7);
                if (array[i + 1][j - 1].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i + 1][j - 1].setState('.');
                }

        array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureTopRight(Subject ** array, int i, int j) { // cure the zombie at the top right

        //i-1,j+1
        //check for the presence of the zombie in the top right 
        if (array[i - 1][j + 1].getState() == '#' || array[i - 1][j + 1].getState() == 'O') {
                array[i - 1][j + 1].setStrength(array[i - 1][j + 1].getStrength() + 7);
                if (array[i - 1][j + 1].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i - 1][j + 1].setState('.');
                }
                array[i][j].setState('.');//return to human
        }

        return 0;
}
int cureBottomRight(Subject ** array, int i, int j) { //cure the zombie at the bottom right

        //i+1,j+1
        //check for the presence of the zombie in the bottom right 
        if (array[i + 1][j + 1].getState() == '#' || array[i + 1][j + 1].getState() == 'O') {
                array[i + 1][j + 1].setStrength(array[i + 1][j + 1].getStrength() + 7);
                if (array[i + 1][j + 1].getStrength() > 10) { //if strength of the zombie increase 10 the return to human
                        array[i + 1][j + 1].setState('.');
                }
                array[i][j].setState('.');//return to human
        }

        return 0;
}
