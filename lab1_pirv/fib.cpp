#include "fib.h"

long long Fib::fib(int n)
{
	if (n <= 1)
	{
		return n;
	}
	return fib(n - 1) + fib(n - 2);
}

void Fib::worker(int n, long long& res)
{
	res = fib(n);
}

void Fib::run()
{
	int fn = 40;
	int tc[] = { 1, 2, 4, 8 };

	cout << "Задача 1: Многопоточное вычисление чисел Фибоначчи" << endl;
	cout << "Вычисляем " << fn << "-е число Фибоначчи" << endl << endl;

	for (int t = 0; t < 4; t++)
	{
		int nt = tc[t];
		vector<long long> res(nt);
		vector<boost::thread> thr;

		auto st = chrono::high_resolution_clock::now();

		for (int i = 0; i < nt; i++)
		{
			thr.emplace_back(&Fib::worker, this, fn, ref(res[i]));
		}

		for (int i = 0; i < nt; i++)
		{
			thr[i].join();
		}

		auto en = chrono::high_resolution_clock::now();
		auto dur = chrono::duration_cast<chrono::milliseconds>(en - st);

		cout << "Потоков: " << nt << ", Время: " << dur.count() << " мс";
		cout << ", Результат: " << res[0] << endl;
	}

	cout << endl;
}
