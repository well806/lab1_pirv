#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <chrono>

using namespace std;

class Task2
{
private:
	mutex mtx;
	condition_variable cv;
	mutex cout_mtx;
	int blanks;
	int processed_count;
	bool machines[3];
	atomic<bool> all_done;

	int get_random_time();
	void machine(int id);

public:
	Task2();
	void run();
};
