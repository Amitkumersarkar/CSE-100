#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define ADMIN_PASSWORD "admin1234"
#define VIEWER_PASSWORD "viewer1234" // Set a simple password for the viewer role
#define MAX_SEMESTERS 10
#define MAX_SUBJECTS 10

typedef struct
{
    char subject[50];
    float grade;
} Semester;

typedef struct
{
    char name[50];
    int id;
    float cgpa;
    char department[50];
    char bloodGroup[5];
    char phoneNumber[15];
    int semesterCount;
    Semester semesters[MAX_SEMESTERS][MAX_SUBJECTS];
    int subjectsPerSemester[MAX_SEMESTERS];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void adminLogin();
void viewerLogin(); // Function for the viewer login
void addStudent();
void editStudent();
void deleteStudent();
void viewAllStudents();
void searchStudent();
void manageSemesterData(Student *student);
void viewSemesterData(Student *student);
void saveToFile();
void loadFromFile();

int main()
{
    loadFromFile();
    int choice;
    printf("Welcome to the Student Record Management System\n");

    while (1)
    {
        printf("\n1. Admin Login\n2. Viewer Login\n3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; // Clear input buffer
            continue;
        }

        switch (choice)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            viewerLogin(); // Calling the viewer login function
            break;
        case 3:
            saveToFile();
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void adminLogin()
{
    char password[20];
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) == 0)
    {
        int choice;
        while (1)
        {
            printf("\nAdmin Menu:\n");
            printf("1. Add Student\n");
            printf("2. Edit Student\n");
            printf("3. Delete Student\n");
            printf("4. View All Students\n");
            printf("5. Search Student\n");
            printf("6. Add Semester Data\n");
            printf("7. View Semester Data\n");
            printf("8. Logout\n");
            printf("Enter your choice: ");
            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n')
                    ; // Clear input buffer
                continue;
            }

            switch (choice)
            {
            case 1:
                addStudent();
                break;
            case 2:
                editStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                viewAllStudents();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
            {
                int id;
                printf("Enter student ID to add semester data: ");
                scanf("%d", &id);
                for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].id == id)
                    {
                        manageSemesterData(&students[i]);
                        break;
                    }
                }
                break;
            }
            case 7:
            {
                int id;
                printf("Enter student ID to view semester data: ");
                scanf("%d", &id);
                for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].id == id)
                    {
                        viewSemesterData(&students[i]);
                        break;
                    }
                }
                break;
            }
            case 8:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
            }
        }
    }
    else
    {
        printf("Incorrect password. Access denied.\n");
    }
}

void viewerLogin() // Viewer login function
{
    char password[20];
    printf("Enter Viewer Password: ");
    scanf("%s", password);

    if (strcmp(password, VIEWER_PASSWORD) == 0)
    {
        int choice;
        while (1)
        {
            printf("\nViewer Menu:\n");
            printf("1. View All Students\n");
            printf("2. Search Student\n");
            printf("3. View Semester Data\n");
            printf("4. Logout\n");
            printf("Enter your choice: ");
            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n')
                    ; // Clear input buffer
                continue;
            }

            switch (choice)
            {
            case 1:
                viewAllStudents();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
            {
                int id;
                printf("Enter student ID to view semester data: ");
                scanf("%d", &id);
                for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].id == id)
                    {
                        viewSemesterData(&students[i]);
                        break;
                    }
                }
                break;
            }
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
            }
        }
    }
    else
    {
        printf("Incorrect password. Access denied.\n");
    }
}

void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("Maximum student limit reached.\n");
        return;
    }

    Student newStudent;
    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter student ID: ");
    if (scanf("%d", &newStudent.id) != 1)
    {
        printf("Invalid input for ID.\n");
        while (getchar() != '\n')
            ;
        return;
    }
    printf("Enter CGPA: ");
    if (scanf("%f", &newStudent.cgpa) != 1)
    {
        printf("Invalid input for CGPA.\n");
        while (getchar() != '\n')
            ;
        return;
    }
    printf("Enter department: ");
    scanf("%s", newStudent.department);
    printf("Enter blood group: ");
    scanf("%s", newStudent.bloodGroup);
    printf("Enter phone number: ");
    scanf("%s", newStudent.phoneNumber);
    newStudent.semesterCount = 0;

    students[studentCount++] = newStudent;
    printf("Student added successfully.\n");
}

