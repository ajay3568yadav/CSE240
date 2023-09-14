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
int baconCodeToEnglishEC(char*, char*);
int function1(char*,char*);
int function2(char*,char*);
char lower(char);
char upper(char);
char bac(char*);
int charToInt(char);
int englishToBaconCodeEC(char*,char*);

int main(int argc, char** argv) {
    char* filename = argv[2];
    char* outputfile = argv[3];
    if (strcmp("-b", argv[1]) == 0) {
        std::cout<<"Translating "<<filename<<" to BACON code"<<endl; 

        englishToBaconCodeEC(filename, outputfile);

    } else if (strcmp("-e", argv[1]) == 0) {
        std::cout<<"Translating "<<filename<<" to English"<<endl; 
        baconCodeToEnglishEC(filename, outputfile);
    } else if(argc<3){
        std::cout << "Error -- usage: <exe> <-b|-e> <input file> <output file>";
    }

    return 0;
}


int englishToBaconCodeEC(char* c,char* outputfile){
ifstream inputFile(c);
    ofstream outputFile(outputfile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error opening file!";
        return -1;
    }

    char line[255];
    //inputFile.getline(line,255);
    while (inputFile.getline(line,255)) {
        int i=0;
        while(line[i]!='\0')
        {   
            outputFile<<englishToBaconCode(line[i]);
            //cout<<lower(line[i]);
            i++;
        }
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();
    std::cout<<outputfile<<" file completed."<<endl;
    return 0;
}





int baconCodeToEnglishEC(char* c, char* outputfile) {
    ifstream inputFile(c);
    ofstream outputFile(outputfile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error opening file!";
        return -1;
    }
    const char messageString[]="Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Eget magna fermentum iaculis eu non diam phasellus. Quis varius quam quisque id diam vel quam elementum. Proin libero nunc consequat interdum varius sit amet mattis. Pretium viverra suspendisse potenti nullam ac tortor. Lectus sit amet est placerat in egestas erat. Dui id ornare arcu odio ut sem nulla pharetra diam. Amet nisl suscipit adipiscing bibendum est. Fermentum et sollicitudin ac orci phasellus egestas. Sed turpis tincidunt id aliquet risus. Tincidunt id aliquet risus feugiat in ante metus dictum at. Tristique risus nec feugiat in fermentum posuere urna nec tincidunt.Suspendisse interdum consectetur libero id faucibus nisl tincidunt. Vitae tortor condimentum lacinia quis vel eros donec ac. Aliquet eget sit amet tellus cras adipiscing enim. Amet tellus cras adipiscing enim eu turpis egestas. Amet massa vitae tortor condimentum. Sit amet tellus cras adipiscing enim eu. Sed egestas egestas fringilla phasellus. Pretium vulputate sapien nec sagittis aliquam malesuada. Vitae proin sagittis nisl rhoncus mattis rhoncus urna neque viverra. Vel pretium lectus quam id leo. Ac turpis egestas integer eget aliquet nibh praesent tristique magna. Quam pellentesque nec nam aliquam sem et tortor. Vitae elementum curabitur vitae nunc sed velit dignissim. Vel facilisis volutpat est velit egestas dui id ornare.Mauris pharetra et ultrices neque ornare. Et tortor at risus viverra. Non odio euismod lacinia at quis risus sed vulputate. Sed faucibus turpis in eu mi bibendum. Aliquam id diam maecenas ultricies mi eget mauris pharetra et. Nulla porttitor massa id neque. Maecenas accumsan lacus vel facilisis volutpat est velit. Id venenatis a condimentum vitae. Lobortis scelerisque fermentum dui faucibus. Diam quam nulla porttitor massa id neque aliquam. Felis donec et odio pellentesque diam volutpat commodo sed.";
    char line[1600];int n=0;
    inputFile.getline(line,1600);
    while (!inputFile.eof()) {
         char* token;
         token = strtok(line, "|");
         
         while(token!=NULL)
         {
            for(int i=0;i<strlen(token);i++)
            {
                if(token[i]=='x')//lowercase
            {
                outputFile<< lower(messageString[n]);
             }
           else if(token[i]=='o')//uppercase
           {
            outputFile<< upper(messageString[n]);
            }
            else{
            outputFile<<messageString[n];
            }
            n++;
            }
            token = strtok(NULL, "|");
         }
        outputFile << "\n"; // add a space between lines
        inputFile.getline(line,1600);
    }

    inputFile.close();
    outputFile.close();
    std::cout<<c<<" file completed."<<endl;
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
char upper(char c){
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

char lower(char c){
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
/*
int function1(char* c, char* outputfile) {
    ifstream inputFile(c);
    ofstream outputFile(outputfile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error opening file!";
        return -1;
    }

    char line[255];
    //inputFile.getline(line,255);
    while (inputFile.getline(line,255)) {
        int i=0;
        while(line[i]!='\0')
        {
            outputFile<<englishToBaconCode(lower(line[i]));
            //cout<<lower(line[i]);
            if(line[i+1]=='\0')
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

int function2(char* c, char* outputfile) {
    ifstream inputFile(c);
    ofstream outputFile(outputfile);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error opening file!";
        return -1;
    }

    char line[1600];
    inputFile.getline(line,1600);
    while (!inputFile.eof()) {
         char* token;
         token = strtok(line, "|");
         while(token!=NULL)
         {
            outputFile<< baconCodeToEnglish(token);
            token = strtok(NULL, "|");
         }
        outputFile << "\n"; // add a space between lines
        inputFile.getline(line,1600);
    }

    inputFile.close();
    outputFile.close();
    std::cout<<c<<" file completed."<<endl;
    return 0;
}
*/