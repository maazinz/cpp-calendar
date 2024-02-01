#include <iostream>
#include <fstream>
using namespace std;

string months[] = {" ", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
string days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}; 
//declares global variables for the arrays of months and days and assigns values to the indexes

/*
after careful analysis of the calendars of previous years, it was seen that 1973 is a year that starts with 1st Jan on a monday. that helped initialise
any 1st Jan of the following years since we had to compare it to the 1st Jan of 1973. 
we also noticed that every year, the 1st of Jan moves one day ahead every year, except after a leap year, where it moves two days ahead; all of this was
incorporated into our program
*/

int startday(int year, int k) //function "startday" that will figure out which day each month starts with
{
    int diff, leaps, inpush, pm;
    int flag;

    flag = year % 4; //calculates whether or not its a leap year. if it is the remainder will be 0, otherwise it'll be an integer between 1-3

    if(k == 1)
    {
        pm = 0;
    }
    
    if(k == 2)
    {
        pm = 3;
    }
    //the first day of january and february will not be affected regardless of whether or not it is a leap year

    if(flag != 0) //if the rem is not 0 (i.e. it is not a leap year), the code will assign values to all the months, taking 1973 as our reference year 
    {
        switch(k)
        {
            case 10:
                pm = 0;
                break;
            case 3:
            case 11:
                pm = 3;
                break;
            case 4:
            case 7:
                pm = 6;
                break;
            case 5:
                pm = 1;
                break;
            case 6:
                pm = 4;
                break;
            case 8:
                pm = 2;
                break;
            case 9:
            case 12:
                pm = 5;
                break;
        }
        //this switch...case statement relates the starting days of each month back to the ones in 1973 and assigns them a ground value.
    }
    else
    {
        switch(k)
        {
            case 10:
                pm = 1;
                break;
            case 3:
            case 11:
                pm = 4;
                break;
            case 4:
            case 7:
                pm = 0;
                break;
            case 5:
                pm = 2;
                break;
            case 6:
                pm = 5;
                break;
            case 8:
                pm = 3;
                break;
            case 9:
            case 12:
                pm = 6;
                break;
        }
        //this switch case statement does the same, except increments each by one since feb will have 29 days and will push all the months ahead by one day
    }
    
    diff = year - 1973; //this will calculate the number of years - and therefore days pushed forward - between the year input and 1973
    leaps = floor(diff/4); //this will calculate the number of leap years (i.e. the number of extra days to be added due to a leap year)
    
    inpush = diff % 7; //this will eliminate weeks from the start date and will bring the offset to a value between 0-6
    inpush = pm + inpush; //this will then add said offset to the ground value
    inpush = inpush + leaps; //this will add the previous value to the number of leap years (extra days)

    while (inpush > 6)
    {
        inpush = inpush - 7;
    }
    //this will remove any weeks from our new offset value to give us one between 0 and 6

    return inpush; //returns our start day (offset) for the year input in comparison to 1973
}


int leapflag(int year) //a function with the parameter year being passed
{
    int flag;

    if ((year % 4) == 0)
        flag = 1;
    else
    {
        flag = 0;
    }
    //checks whether or not its a leap year. if it is the remainder will be 0 and the flag will return 1, otherwise it'll return 0
    
    return flag;
}


//now that we have essentially calculated the starting day of our month, we will try and print it as well as we can, using the following procedure
void displayyear(int year, ofstream& myFile)
{
    int start, monthdays, leapcheck;
    int line1[7]; //declares an array with 7 indexes to match our days, we just need this for our first line
    
    for(int k = 1; k <= 12; k++)
    {
        for(int l = 0; l < 7; l++)
        {
            line1[l] = 0;
        }
        //this for loop is to initalise the array to 0 for each month

        cout << "--------------------- " << months[k] << " ---------------------" << endl; 
        myFile << "--------------------- " << months[k] << " ---------------------" << endl; 
        //prints the name of the month using the array globally declared and our counter k

        for(int i = 0; i < 7; i++)
        {
            cout << days[i] << "\t";
            myFile << days[i] << "\t";
        }
        cout << endl;
        myFile << endl;
        //we will then print all of our days using our globally declared array of days. we will also create equal spacing between them, and then break the line

        start = startday(year, k); 
        //we will calculate which day our month, k, will start at in the year input, and the return value, which will essentially be the index of the day
        //will be stored in the variable start.

        int i = 1;
        
        line1[start] = 1; //we will then place 1 in the index given by start, calculated above
        start = start + 1; // and then we will increment start

        for(int j = start, n = 2; j < 7; j++, n++)
        {
            line1[j] = n;
        }
        //after incrementing start, we will fill out the rest of the array of the first line

        for(int j = 0; j < 7; j++)
        {
            if(line1[j] == 0)
            {
                cout << " " << "\t";
                myFile << " " << "\t";
            }
            else
            {
                cout << line1[j] << "\t";
                myFile << line1[j] << "\t";
                i++;
            }
        }
        //then we will output the the dates, given that if our stored number at index j is 0, we will simply add a space, otherwise we will print the number
        //and increment i (which was at 1 to begin with)

        switch(k)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                monthdays = 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                monthdays = 30;
                break;
            case 2:
                leapcheck = leapflag(year); 
                //using the leapflag function above, we will check whether or not our current year is a leap year, if it is, the number of days in feb will
                //be 29, if not, the days will be 28.
                if (leapcheck == 0)
                    monthdays = 28;
                else
                {
                    monthdays = 29;        
                } 
                break;
        }
        //this switch...case statement will now allow the program to see whether our month has 28, 29, 30, or 31 days.

        while (i <= monthdays) //we will run our loop as long as we havent reached the number of days assigned to our given month.
        {
            cout << endl;
            myFile << endl;
            for(int j = 0; j < 7; j++)
            {
                cout << i <<  "\t";
                myFile << i <<  "\t";
                i++;
                if(i > monthdays) 
                    break;
                //in case we reach our "monthdays" mark before the line is finished, we will immediately break the loop and go on to the next line   
            }
            //this for loop will print the rest of the lines, given that our i has already been incremented for the dates printed in the first line.
        }
        cout << endl << endl;
        myFile << endl << endl;
        //these endlines are to make our calendar neater
    }
    return; //ends the function
}



int main()
{
    int year;
    ofstream myFile; //initialising a file handler
    myFile.open("Calendar.txt", ios::out | ios::app);


    cout << "THIS CALENDAR ONLY WORKS FOR YEARS AFTER 1972 (not including 1972)" << endl << endl;
    //a disclaimer message since we couldn't get the program to work for a reference year less than 1973

    cout << "Please enter the year for which you want the calendar printed" << endl;
    cin >> year;
    cout << endl;
    //asks the user to input the year they want, and will then store it in our variable "year"

    myFile << "---------------------" << "  " << year << "  " << "---------------------" << endl << endl << endl;

    if(year % 4 == 0)
    {
        cout << "This year is a leap year" << endl << endl;
        myFile << "This year is a leap year" << endl << endl;
    }
    //will check whether or not the year is a leap year, provided it is, the console will print the message shown above

    displayyear(year, myFile);
    //since displayyear is a procedure, it will not return any value, and we can simply call it, while passing the parameters required.

    cout << endl;
    myFile << "-----------------------------------------------------";
    myFile << endl << endl << endl << endl;

    myFile.close();


    return 0; //finally ends our very very long program.
}
