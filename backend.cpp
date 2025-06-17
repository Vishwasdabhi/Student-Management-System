
// Arit & Shashank will write here to load and save data from file.
/*
include classes.cpp
make arrays/vectors of all classes
write save and load data functions in good manner
*/
#include "classes.cpp"

using namespace std;

// 1) Student information file // name, branch, roll number, subject name, credits, faculty id, total marks, sem number
// 2) Semester_wise attendence file
// 3) Semester wise marks with subjects

// 4) Faculty information file // faculty id, faculty name, subject name, faculty branch, faculty email
// 5) Leave application file .json/.txt Start Date, End Date, Reason, Status, FA id, Roll Numeber.
// 6) Login file -> student.txt -> faculty.txt(username, password, isFA)

vector<Student *> students;
vector<Course *> courses_sem1;
vector<Course *> courses_sem2;
vector<Faculty *> faculties;
vector<FA *> fa;
vector<LeaveApplication *> leaveApplications;

unordered_map<string, Student *> students_map;
unordered_map<string, Faculty *> faculties_map;
unordered_map<string, Course *> courses_sem1_map;
unordered_map<string, Course *> courses_sem2_map;
unordered_map<string, FA *> fa_map;
unordered_map<string, LeaveApplication *> leave_applications_map;

void fillMaps()
{
    for (auto &&student : students)
    {
        students_map[student->getRollNo()] = student;
        // students_map[student.getRollNo()] = student; // if we want to store the object instead of pointer
    }
    for (auto &&faculty : faculties)
    {
        faculties_map[faculty->getFacultyID()] = faculty;
    }
    for (auto &&course : courses_sem1)
    {
        courses_sem1_map[course->getID()] = course;
    }
    for (auto &&course : courses_sem2)
    {
        courses_sem2_map[course->getID()] = course;
    }
    for (auto &&fa : fa)
    {
        fa_map[fa->getID()] = fa;
    }
    for (auto &&leave : leaveApplications)
    {
        leave_applications_map[leave->getRollNo()] = leave;
    }
}

