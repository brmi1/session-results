#include "process.h"
#include "session_results.h"
#include <cstring>
#include <iostream>

int date_to_days(const date& d) {
	return d.year * 365 + d.month * 30 + d.day;
}

int calculate_session_duration(session_results* array[], int size, string subject)
{
	int count_subject = 0;
	int session_duration = 0;
	int max_days = INT_MIN;
	int min_days = INT_MAX;

	for (int i = 0; i < size; i++)
	{
		if (array[i]->subject == subject)
		{
			count_subject++;
		}
	}

	if (count_subject < 2)
	{
		return session_duration;
	}

	for (int i = 0; i < size; i++) {
		if (array[i]->subject == subject) {
			int days = date_to_days(array[i]->date);
			if (days < min_days) {
				min_days = days;
			}
			if (days > max_days) {
				max_days = days;
			}
		}
	}

	return max_days - min_days;
}