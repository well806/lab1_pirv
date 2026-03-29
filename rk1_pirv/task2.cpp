#include "task2.h"
#include <cstdlib>
#include <ctime>

Task2::Task2() : blanks(10), processed_count(0), all_done(false)
{
	for (int i = 0; i < 3; i++)
	{
		machines[i] = false;
	}
}

int Task2::get_random_time()
{
	return 1 + rand() % 2;
}

void Task2::machine(int id)
{
	while (!all_done.load())
	{
		unique_lock<mutex> lock(mtx);

		cv.wait(lock, [this]()
		{
			if (all_done.load()) return true;
			if (blanks > 0 && processed_count < 10)
			{
				for (int i = 0; i < 3; i++)
				{
					if (!machines[i]) return true;
				}
			}
			return false;
		});

		if (all_done.load() || processed_count >= 10 || blanks <= 0)
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

		blanks--;
		processed_count++;
		int current_blank = processed_count;
		lock.unlock();

		{
			lock_guard<mutex> cout_lock(cout_mtx);
			cout << "Машина " << id << " начала обработку заготовки #" << current_blank << endl;
		}
		this_thread::sleep_for(chrono::seconds(get_random_time()));
		{
			lock_guard<mutex> cout_lock(cout_mtx);
			cout << "Машина " << id << " закончила обработку заготовки #" << current_blank << endl;
		}

		lock.lock();
		machines[machine_num] = false;
		blanks++;
		{
			lock_guard<mutex> cout_lock(cout_mtx);
			cout << "Заготовка #" << current_blank << " возвращена на склад" << endl;
		}

		if (processed_count >= 10)
		{
			all_done = true;
		}
		cv.notify_all();
	}
}

void Task2::run()
{
	vector<thread> machines;
	for (int i = 0; i < 3; i++)
	{
		machines.push_back(thread(&Task2::machine, this, i + 1));
	}

	for (int i = 0; i < 3; i++)
	{
		machines[i].join();
	}
	cout << "\nВсе 10 заготовок обработаны и находятся на складе." << endl;
}