string toUpper(string &str)
{
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

void retrieve_info()
{
    ifstream file("student_information.csv");
    if (!file.is_open())
    {
        cout << "Error opening student information file." << endl;
        exit(1);
    }

    int line_count = 0;
    string line;
    while (getline(file, line))
    {
        line_count++;
    }
    line_count--; // to ignore the header line
    if (line_count == 0)
    {
        file.close();
        return;
    }
    file.clear();            // clear the EOF flag
    file.seekg(0, ios::beg); // move the cursor back to the beginning of the file

    string header;
    getline(file, header);

    // students = new Student[line_count];
    students.resize(line_count);
    char ch;
    string s;
    int sem_num, year;
    float cgpa;
    for (int j = 0; j < line_count; j++)
    {
        getline(file, s);
        stringstream ss(s);
        string name, password, branch, rollNo, sem_num_str, FA_ID, Gender, dob, email, year_str, cgpa_str;
        getline(ss, name, ',');
        getline(ss, password, ',');
        getline(ss, branch, ',');
        getline(ss, rollNo, ',');
        getline(ss, sem_num_str, ',');
        getline(ss, FA_ID, ',');
        getline(ss, Gender, ',');
        getline(ss, dob, ',');
        getline(ss, email, ',');
        getline(ss, year_str, ',');
        getline(ss, cgpa_str, ',');
        sem_num = stoi(sem_num_str);
        year = stoi(year_str);
        cgpa = stof(cgpa_str);
        students[j] = new Student(rollNo, password, name, rollNo, year, branch, FA_ID, cgpa, Gender, dob, email, sem_num);
    }
    file.close();

    ifstream file1("marks_sem1.csv");
    if (!file1.is_open())
    {
        cout << "Error opening attendance file for Semester 1." << endl;
        exit(1);
    }
    getline(file1, header);
    vector<string> subject_names_sem1;
    vector<int> credits_sem1;
    vector<bool> is_compulsory_sem1;
    stringstream ss1(header);
    string subject_name;
    while (getline(ss1, subject_name, ','))
    {
        if (subject_name != "Roll Number")
        {
            subject_names_sem1.push_back(subject_name.substr(0, subject_name.find('(')));
            string credits_str = subject_name.substr(subject_name.find('(') + 1, subject_name.find('-') - subject_name.find('(') - 1);
            string is_compulsory_str = subject_name.substr(subject_name.find('-') + 1, subject_name.find(')') - subject_name.find('-') - 1);
            int credits = stoi(credits_str);
            bool is_compulsory = (is_compulsory_str == "1");
            credits_sem1.push_back(credits);
            is_compulsory_sem1.push_back(is_compulsory);
        }
    }
    courses_sem1.resize(subject_names_sem1.size());
    // courses_sem1 = new Course[subject_names_sem1.size()];
    for (int i = 0; i < subject_names_sem1.size(); i++)
    {
        string branch = subject_names_sem1[i].substr(0, 2);
        courses_sem1[i] = new Course(subject_names_sem1[i], branch, credits_sem1[i], is_compulsory_sem1[i]);
    }

    while (getline(file1, s))
    {
        stringstream ss(s);
        string rollNo;
        getline(ss, rollNo, ',');
        for (int i = 0; i < subject_names_sem1.size(); i++)
        {
            string marks_str;
            getline(ss, marks_str, ',');
            if (!marks_str.empty())
            {
                int marks = stoi(marks_str);
                for (int j = 0; j < line_count; j++)
                {
                    if (students[j]->getRollNo() == rollNo)
                    {
                        students[j]->addSubject(courses_sem1[i]); // add the course to the student's registered courses

                        courses_sem1[i]->enrollStudent(students[j]->getRollNo());
                        students[j]->addMarks(subject_names_sem1[i], marks);

                        courses_sem1[i]->add_marks(students[j]->getRollNo(), marks);
                        break;
                    }
                }
            }
        }
    }
    file1.close();

    ifstream file2("attendance_sem1.csv");
    if (!file2.is_open())
    {
        cout << "Error opening attendance file for Semester 1." << endl;
        exit(1);
    }
    getline(file2, header);
    while (getline(file2, s))
    {
        stringstream ss(s);
        string rollNo;
        getline(ss, rollNo, ',');
        for (int i = 0; i < subject_names_sem1.size(); i++)
        {
            string attendance_str;
            getline(ss, attendance_str, ',');
            if (!attendance_str.empty())
            {
                int attendance = stoi(attendance_str);
                for (int j = 0; j < line_count; j++)
                {
                    if (students[j]->getRollNo() == rollNo)
                    {
                        students[j]->addAttendance(subject_names_sem1[i], attendance);

                        courses_sem1[i]->add_attendance(students[j]->getRollNo(), attendance);

                        break;
                    }
                }
            }
        }
    }
    file2.close();

    ifstream file3("marks_sem2.csv");
    if (!file3.is_open())
    {
        cout << "Error opening attendance file for Semester 2." << endl;
        exit(1);
    }
    getline(file3, header);
    vector<string> subject_names_sem2;
    vector<int> credits_sem2;
    vector<bool> is_compulsory_sem2;
    stringstream ss2(header);
    while (getline(ss2, subject_name, ','))
    {
        if (subject_name != "Roll Number")
        {
            subject_names_sem2.push_back(subject_name.substr(0, subject_name.find('(')));
            string credits_str = subject_name.substr(subject_name.find('(') + 1, subject_name.find('-') - subject_name.find('(') - 1);
            string is_compulsory_str = subject_name.substr(subject_name.find('-') + 1, subject_name.find(')') - subject_name.find('-') - 1);
            int credits = stoi(credits_str);
            bool is_compulsory = (is_compulsory_str == "1");
            credits_sem2.push_back(credits);
            is_compulsory_sem2.push_back(is_compulsory);
        }
    }
    courses_sem2.resize(subject_names_sem2.size());
    // courses_sem2 = new Course[subject_names_sem2.size()];
    for (int i = 0; i < subject_names_sem2.size(); i++)
    {
        string branch = subject_names_sem2[i].substr(0, 2);
        courses_sem2[i] = new Course(subject_names_sem2[i], branch, credits_sem2[i], is_compulsory_sem2[i]);
    }
    while (getline(file3, s))
    {
        stringstream ss(s);
        string rollNo;
        getline(ss, rollNo, ',');
        for (int i = 0; i < subject_names_sem2.size(); i++)
        {
            string marks_str;
            getline(ss, marks_str, ',');
            if (!marks_str.empty())
            {
                int marks = stoi(marks_str);
                for (int j = 0; j < line_count; j++)
                {
                    if (students[j]->getRollNo() == rollNo)
                    {
                        students[j]->addSubject(courses_sem2[i]);

                        courses_sem2[i]->enrollStudent(students[j]->getRollNo());

                        students[j]->addMarks(subject_names_sem2[i], marks);

                        courses_sem2[i]->add_marks(students[j]->getRollNo(), marks);
                        break;
                    }
                }
            }
        }
    }
    file3.close();

    ifstream file4("attendance_sem2.csv");
    if (!file4.is_open())
    {
        cout << "Error opening attendance file for Semester 2." << endl;
        exit(1);
    }
    getline(file4, header);
    while (getline(file4, s))
    {
        stringstream ss(s);
        string rollNo;
        getline(ss, rollNo, ',');
        for (int i = 0; i < subject_names_sem2.size(); i++)
        {
            string attendance_str;
            getline(ss, attendance_str, ',');
            if (!attendance_str.empty())
            {
                int attendance = stoi(attendance_str);
                for (int j = 0; j < line_count; j++)
                {
                    if (students[j]->getRollNo() == rollNo)
                    {
                        students[j]->addAttendance(subject_names_sem2[i], attendance);

                        courses_sem2[i]->add_attendance(students[j]->getRollNo(), attendance);
                        break;
                    }
                }
            }
        }
    }
    file4.close();

    ifstream file5("faculty_information.csv");
    if (!file5.is_open())
    {
        cout << "Error opening faculty information file." << endl;
        exit(1);
    }
    int faculty_count = 0;
    while (getline(file5, line))
    {
        faculty_count++;
    }
    faculty_count--;
    file5.clear();
    file5.seekg(0, ios::beg);
    getline(file5, header);

    faculties.resize(faculty_count);
    // faculties = new Faculty[faculty_count];
    for (int i = 0; i < faculty_count; i++)
    {
        getline(file5, s);
        stringstream ss(s);
        string faculty_id, password, faculty_name, branch, email, gender, officeNo;
        bool is_FA = false;
        getline(ss, faculty_id, ',');
        getline(ss, password, ',');
        getline(ss, faculty_name, ',');
        getline(ss, gender, ',');
        getline(ss, email, ',');
        getline(ss, branch, ',');
        getline(ss, officeNo, ',');
        getline(ss, s, ',');
        if (s == "1")
        {
            is_FA = true;
        }
        else if (s == "0")
        {
            is_FA = false;
        }

        vector<string> subjects;
        string subject;
        while (getline(ss, subject, ','))
        {
            if (!subject.empty())
            {
                subjects.push_back(subject);
            }
        }

        faculties[i] = new Faculty(faculty_id, password, faculty_name, faculty_id, gender, email, branch, officeNo, is_FA);
        for (const auto &sub : subjects)
        {
            int flag = 0;
            for (int j = 0; j < subject_names_sem1.size(); j++)
            {
                if (sub == subject_names_sem1[j])
                {
                    faculties[i]->AssignSubject(courses_sem1[j]);
                    courses_sem1[j]->addfaculty(faculties[i]->getFacultyID());
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                for (int j = 0; j < subject_names_sem2.size(); j++)
                {
                    if (sub == subject_names_sem2[j])
                    {
                        faculties[i]->AssignSubject(courses_sem2[j]);
                        courses_sem2[j]->addfaculty(faculties[i]->getFacultyID());
                        break;
                    }
                }
            }
        }
    }
    file5.close();
    int faculty_count_fa = 0;
    for (int j = 0; j < faculty_count; j++)
    {
        if (faculties[j]->is_FA_function())
        {
            faculty_count_fa++;
        }
    }

    fa.resize(faculty_count_fa);
    // fa = new FA[faculty_count_fa];
    int fa_index = 0;
    for (int j = 0; j < faculty_count; j++)
    {
        if (faculties[j]->is_FA_function())
        {
            fa[fa_index] = new FA(faculties[j]->getFacultyID(), faculties[j]->getPassword(), faculties[j]->getFacultyName(), faculties[j]->getFacultyID(),
                                  faculties[j]->getGender(), faculties[j]->getEmail(), faculties[j]->getBranch(), faculties[j]->getOfficeNo(), true);
            fa_index++;
        }
    }

    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < faculty_count_fa; j++)
        {
            if (students[i]->getFA_ID() == fa[j]->getID())
            {
                fa[j]->setAssignedStudents(students[i]);
                break;
            }
        }
    }
    // Problem: Either student should have a vector of marks or we should have a vector of courses in student class.

    ifstream file6("leave_applications.txt");
    if (!file6.is_open())
    {
        cout << "Error opening leave applications file." << endl;
        exit(1);
    }
    getline(file6, header);
    while (getline(file6, s))
    {
        stringstream ss(s);
        string rollNo, fa_id, reason, status;
        string startDate_str, endDate_str;
        Date startDate, endDate;
        getline(ss, rollNo, ',');
        getline(ss, fa_id, ',');
        getline(ss, reason, ',');
        getline(ss, startDate_str, ',');
        getline(ss, endDate_str, ',');
        getline(ss, status);
        int start_day, start_month, start_year;
        int end_day, end_month, end_year;
        sscanf(startDate_str.c_str(), "%d-%d-%d", &start_day, &start_month, &start_year);
        sscanf(endDate_str.c_str(), "%d-%d-%d", &end_day, &end_month, &end_year);
        startDate = Date(start_day, start_month, start_year);
        endDate = Date(end_day, end_month, end_year);
        LeaveApplication *leavePtr = new LeaveApplication(reason, startDate, endDate, status, fa_id, rollNo);
        leaveApplications.push_back(leavePtr);

        for (int i = 0; i < line_count; i++)
        {
            if (students[i]->getRollNo() == rollNo)
            {
                students[i]->addLeaveApplication(leavePtr);
                break;
            }
        }

        for (int i = 0; i < faculty_count_fa; i++)
        {
            if (fa[i]->getID() == fa_id)
            {
                if (status == "Pending")
                {
                    fa[i]->setNewNotification(true);
                    fa[i]->newLeaveRequests(leavePtr);
                }
                else
                {
                    fa[i]->LeaveRequests(leavePtr);
                }
                break;
            }
        }
    }
    file6.close();
    fillMaps();
}

