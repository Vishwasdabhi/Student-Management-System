#include <backend.cpp>

/*
We have to implement some functions
Before viewing any pannel or any new window we need to clear the console

think if we can add some colsole based design
*/

void addstudents()
{
    cout<<"Enter the number of students to add: ";
    int n;
    cin >> n;
    cin.ignore(); // to ignore the newline character after entering n
    for (int i = 0; i < n; i++)
    {
        string name, rollNo, branch, FA_ID, gender, dob, email;
        int year, sem_num;
        cout<< "Enter details for Student " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin.ignore(); // to ignore the newline character
        getline(cin, name);
        cout << "Roll Number: ";
        getline(cin, rollNo);
        cout << "Branch: ";
        getline(cin, branch);
        cout << "FA ID: ";
        getline(cin, FA_ID);
        cout<< "Year: ";
        cin >> year;
        cout << "Semester Number: ";
        cin >> sem_num;
        cin.ignore(); // to ignore the newline character after entering sem_num
        cout<<"Date of Birth (DD MM YYYY): ";
        int day, month, year_dob;
        cin >> day >> month >> year_dob;
        dob = to_string(day) + " " + to_string(month) + " " + to_string(year_dob);
        cout << "Email: ";
        getline(cin, email);
        cout << "Gender: ";
        getline(cin, gender);
        students.push_back(Student(rollNo, rollNo + "@iitbbs",name, rollNo, year, branch, FA_ID, 0.0, gender, dob, email, sem_num));

        for (int j = 0; j < sizeof(fa) / sizeof(fa[0]); j++)
        {
            if (fa[j].getID() == FA_ID)
            {
                fa[j].setAssignedStudents(&students.back());
                students.back().setFA(&fa[j]);
                break;
            }
        }

        cout << "Student " << name << " added successfully!" << endl;
    }
}

