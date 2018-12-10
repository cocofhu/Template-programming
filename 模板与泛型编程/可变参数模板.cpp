#include "iostream"
#include "stdexcept"
using namespace std;
// 一个可变参数模板(variadic template)就是可以接受可变数目参数的
// 模板函数或模板类.可变数目的参数被称为参数包(parameter packet)
// 存在两种参数包:模板参数包(template parameter packet),表示零个
// 或多个模板参数;函数参数包(function parameter packet),表示零个
// 或多个函数参数

// Args是一个模板参数包;rest是一个函数参数包
// Args表示零个或多个模板类型参数
// rest表示零个或多个函数参数
template <typename T,typename ...Args>
void foo(const T& t, const Args...rest) 
{
	// 当我们需要知道包中有多少元素时,可使用sizeof...运算符
	// 类似sizeof，sizeof...也返回一个常量表达式,而且不会对
	// 其实参求值
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
}
// 终止递归函数
int variadic_print(const char *format);
// 我们可以使用一个initializer_list来定义一个可以接受可变数目实参的函数
// 但是,所有实参必须具有相同的类型(或他们的类型可以转换为同一个公共类型).
// 当我们既不知道想要处理的实参的数目也不知道它们的类型时,可变参数函数是
// 很有用的
template <typename T,typename...Args>
int variadic_print(const char *format,T t,Args...args)
{
	while (*format)
	{
		if (*format == '%' && *(++format) != '%')
		{
			std::cout << t;
			// recursively call
			return 1 + variadic_print(++format,args...);
		}
		std::cout << *format++;
	}
	throw std::logic_error("too many arguments");
}
int variadic_print(const char *format) 
{
	while (*format)
	{
		if (*format == '%' && *(++format) != '%')
		{
			throw std::runtime_error("invalid format string:missing arguments");
		}
		std::cout << *format++;
	}
	return 0; 
}
// 对于最后一个调用 此版本更加特例化,因此编译器选择此版本
template<typename T>
void print(T t) 
{
	cout << t << endl;
}
template<typename T,typename...Args>
void print(T t, Args...args) 
{
	cout << t << endl;
	print(args...);
}
int main()
{
	int ret = variadic_print("just like dreaming:( %d , %d , %s )", 1, 222, "hello");
	cout << endl; 
	cout << "count:" << ret << endl;
	print(1, 2, 3, 4, 5, 6);
	system("pause");
	return 0; 
}