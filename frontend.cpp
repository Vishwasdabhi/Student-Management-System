#include "backend.cpp"

/*
think if we can add some colsole based design
*/

void adminMenu();
void studentMenu(Student *student);
void facultyMenu(Faculty *faculty);
void FAMenu(FA *fa);

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

void loginPage()
{
    cout << "Welcome to ..." << endl; // to be decided
    cout << "Login as :" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Student" << endl;
    cout << "3. Faculty" << endl;
    cout << "4. FA" << endl;
    cout << "0. Exit" << endl;
    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        string username, password;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;
        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        {
            system("cls");
            adminMenu();
        }
        else
        {
            cout << "Invalid credentials." << endl;
        }
        break;
    }
    case 2:
    {
        string username, password;
        cout << "Enter Student Username: ";
        cin >> username;
        cout << "Enter Student Password: ";
        cin >> password;
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].login(username, password))
            {
                system("cls");
                studentMenu(&students[i]);
                return;
            }
        }
        cout << "Invalid credentials." << endl;
        break;
    }
    case 3:
    {
        string username, password;
        cout << "Enter Faculty Username: ";
        cin >> username;
        cout << "Enter Faculty Password: ";
        cin >> password;
        for (int i = 0; i < faculties.size(); i++)
        {
            if (faculties[i].login(username, password))
            {
                system("cls");
                facultyMenu(&faculties[i]);
                return;
            }
        }
        cout << "Invalid credentials." << endl;
        break;
    }
    case 4:
    {
        string username, password;
        cout << "Enter FA Username: ";
        cin >> username;
        cout << "Enter FA Password: ";
        cin >> password;
        for (int i = 0; i < fa.size(); i++)
        {
            if (fa[i].login(username, password))
            {
                system("cls");
                FAMenu(&fa[i]);
                return;
            }
        }
        cout << "Invalid credentials." << endl;
        break;
    }
    case 0:
    {
        cout << "Exiting..." << endl;
        return;
    }
    }
}

