/*
    STUDENTS: Don't change the code in this file (unless you are very
                comfortable with using the BearLibTerminal) 
*/ 

#ifndef GOOSE_CONSOLE
#define GOOSE_CONSOLE
#include <iostream>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

/* 
    Going further:  Learn the other syntax for implementing a class that is
    more appropriate for working with multiple files, and improve the class code.
*/
class Console
{
  private:
	string messages[NUM_CONSOLE_Y];
	int messageRow;

  public:
    Console()
    {
        // each string element in messages is initialized to "" by the string constructor
	   messageRow = 0;
    }
	
    void writeLine(string new_message_to_print)
    {
        //clear the whole console
        terminal_clear_area(MIN_CONSOLE_X, MIN_CONSOLE_Y, NUM_CONSOLE_X, NUM_CONSOLE_Y);

        // update content of console rows
        if(messageRow < NUM_CONSOLE_Y)
        {
            messages[messageRow] = new_message_to_print;
            messageRow++;
        }
        else
        {
            for(int index = 0; index < NUM_CONSOLE_Y-1; index++)
                messages[index] = messages[index+1];
            messages[NUM_CONSOLE_Y-1] = new_message_to_print;
        }
		
        // output all message rows to the console		 
        for(int line = 0; line < NUM_CONSOLE_Y; line++)
            terminal_print(MIN_CONSOLE_X, MIN_CONSOLE_Y + line, messages[line].c_str());
		
        terminal_refresh();
    }

/*
    Having more than one console is a bad idea.  So you really shouldn't be
    calling these functions.
*/
    Console(Console const & src)
    {
        // memory allocation of array is fixed, so copy constructor and assignment operator are the same
        *this = src;
    }
	
    Console& operator=(Console const & src)
    {
        cerr << "Warning!  You have more than one Console object" << endl;
        for (int index = 0; index < NUM_CONSOLE_Y; index++)
            messages[index] = src.messages[index];
        messageRow = src.messageRow;
        return *this;
    }
};
#endif