void deletestudents()
{
    cout << "Enter the Roll Number of the student to delete: ";
    string rollNo;
    cin >> rollNo;
    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if (it->getRollNo() == rollNo)
        {
            cout << "Deleting student: " << it->getName() << endl;
            students.erase(it);
            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student with Roll Number " << rollNo << " not found." << endl;
}

void addfaculty()
{
    cout << "Enter the number of faculty members to add: ";
    int n;
    cin >> n;
    cin.ignore(); // to ignore the newline character after entering n
    for (int i = 0; i < n; i++)
    {
        string name, id, branch, gender, email, officeNo, is_FA_str;
        bool is_FA;
        cout << "Enter details for Faculty " << i + 1 << ":" << endl;
        cout << "Name: ";
        getline(cin, name);
        cout << "ID: ";
        getline(cin, id);
        cout << "Branch: ";
        getline(cin, branch);
        cout << "Gender: ";
        getline(cin, gender);
        cout << "Email: ";
        getline(cin, email);
        cout << "Office Number: ";
        getline(cin, officeNo);
        cout << "Is this faculty a FA? (1 for Yes, 0 for No): ";
        getline(cin, is_FA_str);
        is_FA = (is_FA_str == "1");
        faculties.push_back(Faculty(id, id + "@iitbbs", name, id, gender, email, branch, officeNo, is_FA));
        cout << "Faculty " << name << " added successfully!" << endl;
        if (is_FA)
        {
            fa.push_back(FA(id, id + "@iitbbs", name, id, gender, email, branch, officeNo, is_FA));
            cout << "FA " << name << " added successfully!" << endl;
        }
    }
}

void deletefaculty()
{
    cout << "Enter the ID of the faculty to delete: ";
    string id;
    cin >> id;
    for (auto it = faculties.begin(); it != faculties.end(); ++it)
    {
        if (it->getFacultyID() == id)
        {
            cout << "Deleting faculty: " << it->getFacultyName() << endl;
            faculties.erase(it);
            cout << "Faculty deleted successfully!" << endl;
            return;
        }
    }
    cout << "Faculty with ID " << id << " not found." << endl;
}

void addcourse()
{
    cout << "Enter the number of courses to add: ";
    int n;
    cin >> n;
    cin.ignore(); // to ignore the newline character after entering n
    for (int i = 0; i < n; i++)
    {
        string id, branch, is_compulsory_str;
        int credits;
        bool is_compulsory;
        cout << "Enter details for Course " << i + 1 << ":" << endl;
        cout << "Course ID: ";
        getline(cin, id);
        cout << "Branch: ";
        getline(cin, branch);
        cout << "Credits: ";
        cin >> credits;
        cin.ignore(); // to ignore the newline character after entering credits
        cout << "Is this course compulsory? (1 for Yes, 0 for No): ";
        getline(cin, is_compulsory_str);
        is_compulsory = (is_compulsory_str == "1");
        
        if (id.find("sem1") != string::npos)
            courses_sem1.push_back(Course(id, branch, credits, is_compulsory));
        else if (id.find("sem2") != string::npos)
            courses_sem2.push_back(Course(id, branch, credits, is_compulsory));
        
        cout << "Course " << id << " added successfully!" << endl;
    }
}

void deletecourse()
{
    cout << "Enter the Course ID to delete: ";
    string id;
    cin >> id;
    vector<Course> *courses = (id.find("sem1") != string::npos) ? &courses_sem1 : &courses_sem2;
    
    for (auto it = courses->begin(); it != courses->end(); ++it)
    {
        if (it->getID() == id)
        {
            cout << "Deleting course: " << it->getID() << endl;
            courses->erase(it);
            cout << "Course deleted successfully!" << endl;
            return;
        }
    }
    cout << "Course with ID " << id << " not found." << endl;
}

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
        for (int i = 0; i < sizeof(students) / sizeof(students[0]); i++)
        {
            if (students[i].login(username, password))
            {
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
        for (int i = 0; i < sizeof(faculties) / sizeof(faculties[0]); i++)
        {
            if (faculties[i].login(username, password))
            {
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
        for (int i = 0; i < sizeof(fa) / sizeof(fa[0]); i++)
        {
            if (fa[i].login(username, password))
            {
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
        for (int i = 0; i < sizeof(students) / sizeof(students[0]); i++)
        {
            students[i].viewDetails();
        }
        break;
    }
    case 2:
    {
        addstudents(); // to be implimented
        break;
    }
    case 3:
    {
        deletestudents(); // to be implimented
        break;
    }
    case 4:
    {
        cout << "Viewing Faculty..." << endl;
        for (int i = 0; i < sizeof(faculties) / sizeof(faculties[0]); i++)
        {
            faculties[i].viewDetails();
        }
        break;
    }
    case 5:
    {
        addfaculty(); // to be implimented
        break;
    }
    case 6:
    {
        deletefaculty(); // to be implimented
        break;
    }
    case 7:
    {
        cout << "Viewing Courses..." << endl;
        cout << "Semester 1 Courses:" << endl;
        for (int i = 0; i < sizeof(courses_sem1) / sizeof(courses_sem1[0]); i++)
        {
            cout << "Course ID: " << courses_sem1[i].getID() << ", Credits: " << courses_sem1[i].getCredits() << endl;
        }
        cout << "Semester 2 Courses:" << endl;
        for (int i = 0; i < sizeof(courses_sem2) / sizeof(courses_sem2[0]); i++)
        {
            cout << "Course ID: " << courses_sem2[i].getID() << ", Credits: " << courses_sem2[i].getCredits() << endl;
        }
        break;
    }
    case 8:
    {
        addcourse(); // to be implimented
        break;
    }
    case 9:
    {
        deletecourse(); // to be implimented
        break;
    }
    case 0:
    {
        cout << "Exiting..." << endl;
        return;
    }
    }
}

// Vishwas correct the numering below
void studentMenu(Student *student)
{
    cout << "\n--- Student Panel ---" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. Edit Profile" << endl;
    cout << "2. View Courses" << endl;
    cout << "3. View Attendance" << endl;
    cout << "4. View Marks" << endl;
    cout << "5. Apply for Leave" << endl;
    cout << "6. View Notifications" << endl;
    cout << "7. Give Feedback" << endl;
    cout << "8. Register for Courses" << endl;
    cout << "9. View Leave Records" << endl;
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
            cout<< "Registered Courses: " << endl;
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
    case 6:
    {
        cout << "Viewing Notifications..." << endl;
        student->viewNotifications();
        break;
    }
    case 7:
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
    case 8:
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
            if(!course.isCompulsoryCourse())
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
            cout << "You can register for "<<2-count<<" extra courses." << endl;
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
                    course.enrollStudent(student);
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
    case 9:
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
    cout << "5. Assign Grades" << endl;
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
        // to be implemented
        break;
    }
    case 4:
    {
        cout << "Viewing Marks..." << endl;
        // to be implemented
        break;
    }
    case 5:
    {
        cout << "Assigning Grades..." << endl;
        // to be implemented
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
    cout << "5. Assign Grades" << endl;
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
        // to be implemented
        break;
    }
    case 4:
    {
        cout << "Viewing Marks..." << endl;
        // to be implemented
        break;
    }
    case 5:
    {
        cout << "Assigning Grades..." << endl;
        // to be implemented
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

    return 0;
}