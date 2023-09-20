#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Dependig on the compiler directives, chose the approptiate struct
#ifdef PRE_RELEASE
//This struct keeps information about students: first and last names
struct studentData {
    string lastName;
    string firstName;
    string email;
};
#else 
struct studentData {
    string firstName;
    string lastName;
};
#endif

int main() 
{
    //If in pre-release, then open the file that contains email along with first and last name, otherwise 
    //the file without email information 
#ifdef PRE_RELEASE
    cout << "Running pre-release version\n";
    ifstream inFile("Resource Files/StudentData_Emails1.txt");

    //Check if the file is open
    if (!inFile) {
        cerr << "Unable to open file StudentData_Emails1.txt";
        return 1;
    }
#else
    cout << "Running standard version\n";
    ifstream inFile("Resource Files/StudentData.txt");

    //Check if the file is open
    if (!inFile) {
        cerr << "Unable to open file StudentData.txt";
        return 1;
    }
#endif

    vector<studentData> studentDataVector;  

    studentData studentDataTemp;                //Student struct to temporary keep the info from each line

    string line;                            //Represents a line from a file

    int lineNum = 0; //This keeps the number of the current line in file 

    while (getline(inFile, line)) {
        lineNum++; //Increase the number by 1 each iteration; 

        size_t commaPosition = line.find(','); //Find the position of a comma that separates the first and last names

#ifdef PRE_RELEASE
        size_t commaPositionSecond = line.find(',', commaPosition + 1);
#endif

        if (commaPosition != string::npos) //Check if no comma is present in the line
        {
            if (lineNum > 1)
            {
                //If in pre-release mode, then execute the following:
#ifdef PRE_RELEASE
                studentDataTemp.lastName = line.substr(0, commaPosition);
                studentDataTemp.firstName = line.substr(commaPosition + 2, commaPositionSecond - commaPosition - 2);
                studentDataTemp.email = line.substr(commaPositionSecond + 1);

                studentDataVector.push_back(studentDataTemp); //Push the data to the vector

#else           //If in standard mode, then this code otherwise: 
                studentDataTemp.lastName = line.substr(0, commaPosition);
                studentDataTemp.firstName = line.substr(commaPosition + 2);

                studentDataVector.push_back(studentDataTemp); //Push the data to the vector
#endif
            }
        }
    }

    //lineNum = 0; //reset the lineNum

    //Close the file
    inFile.close();

    // Display the student data in debug mode only
#ifdef _DEBUG
    for (const studentData& studentData : studentDataVector) 
    {
        cout << "Last Name: " << studentData.lastName << ", First Name: " << studentData.firstName;
    #ifdef PRE_RELEASE
        cout << ", Email: " << studentData.email; // Print email in pre-release mode
    #endif
        cout << '\n';
    }
#endif

    return 0; 
}