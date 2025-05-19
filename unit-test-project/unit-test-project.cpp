#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/session_results.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
	session_results* build_operation(date date, string subject)
	{
		session_results* operation = new session_results;

		operation->date = date;
		operation->subject = subject;

		return operation;
	}

	void delete_operation(session_results* array[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			delete array[i];
		}
	}
	TEST_CLASS(unittestproject)
	{
	public:

		TEST_METHOD(TestOperation)
		{
			session_results* operations[3];

			operations[0] = build_operation({ 23, 6, 2023 }, "Физика");
			operations[1] = build_operation({ 20, 4, 2024 }, "Физика");
			operations[2] = build_operation({ 31, 1, 2005 }, "История");

			Assert::AreEqual(302, calculate_session_duration(operations, 3, "Физика"));
			delete_operation(operations, 3);
		}
		TEST_METHOD(TestSingleOperationReturnsZero)
		{
			session_results* operations[1];
			operations[0] = build_operation({ 15, 5, 2023 }, "Математика");

			Assert::AreEqual(0, calculate_session_duration(operations, 1, "Математика"));
			delete_operation(operations, 1);
		}

		TEST_METHOD(TestOperationsDifferentSubjects)
		{
			session_results* operations[3];
			operations[0] = build_operation({ 10, 1, 2023 }, "Физика");
			operations[1] = build_operation({ 20, 2, 2023 }, "Химия");
			operations[2] = build_operation({ 30, 3, 2023 }, "Биология");

			Assert::AreEqual(0, calculate_session_duration(operations, 3, "Физика"));
			delete_operation(operations, 3);
		}

		TEST_METHOD(TestMultipleOperationsSameSubject)
		{
			session_results* operations[4];
			operations[0] = build_operation({ 1, 1, 2023 }, "История");
			operations[1] = build_operation({ 1, 2, 2023 }, "История");
			operations[2] = build_operation({ 1, 3, 2023 }, "История");
			operations[3] = build_operation({ 1, 4, 2023 }, "История");

			Assert::AreEqual(90, calculate_session_duration(operations, 4, "История"));
			delete_operation(operations, 4);
		}

		TEST_METHOD(TestOperationsWithSameDate)
		{
			session_results* operations[2];
			operations[0] = build_operation({ 15, 5, 2023 }, "Литература");
			operations[1] = build_operation({ 15, 5, 2023 }, "Литература");

			Assert::AreEqual(0, calculate_session_duration(operations, 2, "Литература"));
			delete_operation(operations, 2);
		}
	};
}