#include "frontend.h"

int main()
{
    headercheck(true);
    generateSymmetricMapping();
    system("cls");

    string frontline = "****************************************\n"
                       "Welcome to the Student Management System!\n"
                       "****************************************\n\n";
    for (char c : frontline)
    {
        cout << c;
        Sleep(40);
    }

    string choice;
    while (true)
    {
        cout << "===========================" << endl
             << "         Main Menu         " << endl
             << "===========================" << endl
             << "          1. Login         " << endl
             << "          2. About Us      " << endl
             << "          3. Exit          " << endl
             << "===========================" << endl;
        cout << "Please select an option: ";
        cin >> choice;
        cin.ignore();
        while (choice != "1" && choice != "2" && choice != "3")
        {
            cout << "Invalid choice. Please try again: ";
            cin >> choice;
            cin.ignore();
        }
        switch (stoi(choice))
        {
        case 1:
            system("cls");
            loginPage(true);
            break;
        case 2:
            system("cls");
            aboutUs();
            break;
        case 3:
            system("cls");
            exit_program();
        }
    }
    return 0;
}