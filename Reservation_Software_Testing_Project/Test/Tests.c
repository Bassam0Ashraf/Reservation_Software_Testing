#include "Tests.h"

/*Function to simulate user input
 * Note:
 * Honestly i asked AI to tell me if there any function simulate user input to make 
 * the testing more easier */

/*
void redirect_input(const char* input)
{
	// Open a temporary file and write the input string to it
	FILE* temp = fopen("temp_input.txt", "w");
	
	if (!temp)		// Check if 'temp' file pointer is NULL (i.e., the temporary file couldn't be created)
	{
		perror("Unable to create temp input file");	// Print a descriptive error message to stderr using the most recent system error.
		exit(EXIT_FAILURE);							// Exit the program with a failure status
	}
	fputs(input, temp);								// Write the input string to the temporary file
	fclose(temp);									// Close the temporary file

	freopen("temp_input.txt", "r", stdin);  // Redirect stdin to read from file
}
*/
static int original_stdin_fd = -1;

void redirect_input(const char* input)
{
	// Save the original stdin file descriptor if not already saved
	if (original_stdin_fd == -1) {
		original_stdin_fd = _dup(_fileno(stdin));
		if (original_stdin_fd == -1) {
			perror("Failed to duplicate stdin");
			exit(EXIT_FAILURE);
		}
	}

	FILE* temp = fopen("temp_input.txt", "w");
	if (!temp) {
		perror("Unable to create temp input file");
		exit(EXIT_FAILURE);
	}
	fputs(input, temp);
	fclose(temp);

	if (freopen("temp_input.txt", "r", stdin) == NULL) {
		perror("Failed to redirect stdin");
		exit(EXIT_FAILURE);
	}
}

void restore_stdin()
{
	if (original_stdin_fd != -1) {
		if (_dup2(original_stdin_fd, _fileno(stdin)) == -1) {
			perror("Failed to restore stdin");
		}
		_close(original_stdin_fd);
		original_stdin_fd = -1;
		remove("temp_input.txt");  // Clean up the temp file
	}
}

/*******************************************************************************
 *                                Data Types                                   *
 *******************************************************************************/

/* Test Code to test the Sign Up */
static struct User_Input_Type Test_User1_ExpectedFormSent =
{
	{
	-1, // this is to indecate user hasn't assigned ID 
	"Ahmed",		// Name
	26,				// Age
	23,				// Day
	10,				// Month
	1998,			// Year
	Male,			// Gender
	Masters_Student // Educational Status
	},
	{
		{
			"EdgesAcademy",	// User Name
			"Edges123"		// Password
		},
	"Edges123"	// Password Recheck
	}
};

/* Test Code to test the Sign Up */
static struct User_Input_Type Test_User2_ExpectedFormSent =
{
	{
	-1, // this is to indecate user hasn't assigned ID 
	"Rania",
	54,
	31,
	12,
	1970,
	Female,
	PHD_Holder
	},
	{
		{
			"EdgesAcademy2024",
			"Edges_123_"
		},
	"Edges_123_$$"
	}
};

/* General users (Correct formart) to use it to intialize the DB or for any test case */
static struct User_Input_Type Test_GeneralUser1=
{
	{
	-1,"AhmedFIRST",26,1,2,1998,Male,Student
	},
	{
		{"AdminUser1","Edges123"},
		"Edges123"
	}
};

static struct User_Input_Type Test_GeneralUser2 =
{
	{
	-1,"AhmedSECOND",26,1,2,1998,Male,Student
	},
	{
		{"AdminUser1","Edges123"},
		"Edges123"
	}
};

static struct User_Input_Type Test_GeneralUser3 =
{
	{
	-1,"AhmedTHIRD",26,1,2,1998,Male,Student
	},
	{
		{"AdminUser1","Edges123"},
		"Edges123"
	}
};

static struct User_Input_Type Test_GeneralUser4 =
{
	{
	-1,"AhmedFOURTH",26,1,2,1998,Male,Student
	},
	{
		{"AdminUser1","Edges123"},
		"Edges123"
	}
};

static struct User_Input_Type Test_GeneralUser5 =
{
	{
	-1,"AhmedFITH",26,1,2,1998,Male,Student
	},
	{
		{"AdminUser1","Edges123"},
		"Edges123"
	}
};

/*******************************************************************************
 *                   Initialize & Closure functions for Suites                 *
 *******************************************************************************/

/* init function for Test Suite 1 */
static unsigned char TestSuite_AddAccountFunction_Start(void)
{
	printf("\n\n--- Starting Testing Add Account Functionality (vaild user) ---\n\n");

	return 0;
}

/* Closure Function For Test Suite 1 */
static unsigned char TestSuite_AddAccountFunction_End(void)
{
	printf("\n\n--- Ending Testing Add Account Functionality (vaild user) ---\n\n");

	return 0;
}



/* init function for Test Suite 2 */
static unsigned char TestSuite_start(void)
{
	printf("\n\n--- Starting Testing Add Account Functionality (Invaild user) ---\n\n");

	unsigned char RET = Add_Account(&Test_User2_ExpectedFormSent);
	Test_User2_ExpectedFormSent.PersonalInfo_Form.id = (current_user_test - 1);
	DBM_PrintUsers();
	return RET;
}

/* Closure Function For Test Suite 2 */
static unsigned char TestSuite_end(void)
{
	// Only try to delete if a user was actually added
	if (Test_User2_ExpectedFormSent.PersonalInfo_Form.id < 0) {
		unsigned char RET = Delete_Account(current_user_test - 1);
		DBM_PrintUsers();
		return !RET;
	}

	// No user was added, so nothing to delete
	return 0;
}



/* init function for Test Suite 2 */
static unsigned char TestSuite_DeteleFunction_Start(void)
{
	printf("\n\n--- Starting Testing Delete Account Functionality ---\n\n");

	return 0;
}

/* Closure Function For Test Suite 2 */
static unsigned char TestSuite_DeteleFunction_End(void)
{

	printf("\n\n--- Start Deleting all users ---\n\n");


	printf("\n\n--- Ending Testing Delete Account Functionality ---\n\n");

	return 0;
}



/* init function for Test Suite 3 */
static unsigned char TestSuite_GetNumberOfDays_Start(void)
{
	printf("\n\n--- Start testing Suite_NumberOfDays ---\n\n");

	return 0;
}

/* Closure Function For Test Suite 3 */
static unsigned char TestSuite_GetNumberOfDays_End(void)
{
	printf("\n\n--- End testing Suite_NumberOfDays ---\n\n");

	return 0;
}



/* init function for Test Suite 4 */
static unsigned char TestSuite_ShowStudentCourses_Start(void)
{
	printf("\n\n--- Start testing Suite Show Student Courses Function ---\n\n");

	return 0;
}

/* Closure Function For Test Suite 4 */
static unsigned char TestSuite_ShowStudentCourses_End(void)
{
	printf("\n\n--- End testing Suite Show Student Courses Function ---\n\n");

	return 0;
}



/* init function for Test Suite 5 */
static unsigned char TestSuite_AddStudentToCourse_Start(void)
{
	printf("\n\n--- Start testing Suite Add Student To Course Function ---\n\n");
	return 0;
}

/* Closure Function For Test Suite 5 */
static unsigned char TestSuite_AddStudentToCourse_End(void)
{
	printf("\n\n--- End testing Suite Add Student To Course Function ---\n\n");
	return 0;
}


/* init function for Test Suite 6 */
static unsigned char TestSuite_DetectUserType_Start(void)
{
	printf("\n\n--- Start testing Suite Detect User Type Function ---\n\n");
	return 0;
}

/* Closure Function For Test Suite 6 */
static unsigned char TestSuite_DetectUserType_End(void)
{
	printf("\n\n--- End testing Suite Detect User Type Function ---\n\n");
	return 0;
}


/* init function for Test Suite 7 */
static unsigned char TestSuite_VerifyAdmin_Start(void)
{
	printf("\n\n--- Start testing Suite Verify Admin Function ---\n\n");
	return 0;
}

/* Closure Function For Test Suite 7 */
static unsigned char TestSuite_VerifyAdmin_End(void)
{
	printf("\n\n--- End testing Suite Verify Admin Function ---\n\n");
	return 0;
}


/* init function for Test Suite 8 */
static unsigned char TestSuite_VerifyUser_Start(void)
{
	printf("\n\n--- Start testing Suite Verify User Function ---\n\n");
	return 0;
}

/* Closure Function For Test Suite 8 */
static unsigned char TestSuite_VerifyUser_End(void)
{
	printf("\n\n--- End testing Suite Verify User Function ---\n\n");
	return 0;
}



/*******************************************************************************
 *                           Test cases for Suites                             *
 *******************************************************************************/

/* Test Case for Suite 1 (Add Account Functionality) */

/************************************************************************************
* Test ID                : 1
* Test Case				 : Add Account Functionality
* Description            : Testing the Add Account Functionality
* 
* Technique              : Equivalence Partitioning
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                          Name                         -> Ahmed
*                          Age                          -> 26
*                          DOB_day                      -> 01
*                          DOB_Month                    -> 02
*                          DOB_Year                     -> 1999
*                          Educational_Status           -> Masters_Student
*                          Gender                       -> Male
*                          UserName                     -> EdgesAcademy
*                          Password                     -> Edges123
*                          Password Recheck             -> Edges123
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : All inputs are in correct format
* Bug Found              : None
*************************************************************************************/
static void TestCase_AddVaildAccount(void)
{
	unsigned char result = Add_Account(&Test_User1_ExpectedFormSent);
	Test_User1_ExpectedFormSent.PersonalInfo_Form.id = current_user_test - 1;
	DBM_PrintUsers();

	// (Actual , Expected)
	CU_ASSERT_EQUAL(result, TRUE);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.Age, Test_User1_ExpectedFormSent.PersonalInfo_Form.Age);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.DOB_day, Test_User1_ExpectedFormSent.PersonalInfo_Form.DOB_day);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.DOB_month, Test_User1_ExpectedFormSent.PersonalInfo_Form.DOB_month);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.DOB_year, Test_User1_ExpectedFormSent.PersonalInfo_Form.DOB_year);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.educational_status, Test_User1_ExpectedFormSent.PersonalInfo_Form.educational_status);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.gender, Test_User1_ExpectedFormSent.PersonalInfo_Form.gender);
	CU_ASSERT_STRING_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.name, Test_User1_ExpectedFormSent.PersonalInfo_Form.name);
	CU_ASSERT_STRING_EQUAL(Test_ActualFormRecieved.LoginCredentials_Form.LoginCredentials.User_Name, Test_User1_ExpectedFormSent.LoginCredentials_Form.LoginCredentials.User_Name);
	CU_ASSERT_STRING_EQUAL(Test_ActualFormRecieved.LoginCredentials_Form.LoginCredentials.Password, Test_User1_ExpectedFormSent.LoginCredentials_Form.LoginCredentials.Password);
	CU_ASSERT_EQUAL(Test_ActualFormRecieved.PersonalInfo_Form.id, Test_User1_ExpectedFormSent.PersonalInfo_Form.id);

	// Cleanup DB
	Delete_Account(current_user_test - 1);
	DBM_PrintUsers();
}


