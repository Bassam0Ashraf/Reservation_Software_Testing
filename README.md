# EDGES Reservation Software Testing Project

A comprehensive testing project for the EDGES Reservation software written in C language using the CUnit testing framework. This project demonstrates software testing techniques including boundary value analysis, equivalence partitioning, and decision table testing.

## Table of Contents

- [Project Overview](#project-overview)
- [Software Components](#software-components)
- [User Types](#user-types)
- [Testing Scope](#testing-scope)
- [Installation & Setup](#installation--setup)
- [Running Tests](#running-tests)
- [Test Results](#test-results)
- [Known Issues](#known-issues)
- [Testing Techniques](#testing-techniques)
- [Contributing](#contributing)
- [Project Structure](#project-structure)

## Project Overview

The EDGES Reservation software is a course reservation system that allows administrators to manage users and courses, while students can create accounts, login, and register for available courses. This testing project applies various software testing standards and techniques to ensure the reliability and correctness of the system.

### Key Features

- User account management (create, delete, login)
- Course registration system
- Admin panel for user management
- Database operations (CRUD)
- Security token-based admin authentication

## Software Components

The project consists of multiple modular components:

1. **APP** - Main application logic and user type detection
2. **Backend** - Core business logic for admin, customer, and student operations
3. **Course Registration** - Course enrollment and management functionality
4. **Create Account** - User account creation and validation
5. **CUnit** - CUnit testing framework library files
6. **DB** - Database manager with CRUD operations
7. **Login** - Authentication and user verification
8. **Security** - Admin token management and security functions
9. **Generic** - Common data types and system definitions
10. **Tests** - Test cases and test suites
11. **Main.c** - Application entry point

## User Types

### Admin User (Mohamed Tarek)
- **Token**: `10203040` (configurable in `Sec.h`)
- **Capabilities**:
  - Register new user accounts
  - Delete user accounts
  - View all course registrations
  - Print user information and credentials
  - Print specific user details

### Normal User (Student)
- **Capabilities**:
  - Create personal account
  - Login/logout functionality
  - Change password
  - View personal information
  - Reserve courses from available list
  - View enrolled courses

## Testing Scope

### Fully Tested Components
- **Create Account** - Complete test coverage
- **Login** - Complete test coverage  
- **Course Registration** - Complete test coverage

### Partially Tested Components
- **Database (DB)** - Limited function testing
- Other components have minimal or no test coverage

### Testing Statistics
- **Total Test Cases**: 42
- **Passed**: 30
- **Failed**: 12
- **Techniques Applied**: Boundary Value Analysis, Equivalence Partitioning, Decision Table Testing

## Installation & Setup

### Prerequisites
- GCC compiler
- CUnit testing framework
- C standard library

### Building the Project

- At the end of file `Tests.c` we have to choose one mode to run test and comment the other modes.
1. Running the Test Suite through Basic Console and we have three option
   ```bash
   - CU_basic_set_mode(CU_BRM_VERBOSE);  ===> Detailed logs for each test (good for debugging)
   - CU_basic_set_mode(CU_BRM_SILENT);   ===> Minimal logs (best for automation/CI)
   - CU_basic_set_mode(CU_BRM_NORMAL);   ===> Default: shows failures + summary
  
2. Running the Test Suite through Console interactive
```bash
   - CU_console_run_tests();
```
## Running Tests

### Run Application
To run the main application:
Keep section 1 **uncommented** in and Comment section 2 `main.c`
```bash
# Section 1
do
	{
		Status = Main_App_Runner();
	} 
while (Status != ERROR);

# Section 2

//Main_Test_Runner();

```

### Run Test Suite
To execute the test cases:
Comment section 1 and uncomment section 2 in `main.c`
```bash
# Section 1
/*
do
	{
		Status = Main_App_Runner();
	} 
while (Status != ERROR);
*/

# Section 2

Main_Test_Runner();
```

### Login Credentials

#### Admin Login
1. Start application
2. Enter `0` for admin
3. Enter token: `10203040`

#### Student Login (Pre-configured users)
- **User 1**: Username: `AdminUser1`, Password: `Edges123`
- **User 2**: Username: `AdminUser2`, Password: `Edges123456`
- **User 3**: Username: `AdminUser3`, Password: `Edges_123`

## Test Results

### Test Coverage by Function

| Function | Test Cases | Passed | Failed | Coverage |
|----------|------------|--------|--------|----------|
| Add Account | 18 | 13 | 5 | Complete |
| Delete Account | 1 | 0 | 1 | Basic |
| Get Number of Days | 4 | 4 | 0 | Complete |
| Show Student Courses | 3 | 2 | 1 | Complete |
| Add Student to Course | 4 | 1 | 3 | Complete |
| Detect User Type | 5 | 4 | 1 | Complete |
| Verify Admin | 4 | 4 | 0 | Complete |
| Verify User | 3 | 3 | 0 | Complete |

## Known Issues

### Critical Bugs Identified

1. **Buffer Overflow Issues** (Multiple Functions)
   - 32-character strings cause buffer overflow
   - **Root Cause**: Fixed buffer size doesn't account for null terminator
   - **Impact**: Memory corruption, validation failures

2. **Boundary Value Handling**
   - Age validation excludes valid boundary values (0, 100)
   - **Root Cause**: Incorrect logical conditions in validation

3. **Array Index Validation**
   - Out-of-bounds access for invalid user/course IDs
   - **Root Cause**: Missing validation before array access
   - **Impact**: Runtime crashes, incorrect deletions

4. **Input Validation**
   - Non-numeric input causes undefined behavior
   - **Root Cause**: No error handling for `scanf()` failures

5. **Return Value Inconsistencies**
   - Functions return success even when operations fail
   - **Root Cause**: Incorrect return value logic

For detailed bug reports and fixes, see `Bugs_Report.pdf`.

## Testing Techniques

### Applied Techniques
- **Boundary Value Analysis**: Testing edge cases and limits
- **Equivalence Partitioning**: Testing representative values from input domains
- **Decision Table Testing**: Testing different combinations of conditions
- **MC/DC Coverage**: Modified Condition/Decision Coverage analysis
- **State Transition Testing**: Testing state changes in the system

### Coverage Metrics
- Statement Coverage: Partial
- Branch Coverage: Partial  
- MC/DC Coverage: Limited
- Boundary Value Coverage: Comprehensive for tested functions

## Project Structure

```
EDGES-Reservation-Testing/
├── APP/                    # Application logic
├── Backend/               # Business logic
├── Course_Registration/   # Course management
├── Create_Account/        # Account creation
├── CUnit/                # Testing framework
├── DB/                   # Database operations
├── Final_Project/        # Build output
├── Generic/              # Common definitions
├── Login/                # Authentication
├── Security/             # Security functions
├── Tests/                # Test cases and suites
├── main.c                # Application entry point
├── Test_Cases_Report.pdf # Detailed test documentation
├── Bugs_Report.pdf       # Bug analysis and fixes
└── README.md            # This file
```

## Important Notes

- Database initializes with 3 default users and sample course registrations
- Application runs continuously until forced termination or specific exit conditions
- Database persists across sessions within the same run
- Maximum users: 5
- Maximum courses: 6
- Maximum students per course: 5

## Contributing

When contributing to the testing suite:

1. **DO NOT** modify source code - only add test cases
2. Work within the `Tests/` directory for new test cases
3. Follow the established test case reporting format
4. Document any new bugs discovered
5. Ensure test cases cover edge cases and boundary conditions

### Test Case Documentation Format and Reports
1.Each test case should include:
  - Test conditions
  - Test steps  
  - Test inputs
  - Expected outputs
  - Actual outputs
  - Prerequisites
  - Testing technique used
  - Bug documentation (if applicable)
2. Reports:
  - [Test Cases Report](Reports/Test_Cases_Report.pdf)
  - [Bug Report](Reports/Bugs_Report.pdf)
  - [Test_Completion_Report](Reports/Test_Completion_Report.pdf)

---

## Future Improvements

- Implement fixes for identified buffer overflow issues
- Add comprehensive input validation
- Extend test coverage to remaining components
- Implement automated test execution
- Add performance and load testing
- Improve error handling and user feedback

## License

This is an educational testing project for the EDGES Training Program.

---

**Developed by**: Bassam Ashraf  
**Course**: SW Testing Diploma  
**Framework**: CUnit Testing Framework  
**Language**: C
