#include "backend.cpp"
#include <conio.h>

/*
think if we can add some colsole based design
*/

void adminMenu();
void studentMenu(Student *student);
void facultyMenu(Faculty *faculty);
void FAMenu(FA *fa);

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";
const int MAX_PASSWORD_LENGTH = 100;

void exit_program()
{
    write_all_files();
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

void loginPage()
{
    cout << "Login (Press quit in username to log out)" << endl;
    cout << "Enter Username: ";
    string username, password;
    cin >> username;
    if (username == "quit")
        exit_program();
    cin.ignore();
    cout << "Enter Password: ";
    maskInput(password);
    cout << "You entered: " << password << endl; // For debugging, can be removed later

    // Check Admin
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        system("cls");
        if (headercheck())
        {
            cout << "Welcome to the Admin Panel!" << endl;
        }
        else
        {
            cout << "Database not created yet. Please create the database first." << endl;
            createheader();
        }
        adminMenu();
        loginPage();
        return;
    }

    // Check Students
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].login(username, password))
        {
            system("cls");
            studentMenu(&students[i]);
            loginPage();
            return;
        }
    }

    // Check Faculty (including FA)
    for (int i = 0; i < faculties.size(); i++)
    {
        if (faculties[i].login(username, password))
        {
            system("cls");
            if (faculties[i].is_FA_function())
            {
                for (int j = 0; j < fa.size(); j++)
                {
                    if (fa[j].getFacultyID() == faculties[i].getFacultyID())
                    {
                        FAMenu(&fa[j]);
                        loginPage();
                        break;
                    }
                }
            }
            else
            {
                facultyMenu(&faculties[i]);
                loginPage();
            }
            return;
        }
    }

    cout << "Invalid username or password." << endl;
    Sleep(1500);
    system("cls");
    loginPage();
}

