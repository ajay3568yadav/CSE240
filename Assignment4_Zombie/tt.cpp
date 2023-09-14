/*
Name: Ajay Yadav
Date: 03/30/2023
Description: c++ assignment
Usage: 
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
        }

        srand(seed);

        //termcolor class
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
        if (x < 5 || y < 5 || x > 40 || y > 40 || bite_accuracy > 1 || bz_probablity > 1 || angry_human_probability >1 ||x < 0 || y < 0 || bite_accuracy < 0 || bz_probablity < 0 || angry_human_probability < 0) {
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
                run_iteration(array, x, y, bite_accuracy, bz_probablity, angry_human_probability);
                if (allHumans(array, x, y)) {
                        cout << "Human Won"; //breaking the loop when there are no zombies left
                        break;
                }
                if (allZombies(array, x, y)) {
                        cout << "Zombies Won";//breaking the loop when no humans are left
                        break;
                }
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
        for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                        if (array[i][j].getState() == '.' || array[i][j].getState() == 'D' || array[i][j].getState() == 'H') {
                                return false;
                        }
                }
        }
        return true;
}
//checks of there are all humans on the map and return false if not
bool allHumans(Subject ** array, int x, int y) {
        for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                        if (array[i][j].getState() == 'O' || array[i][j].getState() == '#' || array[i][j].getState() == '*') {
                                return false;
                        }
                }
        }
        return true;
}

//<-------------------------------------------------------------/*bite functions*///-------------------------------------------------------------------------->//