/************************************************************************************
* Test ID                : 2
* Test Case				 : Add Account with Invaild name
* Description            : Testing the Add Account Functionality by adding invaild name
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                         1- Name                        -> Al		(Invalid, 3 chars)
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                         2- Name                        -> ThisIs33CharactersLong12345678901	(Invalid, 33 chars)
*                         3- Name                        -> ""			    (Empty)
* 
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : Name length does not meet the required range (3 - 32 characters).
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvaildNameBoundaries(void)
{
	struct User_Input_Type Test_NameBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function


	/* Name length just below minimum(2) */
	strcpy(Test_NameBoundaries.PersonalInfo_Form.name, "Al");
	result = Add_Account(&Test_NameBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong


	/* Name length just above maximum(33) */
	strcpy(Test_NameBoundaries.PersonalInfo_Form.name, "ThisIs33CharactersLong12345678901");	// Fill name with 33 characters
	result = Add_Account(&Test_NameBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong


	/* Empty name */
	strcpy(Test_NameBoundaries.PersonalInfo_Form.name, "");
	result = Add_Account(&Test_NameBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong
}


/************************************************************************************
* Test ID                : 3
* Test Case				 : Add Account Functionality Valid Name
* Description            : Testing the Add Account Functionality by adding vaild name
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                         1- Name                        -> AhmedFIRST		(valid, 10 chars)
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                         2- Name                        -> Ali				(valid, 3 chars)
*                         3- Name                        -> ThisIsExactly32CharactersLong123	(valid, 32 chars)
* 
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : Name length meet the required range (3 - 32 characters).
* 
* Bug                    : The name length is 32 but the string is not added
*************************************************************************************/
static void TestCase_VaildNameBoundaries(void)
{
	struct User_Input_Type Test_NameBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Vaid name length between (3-32) */
	result = Add_Account(&Test_GeneralUser1);					// Store return of funtion add account

	CU_ASSERT_EQUAL(result, TRUE);
	DBM_PrintUsers();
	Delete_Account(current_user_test - 1);						// Cleanup DB


	/* Minimum valid name length(3) */
	strcpy( Test_NameBoundaries.PersonalInfo_Form.name, "Ali" ); // Fill name with 3 characters
	result = Add_Account(&Test_NameBoundaries);					// Store return of funtion add account

	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB

	/* Bug found : The name length is 32 but the string is not added
	 The Problem:
	 A 32-character string requires 33 bytes of storage (32 chars + null terminator)
	 strcpy of a 32-character string into a 32-byte buffer overflows and corrupts memory
	 This causes undefined behavior, making the validation fail */

	/* Maximum valid name length(32) */
	strcpy(Test_NameBoundaries.PersonalInfo_Form.name, "ThisIsExactly32CharactersLong123");	// Fill name with 32 characters
	result = Add_Account(&Test_NameBoundaries);					// Store return of funtion add account

	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB
}


/************************************************************************************
* Test ID                : 4
* Test Case				 : Add Account with (Invalid Age)
* Description            : Testing the Add Account Functionality by adding invaild age
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> AhmedFIRST
*                         1- Age                         -> -1			(Invalid, -1 Age)
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                         2- Age                         -> 101			(Invalid, 101 Age)
*
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : Age does not meet the required range (0 - 100 Age).
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvaildAgeBoundaries(void)
{
	struct User_Input_Type Test_AgeBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Age just below minimum(-1) */
	Test_AgeBoundaries.PersonalInfo_Form.Age = -1;				// Fill age with -1
	result = Add_Account(&Test_AgeBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong


	/* Age just above maximum(101) */
	Test_AgeBoundaries.PersonalInfo_Form.Age = 101;				// Fill age with 101
	result = Add_Account(&Test_AgeBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong

}


/************************************************************************************
* Test ID                : 5
* Test Case				 : Add Account (valid Age)
* Description            : Testing the Add Account Functionality by adding vaild age
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> AhmedFIRST
*                         1- Age                         -> 26			(Valid, 26 Age)
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                         2- Age                         -> 0			(Valid, 0 Age)
*                         3- Age						 -> 100			(Valid, 100 Age)
*
* Test Expected output   : The DB should be updated with the previous inputs
* Reason                 : Age meet the required range (0 - 100 Age).
* 
* Bug                    : 1- The age is 100 but the User is not added however its (impossible nowdays)
*                          2- The age is 0 but the User is not added however its (meaningless)
*************************************************************************************/
static void TestCase_VaildAgeBoundaries(void)
{
	struct User_Input_Type Test_AgeBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Age between Acceptable range 0 - 100 (26) */
	Test_AgeBoundaries.PersonalInfo_Form.Age = 26;				// Fill age with 26
	result = Add_Account(&Test_AgeBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB 


	/* Bug found due to the conditon in if its not include '0' in the range of age however age 0 its meaningless */
	/* Age just minimum (0) */
	Test_AgeBoundaries.PersonalInfo_Form.Age = 0;				// Fill age with 0
	result = Add_Account(&Test_AgeBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB 


	/* Bug found due to the conditon in if its not include '100' in the range of age however age 100 its impossible nowdays */
	/* Age just maximum (100) */
	Test_AgeBoundaries.PersonalInfo_Form.Age = 100;			    // Fill age with 100
	result = Add_Account(&Test_AgeBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB 
}


/************************************************************************************
* Test ID                : 6
* Test Case				 : Add Account(invaild gender)
* Description            : Testing the Add Account Functionality by adding invaild gender
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						 1- Gender                       -> DEFAULT_Gender
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                        2- Gender                       -> -1
*                        3- Gender					     -> 5
*
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : becuase gender inputs are in invaild format
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvaildGender(void)
{
	struct User_Input_Type Test_Gender = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Trying to fill gender with DEFAULT_Gender (0) */
	Test_Gender.PersonalInfo_Form.gender = DEFAULT_Gender;		// Fill the gender section with default value
	result = Add_Account(&Test_Gender);						    // Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong


	/* Trying to fill gender with (-1) out of range of enum */
	Test_Gender.PersonalInfo_Form.gender = -1;					// Fill the gender section with -1
	result = Add_Account(&Test_Gender);							// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong


	/* Trying to fill gender with (5) out of range of enum */
	Test_Gender.PersonalInfo_Form.gender = 5;					// Fill the gender section with 5
	result = Add_Account(&Test_Gender);							// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);						// Cleanup DB if it added by wrong
}


/************************************************************************************
* Test ID                : 7
* Test Case				 : Add Account (vaild gender)
* Description            : Testing the Add Account Functionality by adding vaild gender
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						 1- Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                        2- Gender                       -> Female
*
* Test Expected output   : The DB should be updated with the previous inputs
* Reason                 : becuase gender inputs are in vaild format
* Bug Found              : None
*************************************************************************************/
static void TestCase_VaildGender(void)
{
	struct User_Input_Type Test_Gender = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Trying to fill gender with Male */
	Test_Gender.PersonalInfo_Form.gender = Male;				// Fill the gender section with Male
	result = Add_Account(&Test_Gender);						    // Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB

	
	/* Trying to fill gender with Female */
	Test_Gender.PersonalInfo_Form.gender = Female;				// Fill the gender section with Female
	result = Add_Account(&Test_Gender);							// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);						// Cleanup DB
}


/************************************************************************************
* Test ID                : 8
* Test Case				 : Add Account (invaild educational status)
* Description            : Testing the Add Account Functionality by adding invaild educational status
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                        1- Educational_Status           -> DEFAULT_Status
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                        2- Educational_Status           -> -1
*                        3- Educational_Status           -> 8
*
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : becuase educational status inputs are in invaild format
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvaildEducationalStatus(void)
{
	struct User_Input_Type Test_EducationalStatus = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Trying to fill educational status with DEFAULT_Status (0) */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = DEFAULT_Status;	// Fill the educational status section with default value
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);											// Cleanup DB if it added by wrong


	/* Trying to fill educational status with (-1) out of range of enum */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = -1;				// Fill the educational status section with -1
	result = Add_Account(&Test_EducationalStatus);								    // Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);											// Cleanup DB if it added by wrong


	/* Trying to fill educational status with (8) out of range of enum */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = 8;				// Fill the educational status section with 8
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);											// Cleanup DB if it added by wrong

}


/************************************************************************************
* Test ID                : 9
* Test Case				 : Add Account (vaild educational status)
* Description            : Testing the Add Account Functionality by adding vaild educational status
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                        1- Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                        2- Educational_Status           -> Faculty_Student
*                        3- Educational_Status           -> Graduate
*                        4- Educational_Status           -> Masters_Student
*                        5- Educational_Status           -> PHD_Student
*                        6- Educational_Status           -> PHD_Holder
*
* Test Expected output   : The DB should be updated with the previous inputs
* Reason                 : becuase educational status inputs are in vaild format
* Bug Found              : None
*************************************************************************************/
static void TestCase_VaildEducationalStatus(void)
{
	struct User_Input_Type Test_EducationalStatus = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Trying to fill educational status with Student */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = Student;			// Fill the educational status section with Student
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);											// Cleanup DB


	/* Trying to fill educational status with Faculty_Student */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = Faculty_Student;	// Fill the educational status section with Faculty_Student
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);											// Cleanup DB


	/* Trying to fill educational status with Graduate */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = Graduate;			// Fill the educational status section with Graduate
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);											// Cleanup DB


	/* Trying to fill educational status with Masters_Student */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = Masters_Student;	// Fill the educational status section with Masters_Student
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);											// Cleanup DB


	/* Trying to fill educational status with PHD_Student */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = PHD_Student;		// Fill the educational status section with PHD_Student
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);											// Cleanup DB


	/* Trying to fill educational status with PHD_Holder */
	Test_EducationalStatus.PersonalInfo_Form.educational_status = PHD_Holder;		// Fill the educational status section with PHD_Holder
	result = Add_Account(&Test_EducationalStatus);									// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);											// Cleanup DB

}