void adminMenu()
{
    cout << "\n--- Admin Panel ---" << endl;
    cout << "1. View Students" << endl;
    cout << "2. Add Student" << endl;
    cout << "3. Delete Student" << endl;
    cout << "4. View Faculty" << endl;
    cout << "5. Add Faculty" << endl;
    cout << "6. Delete Faculty" << endl;
    cout << "7. View Courses" << endl;
    cout << "8. Add Course" << endl;
    cout << "9. Delete Course" << endl;

    cout << "0. Exit" << endl;
    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Viewing Students..." << endl;
        for (int i = 0; i < students.size(); i++)
        {
            students[i].viewDetails();
        }
        break;
    }
    case 2:
    {
        addstudents();
        break;
    }
    case 3:
    {
        deletestudents();
        break;
    }
    case 4:
    {
        cout << "Viewing Faculty..." << endl;
        for (int i = 0; i < faculties.size(); i++)
        {
            faculties[i].viewDetails();
        }
        break;
    }
    case 5:
    {
        addfaculty();
        break;
    }
    case 6:
    {
        deletefaculty();
        break;
    }
    case 7:
    {
        cout << "Viewing Courses..." << endl;
        cout << "Semester 1 Courses:" << endl;
        for (int i = 0; i < courses_sem1.size(); i++)
        {
            cout << "Course ID: " << courses_sem1[i].getID() << ", Credits: " << courses_sem1[i].getCredits() << endl;
        }
        cout << "Semester 2 Courses:" << endl;
        for (int i = 0; i < courses_sem2.size(); i++)
        {
            cout << "Course ID: " << courses_sem2[i].getID() << ", Credits: " << courses_sem2[i].getCredits() << endl;
        }
        break;
    }
    case 8:
    {
        addcourse();
        break;
    }
    case 9:
    {
        deletecourse();
        break;
    }
    case 0:
    {
        cout << "Exiting..." << endl;
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
    cout << "0. Exit" << endl;

    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Viewing Profile..." << endl;
        student->viewDetails();
        break;
    }
    case 2:
    {
        student->editProfile();
    }
    case 3:
    {
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
        break;
    }
    case 4:
    {
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
        break;
    }
    case 5:
    {
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
        break;
    }
    case 6:
    {
        cout << "Applying for Leave..." << endl;
        string reason;
        Date startDate, endDate;
        cout << "Enter reason for leave: ";
        cin.ignore();
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
        break;
    }
    case 7:
    {
        cout << "Viewing Notifications..." << endl;
        student->viewNotifications();
        break;
    }
    case 8:
    {
        cout << "Giving Feedback..." << endl;
        cout << "Available Courses: " << endl;
        vector<Course *> registeredCourses = student->getRegisteredCourses();
        if (registeredCourses.empty())
        {
            cout << "No courses registered." << endl;
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
        break;
    }
    case 9:
    {
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
            return;
        }
        if (availableCourses.empty())
        {
            cout << "No courses available." << endl;
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
                    break;
                }
            }
            if (!found)
            {
                cout << "Course ID not found or already registered." << endl;
            }
        }
        break;
    }
    case 10:
    {
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
                cout << "Reason: " << leave.getReason() << ", Start Date: " << leave.getStartDate().showDate()
                     << ", End Date: " << leave.getEndDate().showDate() << endl;
            }
        }
        break;
    }
    case 0:
    {
        cout << "Exiting..." << endl;
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
    cout << "0. Exit" << endl;

    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Viewing Profile..." << endl;
        faculty->viewDetails();
        break;
    }
    case 2:
    {
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
        break;
    }
    case 3:
    {
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
                            cout << "Student Roll No: " << subject.first << ", Attendance: " << subject.second << endl;
                        }
                    }
                }
            }
            if (!flag)
            {
                cout << "Invalid Course ID. Please try again: " << endl;
            }
        }
        break;
    }
    case 4:
    {
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
                            cout << "Student Roll No: " << subject.first << ", Marks: " << subject.second << endl;
                        }
                    }
                }
            }
            if (!flag)
            {
                cout << "Invalid Course ID. Please try again: " << endl;
            }
        }
        break;
    }
    case 5:
    {
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
                        for (auto &student : students)
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
                            students_map[student]->addMarks(it->getID(), mark);
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
                                    students_map[student]->addMarks(it->getID(), mark);
                                    cout << "Marks added for " << student << ": " << mark << endl;
                                }
                            }
                            if(!flag2)
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
        break;
    }
    case 0:
    {
        cout << "Exiting..." << endl;
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
    cout << "0. Exit" << endl;

    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Viewing Profile..." << endl;
        fa->viewDetails();
        break;
    }
    case 2:
    {
        cout << "Viewing Courses..." << endl;
        vector<Course *> subjects = fa->getSubjects();
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
        break;
    }
    case 3:
    {
       cout << "Viewing Attendance..." << endl;

        cout << "Available Courses: " << endl;
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
        break;
    }
    case 4:
    {
        cout << "Viewing Marks..." << endl;
        cout << "Available Courses: " << endl;
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
        break;
    }
    case 5:
    {
        cout << "Add Marks..." << endl;
        cout << "Available Courses: " << endl;
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
                            students_map[student]->addMarks(it->getID(), mark);
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
                                    students_map[student]->addMarks(it->getID(), mark);
                                    cout << "Marks added for " << student << ": " << mark << endl;
                                }
                            }
                            if(!flag2)
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
        break;
    }
    case 6:
    {
        cout << "Viewing Assigned Students..." << endl;
        fa->viewAssignedStudents();
        break;
    }
    case 7:
    {
        cout << "Viewing Notifications / Reviewing Leave application..." << endl;
        if (fa->isNewNotification())
        {
            fa->reviewLeaveApplication();
        }
        else
        {
            cout << "No new notifications." << endl;
        }
        break;
    }
    case 0:
    {
        cout << "Exiting..." << endl;
        return;
    }
    }
}

int main()
{
    loginPage();
    return 0;
}