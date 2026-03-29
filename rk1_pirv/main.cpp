#include <iostream>
#include "task1.h"
#include "task2.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(0));

	int choice;
	cout << "Выберите задачу (1 или 2): ";
	cin >> choice;

	if (choice == 1)
	{
		Task1 task;
		task.run();
	}
	else if (choice == 2)
	{
		Task2 task;
		task.run();
	}
	else
	{
		cout << "Неверный выбор" << endl;
	}

	return 0;
}
