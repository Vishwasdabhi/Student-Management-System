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

vector<Student> students;
vector<Course> courses_sem1;
vector<Course> courses_sem2;
vector<Faculty> faculties;
vector<FA> fa;

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
        students[j] = Student(rollNo, password, name, rollNo, year, branch, FA_ID, cgpa, Gender, dob, email, sem_num);
    }
    file.close();

    ifstream file("marks_sem1.csv");
    if (!file.is_open())
    {
        cout << "Error opening attendance file for Semester 1." << endl;
        exit(1);
    }
    getline(file, header);
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
    //courses_sem1 = new Course[subject_names_sem1.size()];
    for (int i = 0; i < subject_names_sem1.size(); i++)
    {
        string branch = subject_names_sem1[i].substr(0, 2);
        courses_sem1[i] = Course(subject_names_sem1[i], branch, credits_sem1[i], is_compulsory_sem1[i]);
    }

    while (getline(file, s))
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
                    if (students[j].getRollNo() == rollNo)
                    {
                        students[j].addSubject(&courses_sem1[i]); // add the course to the student's registered courses

                        courses_sem1[i].enrollStudent(&students[j]);

                        students[j].addMarks(subject_names_sem1[i], marks);

                        courses_sem1[i].add_marks(&students[j], marks); // add marks to the course's marks map

                        break;
                    }
                }
            }
        }
    }
    file.close();

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
                    if (students[j].getRollNo() == rollNo)
                    {
                        students[j].addAttendance(subject_names_sem1[i], attendance);

                        courses_sem1[i].add_attendance(&students[j], attendance);

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
    //courses_sem2 = new Course[subject_names_sem2.size()];
    for (int i = 0; i < subject_names_sem2.size(); i++)
    {
        string branch = subject_names_sem2[i].substr(0, 2);
        courses_sem2[i] = Course(subject_names_sem2[i], branch, credits_sem2[i], is_compulsory_sem2[i]);
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
                    if (students[j].getRollNo() == rollNo)
                    {
                        students[j].addSubject(&courses_sem2[i]);

                        courses_sem2[i].enrollStudent(&students[j]);

                        students[j].addMarks(subject_names_sem2[i], marks);

                        courses_sem2[i].add_marks(&students[j], marks);
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
                    if (students[j].getRollNo() == rollNo)
                    {
                        students[j].addAttendance(subject_names_sem2[i], attendance);

                        courses_sem2[i].add_attendance(&students[j], attendance);
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
    //faculties = new Faculty[faculty_count];
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

        faculties[i] = Faculty(faculty_id, password, faculty_name, faculty_id, gender, email, branch, officeNo, is_FA);
        for (const auto &sub : subjects)
        {
            int flag = 0;
            for (int j = 0; j < subject_names_sem1.size(); j++)
            {
                if (sub == subject_names_sem1[j])
                {
                    faculties[i].AssignSubject(&courses_sem1[j]);
                    courses_sem1[j].addfaculty(&faculties[i]);
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
                        faculties[i].AssignSubject(&courses_sem2[j]);
                        courses_sem2[j].addfaculty(&faculties[i]);
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
        if (faculties[j].is_FA_function())
        {
            faculty_count_fa++;
        }
    }

    fa.resize(faculty_count_fa);
    //fa = new FA[faculty_count_fa];
    int fa_index = 0;
    for (int j = 0; j < faculty_count; j++)
    {
        if (faculties[j].is_FA_function())
        {
            fa[fa_index] = FA(faculties[j].getFacultyID(), faculties[j].getPassword(), faculties[j].getFacultyName(), faculties[j].getFacultyID(),
                              faculties[j].getGender(), faculties[j].getEmail(), faculties[j].getBranch(), faculties[j].getOfficeNo(), true);
            fa_index++;
        }
    }

    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < faculty_count_fa; j++)
        {
            if (students[i].getFA_ID() == fa[j].getID())
            {
                fa[j].setAssignedStudents(&students[i]);
                break;
            }
        }
    }
    // Problem: Either student should have a vector of marks or we should have a vector of courses in student class.
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

    vector<pair<string, pair<int, bool>>> subject_name_sem1;
    vector<pair<string, pair<int, bool>>> subject_name_sem2;

    system("cls");
    cout << "Enter the number of subjects for Semester 1:" << endl;
    int no_subjects_sem1;
    cin >> no_subjects_sem1;
    getchar(); // to consume the newline character after entering number of subjects
    cout << "Enter Subject ID, Credits and whether it is a compulsory subject (1 for Yes, 0 for No):" << endl;

    for (int i = 0; i < no_subjects_sem1; i++)
    {
        string subject_name;
        int credits;
        bool is_compulsory;
        cout << "Subject ID" << i + 1 << ": ";
        getline(cin, subject_name);
        cout << "Credits: ";
        cin >> credits;
        cout << "Is it a compulsory subject? (1 for Yes, 0 for No): ";
        cin >> is_compulsory;
        getchar(); // to consume the newline character after entering is_compulsory
        subject_name_sem1.push_back(make_pair(subject_name, make_pair(credits, is_compulsory)));
    }

    fprintf(inFile1, "Roll Number,");
    for (int i = 0; i < no_subjects_sem1; i++)
    {
        fprintf(inFile1, "%s,", subject_name_sem1[i].first.c_str());
    }
    fprintf(inFile1, "\n");

    fprintf(inFile3, "Roll Number,");
    for (int i = 0; i < no_subjects_sem1; i++)
    {
        fprintf(inFile3, "%s(%d-%d)", subject_name_sem1[i].first.c_str(), subject_name_sem1[i].second.first, subject_name_sem1[i].second.second);
    }
    fprintf(inFile3, "\n");

    fclose(inFile1);
    fclose(inFile3);

    system("cls");

    cout << "Enter the number of subjects for Semester 2:" << endl;

    int no_subjects_sem2;
    cin >> no_subjects_sem2;

    getchar(); // to consume the newline character after entering number of subjects

    cout << "Enter Subject Name, Credits and whether it is a compulsory subject (1 for Yes, 0 for No):" << endl;

    for (int i = 0; i < no_subjects_sem2; i++)
    {
        string subject_name;
        int credits;
        bool is_compulsory;
        cout << "Subject " << i + 1 << ": ";
        getline(cin, subject_name);
        cout << "Credits: ";
        cin >> credits;
        cout << "Is it a compulsory subject? (1 for Yes, 0 for No): ";
        cin >> is_compulsory;
        getchar(); // to consume the newline character after entering is_compulsory
        subject_name_sem2.push_back(make_pair(subject_name, make_pair(credits, is_compulsory)));
    }

    fprintf(inFile2, "Roll Number,");
    for (int i = 0; i < no_subjects_sem2; i++)
    {
        fprintf(inFile2, "%s,", subject_name_sem2[i].first.c_str());
    }
    fprintf(inFile2, "\n");

    fprintf(inFile4, "Roll Number,");
    for (int i = 0; i < no_subjects_sem2; i++)
    {
        fprintf(inFile4, "%s(%d-%d)", subject_name_sem2[i].first.c_str(), subject_name_sem2[i].second.first, subject_name_sem2[i].second.second);
    }
    fprintf(inFile4, "\n");

    fclose(inFile2);
    fclose(inFile4);

    // created the header files for student information, attendance and marks for semester 1 and 2.

    inFile1 = fopen("faculty_information.csv", "w");
    fprintf(inFile1, "Faculty ID,Password,Faculty Name,Gender,Email,Branch,Office_No,is_FA,Subject_1,Subject_2,Subject_3,Subject_4,Subject_5\n");
    fclose(inFile1);

    cout << "Database created successfully!" << endl;
    cout << "Press Enter to continue..." << endl;
    getchar();
    system("cls");
}

// function to check whether the file has an appropriate heading.
void headercheck()
{
    ifstream file1("student_information.csv");
    if (!file1.is_open())
    {
        createheader();
    }
    string header;
    getline(file1, header);
    if (header != "Name,Password,Branch,Roll Number,Sem Number,FA ID,Gender,DOB,Email,Year,CGPA")
    {
        createheader();
        file1.close();
        return;
    }
    // retrieve_info();
    // retrieve_attendance();
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
        file << students[i].getName() << ","
             << students[i].getPassword() << ","
             << students[i].getBranch() << ","
             << students[i].getRollNo() << ","
             << students[i].getSemNum() << ","
             << students[i].getFA_ID() << ","
             << students[i].getGender() << ","
             << students[i].getDOB() << ","
             << students[i].getEmail() << ","
             << students[i].getYear() << ","
             << students[i].getCGPA() << "\n";
    }
    file.close();

    ofstream inFile1("marks_sem1.csv");
    if (!inFile1.is_open())
    {
        cout << "Error opening marks file for Semester 1." << endl;
        return;
    }
    inFile1 << "Roll Number,";
    for (int i = 0; i <courses_sem1.size(); i++)
    {
        string subject_name = courses_sem1[i].getID();
        int credits = courses_sem1[i].getCredits();
        bool is_compulsory = courses_sem1[i].isCompulsoryCourse();
        inFile1 << subject_name << "(" << credits << "-" << is_compulsory << "),";
    }
    inFile1 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getSemNum() != 1)
            continue;
        inFile1 << students[i].getRollNo() << ",";
        map<string, int> marks = students[i].getMarks();
        for (int j = 0; j < courses_sem1.size(); j++)
        {
            if (marks.find(courses_sem1[j].getID()) != marks.end())
            {
                inFile1 << marks.at(courses_sem1[j].getID()) << ",";
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
        inFile2 << courses_sem1[i].getID() << ",";
    }
    inFile2 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getSemNum() != 1)
            continue;
        inFile2 << students[i].getRollNo() << ",";
        map<string, int> attendance = students[i].getAttendance();
        for (int j = 0; j < courses_sem1.size(); j++)
        {
            if (attendance.find(courses_sem1[j].getID()) != attendance.end())
            {
                inFile2 << attendance.at(courses_sem1[j].getID()) << ",";
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
        string subject_name = courses_sem2[i].getID();
        int credits = courses_sem2[i].getCredits();
        bool is_compulsory = courses_sem2[i].isCompulsoryCourse();
        inFile3 << subject_name << "(" << credits << "-" << is_compulsory << "),";
    }
    inFile3 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getSemNum() != 2)
            continue;
        inFile3 << students[i].getRollNo() << ",";
        map<string, int> marks = students[i].getMarks();
        for (int j = 0; j < courses_sem2.size(); j++)
        {
            if (marks.find(courses_sem2[j].getID()) != marks.end())
            {
                inFile3 << marks.at(courses_sem2[j].getID()) << ",";
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
        inFile4 << courses_sem2[i].getID() << ",";
    }
    inFile4 << "\n";
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getSemNum() != 2)
            continue;
        inFile4 << students[i].getRollNo() << ",";
        map<string, int> attendance = students[i].getAttendance();
        for (int j = 0; j < courses_sem2.size(); j++)
        {
            if (attendance.find(courses_sem2[j].getID()) != attendance.end())
            {
                inFile4 << attendance.at(courses_sem2[j].getID()) << ",";
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
        inFile5 << faculties[i].getFacultyID() << ","
        << faculties[i].getPassword() << ","
        << faculties[i].getFacultyName() << ","
        << faculties[i].getGender() << ","
        << faculties[i].getEmail() << ","
        << faculties[i].getBranch() << ","
        << faculties[i].getOfficeNo() << ","
        << (faculties[i].is_FA_function() ? "1" : "0") << ",";
        vector<Course *> subjects = faculties[i].getSubjects();
        for (int j = 0; j < subjects.size(); j++)
        {
            inFile5 << subjects[j]->getID() << ",";
        }
        for (int j = subjects.size(); j < 5; j++)
        {
            inFile5 << ",";
        }
        inFile5 << "\n";
    }
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
        cin.ignore(); // to ignore the newline character
        getline(cin, name);
        cout << "Roll Number: ";
        getline(cin, rollNo);
        cout << "Branch: ";
        getline(cin, branch);
        cout << "FA ID: ";
        getline(cin, FA_ID);
        cout << "Year: ";
        cin >> year;
        cout << "Semester Number: ";
        cin >> sem_num;
        cin.ignore(); // to ignore the newline character after entering sem_num
        cout << "Date of Birth (DD MM YYYY): ";
        int day, month, year_dob;
        cin >> day >> month >> year_dob;
        dob = to_string(day) + " " + to_string(month) + " " + to_string(year_dob);
        cout << "Email: ";
        getline(cin, email);
        cout << "Gender: ";
        getline(cin, gender);
        students.push_back(Student(rollNo, rollNo + "@iitbbs", name, rollNo, year, branch, FA_ID, 0.0, gender, dob, email, sem_num));

        for (int j = 0; j < fa.size(); j++)
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

int main()
{
}