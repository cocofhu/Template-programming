#include "iostream"
// 其中函数参数p是一个模板类型参数T的引用,非常重要的是记住两点:
// 编译器会应用正常的引用绑定规则;const是底层的,不是顶层的
template<typename T>
void f(T &p) {}
template<typename T>
// 实参必须是左值
void f1(T&) {}
template <typename T>
void f2(const T&) {}
int main()
{
	// 当一个函数参数是模板类型参数的一个普通(左值)引用时(即,形如T&),绑定规则
	// 告诉我们,只能传递给它一个左值(如,一个变量或一个返回引用类型的表达式),实参
	// 可以是const类型,也可以不是.如果实参是const的,则T将被推断为const类型
	int i = 0; 
	const int ci = 0;
	const int *p = nullptr; 
	const int *const q = nullptr;
	f1(i);	// 成功 i是左值 T被推断为int
	f1(ci);	// 成功 ci是左值	T被推断为const int
	f1(p);	// 成功 p是左值 T被推断为const int *&
	f1(q);	// 成功 q是左值 T被推断为const int * const&
	//f1(4);	// 错误 传递给一个&参数的实参必须是一个左值

	// 如果一个函数的参数类型是const T&,正常的绑定规则告诉我们可以传递给它任何
	// 类型的实参:一个对象(const 或非 const)、一个临时对象或是一个字面值常量.
	f2(i);	// 成功 T被推断为int
	f2(ci);	// 成功 T被推断为int
	f2(5);	// 成功 一个const &参数可以绑定到一个右值 T被推断为int
	return 0;
}