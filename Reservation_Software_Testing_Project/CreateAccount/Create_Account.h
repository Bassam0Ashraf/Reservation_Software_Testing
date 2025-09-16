#pragma once
#include "../Generic/System_info.h"
#include "../Generic/Data_Types.h"
#include "../Test/Tests.h"

/* prototype for the function that takes a form to create account*/
unsigned char Add_Account(struct User_Input_Type* Form);
/* prototype for the function that deletes a user by his ID */
unsigned char Delete_Account(unsigned short user_id);


#if ( TESTING_MODE == STD_ON )

/* prototype for the testing function Get_Number_OfDays */
unsigned char Test_Get_Number_OfDays(unsigned char Month, unsigned short Year);

#endif // TESTING_MODE

