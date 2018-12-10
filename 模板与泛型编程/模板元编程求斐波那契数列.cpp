#include "iostream"
#include "windows.h"
using namespace std;
template<int N>
struct Fibonacci {
	enum :unsigned long long{
		val = Fibonacci<N-1>::val + Fibonacci<N-2>::val 
	};
};
// 利用模板特例化终止递归
template<>
struct Fibonacci<1> {
	enum :unsigned long long {
		val = 1
	};
};
template<>
struct Fibonacci<2> {
	enum :unsigned long long {
		val = 1
	};
};
unsigned long long fibonacci(int n) {
	if (n == 1 || n == 2) return 1;
	int last = 1;
	int ret = 1;
	int tmp; 
	for (int i = 0; i < n - 2; i++) {
		tmp = last;
		last = ret;
		ret += tmp;
	}
	return ret;
}
int main()
{
	{
		DWORD start_time = GetTickCount();
		for (size_t i = 0; i < 1000000000; i++)
		{
			//Fibonacci<30>::val;		// 编译期间确定
			fibonacci(30);				// 需要调用函数
		}
		DWORD end_time = GetTickCount();
		cout << end_time - start_time << endl;
	}
	
	
	system("pause");
	return 0; 
}