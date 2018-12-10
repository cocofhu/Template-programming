// 对于函数模板,编译器利用调用中的函数实参来确定其模板参数,
// 从函数实参来确定模板实参的过程被称为模板实参推断(template argument deduction)
// 在模板实例推断过程中,编译器使用函数调用中的实参类型来寻找模板实参,用这些模板实参
// 生成的函数版本与给定的函数调用最为匹配
#include "iostream"
using namespace std;
// 模板实参推断：编译器用来确定实例化哪个函数模板的过程。编译器检查用模板形参指定的实参的类型，它用绑定到模板形参的类型或值自动实例化函数的一个版本。
// 简单的说，就是（根据调用函数模板的方式）确认函数模板类型形参的类型。
// 注意：只有函数模板才有模板实参推断，类模板的形参该实例化为什么类型是写死的，用不着“推断”。

// 一般而言，不会转化实参以匹配已有的实例化，相反，会产生新的实例化，或产生不了实例化，报错。
// 与往常一样,顶层const无论形参中还是实参中,都会被忽略.在其它类型转换中
// 能在调用中应用于函数模板的包括如下两项:
// const 转换:可以将一个非const对象的引用(或指针)传递给一个const的引用
// (或指针)形参.
// 数组或函数指针转换:如果函数形参不是引用类型,则可以对数组或函数类型的实
// 参应用正常的指针转换
// 将实参传递给带模板类型的函数形参时,能够自动应用的类型转换只有const转换
// 及数组或函数到指针的转换
template<typename T>
void f(T& t) {
	cout << typeid(T).name() << endl;
}
template<typename T>
void g(T& t1,T &t2) {
	cout << typeid(t1).name() << endl;
	cout << typeid(t2).name() << endl;
}
template<typename T>
void u(T& t) {
	cout << typeid(t).name() << endl;
}
template<typename T>
void v(T& t) {
	cout << typeid(t).name() << endl;
}
void p(int& t) {
	cout << typeid(t).name() << endl;
}
int main()
{
	int arr1[10]; 
	int arr2[20];
	f(arr1);
	//g(arr1,arr2); 数组类型不匹配
	const int c1 = 100 ; 
	f(c1);	// 顶层const将被忽略
	u(c1);
	v(c1);
	//p(c1);
	system("pause");
	return 0 ; 
}