/************************************************************************************
* Test ID                : 10
* Test Case				 : Add Account (invaild username)
* Description            : Testing the Add Account Functionality by adding invaild username
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                        -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                        1- UserName                     -> ThisIs33CharactersLong12345678901	(Invalid, 33 chars)
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                        2- UserName                     -> ABCDEFG			(Invalid, 7 chars)
*                        3- UserName                     -> ""			    (Empty)
*
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : UserName length does not meet the required range (8 - 32 characters).
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvaildUsernameBoundaries(void)
{

	struct User_Input_Type Test_UsernameBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Username length just below minimum(8) */
	strcpy(Test_UsernameBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "ABCDEFG");	// Fill username with 7 characters
	result = Add_Account(&Test_UsernameBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															// Cleanup DB if it added by wrong


	/* Username length just above maximum(32) */
	strcpy(Test_UsernameBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "ThisIs33CharactersLong12345678901");	// Fill username with 33 characters
	result = Add_Account(&Test_UsernameBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															// Cleanup DB if it added by wrong


	/* Empty username */
	strcpy(Test_UsernameBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "");			// Fill username with empty string
	result = Add_Account(&Test_UsernameBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															// Cleanup DB if it added by wrong
}


/************************************************************************************
* Test ID                : 11
* Test Case				 : Add Account (vaild username)
* Description            : Testing the Add Account Functionality by adding vaild username
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> Ahmed
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                        1- UserName                     -> AdminUser1	(valid, 10 chars)
*                           Password                     -> Edges123
*                           Password Recheck             -> Edges123
*                        2- UserName                     -> ABCDEFGH	(valid, 8 chars)
*                        3- UserName                     -> ThisIsExactly32CharactersLong123	(valid, 32 chars)
*
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : UserName length meet the required range (8 - 32 characters).
* 
* Bug                    : The username length is 32 but the string is not added.
*************************************************************************************/
static void TestCase_VaildUsernameBoundaries(void)
{
	struct User_Input_Type Test_UsernameBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Username length between Acceptable range 8 - 32 (26) */
	result = Add_Account(&Test_UsernameBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);							// Cleanup DB


	/* Minimum valid username length (8) */
	strcpy(Test_UsernameBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "ABCDEFGH");	// Fill username with 8 characters
	result = Add_Account(&Test_UsernameBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);															// Cleanup DB

	/* Bug found : The username length is 32 but the string is not added
	   The Problem:
	   A 32-character string requires 33 bytes of storage (32 chars + null terminator)
	   strcpy of a 32-character string into a 32-byte buffer overflows and corrupts memory
	   his causes undefined behavior, making the validation fail */

	/* Maximum valid username lenght (32) */
	strcpy(Test_UsernameBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "ThisIsExactly32CharactersLong123");	// Fill username with 8 characters
	result = Add_Account(&Test_UsernameBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);															// Cleanup DB
}


/************************************************************************************
* Test ID                : 12
* Test Case				 : Add Account (invaild password length)
* Description            : Testing the Add Account Functionality by adding invaild password length
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                        -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                        1- Password                     -> ThisIs33CharactersLong12345678901	(Invalid, 33 chars)
*                           Password Recheck             -> Edges123
*                        2- Password                     -> ABCDEFG			(Invalid, 7 chars)
*                        3- Password                     ->	""			    (Empty)
*
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : Password length does not meet the required range (8 - 32 characters).
* Bug Found              : None
*************************************************************************************/
#pragma runtime_checks("s", off)  // Disable stack overflow checks for this test case
static void TestCase_InvaildPasswordLengthBoundaries(void)
{
	struct User_Input_Type Test_PasswordBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function


	/* Password length just above maximum(32) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "ThisIs33CharactersLong12345678901");	// Fill password with 33 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ThisIs33CharactersLong12345678901");
	result = Add_Account(&Test_PasswordBoundaries);														// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);																// Cleanup DB if it added by wrong


	/* Password length just below minimum(8) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "ABCDEFG");			// Fill password with 7 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ABCDEFG");
	result = Add_Account(&Test_PasswordBoundaries);														// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															   // Cleanup DB if it added by wrong


	/* Empty password */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "");		      // Fill password with empty string
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "");
	result = Add_Account(&Test_PasswordBoundaries);													  // Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															 // Cleanup DB if it added by wrong
}
#pragma runtime_checks("s", restore)  // Re-enable checks stack overflow


/************************************************************************************
* Test ID                : 13
* Test Case				 : Add Account (vaild password length)
* Description            : Testing the Add Account Functionality by adding vaild password length
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> Ahmed
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                        1- Password                     -> Edges12345  (valid, 10 chars)
*                           Password Recheck             -> Edges12345
*                        2- Password                     -> ABCDEFGH    (valid, 8 chars)
*                        3- Password                     -> ThisIsExactly32CharactersLong123 (valid, 32 chars)
*
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : Password length meets the required range (8 - 32 characters).
* 
* Bug                    : The password length is 32 but the string is not added
*************************************************************************************/
#pragma runtime_checks("s", off)  // Disable stack overflow checks for this test case
static void TestCase_VaildPasswordLengthBoundaries(void)
{
	struct User_Input_Type Test_PasswordBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function
	/* Password length between Acceptable range 8 - 32 (10) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "Edges12345");	// Fill password with 8 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "Edges12345");
	result = Add_Account(&Test_PasswordBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);							// Cleanup DB


	/* Minimum valid password length (8) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "ABCDEFGH");	// Fill password with 8 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ABCDEFGH");
	result = Add_Account(&Test_PasswordBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);															 // Cleanup DB


	/* Bug found : The password length is 32 but the string is not added
	The Problem:
	A 32-character string requires 33 bytes of storage (32 chars + null terminator)
    strcpy of a 32-character string into a 32-byte buffer overflows and corrupts memory
    this causes undefined behavior, making the validation fail */

	/* Maximum valid password length (32) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "ThisIsExactly32CharactersLong123");	// Fill password with 32 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ThisIsExactly32CharactersLong123");
	result = Add_Account(&Test_PasswordBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);															 // Cleanup DB

}
#pragma runtime_checks("s", restore)  // Re-enable checks stack overflow


/************************************************************************************
* Test ID                : 14
* Test Case				 : Add Account Functionality
* Description            : Testing the Add Account Functionality by adding invaild password Recheck length
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                        -> AhmedFIRST
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> ThisIs33CharactersLong12345678901	
*                        1- Password Recheck             -> ThisIs33CharactersLong12345678901	(Invalid, 33 chars)
*                        2- UserName                     -> ABCDEFG			(Invalid, 7 chars)
*                        3- UserName                     ->	""			    (Empty)
*
* Test Expected output   : The DB shouldn't be updated with the previous inputs
* Reason                 : Password Recheck length does not meet the required range (8 - 32 characters).
* Bug Found              : None
*************************************************************************************/
#pragma runtime_checks("s", off)  // Disable stack overflow checks for this test case
static void TestCase_InvaildPasswordREcheckLengthBoundaries(void)
{
	struct User_Input_Type Test_PasswordBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function


	/* Password length just above maximum(32) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.User_Name, "ThisIs33CharactersLong12345678901");	// Fill password with 33 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ThisIs33CharactersLong12345678901");
	result = Add_Account(&Test_PasswordBoundaries);														// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);																// Cleanup DB if it added by wrong


	/* Password length just below minimum(8) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "ABCDEFG");			// Fill password with 7 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ABCDEFG");
	result = Add_Account(&Test_PasswordBoundaries);														// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															   // Cleanup DB if it added by wrong


	/* Empty password */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "");		      // Fill password with empty string
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "");
	result = Add_Account(&Test_PasswordBoundaries);													  // Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);															 // Cleanup DB if it added by wrong
}
#pragma runtime_checks("s", restore)  // Re-enable checks stack overflow


/************************************************************************************
* Test ID                : 15
* Test Case				 : Add Account (vaild password recheck length)
* Description            : Testing the Add Account Functionality by adding vaild password Recheck length
* 
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                           Name                         -> Ahmed
*                           Age                          -> 26
*                           DOB_day                      -> 1
*                           DOB_Month                    -> 2
*                           DOB_Year                     -> 1998
*						    Gender                       -> Male
*                           Educational_Status           -> Student
*                           UserName                     -> AdminUser1
*                           Password                     -> Edges12345  
*                        1- Password Recheck             -> Edges12345	(valid, 10 chars)
*                        2- Password                     -> ABCDEFGH    (valid, 8 chars)
*                        3- Password                     -> ThisIsExactly32CharactersLong123 (valid, 32 chars)
*
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : Password Recheck length meets the required range (8 - 32 characters).
* 
* Bug                    : The password Recheck length is 32 but the string is not added.
*************************************************************************************/
#pragma runtime_checks("s", off)  // Disable stack overflow checks for this test case
static void TestCase_VaildPasswordREcheckLengthBoundaries(void)
{
	struct User_Input_Type Test_PasswordBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function
	/* Password length between Acceptable range 8 - 32 (10) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "Edges12345");	// Fill password with 8 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "Edges12345");
	result = Add_Account(&Test_PasswordBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);							// Cleanup DB


	/* Minimum valid password length (8) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "ABCDEFGH");	// Fill password with 8 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ABCDEFGH");
	result = Add_Account(&Test_PasswordBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);															 // Cleanup DB


	/* Bug found : The password Recheck length is 32 but the string is not added
	The Problem:
	A 32-character string requires 33 bytes of storage (32 chars + null terminator)
	strcpy of a 32-character string into a 32-byte buffer overflows and corrupts memory
	this causes undefined behavior, making the validation fail */

	/* Maximum valid password length (32) */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.LoginCredentials.Password, "ThisIsExactly32CharactersLong123");	// Fill password with 32 characters
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "ThisIsExactly32CharactersLong123");
	result = Add_Account(&Test_PasswordBoundaries);													// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);															 // Cleanup DB

}
#pragma runtime_checks("s", restore)  // Re-enable checks stack overflow