void createheader()
{
    FILE *file, *inFile1, *inFile2, *inFile3, *inFile4;

    file = fopen("student_information.csv", "w");
    inFile1 = fopen("attendance_sem1.csv", "w");
    inFile2 = fopen("attendance_sem2.csv", "w");
    inFile3 = fopen("marks_sem1.csv", "w");
    inFile4 = fopen("marks_sem2.csv", "w");

    if (file == NULL || inFile1 == NULL || inFile2 == NULL || inFile3 == NULL || inFile4 == NULL)
    {
        cout << "Error opening file for writing." << endl;
        exit(1);
    }

    system("cls");

    cout << "The Database has not yet been created. PLease enter the following details to create the database.(Press enter to continue)" << endl;

    getchar();

    fprintf(file, "Name,Password,Branch,Roll Number,Sem Number,FA ID,Gender,DOB,Email,Year,CGPA\n");
    fclose(file);

    // vector<pair<string, pair<int, bool>>> subject_name_sem1;
    // vector<pair<string, pair<int, bool>>> subject_name_sem2;

    system("cls");
    cout << "Enter the number of subjects for Semester 1: ";
    int no_subjects_sem1;
    cin >> no_subjects_sem1;
    getchar(); // to consume the newline character after entering number of subjects
    cout << "Enter Subject ID, Credits and whether it is a compulsory subject (1 for Yes, 0 for No):" << endl;

    for (int i = 0; i < no_subjects_sem1; i++)
    {
        string subject_name;
        int credits;
        bool is_compulsory;
        cout << "Subject ID of subject number " << i + 1 << ": ";
        getline(cin, subject_name);
        cout << "Credits: ";
        cin >> credits;
        cout << "Is it a compulsory subject? (1 for Yes, 0 for No): ";
        cin >> is_compulsory;
        getchar(); // to consume the newline character after entering is_compulsory
        // subject_name_sem1.push_back(make_pair(subject_name, make_pair(credits, is_compulsory)));
        courses_sem1.push_back(new Course(subject_name, subject_name.substr(0, 2), credits, is_compulsory));
    }

    fprintf(inFile1, "Roll Number,");
    for (int i = 0; i < no_subjects_sem1; i++)
    {
        fprintf(inFile1, "%s,", courses_sem1[i]->getID().c_str());
    }
    fprintf(inFile1, "\n");
    fprintf(inFile3, "Roll Number,");
    for (int i = 0; i < no_subjects_sem1; i++)
    {
        fprintf(inFile3, "%s(%d-%d),", courses_sem1[i]->getID().c_str(), courses_sem1[i]->getCredits(), courses_sem1[i]->isCompulsoryCourse());
    }
    fprintf(inFile3, "\n");

    fclose(inFile1);
    fclose(inFile3);

    system("cls");

    cout << "Enter the number of subjects for Semester 2: ";

    int no_subjects_sem2;
    cin >> no_subjects_sem2;

    getchar(); // to consume the newline character after entering number of subjects

    cout << "Enter Subject ID, Credits and whether it is a compulsory subject (1 for Yes, 0 for No):" << endl;

    for (int i = 0; i < no_subjects_sem2; i++)
    {
        string subject_name;
        int credits;
        bool is_compulsory;
        cout << "Subject ID of subject number " << i + 1 << ": ";
        getline(cin, subject_name);
        cout << "Credits: ";
        cin >> credits;
        cout << "Is it a compulsory subject? (1 for Yes, 0 for No): ";
        cin >> is_compulsory;
        getchar(); // to consume the newline character after entering is_compulsory
        courses_sem2.push_back(new Course(subject_name, subject_name.substr(0, 2), credits, is_compulsory));
    }

    fprintf(inFile2, "Roll Number,");
    for (int i = 0; i < no_subjects_sem2; i++)
    {
        fprintf(inFile2, "%s,", courses_sem2[i]->getID().c_str());
    }
    fprintf(inFile2, "\n");

    fprintf(inFile4, "Roll Number,");
    for (int i = 0; i < no_subjects_sem2; i++)
    {
        fprintf(inFile4, "%s(%d-%d),", courses_sem2[i]->getID().c_str(), courses_sem2[i]->getCredits(), courses_sem2[i]->isCompulsoryCourse());
    }
    fprintf(inFile4, "\n");

    fclose(inFile2);
    fclose(inFile4);

    // created the header files for student information, attendance and marks for semester 1 and 2.

    inFile1 = fopen("faculty_information.csv", "w");
    fprintf(inFile1, "Faculty ID,Password,Faculty Name,Gender,Email,Branch,Office_No,is_FA,Subject_1,Subject_2,Subject_3,Subject_4,Subject_5\n");
    fclose(inFile1);

    inFile1 = fopen("leave_applications.txt", "w");
    fprintf(inFile1, "Roll Number,FA ID,Reason,Start Date,End Date,Status\n");
    fclose(inFile1);
    cout << "Database created successfully!" << endl;
    cout << "Press Enter to continue..." << endl;
    getchar();
    system("cls");
}

