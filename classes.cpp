#include <bits/stdc++.h>
using namespace std;

class User;
class Student;
class Faculty;
class FA;
class Semester;
class Course;
class Date;
class LeaveApplication;
class User
{
protected:
    string username, password;

public:
    User(string uname = "", string pass = "") : username(uname), password(pass) {}
    virtual bool login(string uname, string pass) = 0;
    virtual bool changePassword(string newPass) = 0;
};

bool User::login(string uname, string pass)
{
    if (uname == username && pass == password)
    {
        cout << "Login successful!" << endl;
        return true;
    }
    else
    {
        cout << "Invalid username or password." << endl;
        return false;
    }
}

bool User::changePassword(string newPass)
{
    if (newPass.empty())
    {
        cout << "New password cannot be empty." << endl;
        return false;
    }
    password = newPass;
    cout << "Password changed successfully!" << endl;
    return true;
}

class Student : public User
{
private:
    string name, branch, gender, dob, email, rollNo;
    FA *My_FA;
    string FA_ID; // to be used for leave application
    int year, sem_num;
    float CGPA;
    bool New_Notification;
    vector<string> notifications;
    vector<LeaveApplication> leaveHistory;
    vector<Course *> registeredCourses;
    map<string, int> marks;
    map<string, int> attendance;
    map<Course *, int> breadthChoice;
    map<Course *, int> lateralChoice;

public:
    Student(string uname = "", string pass = "", string name = "", string rollNo = "",
            int year = 0, string branch = "", string fa = "",
            float cgpa = 0.0, string gender = "", string dob = "", string email = "", int sem = 0)
        : User(uname, pass), name(name), rollNo(rollNo), year(year), branch(branch), FA_ID(fa),
          CGPA(cgpa), gender(gender), dob(dob), email(email), New_Notification(false), sem_num(sem) {}

    bool login(string uname, string pass) override;
    bool changePassword(string newPass) override; // old pass check is important before changing
    void setFA(FA *fa) { My_FA = fa; } // to be used for leave application
    string getFA_ID() { return FA_ID; } // to be used for leave application
    void viewDetails(); // what to show will be decided
    // to be changed to get details
    int getSem();                                                    // done
    void applyForLeave(string reason, Date startDate, Date endDate); // done
    void addnotification(string notification);                       // done
    void viewNotifications();                                        // done
    void giveFeedback(string courseID, string feedback);             // course should be registered by that student
    void registerCourse(Semester *curr_sem);                         // done  // refer semester class based upon curr sem and show available subjects, we will check the curr sem of student and give the number of sem obj to this function while calling
    void viewLeaveRecords();                                         // done
    string getRollNo();                                              // done
    void addSubject(Course *course);                                 // done     // add course to registered courses
    void addAttendance(string courseID, int attendanceCount);        // done      // add attendance for a course
    void addMarks(string courseID, int mark);                        // done    // add marks for a course
};

int Student ::getSem()
{
    return sem_num;
}

void Student ::applyForLeave(string reason, Date startDate, Date endDate)
{
    LeaveApplication leave(reason, startDate, endDate);
    leaveHistory.push_back(leave);
    My_FA->submitApplication(this, leave);
    cout << "Leave application submitted successfully." << endl;
}

void Student ::addnotification(string notification)
{
    notifications.push_back(notification);
    New_Notification = true;
}

