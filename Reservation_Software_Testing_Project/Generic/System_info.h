#pragma once
// this is to supress the error of using strcpy instead of strcpy_s
#define _CRT_SECURE_NO_WARNINGS

// maximum number of users in the SW
#define MAX_USERS 5

// maximum number of students per course 
#define MAX_STUDENTS_PER_COURSE 5

// maximum number of the courses available at Edges
#define MAX_COURSES 6

// The current year should be defined for the Registration consistency check
#define CURRENT_YEAR 2024

// Standard ON & Standard OFF (used for testing)
#define STD_ON          (0x01U)       /* Standard ON */
#define STD_OFF         (0x00U)       /* Standard OFF */

// If you want to disable the testing change the MACRO "TESTING_MODE" from "STD_ON" to "STD_OFF"
#define TESTING_MODE		STD_ON