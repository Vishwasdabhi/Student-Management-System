#include <bits/stdc++.h>
using namespace std;

class User;
class Student;
class Faculty;
class FA;
class Course;

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
    Faculty FA;
    int year;
    float CGPA;
    vector<string> notifications; // think what to do
    vector<string> leaveHistory;
    vector<string> coursesRegistered;

public:
    Student(string uname = "", string pass = "", string name = "", string rollNo = "",
            int year = 0, string branch = "", Faculty fa = Faculty(),
            float cgpa = 0.0, string gender = "", string dob = "", string email = "")
        : User(uname, pass), name(name), rollNo(rollNo), year(year), branch(branch), FA(fa),
          CGPA(cgpa), gender(gender), dob(dob), email(email) {}

    bool login(string uname, string pass) override;
    void changePassword(string newPass) override; // old pass check is important before changing

    void viewDetails();                                                  // what to show will be decided
    void applyForLeave(string reason, string startDate, string endDate); // date formate will be decided.
    void viewNotifications();
    void giveFeedback(string courseID, string feedback); // course should be registered by that student
    void registerCourse(string courseID);
    void viewLeaveRecords();
};

class Faculty : public User
{
protected:
    string name, gender, email, school, id, officeNo;
    vector<string> subjects;

public:
    Faculty(string uname = "", string pass = "", string name = "", string id = "",
            string gender = "", string email = "", string school = "", string officeNo = "")
        : User(uname, pass), name(name), id(id), gender(gender),
          email(email), school(school), officeNo(officeNo) {}

    bool login(string uname, string pass) override;
    void changePassword(string newPass) override;

    void viewStudents(string courseID); // courseId should be from his subjects
    void enterMarks(string studentID, string course, int mark);
    void viewMarks(string studentID);
};

class FA : public Faculty
{
private:
    vector<string> assignedStudents;   // roll no. of students // decide whether to keep roll no. or student instance
    map<string, string> leaveRequests; // key -> roll no. of students, value -> leave applicaiton

public:
    FA(string uname = "", string pass = "", string name = "", string id = "",
       string gender = "", string email = "", string school = "", string officeNo = "")
        : Faculty(uname, pass, name, id, gender, email, school, officeNo) {}

    void viewAssignedStudents();
    void notifications();
    void reviewLeaveApplication(string studentID, bool approve);
    void notifyLeaveApplications();
};

class Course
{
private:
    string name, id, branch;
    vector<string> studentIDs; // do be decided whether to keep instance or id's
    vector<string> facultyIDs;
    map<string, int> attendance; // key = id, value = attendance
    map<string, string> feedbacks; // key = id, value = feedback

public:
    Course(string name = "", string id = "", string branch = "")
        : name(name), id(id), branch(branch) {}

    void addCourse();
    void removeCourse();
    void enrollStudent(int studentID);
    void receiveFeedback(int studentID, string feedback);
};


int main()
{

    return 0;
}