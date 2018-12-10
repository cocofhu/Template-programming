#include "iostream"
using namespace std;
// 编写单一模板,使之对任何可能的模板实参都是最合适的,这并不总是能办到
// 在某些情况下,通用模板的定义对特定类型是不合适的:通用定义可能编译失
// 败或者做得不正确.其他时候,我们也可以利用某些特定知识来编写更高效的
// 代码,而不是从通用模板实例化.当我们不能(或不希望)使用模板版本时,可
// 以定义类或函数模板的一个特例化版本
template<typename T>
int compare(const T& v1, const T& v2)
{
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}
// 对compare函数进行模板特例化(template specialization)
// 当定义函数模板的特例化版本时,我们本质上接管了编译器的工作.即,我们对原模板的
// 一个特殊实例提供了定义.重要的是要弄清:一个特例化版本本质上是一个实例,而非函
// 数名的一个重载版本.
template<>
int compare(const char* const &v1, const char * const &v2)
{
	return strcmp(v1, v2);
}
// 编译器会优先选用非模板版本
int compare(const char* const &v1, const char * const &v2)
{
	return strcmp(v1, v2);
}
// 我们只能部分特例化(partial specialization)类模板,不能部分特例化函数模板
template <class T>
struct remove_refer {
	typedef T type;
};
template <class T>
struct remove_refer<T&> {
	typedef T type;
};
template <class T>
struct remove_refer<T&&> {
	typedef T type;
};

template <typename T>
struct Foo {
	void f() { cout << "hi!" << endl; }
	int k;
};
template<>
void Foo<int>::f() {
	cout << "member specialization!" << endl;
}
template <>
struct Foo<double> {

};
int main()
{
	Foo<int> f; 
	f.f();
	Foo<double> d;

	system("pause");
	return 0;
}
