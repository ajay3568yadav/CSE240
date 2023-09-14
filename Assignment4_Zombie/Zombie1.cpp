#include <string.h>

#include <iostream>

#include <stdlib.h>

#include <fstream>

using namespace std;

class Subject {
        private: char state; //Human
        //' . ': human ; ' * ':Infected ; ' # ':zombie ; ' O ':Bezerk Zombie; 'I': intermediate
        int strength;
        public: Subject() {
                state = '.';
                strength = 0;
        }
        char getState() {
                return state;
        }
        void setState(char c) {
                state = c;
        }
        int getStrength() {
                return strength;
        }
        void setStrength(int s) {
                strength = s;
        }
        void increaseStrength() {
                strength++;
        }

};

int run_iteration(Subject ** , int, int, float, float);
int valid_bite(Subject ** , int, int, float);
void print_map(Subject ** , int, int);
int bite_left(Subject ** , int, int, float, float, int);
int bite_left(Subject ** , int, int, float, float, int);
int bite_left(Subject ** , int, int, float, float, int);
int bite_left(Subject ** , int, int, float, float, int);

int x = 0;
int y = 0;
float bite_accuracy = 0.0f;
float bz_probablity = 0.0f;
int iteration = 0;
int flag = 0;
//main function

int main(int argc, char ** argv) {

        srand(time(NULL));
        cout << "Welcome to ze apocalypse!" << endl << endl;
        cout << "Enter map width (between 4 and 40): ";
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
        cout << endl << endl;

        Subject ** array = new Subject * [x];
        for (int i = 0; i < x; i++) {
                array[i] = new Subject[y];
        }

        int rand_x = 0;
        int rand_y = 0;

        if (x < 5 || y < 5 || x > 40 || y > 40) {
                cout << "enter valid values" << endl;
                return 0;
        }

        rand_x = rand() % x;
        rand_y = rand() % y;

        cout << "Strain dropped at coordinate (" << rand_x << "," << rand_y << "). Zombie of Strength 5 spawned" << endl;

        array[rand_x][rand_y].setState('#');
        array[rand_x][rand_y].setStrength(5);

        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);
        run_iteration(array, x, y, bite_accuracy, bz_probablity);

        for (int i = 0; i < x; i++) {
                delete[] array[i];
        }
        delete[] array;

        return 0;

}

//bite function

