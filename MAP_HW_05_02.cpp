﻿#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

template<typename It, class Function, size_t size = 5>
Function for_each_test(It begin, It end, Function func) 
{
	size_t cur_size = std::distance(begin, end);
	if (cur_size <= size) 
	{
		return std::for_each(begin, end, func);
	}
	
	auto mid = begin;
	std::advance(mid, size / 2);
	
	//для левой части
	std::future<Function> f_res = std::async(for_each_test <It, Function>, begin, mid, func);
	
	//для правой части
	auto right_res = for_each_test(mid, end, func);
	return func;
}

int main() 
{
	auto print = [](const int& index) 
		{
		std::cout << index << " ";
		};

	std::vector<int> vi{ 11, -9, 6, 4,22, 12, 17, 27, 40, 0, -14, -10 };
	for_each_test(vi.begin(), vi.end(), print);
	
	return 0;
}