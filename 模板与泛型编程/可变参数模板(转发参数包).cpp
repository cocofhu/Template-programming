#include "iostream"
#include "thread"
#include "type_traits"
// 新标准下,我们可以组合使用可变参数模板与forward机制来编写函数,
// 实现将其实参不变地传递给其他函数
using namespace std;
template<typename F,typename...Types>
auto f(F fn,Types&&...args) 
	-> decltype(fn(std::forward<Types>(args)...))
{
	// 对于右值引用函数 应该避免使用Types的类型信息(不一致)
	// cout << "void f(Types&&...args)" << endl;
	// perfect forwarding
	return fn(std::forward<Types>(args)...);
}
// 可变参数函数通常将它们的参数转发给其他函数.
// fun有零个或多个参数,每个参数都是一个模板参数类型的右值引用
template<typename... Args>
// 将Args扩展为一个右值引用的列表
void fun(Args&&... args)
{
	// f 的实参既扩展Args又扩展args
	f(std::forward<Args>(args)...);
}
// 
int main()
{
	int i, j, k, m, n;
	j = 1;
	k = 2;
	m = 3;
	n = 5;
	auto fnc = [](int &a, int &b, int &c, int &d)-> int {
		a++; b++; c++; d++;
		return a + b + c + d;
	};
	cout << f( fnc, j, k, m, n) << endl;
	cout << j << k << m << n << endl;
	f(printf, "Hello World! %d\n", 1);
	f(scanf_s, "%d", &i);
	system("pause");
	return 0;
}