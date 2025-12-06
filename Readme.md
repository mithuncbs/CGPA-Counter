#### **CGPA Counter System Using C Programming**



###### **Introduction:**

This project is a simple CGPA Counter System developed using the C programming language. The main goal of the project is to help students calculate their SGPA for each semester and the overall CGPA based on their course marks and credit hours. The system supports multiple semesters and allows the user to input marks and view results through a menu-based interface.



###### **Design Decisions:**

To organize the data properly, I used a structure (struct) to store each courses information. The structure contains three values: course name, credit hours, and obtained marks. Since each semester contains multiple courses, I used a 2D array of structures, where rows represent semesters and columns represent courses.

For grade calculation, I used a numeric marks-to-grade-point mapping (for example, 80+ = 4.0, 75?79 = 3.75, etc.). This approach is simple, clear, and commonly used in universities.



###### **SGPA Calculation Method:**

SGPA is calculated using the standard formula:

SGPA = (sum of (grade point \* credit hours)) / (total credits of the semester)

This makes the system accurate and consistent across all semesters.



###### **CGPA Calculation Method:**

CGPA is calculated using cumulative data of all completed semesters:

CGPA = (total grade point ? credit hours of all semesters) / (total credits of all semesters)

This method ensures that semesters with more credits have a fair impact on the final CGPA.



###### **Features:**

\* Input course names, credits, and marks.

\* Calculate SGPA for each semester.

\* Calculate total CGPA across all semesters.

\* Simple text-based menu for easy navigation.

\* Input validation for marks and credits.

\* Save, load and view all inputs and data.

###### 

###### **Conclusion:**

The CGPA Counter System is a practical tool for students and a strong demonstration of structured programming in C. The project uses modular functions, structures, loops, and arrays, which makes the code clean and easy to maintain.





