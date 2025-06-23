#include "backend.h"
#include <conio.h>


void adminMenu();
void studentMenu(Student *student);
void facultyMenu(Faculty *faculty);
void FAMenu(FA *fa);

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";
const int MAX_PASSWORD_LENGTH = 100;

void exit_program()
{
    system("cls");
    write_all_files();
    string thank = " ========= Thank You =========\n";
    string greet = " ======== See You Soon =======\n";
    for (char c : thank)
    {
        printf("%c", c);
        Sleep(40);
    }
    for (char c : greet)
    {
        printf("%c", c);
        Sleep(40);
    }
    Sleep(1000);
    system("cls");
    exit(0);
}

void maskInput(string &password)
{
    password.clear();
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == '\r' || ch == '\n')
        {
            cout << endl;
            break;
        }
        else if (ch == '\b' && !password.empty())
        {
            cout << "\b \b";
            password.pop_back();
        }
        else if (password.length() < MAX_PASSWORD_LENGTH && ch != '\b')
        {
            cout << "*";
            password.push_back(ch);
        }
    }
}

void loginPage(bool firstTime = false)
{
    if (!firstTime)
    {
        cout << "Press 1 to continue to login page or 0 to go back to main menu: ";
        int choice;
        cin >> choice;
        if (choice == 0)
        {
            system("cls");
            return;
        }
        else if (choice != 1)
        {
            cout << "Invalid choice. Returning to main menu." << endl;
            Sleep(1500);
            system("cls");
            return;
        }
    }

    system("cls");
    cout << "===========================" << endl
         << "         Login Page        " << endl
         << "===========================" << endl;
    cout << "Enter Username: ";
    string username, password;
    cin >> username;
    cin.ignore();
    cout << "Enter Password: ";
    maskInput(password);

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        system("cls");
        if (!headercheck(false))
        {
            cout << "Database not created yet. Please create the database first." << endl;
            createheader();
        }
        adminMenu();
        loginPage();
        return;
    }

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i]->login(username, password))
        {
            system("cls");
            studentMenu(students[i]);
            loginPage();
            return;
        }
    }

    for (int i = 0; i < faculties.size(); i++)
    {
        if (faculties[i]->login(username, password))
        {
            system("cls");
            if (faculties[i]->is_FA_function())
            {
                for (int j = 0; j < fa.size(); j++)
                {
                    if (fa[j]->getFacultyID() == faculties[i]->getFacultyID())
                    {
                        FAMenu(fa[j]);
                        loginPage();
                        break;
                    }
                }
            }
            else
            {
                facultyMenu(faculties[i]);
                loginPage();
            }
            return;
        }
    }
    cout << "Invalid username or password." << endl;
    Sleep(1500);
    system("cls");
    loginPage(true);
}

