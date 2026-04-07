#include <iostream>
#include "fib.h"
#include "cnt.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");

	int ch;
	cout << "Выберите задачу (1 или 2): ";
	cin >> ch;
	cout << endl;

	if (ch == 1)
	{
		Fib task;
		task.run();
	}
	else if (ch == 2)
	{
		Cnt task;
		task.run();
	}
	else
	{
		cout << "Неверный выбор" << endl;
	}
}
