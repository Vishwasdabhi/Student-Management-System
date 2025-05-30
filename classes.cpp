#include <bits/stdc++.h>
using namespace std;

class User;
class Student;
class Faculty;
class FA;
class Course;
class Date;

class User
{
protected:
    string username, password;

public:
    User(string uname = "", string pass = "") : username(uname), password(pass) {}
    virtual bool login(string uname, string pass) = 0;
    virtual void changePassword(string newPass) = 0;
};

class Student : public User
{
private:
    string name, branch, gender, dob, email, rollNo;
    string FA_id;
    int year, sem_num;
    float CGPA;
    bool New_Notification;
    vector<string> notifications;
    vector<string> leaveHistory;
    vector<Course *> registeredCourses;
    map<string, int> marks;
    map<string, int> attendance;
public:
    Student(string uname = "", string pass = "", string name = "", string rollNo = "",
            int year = 0, string branch = "", string fa = "",
            float cgpa = 0.0, string gender = "", string dob = "", string email = "", int sem = 0)
        : User(uname, pass), name(name), rollNo(rollNo), year(year), branch(branch), FA_id(fa),
          CGPA(cgpa), gender(gender), dob(dob), email(email), New_Notification(false), sem_num(sem) {}

    bool login(string uname, string pass) override;
    void changePassword(string newPass) override; // old pass check is important before changing

    void viewDetails(); // what to show will be decided
    // to be changed to get details
    int getSem();
    void applyForLeave(string reason, Date startDate, Date endDate);
    void viewNotifications();
    void giveFeedback(string courseID, string feedback); // course should be registered by that student
    void registerCourse(Semester *curr_sem);             // refer semester class based upon curr sem and show available subjects, we will check the curr sem of student and give the number of sem obj to this function while calling
    void viewLeaveRecords();
    string getRollNo() const { return rollNo; }
    void addSubject(Course *course) { registeredCourses.push_back(course); } // add course to registered courses
    void addAttendance(string courseID, int attendanceCount) { attendance[courseID] = attendanceCount; } // add attendance for a course
    void addMarks(string courseID, int mark) { marks[courseID] = mark; } // add marks for a course
};

int Student ::getSem()
{
    return sem_num;
}
class Faculty : public User
{
protected:
    string name, gender, email, school, id, officeNo;
    vector<Course *> subjects;

public:
    Faculty(string uname = "", string pass = "", string name = "", string id = "",
            string gender = "", string email = "", string school = "", string officeNo = "")
        : User(uname, pass), name(name), id(id), gender(gender),
          email(email), school(school), officeNo(officeNo) {}

    bool login(string uname, string pass);
    void changePassword(string newPass);

    void subjectsAssigned(Course *course);
    // Faculty -> Course -> Student -> Update,View.

    // void viewStudents(string courseID); // courseId should be from his subjects
    // void enterMarks(Course *course, int mark);
    // void viewMarks(string studentID);
    // while accessing check if student is registered in that course and he is the faculty of that course
    // void updateAttendance(Course *course);
    // void viewAttendance(Course *course);
};

class FA : public Faculty
{
private:
    vector<Student *> assignedStudents;
    map<Student *, string> leaveRequests; // key -> pointer to student object, value -> leave applicaiton

public:
    FA(string uname = "", string pass = "", string name = "", string id = "",
       string gender = "", string email = "", string school = "", string officeNo = "")
        : Faculty(uname, pass, name, id, gender, email, school, officeNo) {}

    void viewAssignedStudents();
    void notifications();
    void reviewLeaveApplication(string studentID, bool approve);
    void notifyLeaveApplications();
};

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
    void viewCompulsoryCourse();
    void viewBreadthCourse();
    void viewLateralCourse();
};
class Course
{
private:
    string id, branch;
    vector<Student *> studentIDs;
    vector<string> facultyIDs;
    int credits;
    bool isCompulsory; // true if compulsory, false if breadth or lateral
    map<string, int> attendance;   // key = id, value = attendance
    map<string, string> feedbacks; // key = id, value = feedback

public:
    Course(string id = "", string branch = "", int credits = 0, bool isCompulsory = false)
        :id(id), branch(branch), credits(credits), isCompulsory(isCompulsory) {}

    void addfaculty();
    void removefaculty();
    void enrollStudent(Student *student); //push_back
    void receiveFeedback(Student *studentID, string feedback); //push_back feedback
};

class Date
{
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0) : day(day), month(month), year(year) {}
    int Calculate_days(Date Start_date, Date End_date);
};
int main()
{

    return 0;
}