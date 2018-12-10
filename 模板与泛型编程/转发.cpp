#include "iostream"
#include "type_traits"

// 某些函数需要将其一个或多个实参连同类型不变地转发给其他函数.在此情况下,
// 我们需要保持被转发实参的所有性质,包括实参类型是否是const的以及实参是左
// 值还是右值

template<typename T>
auto forwardArg(int && arg) {
	return static_cast<int&&>(arg);
}

// 接受一个可调用对象和另外两个参数的模板
// flip1是一个不完整的实现:顶层const和引用丢失了
template <typename F,typename T1,typename T2>
void flip1(F f, T1&& t1, T2&& t2) 
{ 
	//static_cast<int&&>(t1);
	forwardArg<int>(t1);
	//f(forwardArg<T1>(t1), forwardArg<T2>(t2));
	//f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void f(int v1, int &v2) {
	std::cout << v1 << " " << ++v2 << std::endl;
}
void g(int v1, int v2) {
	std::cout << v1 << " " << ++v2 << std::endl;
}
int main()
{

	int i = 100, j = 200;
	flip1(g, 200, 100);
	//g(100, 200);
	std::cout << i << " " << j << std::endl;
	system("pause");
	return 0;
}