#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <chrono>

using namespace std;

class Cnt
{
private:
	int cnt_ns;
	atomic<int> cnt_at;
	int cnt_mx;
	mutex mtx;

	void inc_ns();
	void inc_at();
	void inc_mx();

public:
	Cnt();
	void run();
};
