

//Author:liuiuge(1220595883@qq.com

#include "Threadpool.h"
#include "Buffer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
class Mytask
{
public:
	void process()
	{
		::srand(::time(NULL));
		int number = ::rand() % 100;
		cout << "produce a number: " << number << endl;
		::sleep(1);
	}
};


int main(void)
{
	Threadpool threadpool(4, 10);
	threadpool.start();

	int taskCount = 20;
	::sleep(1);
	while(taskCount--)
	{
		threadpool.addtask(std::bind(&Mytask::process, Mytask()));
	}

	threadpool.stop();

	return 0;
}