/************************************************************************************
* Test ID                : 16
* Test Case				 : Add Account (password and Password Recheck doesnt matched)
* Description            : Testing the Add Account Functionality by make password and
*						   Password Recheck doesnt matched
* 
* Technique              : Decision Table Testing
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                          Name                         -> AhmedFIRST
*                          Age                          -> 26
*                          DOB_day                      -> 01
*                          DOB_Month                    -> 02
*                          DOB_Year                     -> 1998
*                          Educational_Status           -> Student
*                          Gender                       -> Male
*                          UserName                     -> AdminUser1
*                          Password                     -> Edges123
*                          Password Recheck             -> differentPass
*
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : Password and Password Recheck doesnt match each other.
* Bug Found              : None
*************************************************************************************/
static void TestCase_InVaildPasswordAndPasswordREcheck(void)
{
	struct User_Input_Type Test_PasswordBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function

	/* Password and Password Recheck doesnt match each other */
	strcpy(Test_PasswordBoundaries.LoginCredentials_Form.Password_Recheck, "differentPass");
	result = Add_Account(&Test_PasswordBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, FALSE);
	Delete_Account(current_user_test - 1);							// Cleanup DB if it added by wrong
}


/************************************************************************************
* Test ID                : 17
* Test Case				 : Add Account (password and Password Recheck matched)
* Description            : Testing the Add Account Functionality by make password and 
*						   Password Recheck matched
* 
* Technique              : Decision Table Testing
* Pre-requisits          : There is a User Assigned to DB
* Test inputs            :
*                          Name                         -> AhmedFIRST
*                          Age                          -> 26
*                          DOB_day                      -> 01
*                          DOB_Month                    -> 02
*                          DOB_Year                     -> 1998
*                          Educational_Status           -> Student
*                          Gender                       -> Male
*                          UserName                     -> AdminUser1
*                          Password                     -> Edges123		(Vaild)
*                          Password Recheck             -> Edges123		(Vaild)
*
* Test Expected output   : The DB should be updated with the previous inputs correctly
* Reason                 : Password and Password Recheck match each other.
* Bug Found              : None
*************************************************************************************/
static void TestCase_VaildPasswordAndPasswordREcheck(void)
{
	struct User_Input_Type Test_PasswordBoundaries = Test_GeneralUser1;
	unsigned char result = NULL;								// Variable to store return of add account function
	
	/* Password and Password Recheck match each other */
	result = Add_Account(&Test_PasswordBoundaries);					// Store return of funtion add account
	DBM_PrintUsers();
	CU_ASSERT_EQUAL(result, TRUE);
	Delete_Account(current_user_test - 1);							// Cleanup DB
}


/************************************************************************************
* Test ID                : 18
* Test Case				 : Add Account (adding extera user above Maximum user 5)
* Description            : Testing the Add Account Functionality by adding extera user
*						   above Maximum user (5)
* 
* technique              : Equivalence Partitioning
* Pre-requisits          : There is a 5 User Assigned to DB
* Test inputs            :
*                         1- Name                         -> AhmedFIRST
*                            Age                          -> 26
*                            DOB_day                      -> 01
*                            DOB_Month                    -> 02
*                            DOB_Year                     -> 1998
*                            Educational_Status           -> Student
*                            Gender                       -> Male
*                            UserName                     -> AdminUser1
*                            Password                     -> Edges123
*                            Password Recheck             -> Edges123
*
*                         2- Name                         -> AhmedSECOND
*                            Age                          -> 26
*                            DOB_day                      -> 01
*                            DOB_Month                    -> 02
*                            DOB_Year                     -> 1998
*                            Educational_Status           -> Student
*                            Gender                       -> Male
*                            UserName                     -> AdminUser1
*                            Password                     -> Edges123
*                            Password Recheck             -> Edges123
* 
*                         3- Name                         -> AhmedTHIRD
*                            Age                          -> 26
*                            DOB_day                      -> 01
*                            DOB_Month                    -> 02
*                            DOB_Year                     -> 1998
*                            Educational_Status           -> Student
*                            Gender                       -> Male
*                            UserName                     -> AdminUser1
*                            Password                     -> Edges123
*                            Password Recheck             -> Edges123
* 
*                         4- Name                         -> AhmedFOURTH
*                            Age                          -> 26
*                            DOB_day                      -> 01
*                            DOB_Month                    -> 02
*                            DOB_Year                     -> 1998
*                            Educational_Status           -> Student
*                            Gender                       -> Male
*                            UserName                     -> AdminUser1
*                            Password                     -> Edges123
*                            Password Recheck             -> Edges123
* 
*                         5- Name                         -> AhmedFITH
*                            Age                          -> 26
*                            DOB_day                      -> 01
*                            DOB_Month                    -> 02
*                            DOB_Year                     -> 1998
*                            Educational_Status           -> Student
*                            Gender                       -> Male
*                            UserName                     -> AdminUser1
*                            Password                     -> Edges123
*                            Password Recheck             -> Edges123
* 
*                         6- Name                         -> Ahmed
*                            Age                          -> 26
*                            DOB_day                      -> 01
*                            DOB_Month                    -> 02
*                            DOB_Year                     -> 1999
*                            Educational_Status           -> Masters_Student
*                            Gender                       -> Male
*                            UserName                     -> EdgesAcademy
*                            Password                     -> Edges123
*                            Password Recheck             -> Edges123
* 
* Test Expected output   : The DB shouldn't be updated with the user input number 6
* Reason                 : Becasue DB can hold only 5 users only.
* 
* Bug					 : The function Add_Account return TRUE even if the user not added to DB
*************************************************************************************/
static void TestCase_AddingUserToFullDB(void)
{
	/* Adding 5 users to DB */
	Add_Account(&Test_GeneralUser1);
	Add_Account(&Test_GeneralUser2);
	Add_Account(&Test_GeneralUser3);
	Add_Account(&Test_GeneralUser4);
	Add_Account(&Test_GeneralUser5);

	DBM_PrintUsers();

	/* Bug Found:
	 * User number 6 didnt added to DB as expecpted but the function add account return True and that indicate
	 * thats all things right and bug found in this line of code
	 * 	else
	 *	{
	 *		DBM_Add_User(Form);
	 *		RET = TRUE;
	 *	}
	 * 
	 * should return value of function DBM_Add_User hold in variable RET to make sure that add account return false
	 * when user not adding to DB and the code should be like that
	 * 
	 * 	else
	 *	{
	 *		RET = DBM_Add_User(Form);
	 *	}
	 */
	unsigned char result = NULL;								// Variable to store return of add account function
	result = Add_Account(&Test_User1_ExpectedFormSent);
	CU_ASSERT_EQUAL(result, FALSE);

	/* Delete all users */
	Delete_Account(0);
	Delete_Account(0);
	Delete_Account(0);
	Delete_Account(0);
	Delete_Account(0);

	DBM_PrintUsers();
}


/*************************************************************************************/


/* Test Case for Suite 2 (Delete Account Functionality) */
/************************************************************************************
* Test ID                : 19
* Test Case				 : Delete Account (vaild and invaild user ID)
* Description            : Verifies correct behavior of account deletion for both valid and 
*						   invalid user IDs.
* 
* Pre-requisits          : There is atleast 3 Users Assigned to DB
* Test inputs            : 5 General users (Correct format)
* 
* Test Cases Steps:
*  1. Attempt to delete with invalid negative ID (-1)
*  2. Attempt to delete with invalid out-of-range ID (6)
*  3. Delete first valid user ID (0)
*  4. Delete last valid user ID (5)
* 
* Expected Results:
*  1. Invalid IDs should return FALSE
*  2. Valid IDs should return TRUE and remove the user
* 
* Reason                 : Delete Account Function should delete user crossponding to his vaild ID 
* 
* Bug					 : When trying to delete user with ID = 6 the function return TRUE and delete user with ID = 5
*************************************************************************************/
static void TestCase_Delete_Account(void)
{
	/* Note: Max user allowed is 5 users */
	char Test_User_id = NULL;	// Variable to store user ID
	/* Adding 5 users to DB */
	Add_Account(&Test_GeneralUser1);
	Add_Account(&Test_GeneralUser2);
	Add_Account(&Test_GeneralUser3);
	Add_Account(&Test_GeneralUser4);
	Add_Account(&Test_GeneralUser5);

	DBM_PrintUsers();

	/* Trying to delete user with Invaild ID */
	Test_User_id = -1;	// invalid user ID= -1
	char RET_ID_1 = Delete_Account(Test_User_id - 1);	// invalid negative ID= -1

	Test_User_id = 0;	// valid user ID= 0
	char RET_ID0 = Delete_Account(Test_User_id - 1);	// valid user ID= 0


	/* Bug found:
	 * since max user allowed in system is 5 users and after we try id = 6 function Delete_Account
	 * returned TRUE not FALSE as expected becuse condition in if not correct 
	 * wrong condition:
	 * if (user_id < 0 || user_id > MAX_USERS)
	 *	{
	 *		RET = FALSE;
	 *	}
	 * 
	 * and should be like this:
	 * if (user_id < 0 || user_id >= MAX_USERS)
	 *	{
	 *		RET = FALSE;
	 *	}*/
	Test_User_id = 6;	// invalid user ID= 6
	char RET_ID6 = Delete_Account(Test_User_id - 1);	    // invalid out-of-range ID= 6




	/* Trying to delete user with vaild ID */
	Test_User_id = 1;	// valid user ID= 1
	char RET_ID1 = Delete_Account(Test_User_id - 1);	// valid user ID= 0

	Test_User_id = 5;	// valid user ID= 5
	char RET_ID5 = Delete_Account(Test_User_id - 1);	// valid user ID= 5

	CU_ASSERT_EQUAL(RET_ID_1, FALSE);
	CU_ASSERT_EQUAL(RET_ID0, FALSE);
	CU_ASSERT_EQUAL(RET_ID6, FALSE);
	CU_ASSERT_EQUAL(RET_ID1, TRUE);
	CU_ASSERT_EQUAL(RET_ID5, TRUE);

	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);

	DBM_PrintUsers();
}


/*************************************************************************************/


/* Test Case for Suite 3 (Get Number Of Days Functionality) */
/************************************************************************************
* Test ID                : 20
* Test Case				 : Get number of days (months with 31 days (non-leap year and leap year))
* Description            : Verifies correct behavior of Get number of days for all month
*						   with 31 days (non-leap year and leap year)
* 
* technique              : Equivalence Partitioning
* Pre-requisits          : None
* Test inputs            : Months that end with 30 days and Years (leap & non-leap)
*
* Expected Results		 : Get number of days Function should return 31
*
* Reason                 : as all input month end with 31 days.
* Bug Found              : None
*************************************************************************************/
static void TestCase_GetNumberOfDays_31DayMonths(void)
{
	// Test months with 31 days (non-leap year)
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(1, 2023) , 31 );  // January
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(3, 2023) , 31 );  // March
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(5, 2023) , 31 );  // May
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(7, 2023) , 31 );  // July
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(8, 2023) , 31 );  // August
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(10, 2023) , 31 ); // October
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(12, 2023) , 31 ); // December

	// Test months with 31 days (leap year)
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(1, 2024) , 31 );  // January
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(3, 2024) , 31 );  // March
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(5, 2024) , 31 );  // May
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(7, 2024) , 31 );  // July
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(8, 2024) , 31 );  // August
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(10, 2024) , 31 ); // October
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(12, 2024) , 31 ); // December
}