// function to check whether the file has an appropriate heading.
bool headercheck()
{
    ifstream file1("student_information.csv");
    if (!file1.is_open())
    {
        file1.close();
        return false;
    }
    string header;
    getline(file1, header);
    if (header != "Name,Password,Branch,Roll Number,Sem Number,FA ID,Gender,DOB,Email,Year,CGPA")
    {
        file1.close();
        return false;
    }
    retrieve_info();
    file1.close();
    return true;
}

void write_all_files()
{
    ofstream file("student_information.csv");
    if (!file.is_open())
    {
        cout << "Error opening student information file for writing." << endl;
        return;
    }
    file << "Name,Password,Branch,Roll Number,Sem Number,FA ID,Gender,DOB,Email,Year,CGPA\n";
    for (int i = 0; i < students.size(); i++)
    {
        file << students[i]->getName() << ","
             << students[i]->getPassword() << ","
             << students[i]->getBranch() << ","
             << students[i]->getRollNo() << ","
             << students[i]->getSemNum() << ","
             << students[i]->getFA_ID() << ","
             << students[i]->getGender() << ","
             << students[i]->getDOB() << ","
             << students[i]->getEmail() << ","
             << students[i]->getYear() << ","
             << students[i]->getCGPA() << "\n";
    }
    file.close();

    ofstream inFile1("marks_sem1.csv");
    if (!inFile1.is_open())
    {
        cout << "Error opening marks file for Semester 1." << endl;
        return;
    }
    inFile1 << "Roll Number,";
    for (int i = 0; i < courses_sem1.size(); i++)
    {
        string subject_name = courses_sem1[i]->getID();
        int credits = courses_sem1[i]->getCredits();
        bool is_compulsory = courses_sem1[i]->isCompulsoryCourse();
        inFile1 << subject_name << "(" << credits << "-" << is_compulsory << "),";
    }
    inFile1 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i]->getSemNum() != 1)
            continue;
        inFile1 << students[i]->getRollNo() << ",";
        map<string, int> marks = students[i]->getMarks();
        for (int j = 0; j < courses_sem1.size(); j++)
        {
            if (marks.find(courses_sem1[j]->getID()) != marks.end())
            {
                inFile1 << marks.at(courses_sem1[j]->getID()) << ",";
            }
            else
            {
                inFile1 << ",";
            }
        }
        inFile1 << "\n";
    }
    inFile1.close();

    ofstream inFile2("attendance_sem1.csv");
    if (!inFile2.is_open())
    {
        cout << "Error opening attendance file for Semester 1." << endl;
        return;
    }
    inFile2 << "Roll Number,";
    for (int i = 0; i < courses_sem1.size(); i++)
    {
        inFile2 << courses_sem1[i]->getID() << ",";
    }
    inFile2 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i]->getSemNum() != 1)
            continue;
        inFile2 << students[i]->getRollNo() << ",";
        map<string, int> attendance = students[i]->getAttendance();
        for (int j = 0; j < courses_sem1.size(); j++)
        {
            if (attendance.find(courses_sem1[j]->getID()) != attendance.end())
            {
                inFile2 << attendance.at(courses_sem1[j]->getID()) << ",";
            }
            else
            {
                inFile2 << ",";
            }
        }
        inFile2 << "\n";
    }
    inFile2.close();

    ofstream inFile3("marks_sem2.csv");
    if (!inFile3.is_open())
    {
        cout << "Error opening marks file for Semester 2." << endl;
        return;
    }
    inFile3 << "Roll Number,";
    for (int i = 0; i < courses_sem2.size(); i++)
    {
        string subject_name = courses_sem2[i]->getID();
        int credits = courses_sem2[i]->getCredits();
        bool is_compulsory = courses_sem2[i]->isCompulsoryCourse();
        inFile3 << subject_name << "(" << credits << "-" << is_compulsory << "),";
    }
    inFile3 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i]->getSemNum() != 2)
            continue;
        inFile3 << students[i]->getRollNo() << ",";
        map<string, int> marks = students[i]->getMarks();
        for (int j = 0; j < courses_sem2.size(); j++)
        {
            if (marks.find(courses_sem2[j]->getID()) != marks.end())
            {
                inFile3 << marks.at(courses_sem2[j]->getID()) << ",";
            }
            else
            {
                inFile3 << ",";
            }
        }
        inFile3 << "\n";
    }
    inFile3.close();

    ofstream inFile4("attendance_sem2.csv");
    if (!inFile4.is_open())
    {
        cout << "Error opening attendance file for Semester 2." << endl;
        return;
    }
    inFile4 << "Roll Number,";
    for (int i = 0; i < courses_sem2.size(); i++)
    {
        inFile4 << courses_sem2[i]->getID() << ",";
    }
    inFile4 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i]->getSemNum() != 2)
            continue;
        inFile4 << students[i]->getRollNo() << ",";
        map<string, int> attendance = students[i]->getAttendance();
        for (int j = 0; j < courses_sem2.size(); j++)
        {
            if (attendance.find(courses_sem2[j]->getID()) != attendance.end())
            {
                inFile4 << attendance.at(courses_sem2[j]->getID()) << ",";
            }
            else
            {
                inFile4 << ",";
            }
        }
        inFile4 << "\n";
    }
    inFile4.close();

    ofstream inFile5("faculty_information.csv");
    if (!inFile5.is_open())
    {
        cout << "Error opening faculty information file for writing." << endl;
        return;
    }
    inFile5 << "Faculty ID,Password,Faculty Name,Gender,Email,Branch,Office_No,is_FA,Subject_1,Subject_2,Subject_3,Subject_4,Subject_5\n";
    for (int i = 0; i < faculties.size(); i++)
    {
        inFile5 << faculties[i]->getFacultyID() << ","
                << faculties[i]->getPassword() << ","
                << faculties[i]->getFacultyName() << ","
                << faculties[i]->getGender() << ","
                << faculties[i]->getEmail() << ","
                << faculties[i]->getBranch() << ","
                << faculties[i]->getOfficeNo() << ","
                << (faculties[i]->is_FA_function() ? "1" : "0") << ",";
        const vector<Course *> &subjects = faculties[i]->getSubjects();
        for (int j = 0; j < subjects.size(); j++)
        {
            if (subjects[j]) // ✅ null check
                inFile5 << subjects[j]->getID() << ",";
            else
                inFile5 << "NULL,";
        }
        for (int j = subjects.size(); j < 5; j++)
        {
            inFile5 << ",";
        }
        inFile5 << "\n";
    }
    inFile5.close();
    ofstream inFile6("leave_applications.txt");
    if (!inFile6.is_open())
    {
        cout << "Error opening leave applications file for writing." << endl;
        return;
    }
    inFile6 << "Roll Number,FA ID,Reason,Start Date,End Date,Status\n";
    for (auto &leave : leaveApplications)
    {
        inFile6 << leave->getRollNo() << ","
                << leave->getFA_ID() << ","
                << leave->getReason() << ","
                << leave->getStartDate().showDate() << ","
                << leave->getEndDate().showDate() << ","
                << leave->getStatus() << "\n";
    }
    inFile6.close();
}

