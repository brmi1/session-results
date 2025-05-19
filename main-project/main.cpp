#include <iostream>
#include <iomanip>

using namespace std;

#include "session_results.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Session results #8. GIT\n";
    cout << "Variant #8. Session results\n";
    cout << "Author: Roman Bachun\n";
    session_results* session_results[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", session_results, size);
        for (int i = 0; i < size; i++)
        {
            cout << session_results[i]->student.last_name << '\n';
            cout << session_results[i]->student.first_name << '\n';
            cout << session_results[i]->student.middle_name << '\n';
            cout << session_results[i]->date.day << '.';
            cout << session_results[i]->date.month << '.';
            cout << session_results[i]->date.year << '\n';
            cout << session_results[i]->grade << '\n';
            cout << session_results[i]->subject << '\n';
            cout << '\n';
        }
        for (int i = 0; i < size; i++)
        {
            delete session_results[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}
