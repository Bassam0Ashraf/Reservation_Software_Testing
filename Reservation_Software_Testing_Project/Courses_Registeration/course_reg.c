#include "course_reg.h"

unsigned char AddStudentToCourse(unsigned int Course_id, unsigned int Student_id)
{
	unsigned char RET = FALSE;
	// Check if already enrolled
	if (Enrollments[Student_id][Course_id-1] == TRUE)
	{
		RET = AlreadyEnrolled;
	}
	else
	{
		// Check if User is added succesfully to the course
		RET = DBM_AddToCourse(Course_id, Student_id);
		if (RET == TRUE)
		{
			RET = Enrolled;
		}
		// User not added the capacity is completed
		else
		{
			RET = CapacityCompleted;
		}
	}
	return RET;
}

/* Function that display list of all available courses */
void ShowListOfCourses()
{
	DBM_DisplayAllCourses();
}

/* Function that shows the Courses enrolled in for a specific Student */
void ShowStudentCourses(unsigned int User_ID)
{
	/* If you want to disable the testing change the MACRO "TESTING_MODE"
	 * in file: Generic/System_info.h from "STD_ON" to "STD_OFF" */
	#if ( TESTING_MODE == STD_ON )
		unsigned char RET = FALSE;
	#endif

	if (User_ID < 0 || User_ID >= MAX_USERS)
	{
		printf("Invalid User Id \n");

	    #if ( TESTING_MODE == STD_ON )
			RET = FALSE;
	    #endif
	}
	else
	{
		printf("You Are Currently Enrolled in:\n");
		
	    #if ( TESTING_MODE == STD_ON )
			 RET = Test_DBM_ShowCourse(User_ID);

		#else
			DBM_ShowCourse(User_ID);

		#endif
	}

#if ( TESTING_MODE == STD_ON )
	return RET;
#endif
}