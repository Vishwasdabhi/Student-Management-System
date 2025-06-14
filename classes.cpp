#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class User;
class Student;
class Faculty;
class FA;
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
    string status;
    // status can be "Pending", "Approved", "Rejected"
    string fa_id;
    string rollNo;

public:
    LeaveApplication(string reason = "", Date startDate = Date(), Date endDate = Date(), string status = "Pending", string fa_id = "", string rollNo = "")
        : reason(reason), startDate(startDate), endDate(endDate), status(status), fa_id(fa_id), rollNo(rollNo) {}

    string getReason();
    Date getStartDate();
    Date getEndDate();
    void setStatus(string newStatus);
    string getStatus();
    string getFA_ID();
    string getRollNo();
};

class Course
{
private:
    string id, branch;
    // vector<Student *> studentIDs;
    // vector<Faculty *> facultyIDs;
    vector<string> studentIDs;
    vector<string> facultyIDs;
    int credits;
    bool isCompulsory; // true if compulsory, false if breadth or lateral
    // map<Student *, int> marks;
    // map<Student *, int> attendance; // key = student object
    map<string, int> marks;      // key = student roll number
    map<string, int> attendance; // key = student roll number
    vector<string> feedbacks;

public:
    Course(string id = "", string branch = "", int credits = 0, bool isCompulsory = false)
        : id(id), branch(branch), credits(credits), isCompulsory(isCompulsory) {}

    void addfaculty(string facultyId);
    void removefaculty();
    void enrollStudent(string studentId);
    void receiveFeedback(string feedback);
    string getID();
    int getCredits();
    void add_marks(string StudentId, int mark);
    void add_attendance(string studentId, int attendanceCount);
    bool isCompulsoryCourse();
    map<string, int> getMarks();
    map<string, int> getAttendance();
    vector<string> getStudents();
    vector<string> getFaculties();
};

class Faculty : public User
{
protected:
    string name, gender, email, branch, id, officeNo;
    vector<Course *> subjects;
    bool is_FA;

public:
    Faculty(string uname = "", string pass = "", string name = "", string id = "",
            string gender = "", string email = "", string branch = "", string officeNo = "", bool is_FA = false)
        : User(uname, pass), name(name), id(id), gender(gender),
          email(email), branch(branch), officeNo(officeNo), is_FA(is_FA) {}

    bool login(string uname, string pass);
    bool changePassword(string newPass);
    bool is_FA_function();
    void AssignSubject(Course *course); // done
    // Faculty -> Course -> Student -> Update,View.
    vector<Course *> getSubjects(); // done
    string getFacultyID();
    string getFacultyName();
    string getPassword();
    string getGender();
    string getEmail();
    string getBranch();
    string getOfficeNo();
    void viewDetails(); // what to show will be decided
    void editProfile(); // to be implemented

    // void viewStudents(string courseID); // courseId should be from his subjects
    // void enterMarks(Course *course, int mark);
    // void viewMarks(string studentID);
    // while accessing check if student is registered in that course and he is the faculty of that course
    // void updateAttendance(Course *course);
    // void viewAttendance(Course *course);
};

class Student : public User
{
private:
    string name, branch, gender, dob, email, rollNo;
    string FA_ID;
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
    bool changePassword(string newPass) override;
    void setFA(string fa);
    string getFA_ID();
    void viewDetails();
    int getSem();
    void applyForLeave(string reason, Date startDate, Date endDate); 
    void addnotification(string notification);                       
    void viewNotifications();                                        
    void giveFeedback(string courseID, string feedback);    
    void registerCourse(int sem_num);                              
    void viewLeaveRecords();                                        
    string getRollNo();                                            
    void addSubject(Course *course);                              
    void addAttendance(string courseID, int attendanceCount);     
    void addMarks(string courseID, int mark);                      
    string getName();                               
    string getPassword();
    string getBranch();   
    int getSemNum();       
    string getGender();     
    string getDOB();       
    string getEmail();      
    int getYear();          
    float getCGPA();
    map<string, int> getMarks();
    map<string, int> getAttendance();
    void addLeaveApplication(LeaveApplication leave);
    void editProfile();
    vector<Course *> getRegisteredCourses();
    vector<LeaveApplication> getLeaveHistory();
};

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
    string getID();
    vector<Student *> getAssignedStudents();
    void setAssignedStudents(Student *student);
    void viewAssignedStudents();
    void reviewLeaveApplication();
    void submitApplication(Student *, LeaveApplication leave);
    bool isNewNotification();
    void setNewNotification(bool status);
    void newLeaveRequests(Student *student, LeaveApplication leave);
    void LeaveRequests(Student *student, LeaveApplication leave);
};