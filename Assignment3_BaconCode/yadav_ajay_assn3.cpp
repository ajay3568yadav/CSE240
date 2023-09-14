/*

Author: Ajay Yadav

Date: 03/21/2023

Description: C++ Assignment 3

Usage: <exe> <-b|-e> <input file> <output file>

*/

#include <string.h> 
#include <iostream> 
#include <fstream>
using namespace std; 

const char* englishToBaconCode(char); // function converts english to bacon code

char baconCodeToEnglish(const char*); // function converts bacon code to english uppercase letters

int translateToBacon(char*,char*,bool); // function writes converted (english ---> bacon code) bacon code to output file

int translateToEnglish(char*,char*,bool); // function writes (bacon ---> english) english to output file converted from bacon code

int encodeToEnglish(char*,char*,bool); // EXTRA CREDIT FUNCTION: decodes the message encrypted in a file

int charToInt(char); // convert char to integer according to ASCII

char lower(char); // convert alphabets to lower case

char upper(char); // convert alphabets to upper case

int main(int argc, char** argv) {

    char* filename = argv[2]; // 3nd argument from command line should be file from which the program will extract text

    char* outputfile = argv[3]; // 4nd argument should be file to which the program will write into

    bool enable=false; // enables verbose: when true, it will enable the display of file processing
    
    if( argc==4 || (argc==5 && strcmp("-v", argv[4]) == 0 )) // checking if 5th argument matches "-v" and if the number of arguments are sufficent
    {
        if(argc==5){ // if -v is present then enable is set true to enable verbose

            enable=true;

        }

    if (strcmp("-b", argv[1]) == 0) { // checking for -b tag that converts englsih to bacon Code

        std::cout<<"Translating "<<filename<<" to BACON code"<<endl; 

        translateToBacon(filename, outputfile,enable); // calling translate function to wrtie into the output file

    } else if (strcmp("-e", argv[1]) == 0) { // checking for -e tag that converts bacon code to english

        std::cout<<"Translating "<<filename<<" to English"<<endl; 

        translateToEnglish(filename, outputfile,enable); // calling translate function to wrtie into the output file

    } else if( strcmp("-x",argv[1])==0){ // checking for -x tag that calls the function that decodes the message hidden in a file

        std::cout<<"Translating "<<filename<<" to English"<<endl; 

        encodeToEnglish(filename, outputfile,enable); // decodes the message hidden in a file and write it into the outputfile

        }
    else{

        std::cout << "Error -- usage: <exe> <-b|-e> <input file> <output file>"; // error message with use case

        }
    }
    else{

        std::cout << "Error -- usage: <exe> <-b|-e> <input file> <output file>"; // error message with use case
    
    }
    return 0;
}


// converts character to int according to ASCII code
int charToInt(char item)
{
if((item >= 'a') && (item <= 'z'))
{
return (int)item;
}
else if ((item >= 'A') && (item <= 'Z'))
{
return (int)item;
}
else
return -1;
}

// decode message hidden in the input file and write the decoded message into the output file 
int encodeToEnglish(char* c, char* outputfile,bool enable) {

    ifstream inputFile(c); // inputstream to read file

    ofstream outputFile(outputfile); // output stream to wrtie to the file

    if (!inputFile.is_open() || !outputFile.is_open()) { // displaying error message when unable to open file

        std::cout << "Error opening file!";

        return -1;
    }

    char line[255]; // this variable stores character in a line red from the input file
    int j=0; //keep track of the characters red in the line array


    while (inputFile.getline(line,255)) { //getting a line as long as there is another line to take


        if(enable==true)
        {
            std::cout<<"Processing "<<c<<"..."<<endl;
            std::cout<<"READ:: "<<line<<endl;
            std::cout<<"WROTE:: ";
        }
        while(line[j]!='\0') 
        {
            char sourceStr[5]; // char array used for storing the bacon code converted from a character red from inputfile
         
            int i=0; // iterator

         while(i!=5){ // loop to store the bacon code of a character obtained from "line"
            
                if(charToInt(line[j])>=97 && charToInt(line[j])<=122)//lowercase
            {
                
                sourceStr[i]='x'; // if the character at the jth index of line is lowercase the sourceStr will take 'x' at its ith

                j++;i++; //incrementing index of sourceStr and line;

             }

           else if(charToInt(line[j])>=65 && charToInt(line[j])<=90)//uppercase
           {

            sourceStr[i]='o'; // if the character at the jth index of line is uppercase the sourceStr will take 'o' at its ith

            j++;i++; //incrementing index of sourceStr and line;

            }

            else{

            j++; //increase the index of line if the character is not an alphabet

            }
            if(line[j]=='\0') // if line[j] reaches the end of the line then loop breaks without finishing filling of sourceStr
                {
                    break;
                }
         }

            if(line[j]=='\0')  // if line[j] reaches the end of the line then outer loop breaks 
                {
                    break;
                }

        char* c=sourceStr; //storing value of sourceStr in a char* to input it to baconCodeToEnglish function 

         
            outputFile<< baconCodeToEnglish(c); //writing to the decoded file
            std::cout<<baconCodeToEnglish(c);

        }

        outputFile << "\n"; // inserting line after the end of the "line"
        inputFile.getline(line,255); // getting line again
    }
    std::cout<<endl;

    inputFile.close(); // closing input file

    outputFile.close();// closing outputfile

    std::cout<<c<<" file completed."<<endl;

    return 0;
}