int bite_left(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //left
{
        if (array[i][j - 1].getState() == '.') {
                if (bite_attempt < success_bite) {
                        array[i][j - 1].setState('*');
                        array[i][j - 1].setStrength(new_strength);
                      //  cout << "Zombie at: " << i << "," << j << " bit left" << endl;
                } else {
                     //   cout << "Zombie at: " << i << "," << j << "bite at top not successful" << endl;
                }
        } else {

                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

int bite_top(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //top
{
        if (array[i - 1][j].getState() == '.') {
                if (bite_attempt < success_bite) {
                        array[i - 1][j].setState('*');
                        array[i - 1][j].setStrength(new_strength);
                      //  cout << "Zombie at: " << i << "," << j << " bit top" << endl;
                } else {
                      //  cout << "Zombie at: " << i << "," << j << "bite at top not successful" << endl;
                }
        } else {

                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

int bite_right(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //right
{
        if (array[i][j + 1].getState() == '.') {
                if (bite_attempt < success_bite) {
                        array[i][j + 1].setState('I');
                        array[i][j + 1].setStrength(new_strength);
                       // cout << "Zombie at: " << i << "," << j << " bit right" << endl;
                } else {
                        //cout << "Zombie at: " << i << "," << j << "bite at right not successful" << endl;
                }
        } else {
                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}
int bite_bottom(Subject ** array, int i, int j, float bite_attempt, float success_bite, int new_strength) //bottom
{

        if (array[i + 1][j].getState() == '.') {
                if (bite_attempt < success_bite) {
                        array[i + 1][j].setState('I');
                        array[i + 1][j].setStrength(new_strength);
                        //cout<<"done: "<<array[i][j].getState()<<endl;
                } else {
                       // cout << "Zombie at: " << i << "," << j << "bite at bottom not successful" << endl;
                }

        } else {
                valid_bite(array, i, j, bite_accuracy);

        }
        return 0;
}

int valid_bite(Subject ** array, int i, int j, float bite_accuracy) {

        int direction = rand() % 4; //getting a random direction to attack
       // cout << "direction: " << direction << endl;
        float success_bite = bite_accuracy * float(array[i][j].getStrength()) / 10; //calculating probability of successful bite
      //  cout << "success bite" << success_bite << endl;
        float bite_attempt = (float) rand() / RAND_MAX; //random bite_attempt to compare with probaility of success
       //cout << "bite_attempt" << bite_attempt << endl;
        int new_strength = int(bite_attempt * 10); //new strength of the zombie/infected created

        //<---------------------------------------------------checking for non-boundry cases-------------------------------------------->
        if (i != 0 && j != 0 && i != (x - 1) && j != (y - 1)) {

                //if there are all zombies and infecteds
                if (array[i][j - 1].getState() != '.' && array[i - 1][j].getState() != '.' && array[i][j + 1].getState() != '.' && array[i + 1][j].getState() != '.') {
                        return 0;
                }
                if (direction == 0) //left
                {
                        //cout << endl << "left" << endl;
                        bite_left(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 1) //top
                {
                        //cout << "\ntop" << endl;
                        bite_top(array, i, j, bite_attempt, success_bite, new_strength);
                } else if (direction == 2) //right
                {
                       // cout << "\nrigth\n";
                        bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                } else if (direction == 3) //bottom
                {
                       // cout << "\nbottom\n";
                        bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                }
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
                
                if (direction == 0) //left
                {
                       // cout << "\nleft\n";
                        bite_left(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 2) //right
                {
                       // cout << "\nright\n";
                        bite_right(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 3) { //bottom

                        if (i == 0) {
                               // cout << "\nbottom\n";
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);
                        }

                } else if (direction == 1) { //top

                        if (i == x - 1) {
                                //cout << "\ntop\n";
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                        }

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

                if (direction == 1) { //top
                       // cout << "\ntop\n";

                        bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 3) { //bottom

                       // cout << "\nbottom\n";
                        bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);

                } else if (direction == 0 /*&& j == y - 1*/ ) //left or right
                {
                        if (j == y - 1) {
                              //  cout << "\nleft\n";
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength); //bite right for j==0
                        }

                } else if (direction == 2 /*&& j == 0*/ ) //right
                {
                        if (j == 0) {
                             //   cout << "\nright\n";
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        }

                }
        } //<------------------------------------------------------------ setting conditions for corners----------------------------------------------------------------->
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
                        if (direction == 2) //right
                        {
                              //  cout << "\nright\n";
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 3) //bottom
                        {
                             //   cout << "\nbottom\n";
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == 0 && j == y - 1) //bottom and left
                {

                        if (direction == 3) //bottom
                        {
                             //   cout << "\nbottom\n";
                                bite_bottom(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 0) //left
                        {
                             //   cout << "\nleft\n";
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == x - 1 && j == 0) //top and right
                {

                        if (direction == 1) //top
                        {
                             //   cout << "\ntop\n";
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 2) //right
                        {
                             //   cout << "\nright\n";
                                bite_right(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                valid_bite(array, i, j, bite_accuracy);
                        }

                } else if (i == x - 1 && j == 0) //top and left
                {

                        if (direction == 1) //top
                        {
                               // cout << "\ntop\n";
                                bite_top(array, i, j, bite_attempt, success_bite, new_strength);

                        } else if (direction == 0) //left
                        {
                              //  cout << "\nleft\n";
                                bite_left(array, i, j, bite_attempt, success_bite, new_strength);
                        } else {
                                valid_bite(array, i, j, bite_accuracy);
                        }
                }
        }
        return 0;
}

bool is_berserker(float p_of_berserk) {
        return (((float) rand() / RAND_MAX) <= p_of_berserk) ? true : false;
}

int run_iteration(Subject ** array, int width, int height, float bite_accuracy, float bz_probablity) {

        cout << "Iteration: " << iteration << endl;
        print_map(array, width, height);

        for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {

                        char current_state = array[i][j].getState();
                        if (current_state == '#') {
                                if (array[i][j].getStrength() > 10) {
                                        array[i][j].setStrength(0);
                                        array[i][j].setState('.');
                                } else {
                                        array[i][j].increaseStrength();
                                }

                                //cout << array[i][j].getStrength() << endl;
                                valid_bite(array, i, j, bite_accuracy);
                        } else if (current_state == 'O') {

                                if (array[i][j].getStrength() > 10) {
                                        array[i][j].setStrength(0);
                                        array[i][j].setState('.');
                                } else {
                                        array[i][j].increaseStrength();
                                }
                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);
                        } else if (current_state == '*') {
                                //randomly will become beserk or bitey
                                is_berserker(bz_probablity) ? array[i][j].setState('O') : array[i][j].setState('#');
                                if(array[i][j].getState()=='O'){
                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);
                                valid_bite(array, i, j, bite_accuracy);
                                }
                                else{
                                        valid_bite(array, i, j, bite_accuracy);
                                }
                                //strength wont increase
                        } else if (current_state == 'I') {
                                array[i][j].setState('*');
                        }
                }
        }

        iteration++;
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