void adminMenu()
{
    cout << "===========================" << endl
         << "        Admin Panel        " << endl
         << "===========================" << endl
         << "      1. View Students     " << endl
         << "      2. Add Student       " << endl
         << "      3. Delete Student    " << endl
         << "      4. View Faculty      " << endl
         << "      5. Add Faculty       " << endl
         << "      6. Delete Faculty    " << endl
         << "      7. View Courses      " << endl
         << "      8. Add Course        " << endl
         << "      9. Delete Course     " << endl
         << "      0. Log Out           " << endl
         << "===========================" << endl
         << endl
         << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        cout << "Roll No of the present students:" << endl;
        cin.ignore();
        if (students.empty())
        {
            cout << "No students available." << endl;
            cout << "\nPress any key to continue..." << endl;
            cin.ignore();
            system("cls");
            adminMenu();
            return;
        }
        for (int i = 0; i < students.size(); i++)
        {
            cout << students[i]->getRollNo() << endl;
        }
        cout << "Enter the Roll Number of the student to view details: ";
        string rollNo;
        cin >> rollNo;
        bool found = false;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i]->getRollNo() == rollNo)
            {
                found = true;
                system("cls");
                cout << "Details of Student with Roll Number " << rollNo << ":" << endl;
                cin.ignore();
                students[i]->viewDetails();
                break;
            }
        }
        if (found == false)
        {
            cin.ignore();
            cout << "Student with Roll Number " << rollNo << " not found." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
        }
        else
        {
            cout << "Press any key to continue..." << endl;
            cin.ignore();
        }
        system("cls");
        adminMenu();
        break;
    }
    case 2:
    {
        system("cls");
        addstudents();
        cout << "\n\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 3:
    {
        system("cls");
        int size = students.size();
        if (size == 0)
        {
            cin.ignore();
            cout << "No students available to delete." << endl;
            cout << "\n\nPress any key to continue..." << endl;
            cin.ignore();
            system("cls");
            adminMenu();
            return;
        }
        cout << "List of students present:" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << students[i]->getRollNo() << endl;
        }
        deletestudents();
        cout << "\n\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 4:
    {
        system("cls");
        if (faculties.empty())
        {
            cin.ignore();
            system("cls");
            cout << "No faculty available." << endl;
            cout << "\nPress any key to continue..." << endl;
            cin.ignore();
            system("cls");
            adminMenu();
            return;
        }
        cout << "List of Faculty IDs:" << endl;
        for (int i = 0; i < faculties.size(); i++)
        {
            cout << faculties[i]->getFacultyID() << endl;
        }
        cout << "Enter the Faculty ID to view details: ";
        string facultyID;
        cin >> facultyID;
        bool found = false;
        for (int i = 0; i < faculties.size(); i++)
        {
            if (faculties[i]->getFacultyID() == facultyID)
            {
                found = true;
                system("cls");
                cout << "Details of Faculty with ID " << facultyID << ":" << endl;
                cin.ignore();
                faculties[i]->viewDetails();
                break;
            }
        }
        if (!found)
        {
            cin.ignore();
            system("cls");
            cout << "Faculty with ID " << facultyID << " not found." << endl;
        }
        cout << "\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 5:
    {
        system("cls");
        cout << "Adding Faculty..." << endl;
        addfaculty();
        cout << "\n\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 6:
    {
        system("cls");
        if (faculties.empty())
        {
            cin.ignore();
            cout << "No faculty available to delete." << endl;
            cout << "\n\nPress any key to continue..." << endl;
            cin.ignore();
            system("cls");
            adminMenu();
            return;
        }
        cout << "List of Faculty IDs:" << endl;
        for (int i = 0; i < faculties.size(); i++)
        {
            cout << faculties[i]->getFacultyID() << endl;
        }
        deletefaculty();
        cout << "\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 7:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Courses..." << endl;
        cout << "Semester 1 Courses:" << endl;
        if (courses_sem1.empty())
        {
            cout << "No courses available for Semester 1." << endl;
        }
        else
        {
            for (int i = 0; i < courses_sem1.size(); i++)
            {
                cout << "Course ID: " << courses_sem1[i]->getID() << ", Credits: " << courses_sem1[i]->getCredits() << endl;
            }
        }
        cout << "Semester 2 Courses:" << endl;
        if (courses_sem2.empty())
        {
            cout << "No courses available for Semester 2." << endl;
        }
        else
        {
            for (int i = 0; i < courses_sem2.size(); i++)
            {
                cout << "Course ID: " << courses_sem2[i]->getID() << ", Credits: " << courses_sem2[i]->getCredits() << endl;
            }
        }
        cout << "\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 8:
    {
        system("cls");
        addcourse();
        cout << "\n\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 9:
    {
        system("cls");
        cin.ignore();
        cout << "Courses available for deletion in Semester 1:" << endl;
        if (courses_sem1.empty())
            cout << "No courses available for Semester 1." << endl;
        else
        {
            for (int i = 0; i < courses_sem1.size(); i++)
            {
                cout << "Course ID: " << courses_sem1[i]->getID() << ", Credits: " << courses_sem1[i]->getCredits() << endl;
            }
        }
        cout << "Courses available for deletion in Semester 2:" << endl;
        if (courses_sem2.empty())
            cout << "No courses available for Semester 2." << endl;
        else
        {
            for (int i = 0; i < courses_sem2.size(); i++)
            {
                cout << "Course ID: " << courses_sem2[i]->getID() << ", Credits: " << courses_sem2[i]->getCredits() << endl;
            }
        }
        deletecourse();
        cout << "\nPress any key to continue..." << endl;
        cin.ignore();
        system("cls");
        adminMenu();
        break;
    }
    case 0:
    {
        system("cls");
        return;
    }
    }
}

void studentMenu(Student *student)
{
    system("cls");
    cout << "Welcome, " << student->getName() << "!" << endl;
    cout << "Roll Number: " << student->getRollNo() << endl;

    cout << "=================================" << endl
         << "          Student Panel          " << endl
         << "=================================" << endl
         << "         1. View Profile         " << endl
         << "         2. Edit Profile         " << endl
         << "         3. View Courses         " << endl
         << "         4. View Attendance      " << endl
         << "         5. View Marks           " << endl
         << "         6. Apply for Leave      " << endl
         << "         7. Register for Courses " << endl
         << "         8. View Leave Records   " << endl
         << "         9. Change Password      " << endl
         << "         0. Log Out              " << endl
         << "=================================" << endl
         << endl;
    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Profile..." << endl;
        student->viewDetails();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 2:
    {
        cin.ignore();
        system("cls");
        student->editProfile();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 3:
    {
        cin.ignore();
        system("cls");
        vector<Course *> registeredCourses = student->getRegisteredCourses();
        if (registeredCourses.empty())
        {
            cout << "No courses registered." << endl;
        }
        else
        {
            cout << "Registered Courses: " << endl;
            cout << "Course ID\tCredits\t\tCompulsory" << endl;
            for (auto &&course : registeredCourses)
            {
                cout << course->getID() << "\t\t" << course->getCredits() << "\t\t" << (course->isCompulsoryCourse() ? "Yes" : "No") << endl;
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 4:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Attendance..." << endl;
        map<string, int> attendance = student->getAttendance();
        if (attendance.empty())
        {
            cout << "No attendance records found." << endl;
        }
        else
        {
            for (auto &&entry : attendance)
            {
                if (entry.second == -1)
                {
                    cout << "Course ID: " << entry.first << ", Attendance: Not recorded" << endl;
                }
                else
                {
                    cout << "Course ID: " << entry.first << ", Attendance: " << entry.second << endl;
                }
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 5:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Marks..." << endl;
        map<string, int> marks = student->getMarks();
        if (marks.empty())
        {
            cout << "No marks records found." << endl;
        }
        else
        {
            for (auto &&subject : marks)
            {
                if (subject.second == -1)
                {
                    cout << "Course ID: " << subject.first << ", Marks: Not recorded" << endl;
                    continue;
                }
                else
                {
                    cout << "Course ID: " << subject.first << ", Marks: " << subject.second << endl;
                }
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 6:
    {
        cin.ignore();
        system("cls");
        cout << "Applying for Leave..." << endl;
        string reason;
        Date startDate, endDate;
        cout << "Enter reason for leave: ";
        getline(cin, reason);
        cout << "Enter start date (DD MM YYYY): ";
        int day, month, year;
        cin >> day >> month >> year;
        startDate = Date(day, month, year);
        cout << "Enter end date (DD MM YYYY): ";
        cin >> day >> month >> year;
        endDate = Date(day, month, year);
        while (startDate.Calculate_days(startDate, endDate) < 0)
        {
            cout << "Invalid date range." << endl;
            cout << "Enter start date (DD MM YYYY): ";
            cin >> day >> month >> year;
            startDate = Date(day, month, year);
            cout << "Enter end date (DD MM YYYY): ";
            cin >> day >> month >> year;
            endDate = Date(day, month, year);
        }
        student->applyForLeave(reason, startDate, endDate);
        cin.ignore();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 7:
    {
        cin.ignore();
        system("cls");
        cout << "Registering for Courses..." << endl;
        int sem_num = student->getSemNum();
        vector<Course *> availableCourses;
        if (sem_num == 1)
        {
            availableCourses = courses_sem1;
        }
        else if (sem_num == 2)
        {
            availableCourses = courses_sem2;
        }
        else
        {
            cout << "No courses available for this semester." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            studentMenu(student);
            return;
        }
        if (availableCourses.empty())
        {
            cout << "No courses available." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            studentMenu(student);
            return;
        }

        cout << "Extra Courses for Semester " << sem_num << ":" << endl;
        cout << "Course ID\tCredits\t\tRegistered" << endl;
        vector<Course *> notCompulsoryCourses;
        int count = 0;
        int flag = 0;
        for (auto &&course : availableCourses)
        {
            if (!course->isCompulsoryCourse())
            {
                cout << course->getID() << "\t\t" << course->getCredits() << "\t\t";
                for (auto &&registeredCourse : student->getRegisteredCourses())
                {
                    if (registeredCourse->getID() == course->getID())
                    {
                        count++;
                        cout << "Yes" << endl;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    cout << "No" << endl;
                    notCompulsoryCourses.push_back(course);
                }
            }
        }
        if (notCompulsoryCourses.empty())
        {
            cout << "No extra courses available for registration." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            studentMenu(student);
            return;
        }
        if (count >= 2)
        {
            cout << "No extra courses can be registered." << endl;
        }
        else
        {
            cout << "You can register for " << 2 - count << " extra courses." << endl;
            cout << "Enter Course ID to register: ";
            string courseID;
            cin >> courseID;
            cin.ignore();
            bool found = false;
            for (auto &&course : notCompulsoryCourses)
            {
                if (course->getID() == courseID)
                {
                    found = true;
                    course->enrollStudent(student->getRollNo());
                    cout << "Course ID: " << courseID << " registered successfully." << endl;
                    student->addSubject(course);
                    student->addMarks(courseID, -1);
                    student->addAttendance(courseID, -1);
                    cout << "Press any key to continue..." << endl;
                    cin.ignore();
                    system("cls");
                    studentMenu(student);
                    return;
                }
            }
            if (!found)
            {
                cout << "Course ID not found or already registered." << endl;
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        return;
    }
    case 8:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Leave Records..." << endl;
        vector<LeaveApplication *> leaveHistory = student->getLeaveHistory();
        if (leaveHistory.empty())
        {
            cout << "No leave records found." << endl;
        }
        else
        {
            for (auto leave : leaveHistory)
            {
                cout << endl
                     << "Reason: " << leave->getReason() << endl
                     << "Start Date: " << leave->getStartDate().showDate()
                     << endl
                     << "End Date: " << leave->getEndDate().showDate() << endl
                     << "Status: " << leave->getStatus() << endl;
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        return;
    }
    case 9:
    {
        cin.ignore();
        system("cls");
        cout << "Changing Password..." << endl;
        string newPassword;
        cout << "Enter new password: ";
        maskInput(newPassword);
        cout << "Confirm new password: ";
        string confirmPassword;
        cin >> confirmPassword;
        cin.ignore();
        if (confirmPassword == newPassword && student->changePassword(newPassword))
        {
            cout << "Password changed successfully." << endl;
        }
        else
        {
            cout << "Both the passwords dont match or failed to change password." << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        return;
    }
    case 0:
    {
        system("cls");
        return;
    }
    }
}

void facultyMenu(Faculty *faculty)
{
    system("cls");
    cout << "Welcome, " << faculty->getFacultyName() << "!" << endl
         << "Faculty ID: " << faculty->getFacultyID() << endl;

    cout << "=================================" << endl
         << "          Faculty Panel          " << endl
         << "=================================" << endl
         << "          1. View Profile        " << endl
         << "          2. View Courses        " << endl
         << "          3. View Attendance     " << endl
         << "          4. Add Attendance      " << endl
         << "          5. View Marks          " << endl
         << "          6. Add Marks           " << endl
         << "          7. Add Course          " << endl
         << "          8. Remove Course       " << endl
         << "          9. Edit Profile        " << endl
         << "          10. Change Password    " << endl
         << "          0. Log Out             " << endl
         << "=================================" << endl
         << endl
         << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Profile..." << endl;
        faculty->viewDetails();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 2:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Courses..." << endl;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 3:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Attendance..." << endl;
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            break;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        cout << "Enter Course ID to view attendance: ";
        string subjectId;
        cin >> subjectId;
        bool flag = false;
        cin.ignore();
        system("cls");
        for (auto &&it : faculty->getSubjects())
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Attendance for Course ID: " << it->getID() << endl;
                map<string, int> attendance = it->getAttendance();
                if (attendance.empty())
                {
                    cout << "No attendance records found." << endl;
                }
                else
                {
                    for (auto &&subject : attendance)
                    {
                        if (subject.second == -1)
                        {
                            cout << "Student Roll No: " << subject.first << ", Attendance: Not recorded" << endl;
                            continue;
                        }
                        cout << "Student Roll No: " << subject.first << ", Attendance: " << subject.second << "." << endl;
                    }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 4:
    {
        cin.ignore();
        system("cls");
        cout << "Add Attendance..." << endl;
        cout << "Available Courses: " << endl;
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            break;
        }
        for (auto &&it : alreadyRegistered)
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to add attendance: ";
        string subjectId;
        cin >> subjectId;
        cin.ignore();
        bool flag = false;
        for (auto &&it : alreadyRegistered)
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Adding Attendance for Course ID: " << it->getID() << endl;
                vector<string> students = it->getStudents();
                if (students.empty())
                {
                    cout << "No students enrolled in this course." << endl;
                    break;
                }
                cout << "1. Add Attendance for all students." << endl;
                cout << "2. Add Attendance for specific students." << endl;
                int choice2;
                cin >> choice2;
                while (choice2 < 1 || choice2 > 2)
                {
                    cout << "Invalid choice. Please try again." << endl;
                    cin >> choice2;
                }
                switch (choice2)
                {
                case 1:
                {
                    cout << "Enter attendance for each student:" << endl;
                    for (auto &&student : students)
                    {
                        int attendance;
                        cout << "Student Roll No: " << student << ", Enter Attendance (0-100): ";
                        cin >> attendance;
                        while (attendance < 0 || attendance > 100)
                        {
                            cout << "Invalid attendance. Please enter between 0 and 100: ";
                            cin >> attendance;
                        }
                        it->add_attendance(student, attendance);
                        Student *s = students_map[student];
                        s->addAttendance(it->getID(), attendance);
                        cout << "Attendance added for " << student << ": " << attendance << endl;
                    }
                    break;
                }
                case 2:
                {
                    cout << "All students : " << endl;
                    for (auto &&student : students)
                    {
                        cout << student << endl;
                    }
                    cout << "Enter Roll No of student to add attendance: ";
                    string rollNo;
                    bool flag2 = false;
                    while (!flag2)
                    {
                        cin >> rollNo;
                        for (auto &&student : students)
                        {
                            if (student == rollNo)
                            {
                                flag2 = true;
                                int attendance;
                                cout << "No. of classes attended by Student Roll No: " << student << " is: ";
                                cin >> attendance;
                                while (attendance < 0 || attendance > 100)
                                {
                                    cout << "Invalid attendance. Please enter attendance between 0 and 100: ";
                                    cin >> attendance;
                                }
                                it->add_attendance(student, attendance);
                                Student *s = students_map[student];
                                s->addAttendance(it->getID(), attendance);
                                cout << "Attendance added for " << student << ": " << attendance << endl;
                            }
                        }
                        if (!flag2)
                        {
                            cout << "Invalid Roll No. Please try again." << endl;
                        }
                    }
                }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 5:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Marks..." << endl;
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            break;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        cout << "Enter Course ID to view marks: ";
        string subjectId;
        cin >> subjectId;
        bool flag = false;
        cin.ignore();
        system("cls");
        for (auto &&it : faculty->getSubjects())
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Marks for Course ID: " << it->getID() << endl;
                map<string, int> marks = it->getMarks();
                if (marks.empty())
                {
                    cout << "No marks records found." << endl;
                }
                else
                {
                    for (auto &&subject : marks)
                    {
                        if (subject.second == -1)
                        {
                            cout << "Student Roll No: " << subject.first << ", Marks: Not recorded" << endl;
                            continue;
                        }
                        cout << "Student Roll No: " << subject.first << ", Marks: " << subject.second << "." << endl;
                    }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 6:
    {
        cin.ignore();
        system("cls");
        cout << "Add Marks..." << endl;
        cout << "Available Courses: " << endl;
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            break;
        }
        for (auto &&it : alreadyRegistered)
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to add marks: ";
        string subjectId;
        cin >> subjectId;
        cin.ignore();
        bool flag = false;
        for (auto &&it : alreadyRegistered)
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Adding Marks for Course ID: " << it->getID() << endl;
                vector<string> students = it->getStudents();
                if (students.empty())
                {
                    cout << "No students enrolled in this course." << endl;
                    break;
                }
                cout << "1. Add Marks for all students." << endl;
                cout << "2. Add Marks for specific students." << endl;
                int choice2;
                cin >> choice2;
                while (choice2 < 1 || choice2 > 2)
                {
                    cout << "Invalid choice. Please try again." << endl;
                    cin >> choice2;
                }
                switch (choice2)
                {
                case 1:
                {
                    cout << "Enter marks for each student:" << endl;
                    for (auto &&student : students)
                    {
                        int mark;
                        cout << "Student Roll No: " << student << ", Enter Marks: ";
                        cin >> mark;
                        while (mark < 0 || mark > 100)
                        {
                            cout << "Invalid marks. Please enter marks between 0 and 100: ";
                            cin >> mark;
                        }
                        it->add_marks(student, mark);
                        Student *s = students_map[student];
                        s->addMarks(it->getID(), mark);
                        cout << "Marks added for " << student << ": " << mark << endl;
                    }
                    break;
                }
                case 2:
                {
                    cout << "All students : " << endl;
                    for (auto &&student : students)
                    {
                        cout << student << endl;
                    }
                    cout << "Enter Roll No of student to add marks: ";
                    string rollNo;
                    bool flag2 = false;
                    while (!flag2)
                    {
                        cin >> rollNo;
                        for (auto &&student : students)
                        {
                            if (student == rollNo)
                            {
                                flag2 = true;
                                int mark;
                                cout << "Student Roll No: " << student << ", Enter Marks: ";
                                cin >> mark;
                                while (mark < 0 || mark > 100)
                                {
                                    cout << "Invalid marks. Please enter marks between 0 and 100: ";
                                    cin >> mark;
                                }
                                it->add_marks(student, mark);
                                Student *s = students_map[student];
                                s->addMarks(it->getID(), mark);
                                cout << "Marks added for " << student << ": " << mark << endl;
                            }
                        }
                        if (!flag2)
                        {
                            cout << "Invalid Roll No. Please try again." << endl;
                        }
                    }
                }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 7:
    {
        cin.ignore();
        system("cls");
        cout << "Adding Courses..." << endl;
        int count = 0;
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        count = alreadyRegistered.size();
        if (count == 0)
        {
            cout << "No courses registered." << endl;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        if (count >= 5)
        {
            cout << "You cannot add more than 5 courses." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            return;
        }
        for (auto &course : courses_sem1)
        {
            bool flag = false;
            for (auto &registeredCourse : alreadyRegistered)
            {
                if (course->getID() == registeredCourse->getID())
                {
                    flag = true;
                    continue;
                }
            }
            if (!flag)
            {
                availableCourses.push_back(course);
            }
        }
        for (auto &course : courses_sem2)
        {
            bool flag = false;
            for (auto &registeredCourse : alreadyRegistered)
            {
                if (course->getID() == registeredCourse->getID())
                {
                    flag = true;
                    continue;
                }
            }
            if (!flag)
            {
                availableCourses.push_back(course);
            }
        }
        if (availableCourses.empty())
        {
            cout << "No courses available." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            return;
        }
        bool found = false;
        cout << "Available Courses: " << endl;
        for (auto &course : availableCourses)
        {
            cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
        }
        cout << "Enter Course ID to add: ";
        string courseID;
        cin >> courseID;
        cin.ignore();
        for (auto &course : availableCourses)
        {
            if (course->getID() == courseID)
            {
                found = true;
                faculty->AssignSubject(course, true);
                cout << "Course ID: " << courseID << " added successfully." << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Course ID not found." << endl;
            Sleep(1000);
            system("cls");
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 8:
    {
        cin.ignore();
        system("cls");
        cout << "Deleting Courses..." << endl;
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            facultyMenu(faculty);
            return;
        }
        cout << "Already registered courses: " << endl;
        for (auto &&course : alreadyRegistered)
        {
            cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
        }
        cout << "Enter Course ID to delete: ";
        string courseID;
        cin >> courseID;
        cin.ignore();
        bool found = false;
        for (auto &&course : alreadyRegistered)
        {
            if (course->getID() == courseID)
            {
                found = true;
                faculty->removeSubject(course);
                cout << "Course ID: " << courseID << " deleted successfully." << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Course ID not found." << endl;
            Sleep(1000);
            system("cls");
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 9:
    {
        cin.ignore();
        system("cls");
        faculty->editProfile();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 10:
    {
        cin.ignore();
        system("cls");
        cout << "Changing Password..." << endl;
        string newPassword;
        cout << "Enter new password: ";
        maskInput(newPassword);
        cout << "Confirm new password: ";
        string confirmPassword;
        cin >> confirmPassword;
        cin.ignore();
        if (confirmPassword == newPassword && faculty->changePassword(newPassword))
        {
            cout << "Password changed successfully." << endl;
        }
        else
        {
            cout << "Both the passwords dont match or failed to change password." << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        facultyMenu(faculty);
        break;
    }
    case 0:
    {
        system("cls");
        return;
    }
    }
}

void FAMenu(FA *fa)
{
    system("cls");
    cout << "Welcome, " << fa->getFacultyName() << "!" << endl
         << "FA ID: " << fa->getID() << endl;

    cout << "=============================================" << endl
         << "                Faculty Panel                " << endl
         << "=============================================" << endl
         << "               1. View Profile               " << endl
         << "               2. View Courses               " << endl
         << "               3. View Attendance            " << endl
         << "               4. Add Attendance             " << endl
         << "               5. View Marks                 " << endl
         << "               6. Add Marks                  " << endl
         << "               7. View Assigned Students     " << endl
         << "               8. Review Leave applications  " << endl
         << "               9. Add Courses                " << endl
         << "               10. Delete Courses            " << endl
         << "               11. Edit Profile              " << endl
         << "               12. Change Password           " << endl
         << "               0. Log Out                    " << endl
         << "=============================================" << endl
         << endl;

    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Profile..." << endl;
        fa->viewDetails();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 2:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Courses..." << endl;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 3:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Attendance..." << endl;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            break;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        cout << "Enter Course ID to view attendance: ";
        string subjectId;
        cin >> subjectId;
        bool flag = false;
        cin.ignore();
        system("cls");
        for (auto &&it : faculty->getSubjects())
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Attendance for Course ID: " << it->getID() << endl;
                map<string, int> attendance = it->getAttendance();
                if (attendance.empty())
                {
                    cout << "No attendance records found." << endl;
                }
                else
                {
                    for (auto &&subject : attendance)
                    {
                        if (subject.second == -1)
                        {
                            cout << "Student Roll No: " << subject.first << ", Attendance: Not recorded" << endl;
                            continue;
                        }
                        cout << "Student Roll No: " << subject.first << ", Attendance: " << subject.second << "." << endl;
                    }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 4:
    {
        cin.ignore();
        system("cls");
        cout << "Add Attendance..." << endl;
        cout << "Available Courses: " << endl;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            break;
        }
        for (auto &&it : alreadyRegistered)
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to add attendance: ";
        string subjectId;
        cin >> subjectId;
        cin.ignore();
        bool flag = false;
        for (auto &&it : alreadyRegistered)
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Adding Attendance for Course ID: " << it->getID() << endl;
                vector<string> students = it->getStudents();
                if (students.empty())
                {
                    cout << "No students enrolled in this course." << endl;
                    break;
                }
                cout << "1. Add Attendance for all students." << endl;
                cout << "2. Add Attendance for specific students." << endl;
                int choice2;
                cin >> choice2;
                while (choice2 < 1 || choice2 > 2)
                {
                    cout << "Invalid choice. Please try again." << endl;
                    cin >> choice2;
                }
                switch (choice2)
                {
                case 1:
                {
                    system("cls");
                    cout << "Enter attendance for each student:" << endl;
                    for (auto &&student : students)
                    {
                        int attendance;
                        cout << "Student Roll No: " << student << ", Enter Attendance (0-100): ";
                        cin >> attendance;
                        while (attendance < 0 || attendance > 100)
                        {
                            cout << "Invalid attendance. Please enter between 0 and 100: ";
                            cin >> attendance;
                        }
                        it->add_attendance(student, attendance);
                        Student *s = students_map[student];
                        s->addAttendance(it->getID(), attendance);
                        cout << "Attendance added for " << student << ": " << attendance << endl;
                    }
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "All students : " << endl;
                    for (auto &&student : students)
                    {
                        cout << student << endl;
                    }
                    cout << "Enter Roll No of student to add attendance: ";
                    string rollNo;
                    bool flag2 = false;
                    while (!flag2)
                    {
                        cin >> rollNo;
                        for (auto &&student : students)
                        {
                            if (student == rollNo)
                            {
                                flag2 = true;
                                int attendance;
                                cout << "Student Roll No: " << student << ", Enter Attendance (0-100): ";
                                cin >> attendance;
                                while (attendance < 0 || attendance > 100)
                                {
                                    cout << "Invalid attendance. Please enter attendance between 0 and 100: ";
                                    cin >> attendance;
                                }
                                it->add_attendance(student, attendance);
                                Student *s = students_map[student];
                                s->addAttendance(it->getID(), attendance);
                                cout << "Attendance added for " << student << ": " << attendance << endl;
                            }
                        }
                        if (!flag2)
                        {
                            cout << "Invalid Roll No. Please try again." << endl;
                        }
                    }
                }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 5:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Marks..." << endl;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            break;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        cout << "Enter Course ID to view marks: ";
        string subjectId;
        cin >> subjectId;
        bool flag = false;
        cin.ignore();
        system("cls");
        for (auto &&it : faculty->getSubjects())
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Marks for Course ID: " << it->getID() << endl;
                map<string, int> marks = it->getMarks();
                if (marks.empty())
                {
                    cout << "No marks records found." << endl;
                }
                else
                {
                    for (auto &&subject : marks)
                    {
                        if (subject.second == -1)
                        {
                            cout << "Student Roll No: " << subject.first << ", Marks: Not recorded" << endl;
                            continue;
                        }
                        cout << "Student Roll No: " << subject.first << ", Marks: " << subject.second << "." << endl;
                    }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 6:
    {
        cin.ignore();
        system("cls");
        cout << "Add Marks..." << endl;
        cout << "Available Courses: " << endl;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            break;
        }
        for (auto &&it : alreadyRegistered)
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to add marks: ";
        string subjectId;
        cin >> subjectId;
        cin.ignore();
        bool flag = false;
        for (auto &&it : alreadyRegistered)
        {
            if (it->getID() == subjectId)
            {
                flag = true;
                cout << "Adding Marks for Course ID: " << it->getID() << endl;
                vector<string> students = it->getStudents();
                if (students.empty())
                {
                    cout << "No students enrolled in this course." << endl;
                    break;
                }
                cout << "1. Add Marks for all students." << endl;
                cout << "2. Add Marks for specific students." << endl;
                int choice2;
                cin >> choice2;
                while (choice2 < 1 || choice2 > 2)
                {
                    cout << "Invalid choice. Please try again." << endl;
                    cin >> choice2;
                }
                switch (choice2)
                {
                case 1:
                {
                    system("cls");
                    cout << "Enter marks for each student:" << endl;
                    for (auto &&student : students)
                    {
                        int mark;
                        cout << "Student Roll No: " << student << ", Enter Marks: ";
                        cin >> mark;
                        while (mark < 0 || mark > 100)
                        {
                            cout << "Invalid marks. Please enter marks between 0 and 100: ";
                            cin >> mark;
                        }
                        it->add_marks(student, mark);
                        Student *s = students_map[student];
                        s->addMarks(it->getID(), mark);
                        cout << "Marks added for " << student << ": " << mark << endl;
                    }
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "All students : " << endl;
                    for (auto &&student : students)
                    {
                        cout << student << endl;
                    }
                    cout << "Enter Roll No of student to add marks: ";
                    string rollNo;
                    bool flag2 = false;
                    while (!flag2)
                    {
                        cin >> rollNo;
                        for (auto &&student : students)
                        {
                            if (student == rollNo)
                            {
                                flag2 = true;
                                int mark;
                                system("cls");
                                cout << "Student Roll No: " << student << ", Enter Marks: ";
                                cin >> mark;
                                while (mark < 0 || mark > 100)
                                {
                                    cout << "Invalid marks. Please enter marks between 0 and 100: ";
                                    cin >> mark;
                                }
                                it->add_marks(student, mark);
                                Student *s = students_map[student];
                                s->addMarks(it->getID(), mark);
                                cout << "Marks added for " << student << ": " << mark << endl;
                            }
                        }
                        if (!flag2)
                        {
                            cout << "Invalid Roll No. Please try again." << endl;
                        }
                    }
                }
                }
            }
        }
        if (!flag)
        {
            cout << "Invalid Course ID. Please try again: " << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 7:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Assigned Students..." << endl;
        fa->viewAssignedStudents();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 8:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Notifications / Reviewing Leave application..." << endl;
        if (fa->isNewNotification())
        {
            fa->reviewLeaveApplication();
        }
        else
        {
            cout << "No new notifications." << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 9:
    {
        cin.ignore();
        system("cls");
        cout << "Adding Courses..." << endl;
        int count = 0;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        count = alreadyRegistered.size();
        if (count == 0)
        {
            cout << "No courses registered." << endl;
        }
        else
        {
            cout << "Already registered courses: " << endl;
            for (auto &&course : alreadyRegistered)
            {
                cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
            }
        }
        if (count >= 5)
        {
            cout << "You cannot add more than 5 courses." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            return;
        }
        for (auto &course : courses_sem1)
        {
            bool flag = false;
            for (auto &registeredCourse : alreadyRegistered)
            {
                if (course->getID() == registeredCourse->getID())
                {
                    flag = true;
                    continue;
                }
            }
            if (!flag)
            {
                availableCourses.push_back(course);
            }
        }
        for (auto &course : courses_sem2)
        {
            bool flag = false;
            for (auto &registeredCourse : alreadyRegistered)
            {
                if (course->getID() == registeredCourse->getID())
                {
                    flag = true;
                    continue;
                }
            }
            if (!flag)
            {
                availableCourses.push_back(course);
            }
        }
        if (availableCourses.empty())
        {
            cout << "No courses available." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            return;
        }
        bool found = false;
        cout << "Available Courses: " << endl;
        for (auto &course : availableCourses)
        {
            cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
        }
        cout << "Enter Course ID to add: ";
        string courseID;
        cin >> courseID;
        cin.ignore();
        for (auto &course : availableCourses)
        {
            if (course->getID() == courseID)
            {
                found = true;
                fa->AssignSubject(course, false);
                faculty->AssignSubject(course, true);
                cout << "Course ID: " << courseID << " added successfully." << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Course ID not found." << endl;
            Sleep(1000);
            system("cls");
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 10:
    {
        cin.ignore();
        system("cls");
        cout << "Deleting Courses..." << endl;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course *> availableCourses;
        vector<Course *> alreadyRegistered = faculty->getSubjects();
        if (alreadyRegistered.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            return;
        }
        cout << "Already registered courses: " << endl;
        for (auto &&course : alreadyRegistered)
        {
            cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
        }
        cout << "Enter Course ID to delete: ";
        string courseID;
        cin >> courseID;
        cin.ignore();
        bool found = false;
        for (auto &&course : alreadyRegistered)
        {
            if (course->getID() == courseID)
            {
                found = true;
                faculty->removeSubject(course);
                cout << "Course ID: " << courseID << " deleted successfully." << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Course ID not found." << endl;
            Sleep(1000);
            system("cls");
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 11:
    {
        cin.ignore();
        system("cls");
        fa->editProfile();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 12:
    {
        cin.ignore();
        system("cls");
        cout << "Changing Password..." << endl;
        string newPassword;
        cout << "Enter new password: ";
        maskInput(newPassword);
        cout << "Confirm new password: ";
        string confirmPassword;
        cin >> confirmPassword;
        cin.ignore();
        Faculty *faculty = faculties_map[fa->getID()];
        if (confirmPassword == newPassword && fa->changePassword(newPassword) && faculty->changePassword(newPassword))
        {
            cout << "Password changed successfully." << endl;
        }
        else
        {
            cout << "Both the passwords dont match or failed to change password." << endl;
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        FAMenu(fa);
        break;
    }
    case 0:
    {
        system("cls");
        return;
    }
    }
}

void aboutUs()
{
    system("cls");
    string Intro = "                               *************************************                               \n"
               "--> This project is a collaborative effort by the authors to create a student database management portal,\n"
               "    incorporating various possible features typically present in such a system.\n"
               "--> The code, in its entirety, is based solely on the C++ language.\n"
               "--> This is Version 2 of our previous model, now enhanced with Object-Oriented Programming (OOP) concepts\n"
               "    for better structure, scalability, and maintainability.\n"
               "                               *************************************                               \n\n";

    for (char c : Intro)
    {
        printf("%c", c);
        Sleep(20);
    }
    string Authors = "============================================\n|| Sl.no. |     Authors     | Roll number ||\n============================================\n||   1.   |  Vishwas Dabhi  |  23CS01015  ||\n||   2.   |  Shashank M N   |  23CS02010  ||\n||   3.   |  Arit Gandhi    |  23CS01006  ||\n============================================\n\n";
    for (char c : Authors)
    {
        if (c == '\n')
        {
            printf("%c", c);
            Sleep(50);
            continue;
        }
        printf("%c", c);
        Sleep(30);
    }

    cout << "Press any key to continue..." << endl;
    cin.ignore();

    system("cls");
    int choice;
    cout << "\nEnter  1: Go to Main Menu\n       0: Exit\n";
    cout << "Enter the choice: ";
    cin >> choice;
    if (choice == 1)
    {
        system("cls");
        return;
    }
    else
        exit_program();
}
