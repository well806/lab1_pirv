#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <chrono>

using namespace std;

class Task1
{
private:
	mutex mtx;
	condition_variable cv;
	bool machines[3];
	atomic<int> work_cycles;
	atomic<bool> shift_ended;

	int get_random_time();
	int get_random_wait();
	void worker(int id);
	void shift_timer();

public:
	Task1();
	void run();
};