void addstudents()
{
    cout << "Enter the number of students to add: ";
    int n;
    cin >> n;
    cin.ignore(); // to ignore the newline character after entering n
    for (int i = 0; i < n; i++)
    {
        string name, rollNo, branch, FA_ID, gender, dob, email;
        int year, sem_num;
        cout << "Enter details for Student " << i + 1 << ":" << endl;
        cout << "Name: ";
        getline(cin, name);
        bool valid = false;
        while (!valid)
        {
            cout << "Select the branch from the available branches:" << endl;
            cout << "1. CSE" << endl;
            cout << "2. ECE" << endl;
            cout << "3. EE" << endl;
            cout << "4. ME" << endl;
            cout << "5. CE" << endl;
            cout << "Enter your choice (1-5): ";
            int branch_choice;
            cin >> branch_choice;
            switch (branch_choice)
            {
            case 1:
                branch = "CS";
                valid = true;
                break;
            case 2:
                branch = "EC";
                valid = true;
                break;
            case 3:
                branch = "EE";
                valid = true;
                break;
            case 4:
                branch = "ME";
                valid = true;
                break;
            case 5:
                branch = "CE";
                valid = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                cout << "Please select a valid branch." << endl;
                break;
            }
        }
        cin.ignore();
        cout << "FA ID: ";
        cin >> FA_ID;
        cin.ignore();
        cout << "Year(Batch year): ";
        cin >> year;
        cout << "Semester Number: ";
        cin >> sem_num;
        cin.ignore();
        cout << "Date of Birth (DD MM YYYY, leave the spaces as mentioned): ";
        int day, month, year_dob;
        cin >> day >> month >> year_dob;
        dob = to_string(day) + " " + to_string(month) + " " + to_string(year_dob);
        cin.ignore();
        cout << "Gender: ";
        getline(cin, gender);
        int count = 0;
        for (int j = 0; j < students.size(); j++)
        {
            if (students[j]->getRollNo().substr(0, 2) == to_string(year).substr(2, 2) && students[j]->getRollNo().substr(2, 2) == branch)
            {
                count = max(count, stoi(students[j]->getRollNo().substr(4)));
            }
        }
        if (count < 9)
            rollNo = to_string(year).substr(2, 2) + branch + "0" + to_string(count + 1);
        else
            rollNo = to_string(year).substr(2, 2) + branch + to_string(count + 1);
        students.push_back(new Student(rollNo, rollNo + "@iitbbs", name, rollNo, year, branch, FA_ID, 0.0, gender, dob, rollNo + "@iitbbs.ac.in", sem_num));

        for (int j = 0; j < fa.size(); j++)
        {
            if (fa[j]->getID() == FA_ID)
            {
                fa[j]->setAssignedStudents(students.back());
                students.back()->setFA(fa[j]->getID());
                break;
            }
        }
        students_map[students.back()->getRollNo()] = students.back();
        if(sem_num == 1)
        {
            for(int j = 0; j < courses_sem1.size(); j++)
            {
                if(courses_sem1[j]->isCompulsoryCourse())
                {
                    courses_sem1[j]->enrollStudent(rollNo);
                    students.back()->addSubject(courses_sem1[j]);
                    courses_sem1[j]->add_marks(rollNo, -1);
                    courses_sem1[j]->add_attendance(rollNo, -1);
                    students.back()->addMarks(courses_sem1[j]->getID(), -1);
                    students.back()->addAttendance(courses_sem1[j]->getID(), -1);
                }
            }
        }
        else if(sem_num == 2)
        {
            for(int j = 0; j < courses_sem2.size(); j++)
            {
                if(courses_sem2[j]->isCompulsoryCourse())
                {
                    courses_sem2[j]->enrollStudent(rollNo);
                    students.back()->addSubject(courses_sem2[j]);
                    courses_sem2[j]->add_marks(rollNo, -1);
                    courses_sem2[j]->add_attendance(rollNo, -1);
                }
            }
        }
        cout << "Student " << name << " added successfully!" << endl;
        Sleep(1000);
        system("cls");
    }
}

