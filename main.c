#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SEM 8
#define MAX_COURSE 6

void setColor(const char *colorCode)
{
    char cmd[10];
    sprintf(cmd, "color %s", colorCode);
    system(cmd);
}

struct Course
{
    char name[50];
    float credit;
    float marks;
    float gradePoint;
};

struct Course semesters[MAX_SEM][MAX_COURSE];
int courseCount[MAX_SEM] = {0};

float getGradePoint(float marks)
{
    if (marks >= 80)
        return 4.0;
    else if (marks >= 75)
        return 3.7;
    else if (marks >= 70)
        return 3.3;
    else if (marks >= 65)
        return 3.0;
    else if (marks >= 60)
        return 2.7;
    else if (marks >= 55)
        return 2.3;
    else if (marks >= 50)
        return 2.0;
    else
        return 0.0;
}

void inputSemester(int sem)
{
    setColor("0E");
    printf("\n------------------------------\n");
    printf("     Entering Semester %d\n", sem + 1);
    printf("------------------------------\n");

    courseCount[sem] = MAX_COURSE;

    for (int i = 0; i < MAX_COURSE; i++)
    {
        printf("\nCourse %d name: ", i + 1);
        scanf("%s", semesters[sem][i].name);

        printf("Credit: ");
        scanf("%f", &semesters[sem][i].credit);

        printf("Marks (0-100): ");
        scanf("%f", &semesters[sem][i].marks);

        semesters[sem][i].gradePoint = getGradePoint(semesters[sem][i].marks);
    }

    setColor("0A");
    printf("\nSemester %d data saved successfully!\n", sem + 1);
}

float calculateSGPA(int sem)
{
    float totalGrade = 0, totalCredit = 0;

    for (int i = 0; i < courseCount[sem]; i++)
    {
        totalGrade += semesters[sem][i].gradePoint * semesters[sem][i].credit;
        totalCredit += semesters[sem][i].credit;
    }
    if (totalCredit == 0)
        return 0;
    return totalGrade / totalCredit;
}

float calculateCGPA(int totalSem)
{
    float totalGrade = 0, totalCredit = 0;

    for (int s = 0; s < totalSem; s++)
    {
        for (int c = 0; c < courseCount[s]; c++)
        {
            totalGrade += semesters[s][c].gradePoint * semesters[s][c].credit;
            totalCredit += semesters[s][c].credit;
        }
    }

    if (totalCredit == 0)
        return 0;
    return totalGrade / totalCredit;
}

void displayResults(int totalSem)
{
    setColor("0B");
    printf("\n==============================\n");
    printf("     SGPA & CGPA CALCULATOR\n");
    printf("==============================\n\n");

    for (int s = 0; s < totalSem; s++)
    {
        printf("Semester %d SGPA: %.2f\n", s + 1, calculateSGPA(s));
    }

    setColor("0A");
    printf("\nOverall CGPA: %.2f\n", calculateCGPA(totalSem));
}
void viewAllDetails(int totalSem)
{
    setColor("0B");
    printf("\n==============================\n");
    printf("   ALL SEMESTER DETAILS\n");
    printf("==============================\n\n");

    for (int s = 0; s < totalSem; s++)
    {
        printf("Semester %d:\n", s + 1);
        printf("%-20s %-10s %-10s %-10s\n", "Course Name", "Credit", "Marks", "Grade");
        printf("-----------------------------------------------\n");

        for (int c = 0; c < courseCount[s]; c++)
        {
            printf("%-20s %-10.2f %-10.2f %-10.2f\n",
                   semesters[s][c].name,
                   semesters[s][c].credit,
                   semesters[s][c].marks,
                   semesters[s][c].gradePoint);
        }
        printf("\n");
    }
}

void saveToFile(int totalSem)
{
    FILE *f = fopen("cgpa_data.txt", "w");
    if (!f)
    {
        setColor("0C");
        printf("Error saving file!\n");
        return;
    }

    fprintf(f, "%d\n", totalSem);

    for (int s = 0; s < totalSem; s++)
    {
        fprintf(f, "%d\n", courseCount[s]);
        for (int c = 0; c < courseCount[s]; c++)
        {
            fprintf(f, "%s %.2f %.2f\n",
                    semesters[s][c].name,
                    semesters[s][c].credit,
                    semesters[s][c].marks);
        }
    }

    fclose(f);
    setColor("0A");
    printf("\nData saved to cgpa_data.txt\n");
}

int loadFromFile()
{
    FILE *f = fopen("cgpa_data.txt", "r");
    if (!f)
    {
        setColor("0C");
        printf("\nNo saved file found!\n");
        return 0;
    }

    int totalSem;
    fscanf(f, "%d", &totalSem);

    for (int s = 0; s < totalSem; s++)
    {
        fscanf(f, "%d", &courseCount[s]);
        for (int c = 0; c < courseCount[s]; c++)
        {
            fscanf(f, "%s %f %f",
                   semesters[s][c].name,
                   &semesters[s][c].credit,
                   &semesters[s][c].marks);
            semesters[s][c].gradePoint = getGradePoint(semesters[s][c].marks);
        }
    }

    fclose(f);
    setColor("0A");
    printf("\nData loaded successfully!\n");

    return totalSem;
}

int main()
{
    int choice, totalSem = 0;

    setColor("1F");
    printf("==============================\n");
    printf("       CGPA COUNTER v1.0\n");
    printf("==============================\n");

    while (1)
    {
        setColor("0E");

        printf("\n_______________________________________\n");
        printf("\n-------------- MAIN MENU --------------\n");
        printf("1. Input Semester Data\n");
        printf("2. Display SGPA & CGPA\n");
        printf("3. Save to File\n");
        printf("4. Load from File\n");
        printf("5. View All Semester Details\n");
        printf("6. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (totalSem < MAX_SEM)
            {
                inputSemester(totalSem);
                totalSem++;
            }
            else
            {
                setColor("0C");
                printf("8 Semesters Already Entered!\n");
            }
        }
        else if (choice == 2)
        {
            displayResults(totalSem);
        }
        else if (choice == 3)
        {
            saveToFile(totalSem);
        }
        else if (choice == 4)
        {
            totalSem = loadFromFile();
        }
        else if (choice == 5)
        {
            viewAllDetails(totalSem);
        }
        else if (choice == 6)
        {
            setColor("0A");
            printf("\nThank you for using CGPA Counter!\n");
            break;
        }
        else
        {
            setColor("0C");
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