/************************************************************************************
* Test ID                : 21
* Test Case				 : Get number of days (months with 30 days (non-leap year and leap year))
* Description            : Verifies correct behavior of Get number of days for all month
*						   with 30 days (non-leap year and leap year)
*
* technique              : Equivalence Partitioning
* Pre-requisits          : None
* Test inputs            : Months that end with 30 days and Years (leap & non-leap)
*
* Expected Results		 : Get number of days Function should return 30
*
* Reason                 : as all input month end with 30 days.
* Bug Found              : None
*************************************************************************************/
static void TestCase_GetNumberOfDays_30DayMonths(void)
{
	// Test all months with 30 days (non-leap year)
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(4, 2023) , 30 );  // April
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(6, 2023) , 30 );  // June
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(9, 2023) , 30 );  // September
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(11, 2023) , 30 ); // November

	// Test all months with 30 days (leap year)
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(4, 2024) , 30 );  // April
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(6, 2024) , 30 );  // June
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(9, 2024) , 30 );  // September
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(11, 2024) , 30 ); // November
}


/************************************************************************************
* Test ID                : 22
* Test Case				 : Get number of days (month with february (non-leap year and leap year))
* Description            : Verifies correct behavior of Get number of days for with month
*						   february (non-leap year and leap year)
*
* technique              : Equivalence Partitioning
* Pre-requisits          : None
* Test inputs            : Month (february) and Year (leap & non-leap)
*
* Expected Results		 : Get number of days Function should return 28 with non-leap year
*						   and 29 with leap year
*
* Reason                 : as february month end with 28 with non-leap and 29 with leap year
* Bug Found              : None
*************************************************************************************/
static void TestCase_GetNumberOfDays_February(void)
{
	// Non-leap years
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 2023) , 28 ); // Regular non-leap
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 1900) , 28 ); // Century non-leap

	// Leap years
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 2024) , 29 ); // Regular leap
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 2000) , 29 ); // Century leap

	// Boundary years
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 1924) , 29 ); // Min range leap
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 2024) , 29 ); // Max range leap
}


/************************************************************************************
* Test ID                : 23
* Test Case				 : Get number of days (invaild days)
* Description            : Verifies correct behavior of Get number of days when input is invaild
*
* Technique              : Equivalence Partitioning
* Pre-requisits          : None
* Test inputs            : Months and Years
*
* Expected Results		 : Get number of days Function should return 0
*
* Reason                 : as all input month and year are invaild.
* Bug Found              : None
*************************************************************************************/
static void TestCase_GetNumberOfDays_InvaildInputs(void)
{
	// Test invalid month numbers
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(0, 2023) , 0 );   // Month too low
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(13, 2023 ) , 0 );  // Month too high
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(255, 2023) , 0 ); // Extreme invalid

	// Test year outside range (though function doesn't enforce this)
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 1923) , 28 );  // Below min
	CU_ASSERT_EQUAL( Test_Get_Number_OfDays(2, 2025) , 28 );  // Above max
}


/*************************************************************************************/


/* Test Case for Suite 4 (Show Student Courses Functionality) */

/************************************************************************************
* Test ID                : 24
* Test Case				 : Show Student Courses (ID input is invaild)
* Description            : Verifies correct behavior of Show Student Courses when ID input is invaild.
*
* Technique              : Equivalence Partitioning
* Pre-requisits          : There is a at least User Assigned to DB.
* Test inputs            : assign User with ID = -1 to DB and enrolled in course id = 1 (Standard_Diploma) & 2 (AUTOSAR_Diploma)
*                          assign User with ID = 0 to DB and enrolled in course id = 3 (ARM_Diploma) & 4 (RTOS_Diploma)
*                          assign User with ID = 6 to DB and enrolled in course id = 5 (Testing_Diploma) & 6 (EmbeddedLinux_Diploma)
*
* Expected Results		 : Should be printed "Invalid User Id".
* Reason                 : Because ID input to function is invaild.
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvalidUserIDs(void)
{
	/* Note:
	 * Max user allowed is 5 users
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;				// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function


	Test_User_id = -1;											// valid user ID = -1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = -1 to user 1
	/* Adding user 1 to course id = 1 & 2 */
	DBM_AddToCourse(1, Test_GeneralUser1.PersonalInfo_Form.id);	// Standard_Diploma (1)
	DBM_AddToCourse(2, Test_GeneralUser1.PersonalInfo_Form.id);	// AUTOSAR_Diploma  (2)
	result = ShowStudentCourses(Test_GeneralUser1.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, FALSE);
	printf("\n\n");


	Test_User_id = 0;											// valid user ID = 0
	DBM_Add_User(&Test_GeneralUser2);							// Add user 2 to DB
	Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 0 to user 2
	/* Adding user 2 to course id = 3 & 4 */
	DBM_AddToCourse(3, Test_GeneralUser2.PersonalInfo_Form.id);	// ARM_Diploma  (3)
	DBM_AddToCourse(4, Test_GeneralUser2.PersonalInfo_Form.id);	// RTOS_Diploma (4)
	result = ShowStudentCourses(Test_GeneralUser2.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, FALSE);
	printf("\n\n");


	Test_User_id = 6;											// valid user ID = 6
	DBM_Add_User(&Test_GeneralUser5);							// Add user 5 to DB
	Test_GeneralUser5.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 6 to user 3
	/* Adding user 3 to course id = 5 & 6 */
	DBM_AddToCourse(5, Test_GeneralUser5.PersonalInfo_Form.id);	// Testing_Diploma (5)
	DBM_AddToCourse(6, Test_GeneralUser5.PersonalInfo_Form.id);	// EmbeddedLinux_Diploma (6)
	result = ShowStudentCourses(Test_GeneralUser5.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, FALSE);
	printf("\n\n");

	/* Delete all users if it added by mistake */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
}


/************************************************************************************
* Test ID                : 25
* Test Case				 : Show Student Courses (ID input is vaild ).
* Description            : Verifies correct behavior of Show Student Courses when input in correct format.
*
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a at least User Assigned to DB.
* Test inputs            : assign User with ID = 1 to DB and enrolled in course id = 1 (Standard_Diploma) & 2 (AUTOSAR_Diploma)
*                          assign User with ID = 2 to DB and enrolled in course id = 3 (ARM_Diploma) & 4 (RTOS_Diploma)
*                          assign User with ID = 5 to DB and enrolled in course id = 5 (Testing_Diploma) & 6 (EmbeddedLinux_Diploma)
*
* Expected Results		 : Shows the Courses enrolled in for a specific Student.
* Reason                 : Because ID input to function is vaild.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidUserIDs(void)
{
	/* Note:
	 * Max user allowed is 5 users
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;				// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function


	Test_User_id = 1;											// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 1 to user 1
	/* Adding user 1 to course id = 1 & 2 */
	DBM_AddToCourse(1, Test_GeneralUser1.PersonalInfo_Form.id);	// Standard_Diploma (1)
	DBM_AddToCourse(2, Test_GeneralUser1.PersonalInfo_Form.id);	// AUTOSAR_Diploma  (2)
	result = ShowStudentCourses(Test_GeneralUser1.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, TRUE);
	printf("\n\n");


	Test_User_id = 2;											// valid user ID = 2
	DBM_Add_User(&Test_GeneralUser2);							// Add user 2 to DB
	Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 2 to user 2
	/* Adding user 2 to course id = 3 & 4 */
	DBM_AddToCourse(3, Test_GeneralUser2.PersonalInfo_Form.id);	// ARM_Diploma  (3)
	DBM_AddToCourse(4, Test_GeneralUser2.PersonalInfo_Form.id);	// RTOS_Diploma (4)
	result = ShowStudentCourses(Test_GeneralUser2.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, TRUE);
	printf("\n\n");


	Test_User_id = 5;											// valid user ID = 5
	DBM_Add_User(&Test_GeneralUser5);							// Add user 5 to DB
	Test_GeneralUser5.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 5 to user 5
	/* Adding user 5 to course id = 5 & 6 */
	DBM_AddToCourse(5, Test_GeneralUser5.PersonalInfo_Form.id);	// Testing_Diploma (5)
	DBM_AddToCourse(6, Test_GeneralUser5.PersonalInfo_Form.id);	// EmbeddedLinux_Diploma (6)
	result = ShowStudentCourses(Test_GeneralUser5.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, TRUE);
	printf("\n\n");


	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
}