char upper(char c){ // function to convert lower case letter to uppercase

    char result;

    switch(c) {
        case 'a': result = 'A'; break;
        case 'b': result = 'B'; break;
        case 'c': result = 'C'; break;
        case 'd': result = 'D'; break;
        case 'e': result = 'E'; break;
        case 'f': result = 'F'; break;
        case 'g': result = 'G'; break;
        case 'h': result = 'H'; break;
        case 'i': result = 'I'; break;
        case 'j': result = 'J'; break;
        case 'k': result = 'K'; break;
        case 'l': result = 'L'; break;
        case 'm': result = 'M'; break;
        case 'n': result = 'N'; break;
        case 'o': result = 'O'; break;
        case 'p': result = 'P'; break;
        case 'q': result = 'Q'; break;
        case 'r': result = 'R'; break;
        case 's': result = 'S'; break;
        case 't': result = 'T'; break;
        case 'u': result = 'U'; break;
        case 'v': result = 'V'; break;
        case 'w': result = 'W'; break;
        case 'x': result = 'X'; break;
        case 'y': result = 'Y'; break;
        case 'z': result = 'Z'; break;
        default: result= c; break;
    }
    return result;
}


int translateToEnglish(char* c, char* outputfile,bool enable) {

    ifstream inputFile(c); // inputstream to read file

    ofstream outputFile(outputfile); // output stream to wrtie to the file

    if (!inputFile.is_open() || !outputFile.is_open()) { // display error message if unable to open file

        std::cout << "Error opening file!";

        return -1;
    }

    char line[1600]; // char array to store characters of bacon code in a line 255*6

    inputFile.getline(line,1600); // get line from the inputfile

    while (!inputFile.eof()) { //running to loop until the end of the file

         char* token; //created a token to pass to the baconCodeToEnglish function

         token = strtok(line, "|"); //taking chars upto the delimeter defined "|" for a token

         if(enable==true){ //verbose
                std::cout<<"Processing "<<c<<"..."<<endl;
                std::cout<<"READ:: "<<line<<endl; 
                std::cout<<"WROTE:: "; 
            }

         while(token!=NULL)
         {
            
            outputFile<< baconCodeToEnglish(token); //writing to the output file the translated code

            if(enable==true){ //verbose
                std::cout<<baconCodeToEnglish(token); //printing to terminal
            }

            token = strtok(NULL, "|");

         }

        outputFile << "\n"; // add a space between lines
        std::cout<<endl;

     inputFile.getline(line,1600); //getting next line to check if a new line is present or not
    }

    inputFile.close(); //closing inputfile

    outputFile.close(); //closing outputfile

    std::cout<<c<<" file completed."<<endl;

    return 0;
}

int translateToBacon(char* c, char* outputfile,bool enable) { // function writes converted (english ---> bacon code) bacon code to output file

    ifstream inputFile(c); // inputstream to read file

    ofstream outputFile(outputfile); // output stream to wrtie to the file

    if (!inputFile.is_open() || !outputFile.is_open()) { // display error message if unable to open file

        std::cout << "Error opening file!";

        return -1;
    }

    char line[255]; //character array to store charactes obtained from reading a line from the input file
    
    while (inputFile.getline(line,255)) { //reading lines from the file
        int i=0; //interator

        if(enable==true){ //verbose
                std::cout<<"Processing "<<c<<"..."<<endl;
                std::cout<<"READ:: "<<line<<endl; 
                std::cout<<"WROTE:: "; 
            }

        while(line[i]!='\0')
        {   
            outputFile<<englishToBaconCode(lower(line[i])); //writing to the outputfile

            //verbose
            if(enable==true){
            std::cout<<englishToBaconCode(lower(line[i]));
            if(!(line[i+1]=='\0'))
            {
                std::cout<<"|";
            }
            }

            //checking the end of line
            if(!(line[i+1]=='\0'))
            {
                outputFile<<"|";
            }
            
            i++;
        }
        std::cout<<endl;
        outputFile << endl;
    }

    inputFile.close(); //closing inputfile
    outputFile.close(); //closing outputfile

    std::cout<<outputfile<<" file completed."<<endl;
    return 0;
}


