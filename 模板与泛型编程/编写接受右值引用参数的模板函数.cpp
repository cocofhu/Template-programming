#include "iostream"
struct Test {
	Test() 
	{ 
		std::cout << " Test()" << std::endl;
	}
	Test(const Test&) 
	{
		std::cout << "Test(const Test&)" << std::endl;
	}
	Test(const Test&&)
	{
		std::cout << "Test(const Test&&)" << std::endl;
	}
	Test(int)
	{
		std::cout << "Test(int)" << std::endl;
	}
	void operator=(const Test&)
	{
		std::cout << "operator=(const Test&)" << std::endl;
	}
	void operator=(const Test&&)
	{
		std::cout << "operator=(const Test&&)" << std::endl;
	}
	~Test()
	{
		std::cout << "~Test()" << std::endl;
	}
};
template<typename T>
struct G {
	void f(const T&) 
	{
		std::cout << "const T&" << std::endl;
	}
	void f(T&& ) 
	{
		std::cout << "T&&" << std::endl;
	}
};
// 模板参数可以推断为一个引用类型,这一特性对模板内的代码可能有令人惊讶的影响
// 当我们对一个右值调用f3时,例如字面常量42,T为int.在此情况下,局部变量t的类型
// 为int,且通过拷贝参数val的值被初始化.当我们对t赋值时,参数val保持不变.
// 另一方面,当我们对一个左值i调用f3时,则T为int&.当我们定义并初始化局部变量t时
// 赋予它类型int&.因此对t的初始化将绑定到val,当我们对t赋值时,也同时改变了val的
// 值
template<typename T>
void f3(T&& val) 
{
	T t = val;	// 拷贝还是绑定一个引用
	t = 200;	// 赋值只改变t还是既改变t又改变val
}
// 当代码中涉及的类型可能是普通(非引用)类型,也可能是引用类型时,编写正确的代码就
// 变得异常困难.可以使用以下方式重载
template<typename T>
void f3(const T & val) 
{
	std::cout << "PP" << std::endl;
	T t = val;	
	t = 200;	
}
void f4(const int &v) {
	std::cout << "const int &v" << std::endl;
}
void f4(int && v) {
	std::cout << "int &&v" << std::endl;
}

int main()
{
	
	int&& rri = 100;
	f3(rri);	//和i的效果一样
	int i = 100;
	f3(i);
	//f4(i);
	// 类模板不存在这样的问题
	G<int>().f(i);
	//std::cout << i << std::endl;
	system("pause");
	return 0; 
}