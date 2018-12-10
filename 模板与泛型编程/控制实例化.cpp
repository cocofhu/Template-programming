#include "iostream"
#include "string"
using namespace std;
// 在大系统中,在多个文件中实例化相同模板的额外开销可能非常严重,
// 在新标准中,我们可以通过显示实例化(explicit instantiation)
// 来避免这种开销.
// 一个显示实例化有如下形式:
// extren template declaration ;
// template declaration ;
// declaration 是一个类或函数声明,其中所有模板参数已被替换为模板参数

template<typename T>
class Blob {
public:
	void f();
};
template<typename T>
T compare(const T&,const T&) {return 0; }

// 当编译器遇到extern模板声明时,它不会再本文件中生成实例化代码
// 将一个声明为extern就表示承诺在程序其他位置有该实例化的一个非
// extern声明(定义).对于一个给定实例化的版本,可能有多个extern的
// 声明,但必须只有一个定义
// 由于编译器在使用一个模板时自动对其实例化,因此extern声明必须出
// 现在任何使用此实例化版本的代码之前
// 对每个实例化声明,在程序中某个位置必须有其显式的实例化定义
// note:实例化定义会实例化所有成员,在一个类模板的实例化中所用
// 类型必须能用于模板的所有成员函数(可能是C++11吧)
//extern template class Blob<string>;				// 声明 
template class Blob<string>;
template int compare(const int&, const int&);	// 定义
//extern template int compare(const int&, const int&);
int main()
{
	compare(1, 2);
	// VS2017 能够编译运行 G++不行
	 Blob<string> b;
	// b.f();
	return 0; 
}
