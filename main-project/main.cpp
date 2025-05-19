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
    cout << "Author: Roman Bachun\n\n";
    session_results* session_results[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", session_results, size);
        for (int i = 0; i < size; i++)
        {
            cout << "------------------------------------------------------------------------------" << endl;
            cout << " | " << left << setw(10) << session_results[i]->student.last_name << " "
                << left << setw(8) << session_results[i]->student.first_name << " "
                << left << setw(12) << session_results[i]->student.middle_name << " | "
                << setfill('0') << setw(2) << session_results[i]->date.day << "."
                << setfill('0') << setw(2) << session_results[i]->date.month << "."
                << setfill(' ') << session_results[i]->date.year << " | "
                << setw(2) << session_results[i]->grade << " | "
                << setw(20) << right << session_results[i]->subject << " | \n";
        }
        for (int i = 0; i < size; i++)
        {
            delete session_results[i];
        }
        cout << "------------------------------------------------------------------------------" << endl;
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}