int bite_left(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //left
{
        //checks if there is ahuman to bite left to the zombie's position
        if (array[i][j - 1].getState() == '.' || array[i][j - 1].getState() == 'D' || array[i][j - 1].getState() == 'H') {
                if (bite_attempt < success_bite) {
                        array[i][j - 1].setState('*'); //set the state to infected if the bite is successful
                        array[i][j - 1].setStrength(new_strength);
                }
        } else {

                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

int bite_top(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //top
{
        //checks if there is a human to bite top of the zombie's position
        if (array[i - 1][j].getState() == '.' || array[i - 1][j].getState() == 'D' || array[i - 1][j].getState() == 'H') {
                if (bite_attempt < success_bite) {

                        array[i - 1][j].setState('*'); //set the state to infected if the bite is successful
                        array[i - 1][j].setStrength(new_strength); //passes the new strength to the infected
                }
        } else {

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
                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}
int bite_bottom(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //bottom
{
        //checks if there is ahuman to bite bottom to the zombie's position
        if (array[i + 1][j].getState() == '.' || array[i + 1][j].getState() == 'D' || array[i + 1][j].getState() == 'H') {
                if (bite_attempt < success_bite) {

                        //sets an intermediate state as the run_iteration loops skips the infected state if the zombie bites its' right person
                        
                        array[i + 1][j].setState('I');
                        array[i + 1][j].setStrength(new_strength);

                }
        } else {

                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

//<----------------------------------------------------------------bite functions-END---------------------------------------------------------------------------->

int valid_bite(Subject ** array, int i, int j, float bite_accuracy) {

        int direction = rand() % 4; //getting a random direction to attack
        float success_bite = bite_accuracy * float(array[i][j].getStrength()) / 10; //calculating probability of successful bite
        float bite_attempt = (float) rand() / RAND_MAX; //random bite_attempt to compare with probaility of success
        int new_strength = int(bite_attempt * 10); //new strength of the zombie/infected created

//<----------------------------------------------------------checking for non-boundry cases---------------------------------------------------------------------->

        //           . . . . . . . . .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . * * * * * * * .
        //           . . . . . . . . .

        if (i != 0 && j != 0 && i != (x - 1) && j != (y - 1)) {

                char right=array[i][j + 1].getState();
                char bottom=array[i + 1][j].getState();
                char top=array[i - 1][j].getState();
                char left=array[i][j - 1].getState();

                //if there are all zombies and infecteds
                if ((left == '#' || left == 'O' || left == '*') && (top == '#' || top == 'O' || top == '*') && (right == '#' || right == 'O' || right == '*') && (bottom == '#' || bottom == 'O' || bottom == '*')) {
                        return 0;
                } 
                else if (direction == 0) //left
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


                char right=array[i][j + 1].getState();
                char left=array[i][j - 1].getState();


                if (i == 0) {
                        //checking if there are all zombies

                        char bottom=array[i + 1][j].getState();

                        if ((left == '#' || left == 'O' || left == '*') && (bottom == '#' || bottom == 'O' || bottom == '*') && (right == '#' || right == 'O' || right == '*')) {
                                return 0;
                        }
                        
                } else {

                        char top=array[i - 1][j].getState();

                        if ((left == '#' || left == 'O' || left == '*') && (top == '#' || top == 'O' || top == '*') && (right == '#' || right == 'O' || right == '*')) {
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

                } else {

                //try to looking in another valid direction for the zombie at that point by trying to bite again
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

                
                
                char bottom=array[i + 1][j].getState();
                char top=array[i - 1][j].getState();

                if (j == 0) {
                        //checking if there are zombies surrounding the subject that itself is a zombie
                        char right=array[i][j + 1].getState();

                        if (( right== '#' || right == 'O' || right == '*') && (bottom == '#' || bottom == 'O' || bottom == '*') && ( top == '#' || top == 'O' || top == '*')) {
                                return 0;
                        }
                } else {

                        char left=array[i][j - 1].getState();

                        if (( left== 'O' || left == '#' || left == '*') && (top == '#' || top == 'O' || top == '*') && (bottom == '#' || bottom == 'O' || bottom == '*')) {
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

                        //try to looking in another valid direction for the zombie at that point by trying to bite again
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

                        char right=array[i][j + 1].getState();
                        char bottom=array[i + 1][j].getState();

                        if ((bottom == '#' || bottom == 'O' || bottom =='*') && (right == 'O' || right == '#' || right == '*')) {
                                return 0;
                        }

                        if (direction == 2) //right
                        {
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 3) //bottom
                        {
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {

                                //try to looking in another valid direction for the zombie at that point by trying to bite again
                                valid_bite(array, i, j, bite_accuracy); 
                        }

                } else if (i == 0 && j == y - 1) //bottom and left
                {
                        char bottom=array[i + 1][j].getState();
                        char left=array[i][j - 1].getState();

                        if ((bottom == '#' || bottom == 'O' || bottom == '*') && (left == 'O' || left == '#' || left == '*')) {
                                return 0;
                        }

                        if (direction == 3) //bottom
                        {
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 0) //left
                        {
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                
                                //try to looking in another valid direction for the zombie at that point by trying to bite again
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == x - 1 && j == 0) //top and right
                {
                        char right=array[i][j + 1].getState();
                        char top=array[i - 1][j].getState();

                        if ((right == '#' || right == 'O' || right == '*') && (top == 'O' || top == '#' || top == '*')) {
                                return 0;
                        } else if (direction == 1) //top
                        {
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 2) //right
                        {
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {

                                //try to looking in another valid direction for the zombie at that point by trying to bite again
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == x - 1 && j == y - 1) //top and left
                {

                        char left=array[i][j - 1].getState();
                        char top=array[i - 1][j].getState();

                        if ((left == '#' || left == 'O' || left == '*') && (top == 'O' || top == '#' || top == '*')) {
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

bool is_berserker(float p_of_berserk) {
        return (((float) rand() / RAND_MAX) <= p_of_berserk) ? true : false;
}

int zombiesNorth(Subject ** array, int i, int j) {
        int numZombies = 0;
        int row = i;
        int col = j;

        while (row >= 0) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') {
                        numZombies++;
                }
                row--;
        }

        return numZombies;

}

int zombiesSouth(Subject ** array, int i, int j) {
        int numZombies = 0;
        int row = i;
        int col = j;

        while (row <= x - 1) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') {
                        numZombies++;
                }
                row++;
        }

        return numZombies;
}

int zombiesEast(Subject ** array, int i, int j) {
        int numZombies = 0;
        int row = i;
        int col = j;

        while (col <= y - 1) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') {
                        numZombies++;
                }
                col++;
        }
        return numZombies;
}

int zombiesWest(Subject ** array, int i, int j) {
        int numZombies = 0;
        int row = i;
        int col = j;

        while (col >= 0) {
                if (array[row][col].getState() == 'O' || array[row][col].getState() == '#') {
                        numZombies++;
                }
                col--;
        }
        return numZombies;
}
bool cmp(int x, int y) {
        return (x < y);
}

int hunt(Subject ** array, int i, int j) {
        int north = zombiesNorth(array, i, j);
        int west = zombiesWest(array, i, j);
        int east = zombiesEast(array, i, j);
        int south = zombiesSouth(array, i, j);
        int row = i;
        int col = j;

        int maxDirection = max({
                north,
                south,
                east,
                west
        }, cmp);

        if (north == maxDirection) {
                while (row - 1 >= 0) {
                        if (array[row - 1][col].getState() == '#' || array[row - 1][col].getState() == 'O') {
                                array[row - 1][col].setState('.');
                                array[row - 1][col].setStrength(0);
                        }
                        row--;
                }
        } else if (west == maxDirection) {
                while (col - 1 >= 0) {
                        if (array[row][col - 1].getState() == '#' || array[row][col - 1].getState() == 'O') {
                                array[row][col - 1].setState('.');
                                array[row][col - 1].setStrength(0);
                        }

                        col--;
                }
        } else if (east == maxDirection) {
                while (col + 1 <= y - 1) {
                        if (array[row][col + 1].getState() == '#' || array[row][col + 1].getState() == 'O') {
                                array[row][col + 1].setState('.');
                                array[row][col + 1].setStrength(0);
                        }
                        col++;
                }
        } else if (south == maxDirection) {
                while (row + 1 <= x - 1) {
                        if (array[row + 1][col].getState() == '#' || array[row + 1][col].getState() == 'O') {
                                array[row + 1][col].setState('.');
                                array[row + 1][col].setStrength(0);
                        }
                        row++;
                }
        }

        return 0;

}

int run_iteration(Subject ** array, int width, int height, float bite_accuracy, float bz_probablity, float angry_human_probability) {

        int num_Zombies = 0;

        cout << "Iteration: " << iteration << endl;

        for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                        if (array[i][j].getState() == '#' || array[i][j].getState() == 'O') {
                                num_Zombies++;
                        }
                }
        }
        cout << "Number of Zombies: " << num_Zombies << endl;
        print_map(array, width, height);

        for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {

                        char current_state = array[i][j].getState();
                        if (current_state == '#') {

                                valid_bite(array, i, j, bite_accuracy);
                                if (array[i][j].getStrength() == 10) {

                                        array[i][j].setStrength(0);
                                        array[i][j].setState('.');
                                        num_Zombies--;
                                } else {
                                        array[i][j].increaseStrength();
                                }

                        } else if (current_state == 'O') {

                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);

                                if (array[i][j].getStrength() == 10) {
                                        array[i][j].setStrength(0);
                                        array[i][j].setState('.');
                                } else {
                                        array[i][j].increaseStrength();
                                }

                        } else if (current_state == '*') {
                                //randomly will become beserk or bitey
                                is_berserker(bz_probablity) ? array[i][j].setState('O') : array[i][j].setState('#');
                                if (array[i][j].getState() == 'O') {
                                        valid_bite(array, i, j, bite_accuracy);
                                        valid_bite(array, i, j, bite_accuracy);
                                        valid_bite(array, i, j, bite_accuracy);
                                } else {
                                        valid_bite(array, i, j, bite_accuracy);
                                }
                                //strength wont increase
                        } else if (current_state == 'I') {
                                array[i][j].setState('*');
                        } else if (current_state == 'H') {
                                hunt(array, i, j);
                        } else if (current_state == 'D') {
                                cure(array, i, j);
                        }
                }
        }
        makeAngryHuman(array, angry_human_probability);
        iteration++;
        return 0;
}

int cure(Subject ** array, int i, int j) {

        if (i != 0 && j != 0 && i != (x - 1) && j != (y - 1)) {

                cureLeft(array, i, j);
                cureRight(array, i, j);
                cureBottom(array, i, j);
                cureTop(array, i, j);
                cureTopLeft(array, i, j);
                cureTopRight(array, i, j);
                cureBottomLeft(array, i, j);
                cureBottomRight(array, i, j);

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

                cureLeft(array, i, j);
                cureRight(array, i, j);

                if (i == 0) {

                        cureBottom(array, i, j);
                        cureBottomLeft(array, i, j);
                        cureBottomRight(array, i, j);
                } else {

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

                cureTop(array, i, j);
                cureBottom(array, i, j);

                if (j == 0) {

                        cureRight(array, i, j);
                        cureTopRight(array, i, j);
                        cureBottomRight(array, i, j);

                } else {
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

int makeAngryHuman(Subject ** array, float angry_human_probability) {

        int rand_x = rand() % x;
        int rand_y = rand() % y;
        int coinSide = rand() % 2;
        float specialHuman = (float) rand() / RAND_MAX;
        if (specialHuman > angry_human_probability) {
                if (coinSide == 0) { //hunter
                        if (array[rand_x][rand_y].getState() == '.') {
                                array[rand_x][rand_y].setState('H');
                        } else {
                                makeAngryHuman(array, angry_human_probability);
                        }
                } else { //Dr
                        if (array[rand_x][rand_y].getState() == '.') {
                                array[rand_x][rand_y].setState('D');
                        } else {
                                makeAngryHuman(array, angry_human_probability);
                        }
                }
        }

        return 0;

}

void print_map(Subject ** array, int width, int heigth) {

        for (int i = 0; i < width; i++) {
                for (int j = 0; j < heigth; j++) {
                        cout << array[i][j].getState() << " ";
                }
                cout << endl;
        }
}
int cureLeft(Subject ** array, int i, int j) { //cure the zombie(if any) in the left

        //i,j-1
        if (array[i][j - 1].getState() == '#' || array[i][j - 1].getState() == 'O') {
                array[i][j - 1].setStrength(array[i][j - 1].getStrength() + 7);
                if (array[i][j - 1].getStrength() > 10) {
                        array[i][j - 1].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureRight(Subject ** array, int i, int j) { //cure the zombie(if any) in the right

        //i,j+1
        if (array[i][j + 1].getState() == '#' || array[i][j + 1].getState() == 'O') {
                array[i][j + 1].setStrength(array[i][j + 1].getStrength() + 7);
                if (array[i][j - 1].getStrength() > 10) {
                        array[i][j - 1].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureTop(Subject ** array, int i, int j) { //cure the zombie(if any) at the top

        //i-1 , j
        if (array[i - 1][j].getState() == '#' || array[i - 1][j].getState() == 'O') {
                array[i - 1][j].setStrength(array[i - 1][j].getStrength() + 7);
                if (array[i - 1][j].getStrength() > 10) {
                        array[i - 1][j].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureBottom(Subject ** array, int i, int j) { //cure the zombie(if any) at the bottom

        //i+1 ,j
        if (array[i + 1][j].getState() == '#' || array[i + 1][j].getState() == 'O') {
                array[i + 1][j].setStrength(array[i + 1][j].getStrength() + 7);
                if (array[i + 1][j].getStrength() > 10) {
                        array[i + 1][j].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureTopLeft(Subject ** array, int i, int j) { //cure the zombie(if any) in the top left

        //i-1 ,j-1
        if (array[i - 1][j - 1].getState() == '#' || array[i - 1][j - 1].getState() == 'O') {
                array[i - 1][j - 1].setStrength(array[i - 1][j - 1].getStrength() + 7);
                if (array[i - 1][j - 1].getStrength() > 10) {
                        array[i - 1][j - 1].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureBottomLeft(Subject ** array, int i, int j) { //cure the zombie(if any) in the bottom left

        //i+1,j-1
        if (array[i + 1][j - 1].getState() == '#' || array[i + 1][j - 1].getState() == 'O') {
                array[i + 1][j - 1].setStrength(array[i + 1][j - 1].getStrength() + 7);
                if (array[i + 1][j - 1].getStrength() > 10) {
                        array[i + 1][j - 1].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureTopRight(Subject ** array, int i, int j) { //cure the zombie(if any) in the top right

        //i-1,j+1
        if (array[i - 1][j + 1].getState() == '#' || array[i - 1][j + 1].getState() == 'O') {
                array[i - 1][j + 1].setStrength(array[i - 1][j + 1].getStrength() + 7);
                if (array[i - 1][j + 1].getStrength() > 10) {
                        array[i - 1][j + 1].setState('.');//set state to human if strength increases 10
                }
        }

        return 0;
}
int cureBottomRight(Subject ** array, int i, int j) { //cure the zombie(if any) in the bottom right

        //i+1,j+1
        if (array[i + 1][j + 1].getState() == '#' || array[i + 1][j + 1].getState() == 'O') {
                array[i + 1][j + 1].setStrength(array[i + 1][j + 1].getStrength() + 7);
                if (array[i + 1][j + 1].getStrength() > 10) {
                        array[i + 1][j + 1].setState('.'); //set state to human if strength increases 10
                }
        }

        return 0;
}