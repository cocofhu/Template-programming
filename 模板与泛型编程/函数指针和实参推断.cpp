#include "iostream"
#include "tuple"
#include "string"
using namespace std;
template<typename T>
int compare(const T&, const T&) {
	return 0; 
}
void func(int(*)(const int&,const int&)) {}
void func(int(*)(const string&, const string&)) {}
// 当参数是一个函数模板实例的地址时,
// 程序的上下文必须满足:对每个模板参数能唯一确定其类型或值
int main()
{
	// 当我们用一个函数模板初始化一个函数指针或为一个函数
	// 指针赋值时,编译器根据指针的类型来推断模板实参
	int(*pf)(const int&, const int&) = compare;
	// 无法确定 必须显示指定类型
	func(compare<int>);
	return 0; 
}