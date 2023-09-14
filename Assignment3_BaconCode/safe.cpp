/*

Author: Ajay Yadav

Date: 03/20/2023

Description: C++

Usage: <usage syntax>

*/

#include <string.h> 
#include <iostream> 
#include <fstream>
using namespace std; 


const char* englishToBaconCode(char);
char baconCodeToEnglish(const char*);
int helperFunction1(char*,char*);
int helperFunction2(char*,char*);
char tolowercase(char);

int main(int argc, char** argv) {
    char* fileName = argv[2];
    char* outputFileName = argv[3];
    if (strcmp("-b", argv[1]) == 0) {
        std::cout<<"Translating "<<fileName<<" to BACON code"<<endl; 

        helperFunction1(fileName, outputFileName);

    } else if (strcmp("-e", argv[1]) == 0) {
        std::cout<<"Translating "<<fileName<<" to English"<<endl; 
        helperFunction2(fileName, outputFileName);
    } else if(argc<3){
        std::cout << "Error -- usage: <exe> <-b|-e> <input file> <output file>";
    }

    return 0;
}

int helperFunction2(char* c, char* outputfile) {
    ifstream inputFile(c);
    ofstream outputFile(outputfile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error opening file!";
        return -1;
    }

    char lines[1600];
    inputFile.getline(lines,1600);
    while (!inputFile.eof()) {
         char* token;
         token = strtok(lines, "|");
         while(token!=NULL)
         {
            char outputChar=baconCodeToEnglish(token);
            outputFile<< outputChar;
            token = strtok(NULL, "|");
         }
        outputFile << "\n"; 
        inputFile.getline(lines,1600);
    }

    inputFile.close();
    outputFile.close();
    std::cout<<c<<" file completed."<<endl;
    return 0;
}

int helperFunction1(char* c, char* outputfile) {
    ifstream inputFile(c);
    ofstream outputFile(outputfile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error opening file!";
        return -1;
    }

    char lines[255];
    //inputFile.getline(line,255);
    while (inputFile.getline(lines,255)) {
        int i=0;
        while(lines[i]!='\0')
        {
            const char* outputChar=englishToBaconCode(tolowercase(lines[i]));
            outputFile<<outputChar;

            if(lines[i+1]=='\0')
            {
                outputFile<<"";
            }
            else{
                outputFile<<"|";
            }
            i++;
        }
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();
    std::cout<<outputfile<<" file completed."<<endl;
    return 0;
}


const char* englishToBaconCode(char c)
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



char baconCodeToEnglish(const char* token)
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

char tolowercase(char c){
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
