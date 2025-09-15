# Reservation software Testing (CUnit Project)

## 📌 Overview
This project tests the **EDGES Reservation Software** written in C language. 
The software supports two user roles:
- **Admin**: create/delete accounts, view users, manage courses.
- **Student**: create account, login, change password, reserve courses, view enrolled courses.

The goal of this project was to apply **software testing techniques** and use the **CUnit Framework** to ensure quality and reliability.

---

## 🎯 Project Objectives
- Apply **ISTQB Foundation Level techniques** (BVA, EP, Decision Table, MC/DC, State Transition).
- Perform **Unit, Integration, and Validation testing**.
- Identify and report bugs with **root cause analysis**.
- Generate **detailed test case reports and bug reports**.

---

## 🧪 What Was Tested
- **Fully Tested Modules:**
  - `Create Account`
  - `Login`
  - `Course Registration`
- **Partially Tested Modules:**
  - `Database (DB)` (only some functions tested)
- **Not Covered Yet:**
  - `Backend`, `APP`, etc.

---

## 🛠️ Tools & Techniques
- **Microsoft Visual Studio** ( Integrated Development Environment "IDE")
- **CUnit Framework** (unit test automation)
- **Boundary Value Analysis (BVA)**
- **Equivalence Partitioning (EP)**
- **Decision Table Testing**
- **MC/DC Coverage**
- **State Transition Testing**

---

## 📊 Reports
- [📄 Test Cases Report](docs/Test_Cases_Report.pdf)  
- [🐞 Bug Report](docs/Bugs_Report.pdf)  
- [📘 Test_Completion_Report](docs/Test_Completion_Report.pdf)  

---

## 🐛 Key Bugs Found
1. **Buffer Overflow Issues** – 32-character strings not handled correctly (name, username, password).  
2. **Boundary Value Failures** – Age `0` and `100` rejected due to incorrect conditions.  
3. **DB Logic Issue** – Adding a 6th user returns `TRUE` but user is not added.  
4. **Invalid Deletion** – Delete function incorrectly deletes the last user when invalid ID=6 is passed.  
5. **Poor User Feedback** – Missing error messages when no courses are enrolled.

---

## 🚀 How to Run Tests

### 1️⃣ Setup Testing mode
- At the end of file `Tests.c` we have to choose one mode to run test and comment the other modes
1. Running the Test Suite through Basic Console and we have three option
   - CU_basic_set_mode(CU_BRM_VERBOSE);  ===> Detailed logs for each test (good for debugging)
   - CU_basic_set_mode(CU_BRM_SILENT);   ===> Minimal logs (best for automation/CI)
   - CU_basic_set_mode(CU_BRM_NORMAL);   ===> Default: shows failures + summary
  
2. Running the Test Suite through Console interactive
   - CU_console_run_tests();

### 2️⃣ Build the Project
Just build the project after saveing the mode selected and run it
