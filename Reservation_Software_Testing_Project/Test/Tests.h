#pragma once

// Before including standard headers, remove any macro definitions
#undef snprintf
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <io.h> 

/* Includes to use CUnit Framework */
#include <CUnit.h>	    // ASSERT macros for use in test cases, and includes other framework headers.
#include <Automated.h> // Automated interface with xml output.
#include <Basic.h>     // Basic interface with non-interactive output to stdout.
#include <Console.h>   // Interactive console interface.
#include <stdlib.h>     // For function redirect_input spicially in line exit(EXIT_FAILURE);
/* this is our software under test */
#include "../App/App.h"
//#include <CUnit/Automated.h> // Automated interface with xml output.

extern struct Course ListofCourse[MAX_COURSES];

struct User_Input_Type Test_ActualFormRecieved;



/* Prototype Function to Run the Tests */
void Main_Test_Runner(void);

/* Prototype Function to simulate user input */
/* Note:
 * Honestly i asked AI to tell me if there any function simulate user input to make
 * the testing more easier */
void redirect_input(const char* input);

void restore_stdin();
