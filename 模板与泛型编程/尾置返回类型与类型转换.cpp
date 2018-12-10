#include "iostream"
#include "algorithm"
#include "numeric"
#include "type_traits"
using namespace std;
// 我们不知道返回结果的准确类型,但知道所需类型是所处理的序列的元素类型
// 尾置返回运算我们在参数列表之后声明返回类型 解引用返回的是一个左值
template <typename It>
auto fcn(It beg, It end) -> 
		// 为了使用模板参数成员 必须使用typename 
		typename remove_reference<decltype(*beg)>::type{
	return *beg;
}
int main()
{
	// fcn((int*)0, (int*)0); returnType int ;
	return 0;
}