void deletestudents()
{
    cout << "Enter the Roll Number of the student to delete: ";
    string rollNo;
    cin >> rollNo;
    cin.ignore();
    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if ((*it)->getRollNo() == rollNo)
        {
            cout << "Deleting student: " << (*it)->getName() << endl;
            students.erase(it);
            break;
        }
    }
    for (auto it = students_map.begin(); it != students_map.end(); ++it)
    {
        if (it->first == rollNo)
        {
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
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        string name, id, branch, gender, email, officeNo, is_FA_str;
        bool is_FA;
        cout << "Enter details for Faculty " << i + 1 << ":" << endl;
        cout << "Name: ";
        getline(cin, name);
        bool valid = false;
        while (!valid)
        {
            cout << "Select the branch from the available branches:" << endl;
            cout << "1. CSE" << endl;
            cout << "2. ECE" << endl;
            cout << "3. EE" << endl;
            cout << "4. ME" << endl;
            cout << "5. CE" << endl;
            cout << "Enter your choice (1-5): ";
            int branch_choice;
            cin >> branch_choice;
            switch (branch_choice)
            {
            case 1:
                branch = "CS";
                valid = true;
                break;
            case 2:
                branch = "EC";
                valid = true;
                break;
            case 3:
                branch = "EE";
                valid = true;
                break;
            case 4:
                branch = "ME";
                valid = true;
                break;
            case 5:
                branch = "CE";
                valid = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                cout << "Please select a valid branch." << endl;
                break;
            }
        }
        cin.ignore();
        cout << "Gender: ";
        cin >> gender;
        cin.ignore();
        cout << "Office Number: ";
        cin >> officeNo;
        cin.ignore();
        cout << "Is this faculty a FA? (1 for Yes, 0 for No): ";
        cin >> is_FA_str;
        cin.ignore();
        is_FA = (is_FA_str == "1");

        int count = 0;
        for (int j = 0; j < faculties.size(); j++)
        {
            if (faculties[j]->getFacultyID().substr(0, 2) == branch)
            {
                count = max(count, stoi(faculties[j]->getFacultyID().substr(2)));
            }
        }
        if (count < 9)
            id = branch + "0" + to_string(count + 1) + toUpper(name).substr(0, 2);
        else
            id = branch + to_string(count + 1) + toUpper(name).substr(0, 2);

        faculties.push_back(new Faculty(id, id + "@iitbbs", name, id, gender, id + "@iitbbs.ac.in", branch, officeNo, is_FA));
        faculties_map[id] = faculties.back();
        cout << "Faculty " << name << " added successfully!" << endl;
        if (is_FA)
        {
            fa.push_back(new FA(id, id + "@iitbbs", name, id, gender, id + "@iitbbs.ac.in", branch, officeNo, is_FA));
            fa_map[id] = fa.back();
            // cout << "FA " << name << " added successfully!" << endl;
        }
        Sleep(1000);
        system("cls");
    }
}

void deletefaculty()
{
    cout << "Enter the Faculty ID to delete: ";
    string facultyID;
    cin >> facultyID;
    cin.ignore();
    bool found = false;
    for (int i = 0; i < faculties.size(); i++)
    {
        if (faculties[i]->getFacultyID() == facultyID)
        {
            found = true;
            faculties.erase(faculties.begin() + i);
            break;
        }
    }
    for (auto it = faculties_map.begin(); it != faculties_map.end(); ++it)
    {
        if (it->first == facultyID)
        {
            found = true;
            cout << "Faculty with ID " << facultyID << " deleted successfully." << endl;
            faculties_map.erase(it);
            return;
        }
    }
    if (!found)
    {
        system("cls");
        cout << "Faculty with ID " << facultyID << " not found." << endl;
    }
}

void addcourse()
{
    cout << "Enter the number of courses to add: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        string id, branch, is_compulsory_str;
        int semester;
        int credits;
        bool is_compulsory;
        cout << "Enter details for Course " << i + 1 << ":" << endl;
        cout << "Course ID: ";
        cin >> id;
        cout << "Enter semester number (1 or 2): ";
        cin >> semester;
        while (semester != 1 && semester != 2)
        {
            cout << "Invalid semester number. Please enter 1 or 2: ";
            cin >> semester;
        }
        cin.ignore();
        bool valid = false;
        while (!valid)
        {
            cout << "Select the branch from the available branches:" << endl;
            cout << "1. CSE" << endl;
            cout << "2. ECE" << endl;
            cout << "3. EE" << endl;
            cout << "4. ME" << endl;
            cout << "5. CE" << endl;
            cout << "Enter your choice (1-5): ";
            int branch_choice;
            cin >> branch_choice;
            switch (branch_choice)
            {
            case 1:
                branch = "CS";
                valid = true;
                break;
            case 2:
                branch = "EC";
                valid = true;
                break;
            case 3:
                branch = "EE";
                valid = true;
                break;
            case 4:
                branch = "ME";
                valid = true;
                break;
            case 5:
                branch = "CE";
                valid = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                cout << "Please select a valid branch." << endl;
                break;
            }
        }
        cout << "Credits: ";
        cin >> credits;
        cin.ignore();
        cout << "Is this course compulsory? (1 for Yes, 0 for No): ";
        cin >> is_compulsory_str;
        cin.ignore();
        is_compulsory = (is_compulsory_str == "1");
        Course *course = new Course(id, branch, credits, is_compulsory);
        if (semester == 1)
        {
            courses_sem1.push_back(course);
            courses_sem1_map[id] = courses_sem1.back();
        }
        else
        {
            courses_sem2.push_back(course);
            courses_sem2_map[id] = courses_sem2.back();
        }
        if (is_compulsory)
        {
            for (auto &student : students)
            {
                if (student->getSemNum() == semester)
                {
                    student->addSubject(course);
                    course->enrollStudent(student->getRollNo());
                    student->addAttendance(course->getID(), -1);
                    student->addMarks(course->getID(), -1);
                    course->add_attendance(student->getRollNo(), -1);
                    course->add_marks(student->getRollNo(), -1);
                }
            }
        }
        cout << "Course " << id << " added successfully!" << endl;
        Sleep(1000);
        system("cls");
    }
}

void deletecourse()
{
    cout << "Enter the Course ID to delete: ";
    string id;
    cin >> id;
    cin.ignore();
    for (auto it = courses_sem1.begin(); it != courses_sem1.end(); ++it)
    {
        if ((*it)->getID() == id)
        {
            cout << "Deleting course: " << (*it)->getID() << endl;
            courses_sem1.erase(it);
            cout << "Course deleted successfully!" << endl;
            return;
        }
    }
    for (auto it = courses_sem1_map.begin(); it != courses_sem1_map.end(); ++it)
    {
        if (it->first == id)
        {
            cout << "Deleting course: " << it->first << endl;
            courses_sem1_map.erase(it);
            cout << "Course deleted successfully!" << endl;
            return;
        }
    }
    for (auto it = courses_sem2.begin(); it != courses_sem2.end(); ++it)
    {
        if ((*it)->getID() == id)
        {
            cout << "Deleting course: " << (*it)->getID() << endl;
            courses_sem2.erase(it);
            cout << "Course deleted successfully!" << endl;
            return;
        }
    }
    for (auto it = courses_sem2_map.begin(); it != courses_sem2_map.end(); ++it)
    {
        if (it->first == id)
        {
            cout << "Deleting course: " << it->first << endl;
            courses_sem2_map.erase(it);
            cout << "Course deleted successfully!" << endl;
            return;
        }
    }
    cout << "Course with ID " << id << " not found." << endl;
}

