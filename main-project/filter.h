#ifndef FILTER_H
#define FILTER_H

#include "session_results.h"

session_results** filter(session_results* array[], int size, bool (*check)(session_results* element), int& result_size);

bool filter_by_history(session_results* element);

bool filter_by_grade(session_results* element);

session_results** insertion_sort(session_results* array[], int size, string sort_param);

session_results** merge_sort(session_results* array[], int size, string sort_param);

#endif