void Student ::viewNotifications()
{
    cout << "Notifications for " << name << " (" << rollNo << "):" << endl;
    if (notifications.empty())
    {
        cout << "No notifications found." << endl;
    }
    else
    {
        for (auto &&notification : notifications)
        {
            cout << notification << endl;
        }
    }
    New_Notification = false;
}
void Student ::registerCourse(Semester *curr_sem)
{
    cout << "Registering for courses in semester " << sem_num << endl;
    cout << "Available Compulsory courses: " << endl;
    vector<Course *> availableCourses = curr_sem->viewCompulsoryCourse();
    char choice;
    for (auto &&course : availableCourses)
    {
        cout << "Course ID: " << course->getID() << ", Credits: " << course->getCredits() << endl;
        cout << "Do you want to register for this course? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            addSubject(course);
            cout << "Registered for course: " << course->getID() << endl;
        }
        else
        {
            cout << "Not registered for course: " << course->getID() << endl;
        }
    }
    vector<Course *> breadthCourses = curr_sem->viewBreadthCourse();
    cout << "Available Breadth courses: " << endl;
    for (auto &&Course : breadthCourses)
    {
        cout << "Course ID: " << Course->getID() << ", Credits: " << Course->getCredits() << endl;
    }
    set<int> givenChoices;
    int number;
    for (auto &&course : breadthCourses)
    {
        cout << "Preference number for Course ID: " << course->getID() << endl;
        cin >> number;
        while (givenChoices.find(number) != givenChoices.end() || number < 1 || number > breadthCourses.size())
        {
            cout << "You have already given this preference number. Please enter a different number." << endl;
            cin >> number;
        }
        givenChoices.insert(number);
        breadthChoice[course] = number;
    }
    cout << "You have given the following preferences for breadth courses: " << endl;
    for (auto &&course : breadthChoice)
    {
        cout << "Course ID: " << course.first->getID() << ", Preference Number: " << course.second << endl;
    }
    givenChoices.clear();
    vector<Course *> lateralCourses = curr_sem->viewLateralCourse();
    cout << "Available Lateral courses: " << endl;
    for (auto &&Course : lateralCourses)
    {
        cout << "Course ID: " << Course->getID() << ", Credits: " << Course->getCredits() << endl;
    }
    for (auto &&course : lateralCourses)
    {
        cout << "Preference number for Course ID: " << course->getID() << endl;
        cin >> number;
        while (givenChoices.find(number) != givenChoices.end() || number < 1 || number > lateralCourses.size())
        {
            cout << "You have already given this preference number. Please enter a different number." << endl;
            cin >> number;
        }
        givenChoices.insert(number);
        lateralChoice[course] = number;
    }
    cout << "You have given the following preferences for lateral courses: " << endl;
    for (auto &&course : lateralChoice)
    {
        cout << "Course ID: " << course.first->getID() << ", Preference Number: " << course.second << endl;
    }
}

void Student ::viewLeaveRecords()
{
    cout << "Leave Records for " << name << " (" << rollNo << "):" << endl;
    if (leaveHistory.empty())
    {
        cout << "No leave records found." << endl;
    }
    else
    {
        for (auto &&leave : leaveHistory)
        {
            cout << leave.getReason() << " From: " << leave.getStartDate().showDate() << " To: " << leave.getEndDate().showDate() << endl;
        }
    }
}
string Student ::getRollNo()
{
    return rollNo;
}
void Student ::addSubject(Course *course)
{
    registeredCourses.push_back(course);
}

void Student ::addAttendance(string courseID, int attendanceCount)
{
    attendance[courseID] = attendanceCount;
}
void Student ::addMarks(string courseID, int mark)
{
    marks[courseID] = mark;
}

bool Student::login(string uname, string pass)
{
    if (User::login(uname, pass))
    {
        cout << "Welcome, " << name << "!" << endl;
        return true;
    }
    return false;
}
class Faculty : public User
{
protected:
    string name, gender, email, branch, id, officeNo;
    vector<Course *> subjects;
    bool is_FA;
public:
    Faculty(string uname = "", string pass = "", string name = "", string id = "",
            string gender = "", string email = "", string branch = "", string officeNo = "",bool is_FA = false)
        : User(uname, pass), name(name), id(id), gender(gender),
          email(email), branch(branch), officeNo(officeNo), is_FA(is_FA) {}

    bool login(string uname, string pass);
    bool changePassword(string newPass);

    void AssignSubject(Course *course); // done
    // Faculty -> Course -> Student -> Update,View.
    vector<Course *> getSubjects(); // done

    // void viewStudents(string courseID); // courseId should be from his subjects
    // void enterMarks(Course *course, int mark);
    // void viewMarks(string studentID);
    // while accessing check if student is registered in that course and he is the faculty of that course
    // void updateAttendance(Course *course);
    // void viewAttendance(Course *course);
};

bool Faculty::login(string uname, string pass)
{
    if (User::login(uname, pass))
    {
        cout << "Welcome, " << name << "!" << endl;
        return true;
    }
    return false;
}

void Faculty ::AssignSubject(Course *course)
{
    subjects.push_back(course);
    course->addfaculty(this);
}