/************************************************************************************
* Test ID                : 26
* Test Case				 : Show Student Courses (vaild user but no courses register yet)
* Description            : Verifies correct behavior of Show Student Courses when input is vaild user but 
*						   wiht no courses register yet.
*
* Technique              : Equivalence Partitioning
* Pre-requisits          : There is a at least User Assigned to DB.
* Test inputs            : assign User with ID = 1 to DB and leave it without any enrolled in any courses. 
* 
* Expected Results		 : Should be printed "You Are Currently Enrolled in:" and not showing any courses.
* 
* Reason                 : Because ID input to function is vaild and its lead to that printed but since there is no
*						   registeration for any courses there will not showing any courses.
* 
* Defects               : The function should print a massage like "You Are Currently not register to any courses yet"
*						  when there is no courses registeration.
*************************************************************************************/
static void TestCase_ValidUserNoCourses(void)
{
	/* Note:
	 * Max user allowed is 5 users
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;				// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function


	Test_User_id = 1;											// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 1 to user 1

	result = ShowStudentCourses(Test_GeneralUser1.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, FALSE);

	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
}


/*************************************************************************************/


/* Test case for suite 5 (Add Student To Course Functionality) */

/************************************************************************************
* Test ID                : 27
* Test Case				 : Add Student To Course (Vaild user and vaild course).
* Description            : Verifies correct behavior of Add Student To Course Function when input in correct format.
*
* Technique              : Decision Table Testing
* Pre-requisits          : There is a at least User Assigned to DB.
* Test inputs            : assign User with ID = 1 to DB and enrolled in course id = 1 (Standard_Diploma) & 2 (AUTOSAR_Diploma)
*
* Expected Results		 : Function should retun Enrolled.
* Reason                 : Because this first registration for this user with id 1.
* Bug Found              : None
*************************************************************************************/
static void TestCase_AddStudentToCourse_ValidID(void)
{
	/* Note: 
	 * Max user allowed is 5 users
	 * MAX students per course = 5
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;									// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function
	unsigned char Course_ID = NULL;								// Variable to store course ID

	Test_User_id = 1;											// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 1 to user 1
	Course_ID = 1;												// Standard_Diploma (1)
	result = AddStudentToCourse(Course_ID, Test_GeneralUser1.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = 1
	CU_ASSERT_EQUAL(result, Enrolled);

	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
}


/************************************************************************************
* Test ID                : 28
* Test Case				 : Add Student To Course (Invaild user and valid course).
* Description            : Verifies correct behavior of Add Student To Course Function when input user ID invaild.
*
* Technique              : Boundary Value Analysis
* Pre-requisits          : There is a at least User Assigned to DB.
* 
* Test inputs            : assign User with ID = -1 to DB and enrolled in course id = 1 (Standard_Diploma) & 2 (AUTOSAR_Diploma)
*						   assign User with ID = 0 to DB and enrolled in course id = 1 (Standard_Diploma) & 2 (AUTOSAR_Diploma)
* 					       assign User with ID = 6 to DB and enrolled in course id = 1 (Standard_Diploma) & 2 (AUTOSAR_Diploma)
* 
* Expected Results		 : Function shouldnt add any courses to any IDs (-1,0,6) that provided in input.
* Reason                 : Because this these IDs all Invaild.
* 
* Bug					 : The function AddStudentToCourse return Enrolled even if the user ID (above maximum users) is invaild.
* 
* Error                  : When ID input was = -1 or 0 that lead to system crashed (Run Time Error).
*************************************************************************************/
static void TestCase_AddStudentToCourse_InvalidID(void)
{
	/* Note:
	 * Max user allowed is 5 users
	 * MAX students per course = 5
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;									// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function
	unsigned char Course_ID = NULL;								// Variable to store course ID

    /* Error Found:
	 * when tying to add use with id = -1 this lead to system crashed (Run Time Error)
	 * becasue this line in code:
	 *
	 * if (Enrollments[Student_id][Course_id-1] == TRUE)
	 *
	 * that line cased the system to crash because Student_id = -2 result from our input from these two line
	 *
	 * Test_User_id = -1;
	 * Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;
	 */
	Test_User_id = -1;											// Invalid user ID = -1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = -1 to user 1
	Course_ID = 1;												// Standard_Diploma (1)
	/* Next line lead to RTE */
	result = AddStudentToCourse(Course_ID, Test_GeneralUser1.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = -1
	

	/* Erro Found:
	 * when tying to add use with id = 0 this lead to system crashed (Run Time Error)
	 * becasue this line in code:
	 * 
	 * if (Enrollments[Student_id][Course_id-1] == TRUE)
	 * 
	 * that line cased the system to crash because Student_id = -1 result from our input from these two line
	 * 
	 * Test_User_id = 0;
	 * Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;
	 */
	Test_User_id = 0;											// Invalid user ID = 0
	DBM_Add_User(&Test_GeneralUser2);							// Add user 2 to DB
	Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 0 to user 2
	Course_ID = 1;												// Standard_Diploma (1)
	/* Next line lead to RTE */
	result = AddStudentToCourse(Course_ID, Test_GeneralUser2.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = 0


	/* Bug found:
	 * The function AddStudentToCourse return Enrolled even if the user ID is invaild and that indicate
	 * that the function not check if the user ID is vaild or not and the code should be like this:
	 *
	 * 	if (user_id < 0 || user_id >= MAX_USERS)
	 *	{
	 *		return Enroll_Failed;
	 *	}
	 */
	Test_User_id = 6;											// Invalid user ID = 6
	DBM_Add_User(&Test_GeneralUser5);							// Add user 5 to DB
	Test_GeneralUser5.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 6 to user 5
	Course_ID = 1;												// Standard_Diploma (1)
	result = AddStudentToCourse(Course_ID, Test_GeneralUser5.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = 6
	
	CU_ASSERT_EQUAL(result, Enrolled);	
	/*
	 * This assertion will not fail becuse the function AddStudentToCourse return Enrolled
	 * even if the user ID is invaild and that indicate that the function not check if the user ID is vaild or not
	 */


	 /* Delete all users if it added by mistake */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
}


/************************************************************************************
* Test ID                : 29
* Test Case				 : Add Student To Course (vaild user and invaild course).
* Description            : Verifies correct behavior of Add Student To Course Function when input courses ID invaild.
*
* Technique              : Equivalence Partitioning
* Pre-requisits          : There is a at least User Assigned to DB.
* Test inputs            : assign User with ID = 1 to DB and enrolled in course id = 0
*						   assign User with ID = 2 to DB and enrolled in course id = 7 
* 
* Expected Results		 : Function shouldnt add any courses (0,7) to any ID that provided in input.
* Reason                 : Because these courses IDs all Invaild.
*
* Bug					 : The function AddStudentToCourse return CapacityCompleted even if the course ID (above maximum courses) is invaild.
*
* Error                  : When ID input was = 0 or 7 that lead to system crashed (Run Time Error).
*************************************************************************************/
static void TestCase_AddStudentToCourse_InvalidCoursesID(void)
{
	/* Note:
	 * Max user allowed is 5 users
	 * MAX students per course = 5
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;									// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function
	unsigned char Course_ID = NULL;								// Variable to store course ID

	/* Error Found:
	 * when tying to add use with course id = 0 this lead to system crashed (Run Time Error)
	 * becasue this line in code:
	 *
	 * if (Enrollments[Student_id][Course_id-1] == TRUE)
	 *
	 * that line cased the system to crash because Course_id = -1 result from our input from these two line
	 *
	 * Test_User_id = 1;
	 * Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;
	 */
	Test_User_id = 1;												// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);								// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;		// Assigning ID = 1 to user 1
	Course_ID = 0;													// Invalid course ID = 0
	/* Next line lead to RTE */
	AddStudentToCourse(Course_ID, Test_GeneralUser1.PersonalInfo_Form.id);


	/* Bug found:
	 * The function AddStudentToCourse return CapacityCompleted even if the course ID is invaild (above maximu courses) 
	 * and that indicate that the function not check if the course ID is vaild or not and the code should be like this:
	 *
	 * 	if ( (Course_id - 1) < 1 || (Course_id - 1) > MAX_COURSES )
	 *	{
	 *		return InvalidCourseID; // Invalid Course_id
	 *	}
	 */
	Test_User_id = 2;												// valid user ID = 2
	DBM_Add_User(&Test_GeneralUser2);								// Add user 2 to DB
	Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;		// Assigning ID = 2 to user 2
	Course_ID = 7;													// Invalid course ID = 7
	result = AddStudentToCourse(Course_ID, Test_GeneralUser2.PersonalInfo_Form.id);
	CU_ASSERT_EQUAL(result, CapacityCompleted);
	/* This assertion will not fail becuse the function AddStudentToCourse return CapacityCompleted
	 * even if the course ID is invaild and that indicate that the function not check if the course ID is vaild or not
	 */

	 /* Delete all users if it added by mistake */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);

}


/************************************************************************************
* Test ID                : 30
* Test Case				 : Add Student To Course Functionality.
* Description            : Verifies correct behavior of Add Student To Course Function when all inputs are vaild.
*
* Technique              : Decision Table Testing
* Pre-requisits          : There is a at least User Assigned to DB.
* Test inputs            : assign User with ID = 1 to DB and enrolled in course id = 1 (Standard_Diploma)
* 						   assign User with ID = 2 to DB and enrolled in course id = 1 (Standard_Diploma)
*
* Expected Results		 : Function should return Enrolled at first registration for this user with id 1for corse id 1.
*						   and AlreadyEnrolled at second registration for this user with id 1 for corse id 1.
*						   and CapacityCompleted at registration for this user with id 2 for corse id 1.
*
* Reason                 : Because this first registration for this user with id 1 for corse id 1.
* 					       and AlreadyEnrolled at second registration for this user with id 1 for corse id 1.
* 					       and CapacityCompleted at registration for this user with id 2 for corse id 1.
* 
* Bug Found              : None
*************************************************************************************/
static void TestCase_AddStudentToCourse_ValidUser(void)
{
	/* Note:
	 * Max user allowed is 5 users
	 * MAX students per course = 5
	 * course id = 1 (Standard_Diploma)
	 * course id = 2 (AUTOSAR_Diploma)
	 * course id = 3 (ARM_Diploma)
	 * course id = 4 (RTOS_Diploma)
	 * course id = 5 (Testing_Diploma)
	 * course id = 6 (EmbeddedLinux_Diploma)
	 */
	char Test_User_id = NULL;									// Variable to store user ID
	unsigned char result = NULL;								// Variable to store return of add account function
	unsigned char Course_ID = NULL;								// Variable to store course ID

	Test_User_id = 1;											// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 1 to user 1
	Course_ID = 1;												// valid course ID = 1

	result = AddStudentToCourse(Course_ID, Test_GeneralUser1.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = 1
	CU_ASSERT_EQUAL(result, Enrolled);



	result = AddStudentToCourse(Course_ID, Test_GeneralUser1.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = 1
	CU_ASSERT_EQUAL(result, AlreadyEnrolled);



	ListofCourse[Course_ID - 1].NumberOfEnrolledStudents = 5;		// Make Standard Diploma course full capacity.
	Test_User_id = 2;											// valid user ID = 2
	DBM_Add_User(&Test_GeneralUser2);							// Add user 2 to DB
	Test_GeneralUser2.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 2 to user 2

	result = AddStudentToCourse(Course_ID, Test_GeneralUser2.PersonalInfo_Form.id);	// Standard_Diploma  (1) , user ID = 2
	CU_ASSERT_EQUAL(result, CapacityCompleted);

	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
	Delete_Account(Test_User_id - 1);
}


 /*************************************************************************************/


/* Test case for suite 6 (Detect User Type Functionality) */


/*************************************************************************************
* Test ID                : 31
* Test Case              : Valid Admin Input
* Description            : Tests if the function (Detect User Type) correctly identifies an admin user.
* 
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : User_Type = 0
* 
* Expected Results       : The function should return AdminMohamedTarek
* Reason                 : The input matches the value for AdminMohamedTarek in the enum.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidAdminInput(void)
{
	/* Note:
	 * User Type (AdminMohamedTarek) = 0
	 * User Type (NormalUser) = 1
	 * User Type (IncorrectLogin) = 2
	 */

	unsigned char result = NULL;					// Variable to store return of Detect User Type function.

	redirect_input("0\n");							// Redirect input to simulate user input == scanf("%d", &User_Type); and User_Type = 0.
	result = Detect_User_Type();					// store return of function.
	restore_stdin();								// Restore standard input after redirection.
	CU_ASSERT_EQUAL(result, AdminMohamedTarek);
}


/************************************************************************************
* Test ID                : 32
* Test Case              : Valid Normal User Input
* Description            : Tests if the function (Detect User Type) correctly identifies a normal user.
* 
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : User_Type = 1
* 
* Expected Results       : The function should return NormalUser
* Reason                 : The input matches the value for NormalUser in the enum.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidNormalUserInput(void)
{
	/* Note:
	 * User Type (AdminMohamedTarek) = 0
	 * User Type (NormalUser) = 1
	 * User Type (IncorrectLogin) = 2
	 */

	unsigned char result = NULL;				// Variable to store return of Detect User Type function.

	redirect_input("1\n");						// Redirect input to simulate user input == scanf("%d", &User_Type); and User_Type = 1.
	result = Detect_User_Type();				// store return of function.
	restore_stdin();								// Restore standard input after redirection.
	CU_ASSERT_EQUAL(result, NormalUser);
}


/************************************************************************************
* Test ID                : 33
* Test Case              : Valid IncorrectLogin.
* Description            : Tests if the function correctly identifies IncorrectLogin.
* 
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : User_Type = 2
* 
* Expected Results       : The function should return IncorrectLogin
* Reason                 : The input matches the value for IncorrectLogin in the enum.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidIncorrectLogin(void)
{
	/* Note:
	 * User Type (AdminMohamedTarek) = 0
	 * User Type (NormalUser) = 1
	 * User Type (IncorrectLogin) = 2
	 */
	unsigned char result = NULL;				// Variable to store return of Detect User Type function.

	redirect_input("2\n");						// Redirect input to simulate user input == scanf("%d", &User_Type); and User_Type = 2.
	result = Detect_User_Type();				// store return of function.
	restore_stdin();								// Restore standard input after redirection.
	CU_ASSERT_EQUAL(result, IncorrectLogin);
}


/************************************************************************************
* Test ID                : 34
* Test Case              : Invalid Input (Negative Number)
* Description            : Tests if the function (Detect User Type) correctly handles negative numbers.
* 
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : User_Type = -1
* 
* Expected Results       : The function should return IncorrectLogin
* Reason                 : Any input other than 0 or 1 is treated as invalid.
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvalidInputNegativeNumber(void)
{
	/* Note:
	 * User Type (AdminMohamedTarek) = 0
	 * User Type (NormalUser) = 1
	 * User Type (IncorrectLogin) = 2
	 */
	unsigned char result = NULL;				// Variable to store return of Detect User Type function.

	redirect_input("-1\n");					    // Redirect input to simulate user input == scanf("%d", &User_Type); and User_Type = -1.
	result = Detect_User_Type();				// store return of function.
	restore_stdin();								// Restore standard input after redirection.
	CU_ASSERT_EQUAL(result, IncorrectLogin);
}


/************************************************************************************
* Test ID                : 35
* Test Case              : Non-Numeric Input Handling
* Description            : Tests if the function correctly handles non-numeric input.
* 
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : User enters a character or string instead of a number (e.g., "abc", "$")
* 
* Expected Results       : Function should reject input and return "IncorrectLogin"
* 
* Reason                 : The function currently uses `scanf("%d", &User_Type)`, which
*                          may cause undefined behavior for non-numeric input.
* 
* Bug Found              : If `scanf()` receives a non-numeric input, it may leave
*                          User_Type uninitialized or cause an infinite loop.
*************************************************************************************/
static void TestCase_NonNumericInputHandling(void)
{
	/* Note:
	 * User Type (AdminMohamedTarek) = 0
	 * User Type (NormalUser) = 1
	 * User Type (IncorrectLogin) = 2
	 */

	unsigned char result = NULL;				// Variable to store return of Detect User Type function.

	redirect_input("abc\n");					// Redirect input to simulate user input == scanf("%d", &User_Type); and User_Type = "abc".
	result = Detect_User_Type();				// store return of function.
	restore_stdin();								// Restore standard input after redirection.

	/* Bug found:
	 * due to  `scanf()` receives a non-numeric input, it may leave
     * User_Type uninitialized or cause an infinite loop and the actual value of User_Type after debugging will be = 0
	 * and this mean AdminMohamedTarek not IncorrectLogin so to fix this bug we need to check return value
	 * of `scanf()` so the code should belike this:
	 *
	 * int result;
	 * result = scanf("%d", &User_Type);
	 *
	 *	Check if scanf successfully read an integer
	 *	if (result != 1) 
	 *	{
	 *
	 *	Clear the input buffer to discard invalid input
	 *	while (getchar() != '\n'); // Discard characters until newline
	 *
	 *	// Return IncorrectLogin for invalid input
	 *	return IncorrectLogin;
	 *	}
	 *
	 */
	CU_ASSERT_EQUAL(result, IncorrectLogin);
}


/************************************************************************************/


/* Test case for suite 7 (Verify Admin Functionality) */


/************************************************************************************
* Test ID                : 36
* Test Case              : Valid Token on First Attempt
* Description            : Tests if the function (Verify_Admin) accepts the correct token on the first attempt.
*
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : Token = 10203040 (valid token)
*
* Expected Results       : Function should return TRUE.
* Reason                 : The input matches the SECRET_ADMIN_TOKEN.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidTokenFirstAttempt(void)
{
	unsigned char result = NULL;				// Variable to store return of Detect User Type function.

	redirect_input("10203040\n");		// Redirect input to simulate user input == scanf("%d", &Token); and Token = 10203040.
	result = Verify_Admin();
	CU_ASSERT_EQUAL(result, TRUE);
}


/************************************************************************************
* Test ID                : 37
* Test Case              : Valid Token on Second Attempt
* Description            : Tests if the function (Verify_Admin) accepts the correct token on the second attempt.
*
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : First attempt: Token = 99999999 (invalid). 
*						   Second attempt: Token = 10203040 (valid).
*
* Expected Results       : Function should return TRUE.
* Reason                 : The input matches the SECRET_ADMIN_TOKEN on the second attempt.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidTokenSecondAttempt(void)
{
	unsigned char result = NULL;				// Variable to store return of Detect User Type function.

	redirect_input("99999999\n10203040\n");		// Redirect input to simulate user input == scanf("%d", &Token); and
												// Token 1ST = 99999999 (invalid) Token 2ND = 10203040 (valid).			
	
	result = Verify_Admin();
	CU_ASSERT_EQUAL(result, TRUE);
}


/************************************************************************************
* Test ID                : 38
* Test Case              : Valid Token on Third Attempt
* Description            : Tests if the function (Verify_Admin) accepts the correct token on the third attempt.
*
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : First attempt: Token = 99999999 (invalid), 
*						   Second attempt: Token = 88888888 (invalid), 
*						   Third attempt: Token = 10203040 (valid)
*
* Expected Results       : Function should return TRUE.
* Reason                 : The input matches the SECRET_ADMIN_TOKEN on the third attempt.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidTokenThirdAttempt(void)
{
	unsigned char result = NULL;							// Variable to store return of Detect User Type function.
	redirect_input("99999999\n88888888\n10203040\n");		// Redirect input to simulate user input == scanf("%d", &Token); and
															// Token 1ST = 99999999 (invalid) Token 2ND = 88888888 (invalid). Token 3RD = 10203040 (valid).			

	result = Verify_Admin();
	CU_ASSERT_EQUAL(result, TRUE);
}


/************************************************************************************
* Test ID                : 39
* Test Case              : Invalid Token on All Attempts
* Description            : Tests if the function (Verify_Admin) rejects invalid tokens on all three attempts.
*
* Technique              : Equivalence Partitioning
* Pre-requisites         : None
* Test Inputs            : First attempt: Token = 99999999 (invalid), 
*						   Second attempt: Token = 88888888 (invalid),
*						   Third attempt: Token = 77777777 (invalid)
*
* Expected Results       : Function should return FALSE.
* Reason                 : The input does not match the SECRET_ADMIN_TOKEN on any attempt.
* Bug Found              : None
*************************************************************************************/
static void TestCase_InvalidTokenAllAttempts(void)
{
	unsigned char result = NULL;							// Variable to store return of Detect User Type function.

	redirect_input("99999999\n88888888\n77777777\n");		// Redirect input to simulate user input == scanf("%d", &Token); and
															// Token 1ST = 99999999 (invalid) Token 2ND = 88888888 (invalid). Token 3RD = 77777777 (invalid).			
	result = Verify_Admin();
	CU_ASSERT_EQUAL(result, FALSE);
}



/************************************************************************************/


/* Test case for suite 8 (Verify User Functionality) */

/************************************************************************************
* Test ID                : 40
* Test Case              : Valid Username and Password
* Description            : Tests if the function (Verify_User) accepts a valid username and password.
*
* Technique              : Decision Table Testing
* Pre-requisites         : A valid user exists in the database.
* Test Inputs            :
*                          UserName = "AdminUser1"
*                          Password = "Edges123"
* 
* Expected Results       : Function should return Login_Successful and id_ptr = user index in array [0].
* Reason                 : The username and password match an entry in the database.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidUsernameAndPassword(void)
{
	unsigned char result = NULL;								// Variable to store return of Verify User function.
	unsigned char Test_User_id = NULL;							// Variable to store user ID			

	unsigned int ID_Index = 0;									// variable to check the value id_ptr that an output parameter 
																// to store the id of Logged in User in case of sucessfull login

	Test_User_id = 1;											// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id =  1;	// Assigning ID = 1 to user 1


	result = Verify_User("AdminUser1", "Edges123", &ID_Index);	// Verify user with username = "AdminUser1" and password = "Edges123"
	CU_ASSERT_EQUAL(result, Login_Successful);
	CU_ASSERT_EQUAL(ID_Index, 0);									// Check if the ID is correct (0 for the first user in the array)

	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
}


/************************************************************************************
* Test ID                : 41
* Test Case              : Valid Username, Incorrect Password
* Description            : Tests if the function (Verify_User) rejects an incorrect password for a valid username.
*
* Technique              : Decision Table Testing
* Pre-requisites         : A valid user exists in the database.
* Test Inputs            :
*                          UserName = "AdminUser1"
*                          Password = "WrongPassword"
* 
* Expected Results       : Function should return Password_incorrect and id_ptr = -1.
* Reason                 : The password does not match the entry in the database.
* Bug Found              : None
*************************************************************************************/
static void TestCase_ValidUsernameIncorrectPassword(void)
{
	unsigned char result = NULL;								// Variable to store return of Verify User function.
	unsigned char Test_User_id = NULL;							// Variable to store user ID	

	unsigned int ID_Index = 0;									// variable to check the value id_ptr that an output parameter 
	// to store the id of Logged in User in case of sucessfull login

	Test_User_id = 1;											// valid user ID = 1
	DBM_Add_User(&Test_GeneralUser1);							// Add user 1 to DB
	Test_GeneralUser1.PersonalInfo_Form.id = Test_User_id - 1;	// Assigning ID = 1 to user 1

	result = Verify_User("AdminUser1", "WrongPassword", &ID_Index);	// Verify user with username = "AdminUser1" and password = "WrongPassword"
	CU_ASSERT_EQUAL(result, Password_incorrect);
	CU_ASSERT_EQUAL(ID_Index, -1);								// Check if the ID is correct (-1 for incorrect password)

	/* Delete all users */
	Test_User_id = 1;
	Delete_Account(Test_User_id - 1);
}


/************************************************************************************
* Test ID                : 42
* Test Case              : Non-Existent Username
* Description            : Tests if the function (Verify_User) rejects an Non-Existent username.
*
* Technique              : Decision Table Testing
* Pre-requisites         : (None)No matching user exists in the database.
* Test Inputs            :
*                          UserName = "NonExistentUser"
*                          Password = "Edges123"
* 
* Expected Results       : Function should return UserName_NotFound and id_ptr = -1.
* Reason                 : The username does not exist in the database.
* Bug Found              : None
*************************************************************************************/
static void TestCase_NonExistentUsername(void)
{
	unsigned char result = NULL;								// Variable to store return of Verify User function.

	unsigned int ID_Index = 0;									// variable to check the value id_ptr that an output parameter 
																// to store the id of Logged in User in case of sucessfull login

	result = Verify_User("NonExistentUser", "Edges123", &ID_Index);	// Verify user with username = "NonExistentUser" and password = "Edges123"
	
	CU_ASSERT_EQUAL(result, UserName_NotFound);
	CU_ASSERT_EQUAL(ID_Index, -1);								// Check if the ID is correct (-1 for non-existent username)
}




/*******************************************************************************
 *                           Test Runner Setup                                 *
 *******************************************************************************/

void Main_Test_Runner(void)
{
	/* initialize the Registry */
	CU_initialize_registry();


	/****************************************************************
     *               Adding Test Suite to the Registry              *
     ****************************************************************/

	CU_pSuite Suite_AddAccount_Function = CU_add_suite("Creaet Valid and Invaild Account", TestSuite_AddAccountFunction_Start, TestSuite_AddAccountFunction_End);

	CU_pSuite Suite_Delete_Function = CU_add_suite("Delete Account Functionality Test", TestSuite_DeteleFunction_Start, TestSuite_DeteleFunction_End);
	
	CU_pSuite Suite_NumberOfDays_Function = CU_add_suite("Get Number Of Days Tests", TestSuite_GetNumberOfDays_Start, TestSuite_GetNumberOfDays_End);

	CU_pSuite Suite_ShowStudentCourses_Function = CU_add_suite("Show Student Courses Tests", TestSuite_ShowStudentCourses_Start, TestSuite_ShowStudentCourses_End);

	CU_pSuite Suite_AddStudentToCourse_Function = CU_add_suite("Add Student To Course Tests", TestSuite_AddStudentToCourse_Start, TestSuite_AddStudentToCourse_End);

	CU_pSuite Suite_DetectUserType_Function = CU_add_suite("Detect User Type Tests", TestSuite_DetectUserType_Start, TestSuite_DetectUserType_End);

	CU_pSuite Suite_VerifyAdmin_Function = CU_add_suite("Verify Admin Functionality Tests", TestSuite_VerifyAdmin_Start, TestSuite_VerifyAdmin_End);

	CU_pSuite Suite_VerifyUser_Function = CU_add_suite("Verify User Functionality Tests", TestSuite_VerifyUser_Start, TestSuite_VerifyUser_End);


	/****************************************************************
     *               Adding Test Cases to the Test Suite            *
     ****************************************************************/

	/* Test Case for Suite 1 */
	/*
	CU_add_test(Suite_AddAccount_Function, "Valid Account correct format", TestCase_AddVaildAccount);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild name", TestCase_VaildNameBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild name", TestCase_InvaildNameBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild age", TestCase_InvaildAgeBoundaries);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild age", TestCase_VaildAgeBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild gender", TestCase_InvaildGender);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild gender", TestCase_VaildGender);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild educational status", TestCase_InvaildEducationalStatus);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild educational status", TestCase_VaildEducationalStatus);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild username", TestCase_InvaildUsernameBoundaries);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild username", TestCase_VaildUsernameBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild password length", TestCase_InvaildPasswordLengthBoundaries);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild password length", TestCase_VaildPasswordLengthBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild recheck password length", TestCase_InvaildPasswordREcheckLengthBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild recheck password length", TestCase_VaildPasswordREcheckLengthBoundaries);
	CU_add_test(Suite_AddAccount_Function, "InValid Account invaild password & recheck password", TestCase_InVaildPasswordAndPasswordREcheck);
	CU_add_test(Suite_AddAccount_Function, "Valid Account vaild password & recheck password", TestCase_VaildPasswordAndPasswordREcheck);
	CU_add_test(Suite_AddAccount_Function, "Adding account to full Data Base", TestCase_AddingUserToFullDB);
	*/

	/* Test Case for Suite 2 */
	//CU_add_test(Suite_Delete_Function, "Delete Account Tests (Vaild & Invaild)", TestCase_Delete_Account);


	/* Test Case for Suite 3 */
	/*
	CU_add_test(Suite_NumberOfDays_Function, "31-Day Months", TestCase_GetNumberOfDays_31DayMonths);
	CU_add_test(Suite_NumberOfDays_Function, "30-Day Months", TestCase_GetNumberOfDays_30DayMonths);
	CU_add_test(Suite_NumberOfDays_Function, "February Cases", TestCase_GetNumberOfDays_February);
	CU_add_test(Suite_NumberOfDays_Function, "Invalid Inputs", TestCase_GetNumberOfDays_InvaildInputs);
	*/

	/* Test Case for Suite 4 */
	/*
	CU_add_test(Suite_ShowStudentCourses_Function, "Invalid ID Inputs", TestCase_InvalidUserIDs);
	CU_add_test(Suite_ShowStudentCourses_Function, "Valid ID Inputs", TestCase_ValidUserIDs);
	CU_add_test(Suite_ShowStudentCourses_Function, "Valid ID No Courses", TestCase_ValidUserNoCourses);
	*/

	/* Test Case for Suite 5 */
	
	//CU_add_test(Suite_AddStudentToCourse_Function, "Vaild user ID & vaild Course", TestCase_AddStudentToCourse_ValidID);
	/* theses TCs cause a RTE 
	CU_add_test(Suite_AddStudentToCourse_Function, "Invaild user ID & vaild Course", TestCase_AddStudentToCourse_InvalidID);
	CU_add_test(Suite_AddStudentToCourse_Function, "Invaild Course ID", TestCase_AddStudentToCourse_InvalidCoursesID);
	*/
	//CU_add_test(Suite_AddStudentToCourse_Function, "Vaild user ID & vaild Course", TestCase_AddStudentToCourse_ValidUser);
	

	/* Test Case for Suite 6 */
	
	CU_add_test(Suite_DetectUserType_Function, "Valid Admin Input", TestCase_ValidAdminInput);
	CU_add_test(Suite_DetectUserType_Function, "Valid Normal User Input", TestCase_ValidNormalUserInput);
	CU_add_test(Suite_DetectUserType_Function, "Valid IncorrectLogin", TestCase_ValidIncorrectLogin);
	CU_add_test(Suite_DetectUserType_Function, "Invalid Input (Negative Number)", TestCase_InvalidInputNegativeNumber);
	CU_add_test(Suite_DetectUserType_Function, "Non-Numeric Input Handling", TestCase_NonNumericInputHandling);
	

	/* Test Case for Suite 7 */
	/*
	CU_add_test(Suite_VerifyAdmin_Function, "Valid Token on First Attempt", TestCase_ValidTokenFirstAttempt);
	CU_add_test(Suite_VerifyAdmin_Function, "Valid Token on Second Attempt", TestCase_ValidTokenSecondAttempt);
	CU_add_test(Suite_VerifyAdmin_Function, "Valid Token on Third Attempt", TestCase_ValidTokenThirdAttempt);
	CU_add_test(Suite_VerifyAdmin_Function, "Invalid Token on All Attempts", TestCase_InvalidTokenAllAttempts);
	*/


	/* Test Case for Suite 8 */
	/*
	CU_add_test(Suite_VerifyUser_Function, "Valid Username and Password", TestCase_ValidUsernameAndPassword);
	CU_add_test(Suite_VerifyUser_Function, "Valid Username, Incorrect Password", TestCase_ValidUsernameIncorrectPassword);
	CU_add_test(Suite_VerifyUser_Function, "Non-Existent Username", TestCase_NonExistentUsername);
	*/


	/****************************************************************
     *                     Setup Testing mode                       *
     ****************************************************************/

	/* Running the Test Suite through Basic Console */
	//CU_basic_set_mode(CU_BRM_VERBOSE);	// maximum output or run the tests in a non-interactive mode
	//CU_basic_set_mode(CU_BRM_SILENT);	// minimum output or run the tests in a non-interactive mode
	//CU_basic_set_mode(CU_BRM_NORMAL);	// failures and run summary the tests in a non-interactive mode

	//CU_basic_run_suite(Suite_AddAccount_Function); // Run this tests suite only

	//CU_basic_run_test(Suite_AddAccount_Function, TestCase_InvaildAgeBoundaries); // Run this only test for this suite only

	//CU_basic_run_tests();

	/* Running the Test Suite through Console interactive */
	 CU_console_run_tests();

	/* Clear the registry after test finished */
	CU_cleanup_registry();
}
