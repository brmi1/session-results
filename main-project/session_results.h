#ifndef SESSION_RESULTS_H
#define SESSION_RESULTS_H

#include "constants.h"
#include <string>

using namespace std;

struct date
{
    int day;
    int month;
    int year;
};

struct person
{
    char first_name[MAX_STRING_SIZE];
    char middle_name[MAX_STRING_SIZE];
    char last_name[MAX_STRING_SIZE];
};

struct session_results
{
    person student;
    date date;
    int grade;
    string subject;
};

#endif