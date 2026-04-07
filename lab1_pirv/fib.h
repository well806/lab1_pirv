#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <boost/thread.hpp>

using namespace std;

class Fib
{
private:
	long long fib(int n);
	void worker(int n, long long& res);

public:
	void run();
};
