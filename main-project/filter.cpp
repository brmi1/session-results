#include "filter.h"
#include <cstring>
#include <iostream>
#include <cstring>

using namespace std;

session_results** filter(session_results* array[], int size, bool (*check)(session_results* element), int& result_size)
{
	session_results** result = new session_results * [size];
	result_size = 0;
	for (int i = 0; i < size; i++)
	{
		if (check(array[i]))
		{
			result[result_size++] = array[i];
		}
	}
	return result;
}

session_results** get_copy(session_results* array[], int size)
{
	session_results** result = new session_results * [size];

	for (int i = 0; i < size; i++) {
		result[i] = array[i];
	}

	return result;
}

bool filter_by_history(session_results* element)
{
	return element->subject == "История";
}

bool filter_by_grade(session_results* element)
{
	return element->grade > 7;
}

session_results** insertion_sort(session_results* array[], int size, string sort_param)
{
	session_results** result = get_copy(array, size);

	if (sort_param == "second name")
	{
		for (int i = 1; i < size; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (strcmp(result[j - 1]->student.last_name, result[j]->student.last_name) == -1)
				{
					swap(result[j - 1], result[j]);
				}
			}
		}
	}
	else if (sort_param == "subject")
	{
		for (int i = 1; i < size; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (strcmp(result[j - 1]->subject.c_str(), result[j]->subject.c_str()) == -1)
				{
					swap(result[j - 1], result[j]);
				}
			}
		}
		for (int i = 1; i < size; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (result[j - 1]->subject == result[j]->subject && result[j - 1]->grade > result[j]->grade)
				{
					swap(result[j - 1], result[j]);
				}
			}
		}
	}

	return result;
}

session_results** merge_sort(session_results* array[], int size, string sort_param)
{
    session_results** result = get_copy(array, size);

    if (size <= 1) {
        return result;
    }

    int mid = size / 2;
    session_results** left = new session_results * [mid];
    session_results** right = new session_results * [size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = result[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = result[i];
    }

    left = merge_sort(left, mid, sort_param);
    right = merge_sort(right, size - mid, sort_param);

    session_results** merged = new session_results * [size];
    int left_idx = 0, right_idx = 0, merged_idx = 0;

    if (sort_param == "second name") {
        while (left_idx < mid && right_idx < size - mid) {
            if (strcmp(left[left_idx]->student.last_name, right[right_idx]->student.last_name) >= 0) {
                merged[merged_idx++] = left[left_idx++];
            }
            else {
                merged[merged_idx++] = right[right_idx++];
            }
        }
    }
    else if (sort_param == "subject") {
        while (left_idx < mid && right_idx < size - mid) {
            int cmp = strcmp(left[left_idx]->subject.c_str(), right[right_idx]->subject.c_str());
            if (cmp > 0 || (cmp == 0 && left[left_idx]->grade <= right[right_idx]->grade)) {
                merged[merged_idx++] = left[left_idx++];
            }
            else {
                merged[merged_idx++] = right[right_idx++];
            }
        }
    }

    while (left_idx < mid) {
        merged[merged_idx++] = left[left_idx++];
    }
    while (right_idx < size - mid) {
        merged[merged_idx++] = right[right_idx++];
    }

    for (int i = 0; i < size; i++) {
        result[i] = merged[i];
    }

    delete[] left;
    delete[] right;
    delete[] merged;

    return result;
}