void editStudent()
{
    int id, i;
    printf("Enter student ID to edit: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for ID.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].id == id)
        {
            printf("Editing details for student ID %d\n", id);
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new CGPA: ");
            if (scanf("%f", &students[i].cgpa) != 1)
            {
                printf("Invalid input for CGPA.\n");
                while (getchar() != '\n')
                    ;
                return;
            }
            printf("Enter new department: ");
            scanf("%s", students[i].department);
            printf("Enter new blood group: ");
            scanf("%s", students[i].bloodGroup);
            printf("Enter new phone number: ");
            scanf("%s", students[i].phoneNumber);
            printf("Student details updated successfully.\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void deleteStudent()
{
    int id, i, j;
    printf("Enter student ID to delete: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for ID.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].id == id)
        {
            for (j = i; j < studentCount - 1; j++)
            {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student with ID %d deleted successfully.\n", id);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void viewAllStudents()
{
    if (studentCount == 0)
    {
        printf("No students found.\n");
        return;
    }

    printf("\nStudent Records:\n");
    for (int i = 0; i < studentCount; i++)
    {
        printf("ID: %d, Name: %s, CGPA: %.2f, Department: %s, Blood Group: %s, Phone: %s\n",
               students[i].id, students[i].name, students[i].cgpa, students[i].department,
               students[i].bloodGroup, students[i].phoneNumber);
    }
}

void searchStudent()
{
    int id;
    printf("Enter student ID to search: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for ID.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == id)
        {
            printf("\nStudent Details:\n");
            printf("ID: %d, Name: %s, CGPA: %.2f, Department: %s, Blood Group: %s, Phone: %s\n",
                   students[i].id, students[i].name, students[i].cgpa, students[i].department,
                   students[i].bloodGroup, students[i].phoneNumber);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void manageSemesterData(Student *student)
{
    if (student->semesterCount >= MAX_SEMESTERS)
    {
        printf("Maximum semester limit reached for this student.\n");
        return;
    }

    printf("Adding data for Semester %d\n", student->semesterCount + 1);
    int subjectCount;
    printf("Enter number of subjects for this semester: ");
    scanf("%d", &subjectCount);
    if (subjectCount > MAX_SUBJECTS)
    {
        printf("Subject count exceeds maximum limit of %d.\n", MAX_SUBJECTS);
        return;
    }

    for (int i = 0; i < subjectCount; i++)
    {
        printf("Enter subject name: ");
        scanf("%s", student->semesters[student->semesterCount][i].subject);
        printf("Enter grade: ");
        if (scanf("%f", &student->semesters[student->semesterCount][i].grade) != 1)
        {
            printf("Invalid input for grade.\n");
            while (getchar() != '\n')
                ;
            return;
        }
    }
    student->subjectsPerSemester[student->semesterCount] = subjectCount;
    student->semesterCount++;
    printf("Semester data added successfully.\n");
}

void viewSemesterData(Student *student)
{
    if (student->semesterCount == 0)
    {
        printf("No semester data available for this student.\n");
        return;
    }

    for (int i = 0; i < student->semesterCount; i++)
    {
        printf("\nSemester %d:\n", i + 1);
        for (int j = 0; j < student->subjectsPerSemester[i]; j++)
        {
            printf("  Subject: %s, Grade: %.2f\n",
                   student->semesters[i][j].subject, student->semesters[i][j].grade);
        }
    }
}

void saveToFile()
{
    FILE *file = fopen("students.dat", "wb");
    if (!file)
    {
        printf("Error saving data.\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("Data saved successfully.\n");
}

void loadFromFile()
{
    FILE *file = fopen("students.dat", "rb");
    if (!file)
        return;
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
}
