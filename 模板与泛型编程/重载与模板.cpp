#include "iostream"
#include "string"
// 函数模板可以被另一个模板或一个普通非模板函数重载.
// 与往常一样,名字相同的函数必须具有不同数量或类型的参数
// 对于一个调用,其候选函数包括所有模板实参推断成功的函数模板实例
// 候选的函数模板总是可行的,因为模板实参推断会排除任何不可行的模板
// 与往常一样,如果恰有一个函数提供比任何其他函数都更好的匹配,则选择此函数
// 但是,如果有多个函数提供有同样好的匹配,则:
// -- 如果同样好的函数中只有一个是非模板函数,则选择此函数
// -- 如果同样好的函数中没有非模板函数,而有多个函数模板,且其中一个模板比
//	  其他模板更特例化,则选择此模板
// -- 否则,此调用有歧义
using namespace std;
template<typename T>
int f(T val) { cout << "TEMPLATE" << endl; return 0; }
void f(int val) { cout << "NONE-TEMPLATE" << endl; }
template <typename T>
void debug_rep(const T& t) 
{
	cout << "debug_rep(const T&)" << endl; 
}
template <typename T>
void debug_rep(T *t)
{
	cout << "debug_rep(T*)" << endl;
}
int main()
{
	int m = 10; 
	f(m);
	const int ci = 10;
	// 当有多个重载模板对一个调用提供同样好的匹配是,应选择最特例化的版本
	debug_rep(3);
	debug_rep(ci);
	debug_rep(&m);
	system("pause");
	return 0; 
}