#include "task1.h"
#include <cstdlib>
#include <ctime>

Task1::Task1() : work_cycles(0), shift_ended(false)
{
	for (int i = 0; i < 3; i++)
	{
		machines[i] = false;
	}
}

int Task1::get_random_time()
{
	return 1 + rand() % 3;
}

int Task1::get_random_wait()
{
	return 100 + rand() % 500;
}

void Task1::worker(int id)
{
	while (!shift_ended.load())
	{
		this_thread::sleep_for(chrono::milliseconds(get_random_wait()));

		unique_lock<mutex> lock(mtx);

		cv.wait(lock, [this]()
		{
			for (int i = 0; i < 3; i++)
			{
				if (!machines[i]) return true;
			}
			return false;
		});

		if (shift_ended.load())
		{
			break;
		}

		int machine_num = -1;
		for (int i = 0; i < 3; i++)
		{
			if (!machines[i])
			{
				machines[i] = true;
				machine_num = i;
				break;
			}
		}

		if (machine_num == -1)
		{
			continue;
		}

		lock.unlock();

		cout << "Рабочий " << id << " начал работу на станке " << (machine_num + 1) << endl;
		this_thread::sleep_for(chrono::seconds(get_random_time()));
		cout << "Рабочий " << id << " закончил работу на станке " << (machine_num + 1) << endl;

		lock.lock();
		machines[machine_num] = false;
		work_cycles++;
		cv.notify_all();
	}
}

void Task1::shift_timer()
{
	this_thread::sleep_for(chrono::seconds(15));
	shift_ended = true;
	cv.notify_all();
	cout << "\nСмена окончена (15 секунд прошло)" << endl;
}

void Task1::run()
{
	thread timer_thread(&Task1::shift_timer, this);

	vector<thread> workers;
	for (int i = 0; i < 5; i++)
	{
		workers.push_back(thread(&Task1::worker, this, i + 1));
	}

	for (int i = 0; i < 5; i++)
	{
		workers[i].join();
	}

	timer_thread.join();
	cout << "Всего выполнено рабочих циклов: " << work_cycles.load() << endl;
}