const char* englishToBaconCode(char c) //convert alphabets to bacon code
{
      const char* result;
    switch(c) {
        case 'a': result = "xxxxx"; break;
        case 'b': result = "xxxxo"; break;
        case 'c': result = "xxxox"; break;
        case 'd': result = "xxxoo"; break;
        case 'e': result = "xxoxx"; break;
        case 'f': result = "xxoxo"; break;
        case 'g': result = "xxoox"; break;
        case 'h': result = "xxooo"; break;
        case 'i': result = "xoxxx"; break;
        case 'j': result = "xoxxo"; break;
        case 'k': result = "xoxox"; break;
        case 'l': result = "xoxoo"; break;
        case 'm': result = "xooxx"; break;
        case 'n': result = "xooxo"; break;
        case 'o': result = "xooox"; break;
        case 'p': result = "xoooo"; break;
        case 'q': result = "oxxxx"; break;
        case 'r': result = "oxxxo"; break;
        case 's': result = "oxxox"; break;
        case 't': result = "oxxoo"; break;
        case 'u': result = "oxoxx"; break;
        case 'v': result = "oxoxo"; break;
        case 'w': result = "oxoox"; break;
        case 'x': result = "oxooo"; break;
        case 'y': result = "ooxxx"; break;
        case 'z': result = "ooxxo"; break;
        case ' ': result = "/";break;
        default: result="!!!!!"; break;
    }
    return result;
}



char baconCodeToEnglish(const char* token) //converts bacon code to english
{
    if (strcmp("xxxxx", token) == 0) return 'A';
    else if (strcmp("xxxxo", token) == 0) return 'B';
    else if (strcmp("xxxox", token) == 0) return 'C';
    else if (strcmp("xxxoo", token) == 0) return 'D';
    else if (strcmp("xxoxx", token) == 0) return 'E';
    else if (strcmp("xxoxo", token) == 0) return 'F';
    else if (strcmp("xxoox", token) == 0) return 'G';
    else if (strcmp("xxooo", token) == 0) return 'H';
    else if (strcmp("xoxxx", token) == 0) return 'I';
    else if (strcmp("xoxxo", token) == 0) return 'J';
    else if (strcmp("xoxox", token) == 0) return 'K';
    else if (strcmp("xoxoo", token) == 0) return 'L';
    else if (strcmp("xooxx", token) == 0) return 'M';
    else if (strcmp("xooxo", token) == 0) return 'N';
    else if (strcmp("xooox", token) == 0) return 'O';
    else if (strcmp("xoooo", token) == 0) return 'P';
    else if (strcmp("oxxxx", token) == 0) return 'Q';
    else if (strcmp("oxxxo", token) == 0) return 'R';
    else if (strcmp("oxxox", token) == 0) return 'S';
    else if (strcmp("oxxoo", token) == 0) return 'T';
    else if (strcmp("oxoxx", token) == 0) return 'U';
    else if (strcmp("oxoxo", token) == 0) return 'V';
    else if (strcmp("oxoox", token) == 0) return 'W';
    else if (strcmp("oxooo", token) == 0) return 'X';
    else if (strcmp("ooxxx", token) == 0) return 'Y';
    else if (strcmp("ooxxo", token) == 0) return 'Z';
    else if (strcmp("/", token) == 0) return ' ';
    else if (strcmp("!!!!!", token) == 0) return '#';
      return '%'; // unknown character
}

char lower(char c){ // function to convert lower case letter to uppercase
    char result;
    switch(c) {
        case 'A': result = 'a'; break;
        case 'B': result = 'b'; break;
        case 'C': result = 'c'; break;
        case 'D': result = 'd'; break;
        case 'E': result = 'e'; break;
        case 'F': result = 'f'; break;
        case 'G': result = 'g'; break;
        case 'H': result = 'h'; break;
        case 'I': result = 'i'; break;
        case 'J': result = 'j'; break;
        case 'K': result = 'k'; break;
        case 'L': result = 'l'; break;
        case 'M': result = 'm'; break;
        case 'N': result = 'n'; break;
        case 'O': result = 'o'; break;
        case 'P': result = 'p'; break;
        case 'Q': result = 'q'; break;
        case 'R': result = 'r'; break;
        case 'S': result = 's'; break;
        case 'T': result = 't'; break;
        case 'U': result = 'u'; break;
        case 'V': result = 'v'; break;
        case 'W': result = 'w'; break;
        case 'X': result = 'x'; break;
        case 'Y': result = 'y'; break;
        case 'Z': result = 'z'; break;
        default: result= c; break;
    }
    return result;
}

//