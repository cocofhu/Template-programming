#include "iostream"
#include "vector"
#include "xstddef"
using namespace std;

namespace Test1 {
	// 假定T是一个类型参数的名字,当编译器如下形式的语句时:
	// T::size_type *p ;
	// 它需要知道我们是正在定义一个名为p的变量还是将一个名
	// 为size_type的static变量数据成员与名为p的变量相乘
	// 默认情况下,C++语言假定通过作用域运算符访问的名字不是类型.
	// 因此,如果我们希望使用一个模板类型参数的类型成员,就必须显
	// 示告诉编译器该名字是个类型,我们通过使用关键字typename来实现这一点(不能使用class)
	template<typename T>
	class Blob {
		using size_type = typename std::vector<T>::size_type;
		typename T::size_type * p;
	};

	// 就像我们能为函数参数提供默认实参一样,我们也可以提供默认模板实参
	// (default template argument).在新标准中,我们可以为函数和类模板
	// 提供默认实参.而更早的C++标准只允许为类模板提供默认实参
	// 与函数默认实参一样,对于一个模板参数,只有当它右侧的所有参数都有默认
	// 实参时,它才可以有默认实参
	template <typename T, typename F = less<T>>
	int compare(const T& v1, const T &v2, F f = F())
	{
		if (f(v1, v2)) return -1; 
		if (f(v2, v1)) return 1;
		return 0 ; 
	}
	
	// 模板默认实参与类模板
	// 无论何时使用一个类模板,我们都必须在模板名之后接上尖括号.
	// 尖括号指出类必须从一个模板实例化而来.特别的,如果一个类模板
	// 为其所有模板参数都提供了默认实参,且我们希望使用这些默认实参
	// 就必须在模板之后跟一个空尖括号对:
	template <class T = int > class Numbers {
		
	};
	
}
int main()
{
	int i = Test1::compare(0, 42);
	int j = Test1::compare<int,greater<int>>(0, 42);
	cout << i << endl ;
	cout << j << endl ;
	Test1::Numbers<> n1;
	Test1::Numbers<long> n2;
	system("pause");
	return 0;
}