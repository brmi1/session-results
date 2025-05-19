#include <iostream>
#include <iomanip>

using namespace std;

#include "session_results.h"
#include "file_reader.h"
#include "constants.h"
#include "filter.h"
#include "processing.h"
#include <windows.h>

void output(session_results* result)
{
	cout << "------------------------------------------------------------------------------" << endl;
	cout << " | " << left << setw(10) << result->student.last_name << " "
		<< left << setw(8) << result->student.first_name << " "
		<< left << setw(12) << result->student.middle_name << " | "
		 << setw(2) << result->date.day << "."
		<< setw(2) << result->date.month << "."
		<< setfill(' ') << result->date.year << " | "
		<< setw(2) << result->grade << " | "
		<< setw(20) << right << result->subject << " | \n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Лабораторная работа #1. GIT\n";
	cout << "Вариант #8. Итоги сессии\n";
	cout << "Автор: Роман Бачун\n";
	cout << "Группа: 24ПИнж\n\n";

	session_results* subscriptions[MAX_FILE_ROWS_COUNT];
	int size;

	try
	{
		read("data.txt", subscriptions, size);

		for (int i = 0; i < size; i++)
		{
			output(subscriptions[i]);
		}

		bool (*check_function)(session_results*) = NULL;
		session_results** filtered = NULL;

		string sort_param;
		string subject;
		int item = 1;

		while (item != 0)
		{
			cout << "\n";
			cout << "1) Вывести всех студентов и их оценки по дисциплине 'История Беларуси' \n";
			cout << "2) Вывести всех студентов и дисциплины с оценками выше 7 баллов \n";
			cout << "3) Сортировка по возрастанию фамилии студента \n";
			cout << "4) Сортировка по возрастанию названия дициплины, а в рамках одной дисциплины по убыванию оценки \n";
			cout << "5) Вывести длительность сессии в днях \n";
			cout << "\n->";

			cin >> item;

			cout << '\n';

			switch (item)
			{
				case 1:
					check_function = filter_by_history;
					cout << "***** Все студенты и их оценки по дисциплине 'История' *****\n\n";
					break;
				case 2:
					check_function = filter_by_grade;
					cout << "***** Все студенты и дисциплины с оценкой выше 7 баллов *****\n\n";
					break;
				case 3:
					cout << "\nПо возрастанию фамилии студента:\n";
					cout << "1)Insertion sort\n";
					cout << "2)Merge sort\n";
					cout << "->";

					cin >> item;
					cout << '\n';

					switch (item)
					{
						case 1:
							cout << "***** По возрастанию фамилии студента - Insertion sort *****\n\n";
							filtered = insertion_sort(subscriptions, size, "second name");
							for (int i = 0; i < size; i++)
							{
								output(filtered[i]);
							}
							delete[] filtered;
							cout << "--------------------------------------------------------------------------------------------------" << endl;
							break;
						case 2:
							cout << "*****По возрастанию фамилии студента - Merge sort *****\n\n";
							filtered = merge_sort(subscriptions, size, "second name");
							for (int i = 0; i < size; i++)
							{
								output(filtered[i]);
							}
							delete[] filtered;
							cout << "--------------------------------------------------------------------------------------------------" << endl;
							break;
					}
					break;
				case 4:
					cout << "\nПо возрастанию названия дициплины, а в рамках одной дисциплины по убыванию оценки:\n";
					cout << "1)Insertion sort\n";
					cout << "2)Merge sort\n";
					cout << "->";

					cin >> item;
					cout << '\n';

					switch (item)
					{
						case 1:
							cout << "***** По возрастанию названия дициплины, а в рамках одной дисциплины по убыванию оценки - Insertion sort *****\n\n";
							filtered = insertion_sort(subscriptions, size, "subject");
							for (int i = 0; i < size; i++)
							{
								output(filtered[i]);
							}
							delete[] filtered;
							cout << "--------------------------------------------------------------------------------------------------" << endl;
							break;
						case 2:
							cout << "***** По возрастанию названия дициплины, а в рамках одной дисциплины по убыванию оценки - Merge sort*****\n\n";
							filtered = merge_sort(subscriptions, size, "subject");
							for (int i = 0; i < size; i++)
							{
								output(filtered[i]);
							}
							delete[] filtered;
							cout << "--------------------------------------------------------------------------------------------------" << endl;
							break;
						}
					break;
				case 5:
					cout << "\nВведите предмет:\n";
					cout << "->";

					cin >> subject;
					cout << "\nСессия по предмету '" << subject << "' длилась: " << calculate_session_duration(subscriptions, size, subject) << " дней";
					cout << '\n';

					break;
				default:
					throw "  ";
			}

			if (check_function)
			{
				int new_size;
				session_results** filtered = filter(subscriptions, size, check_function, new_size);
				
				for (int i = 0; i < new_size; i++)
				{
					output(filtered[i]);
				}
				
				delete[] filtered;
				check_function = NULL;
			}
		}

		for (int i = 0; i < size; i++)
		{
			delete subscriptions[i];
		}
	}
	catch (const char* error)
	{
		cout << error << '\n';
	}
	return 0;
}