vector<Course *> Faculty::getSubjects()
{
    return subjects;
}
class FA : public Faculty
{
private:
    vector<Student *> assignedStudents;
    map<Student *, LeaveApplication> newleaveRequests; // key -> pointer to student object, value -> leave applicaiton
    map<Student *, LeaveApplication> leaveRequests;    // key -> pointer to student object, value -> leave applicaiton
    bool New_Notification;

public:
    FA(string uname = "", string pass = "", string name = "", string id = "",
       string gender = "", string email = "", string branch = "", string officeNo = "", bool is_FA = true)
        : Faculty(uname, pass, name, id, gender, email, branch, officeNo, is_FA), New_Notification(false) {}
    string getID() { return id; } // to be used for leave application
    vector<Student *> getAssignedStudents();                   // done
    void viewAssignedStudents();                               // done
    void reviewLeaveApplication();                             // done
    void submitApplication(Student *, LeaveApplication leave); // done
};

vector<Student *> FA::getAssignedStudents()
{
    return assignedStudents;
}

void FA::viewAssignedStudents()
{
    cout << "Assigned Students:" << endl;
    if (assignedStudents.empty())
    {
        cout << "No students assigned." << endl;
    }
    else
    {
        for (auto &&student : assignedStudents)
        {
            cout << student->getRollNo() << " - " << student->getSem() << endl;
        }
    }
}
void FA::reviewLeaveApplication()
{
    for (auto &&request : newleaveRequests)
    {
        string rollNo = request.first->getRollNo();
        string reason = request.second.getReason();
        Date startDate = request.second.getStartDate();
        Date endDate = request.second.getEndDate();

        cout << "Leave Request from " << rollNo << " for :" << reason << " from " << startDate.showDate() << " to " << endDate.showDate() << endl;

        cout << "Do you want to approve this leave request? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            leaveRequests[request.first] = request.second;
            cout << "Leave request approved for " << request.first->getRollNo() << endl;
            request.first->addnotification("Your leave request has been approved");
        }
        else
        {
            cout << "Leave request rejected for " << request.first->getRollNo() << endl;
            request.first->addnotification("Your leave request has been rejected");
        }
    }
    newleaveRequests.clear();
    New_Notification = false;
}

void FA ::submitApplication(Student *student, LeaveApplication leave)
{
    newleaveRequests[student] = leave;
    cout << "Leave application submitted successfully." << endl;
    New_Notification = true;
}
class Semester
{
    // think about doing branch vise
    int sem_num;
    vector<Course *> compulsory_courses;
    vector<Course *> breadth;
    vector<Course *> lateral;

public:
    Semester(int sem = 0) : sem_num(sem) {};
    void addCompulsoryCourse();
    void addBreadthCourse();
    void addLateralCourse();
    void removeCompulsoryCourse();
    void removeBreadthCourse();
    void removeLateralCourse();
    vector<Course *> viewCompulsoryCourse();
    vector<Course *> viewBreadthCourse();
    vector<Course *> viewLateralCourse();
};
class Course
{
private:
    string id, branch;
    vector<Student *> studentIDs;
    vector<string> facultyIDs;
    int credits;
    bool isCompulsory;             // true if compulsory, false if breadth or lateral
    map<string, int> attendance;   // key = id, value = attendance
    map<string, string> feedbacks; // key = id, value = feedback

public:
    Course(string id = "", string branch = "", int credits = 0, bool isCompulsory = false)
        : id(id), branch(branch), credits(credits), isCompulsory(isCompulsory) {}

    void addfaculty(Faculty *faculty);
    void removefaculty();
    void enrollStudent(Student *student);                      // push_back
    void receiveFeedback(Student *studentID, string feedback); // push_back feedback
    string getID() const { return id; }
    int getCredits() const { return credits; }
};

class Date
{
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0) : day(day), month(month), year(year) {}
    int Calculate_days(Date Start_date, Date End_date);
    string showDate();
};
class LeaveApplication
{
private:
    string reason;
    Date startDate;
    Date endDate;

public:
    LeaveApplication(string reason = "", Date startDate = Date(), Date endDate = Date())
        : reason(reason), startDate(startDate), endDate(endDate) {}

    string getReason() const { return reason; }
    Date getStartDate() const { return startDate; }
    Date getEndDate() const { return endDate; }
};
int main()
{

    return 0;
}