void adminMenu()
{
    cout << "--- Admin Panel ---" << endl;
    cout << "1. View Students" << endl;
    cout << "2. Add Student" << endl;
    cout << "3. Delete Student" << endl;
    cout << "4. View Faculty" << endl;
    cout << "5. Add Faculty" << endl;
    cout << "6. Delete Faculty" << endl;
    cout << "7. View Courses" << endl;
    cout << "8. Add Course" << endl;
    cout << "9. Delete Course" << endl;
    cout << "0. Log Out" << endl;
    cout << "Please select an option: ";
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
            cout << students[i].getRollNo() << endl;
        }
        cout << "Enter the Roll Number of the student to view details: ";
        string rollNo;
        cin >> rollNo;
        bool found = false;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getRollNo() == rollNo)
            {
                found = true;
                system("cls");
                cout << "Details of Student with Roll Number " << rollNo << ":" << endl;
                cin.ignore();
                students[i].viewDetails();
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
            cout << students[i].getRollNo() << endl;
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
            cout << faculties[i].getFacultyID() << endl;
        }
        cout << "Enter the Faculty ID to view details: ";
        string facultyID;
        cin >> facultyID;
        bool found = false;
        for (int i = 0; i < faculties.size(); i++)
        {
            if (faculties[i].getFacultyID() == facultyID)
            {
                found = true;
                system("cls");
                cout << "Details of Faculty with ID " << facultyID << ":" << endl;
                cin.ignore();
                faculties[i].viewDetails();
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
            cout << faculties[i].getFacultyID() << endl;
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
                cout << "Course ID: " << courses_sem1[i].getID() << ", Credits: " << courses_sem1[i].getCredits() << endl;
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
                cout << "Course ID: " << courses_sem2[i].getID() << ", Credits: " << courses_sem2[i].getCredits() << endl;
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
                cout << "Course ID: " << courses_sem1[i].getID() << ", Credits: " << courses_sem1[i].getCredits() << endl;
            }
        }
        cout << "Courses available for deletion in Semester 2:" << endl;
        if (courses_sem2.empty())
            cout << "No courses available for Semester 2." << endl;
        else
        {
            for (int i = 0; i < courses_sem2.size(); i++)
            {
                cout << "Course ID: " << courses_sem2[i].getID() << ", Credits: " << courses_sem2[i].getCredits() << endl;
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
    cout << "\n--- Student Panel ---" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. Edit Profile" << endl;
    cout << "3. View Courses" << endl;
    cout << "4. View Attendance" << endl;
    cout << "5. View Marks" << endl;
    cout << "6. Apply for Leave" << endl;
    cout << "7. View Notifications" << endl;
    cout << "8. Give Feedback" << endl;
    cout << "9. Register for Courses" << endl;
    cout << "10. View Leave Records" << endl;
    cout << "0. Log Out" << endl;

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
            cout << "Course ID\tCredits\tCompulsory" << endl;
            for (auto &&course : registeredCourses)
            {
                cout << course->getID() << "\t" << course->getCredits() << "\t" << (course->isCompulsoryCourse() ? "Yes" : "No") << endl;
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
                cout << "Course ID: " << entry.first << ", Attendance: " << entry.second << "%" << endl;
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
                cout << "Course ID: " << subject.first << ", Marks: " << subject.second << endl;
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
        cout << "Viewing Notifications..." << endl;
        student->viewNotifications();
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 8:
    {
        cin.ignore();
        system("cls");
        cout << "Giving Feedback..." << endl;
        cout << "Available Courses: " << endl;
        vector<Course *> registeredCourses = student->getRegisteredCourses();
        if (registeredCourses.empty())
        {
            cout << "No courses registered." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            studentMenu(student);
            return;
        }
        for (auto &&course : registeredCourses)
        {
            cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
        }
        cout << "Enter Course ID to give feedback: ";
        string courseID;
        cin >> courseID;
        string feedback;
        cout << "Enter your feedback: ";
        cin.ignore();
        getline(cin, feedback);
        student->giveFeedback(courseID, feedback); // to be implemented
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 9:
    {
        cin.ignore();
        system("cls");
        cout << "Registering for Courses..." << endl;
        cout << "Available Courses: " << endl;
        int sem_num = student->getSemNum();
        vector<Course> availableCourses;
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
        cout << "Course ID\tCredits\tRegistered" << endl;
        vector<Course> notCompulsoryCourses;
        int count = 0;
        for (auto &&course : availableCourses)
        {
            if (!course.isCompulsoryCourse())
            {
                cout << course.getID() << "\t" << course.getCredits() << "\t";
                for (auto &&registeredCourse : student->getRegisteredCourses())
                {
                    if (registeredCourse->getID() == course.getID())
                    {
                        count++;
                        cout << "Yes" << endl;
                        cout << "Press any key to continue..." << endl;
                        cin.ignore();
                        system("cls");
                        studentMenu(student);
                        break;
                    }
                    else
                    {
                        notCompulsoryCourses.push_back(course);
                        cout << "No" << endl;
                    }
                }
            }
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
            bool found = false;
            for (auto &&course : notCompulsoryCourses)
            {
                if (course.getID() == courseID)
                {
                    found = true;
                    cout << "Registered for course: " << courseID << endl;
                    course.enrollStudent(student->getRollNo());
                    cout << "Course ID: " << courseID << " registered successfully." << endl;
                    student->addSubject(&course);
                    cout << "Press any key to continue..." << endl;
                    cin.ignore();
                    system("cls");
                    studentMenu(student);
                    break;
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
        break;
    }
    case 10:
    {
        cin.ignore();
        system("cls");
        cout << "Viewing Leave Records..." << endl;
        vector<LeaveApplication> leaveHistory = student->getLeaveHistory();
        if (leaveHistory.empty())
        {
            cout << "No leave records found." << endl;
        }
        else
        {
            for (auto &&leave : leaveHistory)
            {
                cout << endl
                     << "Reason: " << leave.getReason() << endl
                     << "Start Date: " << leave.getStartDate().showDate()
                     << endl
                     << "End Date: " << leave.getEndDate().showDate() << endl
                     << "Status: " << leave.getStatus() << endl;
            }
        }
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        system("cls");
        studentMenu(student);
        break;
    }
    case 0:
    {
        system("cls");
        return;
    }
    }
}

// Vishwas implemented the faculty menu and FA menu
void facultyMenu(Faculty *faculty)
{
    cout << "\n--- Faculty Panel ---" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Courses" << endl;
    cout << "3. View Attendance" << endl;
    cout << "4. View Marks" << endl;
    cout << "5. Add Marks" << endl;
    cout << "0. Log Out" << endl;

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
        vector<Course *> subjects = faculty->getSubjects();
        if (subjects.empty())
        {
            cout << "No courses assigned." << endl;
        }
        else
        {
            for (auto &&course : subjects)
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

        cout << "Available Courses: " << endl;
        for (auto &&it : faculty->getSubjects())
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to view attendance: ";
        string subjectId;
        bool flag = false;
        while (!flag)
        {
            flag = false;
            cin >> subjectId;
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
                            cout << "Student Roll No: " << subject.first << ", Attendance: " << subject.second << "." << endl;
                        }
                    }
                }
            }
            if (!flag)
            {
                cout << "Invalid Course ID. Please try again: " << endl;
            }
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
        cout << "Viewing Marks..." << endl;
        cout << "Available Courses: " << endl;
        for (auto &&it : faculty->getSubjects())
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to view marks: ";
        string subjectId;
        bool flag = false;
        while (!flag)
        {
            flag = false;
            cin >> subjectId;
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
                            cout << "Student Roll No: " << subject.first << ", Marks: " << subject.second << "." << endl;
                        }
                    }
                }
            }
            if (!flag)
            {
                cout << "Invalid Course ID. Please try again: " << endl;
            }
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
        cout << "Add Marks..." << endl;
        cout << "Available Courses: " << endl;
        for (auto &&it : faculty->getSubjects())
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to add marks: ";
        string subjectId;
        bool flag = false;
        while (!flag)
        {
            flag = false;
            cin >> subjectId;
            for (auto &&it : faculty->getSubjects())
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
    cout << "\n--- Faculty Panel ---" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Courses" << endl;
    cout << "3. View Attendance" << endl;
    cout << "4. View Marks" << endl;
    cout << "5. Add Marks" << endl;
    cout << "6. View Assigned Students" << endl;
    cout << "7. View Notifications / Review Leave application" << endl;
    cout << "8. Add Courses" << endl;
    cout << "0. Log Out" << endl;

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
        vector<Course *> subjects = fa->getSubjects();
        if (subjects.empty())
        {
            cout << "No courses assigned." << endl;
        }
        else
        {
            for (auto &course : subjects)
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

        cout << "Available Courses: " << endl;
        if (fa->getSubjects().empty())
        {
            cout << "No courses assigned." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            return;
        }
        for (auto &&it : fa->getSubjects())
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to view attendance: ";
        string subjectId;
        bool flag = false;
        while (!flag)
        {
            flag = false;
            cin >> subjectId;
            for (auto &&it : fa->getSubjects())
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
                            cout << "Student Roll No: " << subject.first << ", Attendance: " << subject.second << "." << endl;
                        }
                    }
                }
            }
            if (!flag)
            {
                cout << "Invalid Course ID. Please try again: " << endl;
            }
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
        cout << "Viewing Marks..." << endl;
        cout << "Available Courses: " << endl;
        if (fa->getSubjects().empty())
        {
            cout << "No courses assigned." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            return;
        }
        for (auto &&it : fa->getSubjects())
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to view marks: ";
        string subjectId;
        bool flag = false;
        while (!flag)
        {
            flag = false;
            cin >> subjectId;
            for (auto &&it : fa->getSubjects())
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
                            cout << "Student Roll No: " << subject.first << ", Marks: " << subject.second << "." << endl;
                        }
                    }
                }
            }
            if (!flag)
            {
                cout << "Invalid Course ID. Please try again: " << endl;
            }
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
        cout << "Add Marks..." << endl;
        cout << "Available Courses: " << endl;
        if (fa->getSubjects().empty())
        {
            cout << "No courses assigned." << endl;
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            system("cls");
            FAMenu(fa);
            return;
        }
        for (auto &&it : fa->getSubjects())
        {
            cout << "Course ID: " << it->getID() << ", Credits: " << it->getCredits() << endl;
        }
        cout << "Enter Course ID to add marks: ";
        string subjectId;
        bool flag = false;
        while (!flag)
        {
            flag = false;
            cin >> subjectId;
            for (auto &&it : fa->getSubjects())
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
        cout << "Viewing Assigned Students..." << endl;
        fa->viewAssignedStudents();
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
    case 8:
    {
        cin.ignore();
        system("cls");
        cout << "Adding Courses..." << endl;
        int count = 0;
        Faculty *faculty = faculties_map[fa->getID()];
        vector<Course> availableCourses;
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
            for(auto &registeredCourse : alreadyRegistered)
            {
                if (course.getID() == registeredCourse->getID())
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
            for(auto &registeredCourse : alreadyRegistered)
            {
                if (course.getID() == registeredCourse->getID())
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
            cout << "Course ID: " << course.getID() << ", Credits: " << course.getCredits() << endl;
        }
        cout << "Enter Course ID to add: ";
        string courseID;
        cin >> courseID;
        cin.ignore();
        for (auto &course : availableCourses)
        {
            if (course.getID() == courseID)
            {
                found = true;
                fa->AssignSubject(&course, false);
                faculty->AssignSubject(&course, true);
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
    case 0:
    {
        system("cls");
        return;
    }
    }
}

int main()
{
    if (!headercheck())
    {
        cout << "No database found." << endl;
    }
    system("cls");
    cout << "Welcome to the Student Management System!";
    Sleep(2000);
    system("cls");
    loginPage();
    return 0;
}