#include "cnt.h"

Cnt::Cnt() : cnt_ns(0), cnt_at(0), cnt_mx(0)
{
}

void Cnt::inc_ns()
{
	for (int i = 0; i < 1000000; i++)
	{
		cnt_ns++;
	}
}

void Cnt::inc_at()
{
	for (int i = 0; i < 1000000; i++)
	{
		cnt_at++;
	}
}

void Cnt::inc_mx()
{
	for (int i = 0; i < 1000000; i++)
	{
		lock_guard<mutex> lock(mtx);
		cnt_mx++;
	}
}

void Cnt::run()
{
	int tc[] = { 2, 4, 8 };
	vector<long long> times_ns, times_at, times_mx;

	cout << "Задача 2: Конкурентный счётчик (1 миллион инкрементов на поток)" << endl << endl;

	for (int t = 0; t < 3; t++)
	{
		int nt = tc[t];

		cout << "Количество потоков: " << nt << endl;

		cnt_ns = 0;
		vector<thread> thr1;
		auto st1 = chrono::high_resolution_clock::now();
		for (int i = 0; i < nt; i++)
		{
			thr1.emplace_back(&Cnt::inc_ns, this);
		}
		for (int i = 0; i < nt; i++)
		{
			thr1[i].join();
		}
		auto en1 = chrono::high_resolution_clock::now();
		auto dur1 = chrono::duration_cast<chrono::milliseconds>(en1 - st1);
		times_ns.push_back(dur1.count());
		cout << "Без синхронизации: " << dur1.count() << " мс";
		cout << ", Результат: " << cnt_ns << " (ожидалось: " << nt * 1000000 << ")" << endl;

		cnt_at = 0;
		vector<thread> thr2;
		auto st2 = chrono::high_resolution_clock::now();
		for (int i = 0; i < nt; i++)
		{
			thr2.emplace_back(&Cnt::inc_at, this);
		}
		for (int i = 0; i < nt; i++)
		{
			thr2[i].join();
		}
		auto en2 = chrono::high_resolution_clock::now();
		auto dur2 = chrono::duration_cast<chrono::milliseconds>(en2 - st2);
		times_at.push_back(dur2.count());
		cout << "std::atomic: " << dur2.count() << " мс";
		cout << ", Результат: " << cnt_at.load() << " (ожидалось: " << nt * 1000000 << ")" << endl;

		cnt_mx = 0;
		vector<thread> thr3;
		auto st3 = chrono::high_resolution_clock::now();
		for (int i = 0; i < nt; i++)
		{
			thr3.emplace_back(&Cnt::inc_mx, this);
		}
		for (int i = 0; i < nt; i++)
		{
			thr3[i].join();
		}
		auto en3 = chrono::high_resolution_clock::now();
		auto dur3 = chrono::duration_cast<chrono::milliseconds>(en3 - st3);
		times_mx.push_back(dur3.count());
		cout << "std::mutex: " << dur3.count() << " мс";
		cout << ", Результат: " << cnt_mx << " (ожидалось: " << nt * 1000000 << ")" << endl;

		cout << endl;
	}

}