/*

*/

// User
bool User::login(string uname, string pass)
{
    if (uname == username && pass == password)
    {
        cout << "Login successful!" << endl;
        return true;
    }
    return false;
}

bool User::changePassword(string newPass)
{
    if (newPass.empty())
    {
        cout << "Password cannot be empty." << endl;
        return false;
    }
    password = newPass;
    cout << "Password changed successfully!" << endl;
    return true;
}

// Functions of Date class

int Date ::Calculate_days(Date Start_date, Date End_date)
{
    int days = 0;
    vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day1 = Start_date.day, day2 = End_date.day;
    int month1 = Start_date.month, month2 = End_date.month;
    int year1 = Start_date.year, year2 = End_date.year;

    if (year1 > year2 || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2))
    {
        cout << "Invalid date range." << endl;
        return -1;
    }
    if (year1 == year2)
    {
        if (month1 == month2)
        {
            days = day2 - day1;
        }
        else
        {
            days += days_in_month[month1 - 1] - day1;
            for (int i = month1; i < month2 - 1; i++)
            {
                days += days_in_month[i];
            }
            days += day2;
        }
    }
    else
    {
        days += days_in_month[month1 - 1] - day1;
        for (int i = month1; i < 12; i++)
        {
            days += days_in_month[i];
        }
        for (int i = 0; i < month2 - 1; i++)
        {
            days += days_in_month[i];
        }
        days += day2;
        for (int i = year1 + 1; i < year2; i++)
        {
            if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
                days += 366;
            else
                days += 365;
        }
    }
    return days;
}

string Date::showDate()
{
    string date = "";
    if (day < 10)
        date += "0";
    date += to_string(day) + "-";
    if (month < 10)
        date += "0";
    date += to_string(month) + "-";
    date += to_string(year);
    return date;
}
/*


*/

// LeaveApplication
string LeaveApplication::getReason()
{
    return reason;
}
Date LeaveApplication::getStartDate()
{
    return startDate;
}
Date LeaveApplication::getEndDate()
{
    return endDate;
}
void LeaveApplication ::setStatus(string newStatus)
{
    status = newStatus;
}
string LeaveApplication ::getStatus()
{
    return status;
}
string LeaveApplication ::getFA_ID()
{
    return fa_id;
}
string LeaveApplication ::getRollNo()
{
    return rollNo;
}
/*


*/

// course
void Course::addfaculty(string facultyId)
{
    facultyIDs.push_back(facultyId);
}

void Course::removefaculty()
{
    // show all faculties and then remove the faculty
    for (auto &&faculty : facultyIDs)
    {
        cout << "Faculty ID: " << faculty << ", Name: " << faculties_map[faculty]->getFacultyName() << endl;
    }
    cout << endl;
    cout << "Enter the Faculty ID to remove: ";
    string facultyID;
    cin >> facultyID;
    auto it = find(facultyIDs.begin(), facultyIDs.end(), facultyID);
    if (it != facultyIDs.end())
    {
        facultyIDs.erase(it);
        cout << "Faculty with ID " << facultyID << " removed successfully!" << endl;
    }
    else
    {
        cout << "Faculty with ID " << facultyID << " not found." << endl;
    }
}

void Course::removeFacultyWithID(string facultyId)
{
    auto it = find(facultyIDs.begin(), facultyIDs.end(), facultyId);
    if (it != facultyIDs.end())
    {
        facultyIDs.erase(it);
    }
}

void Course::enrollStudent(string studentId)
{
    studentIDs.push_back(studentId);
}
void Course::receiveFeedback(string feedback)
{
    feedbacks.push_back(feedback);
}

string Course::getID()
{
    return id;
}
int Course::getCredits()
{
    return credits;
}

void Course ::add_marks(string studentId, int mark)
{
    marks[studentId] = mark;
}
void Course ::add_attendance(string studentId, int attendanceCount)
{
    attendance[studentId] = attendanceCount;
}

bool Course::isCompulsoryCourse()
{
    return isCompulsory;
}
map<string, int> Course ::getMarks()
{
    return marks;
}
map<string, int> Course ::getAttendance()
{
    return attendance;
}
vector<string> Course ::getStudents()
{
    return studentIDs;
}
vector<string> Course ::getFaculties()
{
    return facultyIDs;
}

/*




*/

// faculty

bool Faculty::login(string uname, string pass)
{
    if (User::login(uname, pass))
    {
        cout << "Welcome, " << name << "!" << endl;
        return true;
    }
    return false;
}
bool Faculty::is_FA_function()
{
    return is_FA;
}

void Faculty::AssignSubject(Course *course, bool temp)
{
    if (course == nullptr)
    {
        cout << "Invalid course." << endl;
        return;
    }
    if (find(subjects.begin(), subjects.end(), course) != subjects.end())
    {
        cout << "You are already assigned to this course." << endl;
        return;
    }
    subjects.push_back(course);
    if (!temp)
        return;
    course->addfaculty(this->getFacultyID());
}

void Faculty::removeSubject(Course *course)
{
    auto it = find(subjects.begin(), subjects.end(), course);
    if (it != subjects.end())
    {
        subjects.erase(it);
        string facultyID = this->getFacultyID();
        Faculty *faculty = faculties_map[facultyID];
        course->removeFacultyWithID(facultyID);
    }
    else
    {
        cout << "You are not assigned to this subject." << endl;
    }
}

vector<Course *> Faculty::getSubjects()
{
    return subjects;
}

string Faculty::getFacultyID()
{
    return id;
}

string Faculty::getFacultyName()
{
    return name;
}

string Faculty::getPassword()
{
    return password;
}

string Faculty::getGender()
{
    return gender;
}

string Faculty::getEmail()
{
    return email;
}

string Faculty::getBranch()
{
    return branch;
}

string Faculty::getOfficeNo()
{
    return officeNo;
}

void Faculty::viewDetails()
{
    cout << "Faculty ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Branch: " << branch << endl;
    cout << "Office No: " << officeNo << endl;
}

