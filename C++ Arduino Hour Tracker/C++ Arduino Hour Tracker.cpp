// c++ and arduino hour tracker
// by marcus eagle
// 7/1/2025

// libraries

#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <cctype>
using std::cout; // namespace for cout and cin only
using std::cin;

// variables

char startHourCountStr[8];
char addHourCountStr[8];
std::string numberOK = "n";
std::string startNumberOK = "n";

// functions

static void pause() // wait for user input before ending the program
{
    (void)_getch();
}

static void setColor(int value) // allow for text to change color
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

// main

int main() // main loop
{
    while (numberOK == "n") // loop while numberOK variable equals "n"
    {
        std::ifstream file; // check if file exists
        file.open("hours.txt");
        if (!file) // if file doesn't exist, create and ask user for starting number
        {
            while (startNumberOK == "n") // loop while startNumberOK variable equals "n"
            {
                std::ofstream hourFileCreate("hours.txt"); // create "hours.txt"
                cout << "Please enter a starting number: "; // ask user for starting number
                cin >> startHourCountStr; // take user input input and assign it to startHourCountStr
                float startHourCountFloat = atof(startHourCountStr); // convert startHourCountStr into a float

                if (startHourCountFloat == 0) // if user inputted 0 or an invalid option
                {
                    setColor(12); // output the following text in red
                    cout << "To create, please input an integer that is real or above 0, unless you would like to start with 0.\n";
                    setColor(7);
                }

                cout << "Your starting number is: " << startHourCountFloat; // state the starting number
                cout << "\nIs this OK? (Type y or n): "; // ask if it's ok
                cin >> startNumberOK;
                std::transform(startNumberOK.begin(), startNumberOK.end(), startNumberOK.begin(), ::tolower); // convert user input to lowercase
                if (startNumberOK == "y") // if user input is "y"
                {
                    hourFileCreate << startHourCountFloat; // write starting number to file
                    hourFileCreate.close(); // close the text file
                    cout << "Your number has been added.\n";
                }

                else if (startNumberOK == "n"); // if user input is "n" then restart loop

                else // if user input is anything else
                {
                    setColor(12); // set color to red
                    cout << "Please input one of the listed options.\n"; // notify user of incorrect input
                    setColor(7); // reset color back to white
                    startNumberOK = "n"; // restart loop
                }
            }
        }

        std::ifstream hourFileRead("hours.txt"); // open and read text file
        std::string oldHourCountStr;
        getline(hourFileRead, oldHourCountStr); // get string from txt
        cout << "Your current number of hours is: " << oldHourCountStr; // display string
        hourFileRead.close(); // close the text file
        float oldHourCountFloat = stof(oldHourCountStr); // convert string to float for math

        cout << "\nType a number to add: "; // type a number and press enter
        cin >> addHourCountStr; // get user input from keyboard
        float addHourCountFloat = atof(addHourCountStr); // convert ascii to float

        if (addHourCountFloat == 0) // if user inputted 0 or an invalid option
        {
            setColor(12); // set color to red
            cout << "To add, please input an integer that is real or above 0.\n"; // notify user of incorrect input
            setColor(7); // reset color back to white
        }

        float newHourCount = oldHourCountFloat + addHourCountFloat; // add oldHourCountFloat and addHourCountFloat
        cout << "Your new number is: " << newHourCount; // display input value
        cout << "\nIs this OK? (Type y or n): "; // ask if the new number is ok
        cin >> numberOK; // take user input
        std::transform(numberOK.begin(), numberOK.end(), numberOK.begin(), ::tolower); // convert user input to lowercase
        if (numberOK == "y") // if user input is "y"
        {
            std::ofstream hourFileWrite("hours.txt"); // create and open a text file
            hourFileWrite << newHourCount; // write to the text file
            hourFileWrite.close(); // close the text file
            cout << "Your number has been added.\n";
            cout << "Press any button to continue...";
            pause(); // invoke custom pause function
        }

        else if (numberOK == "n"); // if user input is "n" then restart loop

        else // if user input is anything else then inform user and restart loop
        {
            setColor(12);
            cout << "Please input one of the listed options.\n";
            setColor(7);
            numberOK = "n";
        }
    }
    return 0; // return value to check if the program ran successfully
}