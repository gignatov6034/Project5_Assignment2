#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//This struct keeps information about students: first and last names
struct studentData {
    string firstName;
    string lastName;
};

int main() 
{
    //open the file 
    ifstream inFile("Resource Files/StudentData.txt");

    //Check if the file is open
    if (!inFile) {
        cerr << "Unable to open file StudentData.txt";
        return 1; 
    }

    vector<studentData> studentDataVector;  

    studentData studentData;                //Student struct to temporary keep the info from each line

    string line;                            //Represents a line from a file

    int lineNum = 0; //This keeps the number of the current line in file 

    while (getline(inFile, line)) {
        lineNum++; //Increase the number by 1 each iteration; 
        
        size_t commaPosition = line.find(','); //Find the position of a comma that separates the first and last names

        if (commaPosition != string::npos) //Check if no comma is present in the line
        {
            if (lineNum > 1)
            {
                studentData.firstName = line.substr(0, commaPosition);
                studentData.lastName = line.substr(commaPosition + 1);

                studentDataVector.push_back(studentData);
            }
        }
    }

    //lineNum = 0; //reset the lineNum

    //Close the file
    inFile.close();

    return 0; 
}