void Faculty::editProfile()
{
    cout << "Editing profile for " << name << endl;
    cout << "Current details:" << endl;
    viewDetails();
    cout << "What do you want to edit?" << endl;
    cout << "1. Name" << endl;
    cout << "2. Office No" << endl;
    int choice;
    cin >> choice;
    system("cls");
    cin.ignore();
    if (choice == 1)
    {
        cout << "Enter new name: ";
        getline(cin, name);
    }
    else if (choice == 2)
    {
        cout << "Enter new office number: ";
        cin >> officeNo;
        cin.ignore();
    }
    else
    {
        cout << "Invalid choice." << endl;
        Sleep(1000);
        system("cls");
        return;
    }
    cout << "Profile updated successfully!" << endl;
}

void Faculty :: setName(string name1)
{
    name = name1;
}

void Faculty :: setOffice(string office_num)
{
    officeNo = office_num;
}
/*



*/

// Student

bool Student::login(string uname, string pass)
{
    if (User::login(uname, pass))
    {
        cout << "Welcome, " << name << "!" << endl;
        return true;
    }
    return false;
}

void Student ::setFA(string fa)
{
    FA_ID = fa;
}
string Student ::getFA_ID()
{
    return FA_ID;
}

void Student::viewDetails()
{
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << rollNo << endl;
    cout << "Gender: " << gender << endl;
    cout << "Branch: " << branch << endl;
    cout << "Semester Number: " << sem_num << endl;
    cout << "Year: " << year << endl;
}

int Student ::getSem()
{
    return sem_num;
}
void Student ::applyForLeave(string reason, Date startDate, Date endDate)
{
    LeaveApplication* leave = new LeaveApplication(reason, startDate, endDate, "Pending", FA_ID, rollNo);
    leaveHistory.push_back(leave);
    leaveApplications.push_back(leave);
    fa_map[FA_ID]->submitApplication(leave);
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

void Student ::giveFeedback(string courseID, string Feedback)
{
    // to be implimented
}

void Student ::registerCourse(int sem_num)
{
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
            cout << leave->getReason() << " From: " << leave->getStartDate().showDate() << " To: " << leave->getEndDate().showDate() << endl;
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

string Student::getName()
{
    return name;
}

string Student::getPassword()
{
    return password;
}

string Student::getBranch()
{
    return branch;
}

int Student::getSemNum()
{
    return sem_num;
}

string Student::getGender()
{
    return gender;
}

string Student::getDOB()
{
    return dob;
}

string Student::getEmail()
{
    return email;
}

int Student::getYear()
{
    return year;
}

float Student::getCGPA()
{
    return CGPA;
}
map<string, int> Student::getMarks()
{
    return marks;
}
map<string, int> Student::getAttendance()
{
    return attendance;
}
void Student ::addLeaveApplication(LeaveApplication *leave)
{
    leaveHistory.push_back(leave);
}

void Student::editProfile()
{
    cout << "Editing profile for " << name << endl;
    cout << "Current details:" << endl;
    viewDetails();
    cout << "Enter new name (or press Enter to keep current): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty())
        name = newName;

    cout << "Profile updated successfully!" << endl;
}
vector<Course *> Student ::getRegisteredCourses()
{
    return registeredCourses;
}
vector<LeaveApplication*> Student ::getLeaveHistory()
{
    return leaveHistory;
}
/*




*/

string FA ::getID()
{
    return id;
}

vector<Student *> FA::getAssignedStudents()
{
    return assignedStudents;
}

void FA::setAssignedStudents(Student *student)
{
    assignedStudents.push_back(student);
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
        string rollNo = request->getRollNo();
        string reason = request->getReason();
        Date startDate = request->getStartDate();
        Date endDate = request->getEndDate();

        cout << "Leave Request from " << rollNo << " for :" << reason << " from " << startDate.showDate() << " to " << endDate.showDate() << endl;

        cout << "Do you want to approve this leave request? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            leaveRequests.push_back(request);
            cout << "Leave request approved for " << rollNo << endl;
            request->setStatus("Approved");
            for(auto &leaveApplication : leaveApplications)
            {
                if(leaveApplication->getRollNo() == request->getRollNo() && leaveApplication->getStartDate().showDate() == startDate.showDate() && leaveApplication->getEndDate().showDate() == endDate.showDate())
                {
                    leaveApplication->setStatus("Approved");
                    break;
                }
            }
        }
        else
        {
            leaveRequests.push_back(request);
            cout << "Leave request rejected for " << rollNo << endl;
            request->setStatus("Rejected");
            for(auto &leaveApplication : leaveApplications)
            {
                if(leaveApplication->getRollNo() == request->getRollNo() && leaveApplication->getStartDate().showDate() == startDate.showDate() && leaveApplication->getEndDate().showDate() == endDate.showDate())
                {
                    leaveApplication->setStatus("Rejected");
                    break;
                }
            }
        }
    }
    newleaveRequests.clear();
    New_Notification = false;
}

void FA ::submitApplication(LeaveApplication *leave)
{
    newleaveRequests.push_back(leave);
    New_Notification = true;
}

bool FA ::isNewNotification()
{
    return New_Notification;
}
void FA ::setNewNotification(bool status)
{
    New_Notification = status;
}
void FA ::newLeaveRequests(LeaveApplication *leave)
{
    newleaveRequests.push_back(leave);
    New_Notification = true;
}
void FA ::LeaveRequests(LeaveApplication *leave)
{
    leaveRequests.push_back(leave);
    New_Notification = true;
}

void FA::editProfile()
{
    cout << "Editing profile for " << name << endl;
    cout << "Current details:" << endl;
    viewDetails();
    cout << "What do you want to edit?" << endl;
    cout << "1. Name" << endl;
    cout << "2. Office No" << endl;
    int choice;
    cin >> choice;
    system("cls");
    cin.ignore();
    Faculty *faculty = faculties_map[id];
    if (choice == 1)
    {
        string name1;
        cout << "Enter new name: ";
        getline(cin, name1);
        name = name1;
        faculty->setName(name1);
    }
    else if (choice == 2)
    {
        cout << "Enter new office number: ";
        cin >> officeNo;
        faculty->setOffice(officeNo);
        cin.ignore();
    }
    else
    {
        cout << "Invalid choice." << endl;
        Sleep(1000);
        system("cls");
        return;
    }
    cout << "Profile updated successfully!" << endl;
}

bool Student::changePassword(string newPass)
{
    password = newPass;
    return true;
}

bool Faculty::changePassword(string newPass)
{
    password = newPass;
    return true;
}
