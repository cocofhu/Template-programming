#include "iostream"
void f(const int &a) {  }
void g(int a) {}
void u(int &&a) { std::cout << typeid(a).name() << std::endl; }

template<typename T>
T&& forwardArg(T&& t) {
	return static_cast<T&&>(t);
}
template<typename T>
T&& forwardArg(T& t) {
	return static_cast<T&&>(t);
}

template<typename F,typename T>
void indictectCall(F f,T&& t) {
	// 以下情况均假设传入整型变量或整型字面量(不考虑const)

	// 如果 f(forwardArg(t)); 
	// 这个t如果是字面量传入的话在此函数作用域将会变成左值
	// 所以,forward函数必须显示指定模板实例化类型 否则都将为左值
	
	// 如果 f(forwardArg<T>(t));
	// 此时有两种情况 
	//		1)t如果是字面量传入 indictectCall(f,100)
	//			在这种情况下,T将被推断为int类型,而t变量却是一个左值
	//			由于T已经被限定为int,所以无法产生引用"折叠",编译器报错
	//			解决方案:重载一个左值版本
	//		2)t是整型变量传入 indictectCall(f,i)
	//			在这种情况下,T将被推断为int&,此时t是一个左值两个重载都符合
	//			规则,优先调用T&的重载(& &折叠为&)

	// 此时我们已经有了两个转发函数的重载,看起来并没有什么问题
	//forwardArg<int>(100);
	f(forwardArg<T>(t));	
	std::cout << t << std::endl;
}

int main()
{
	
	int i = 10;
	std::forward<int&>(100);
	forwardArg<int>(1000);
	//indictectCall(f, i);
	indictectCall(u, 100);
	//indictectCall(g, i);
	std::cout << i << std::endl;
	system("pause");
	return 0; 
}