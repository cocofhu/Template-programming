#include "iostream"
#include "algorithm"
using namespace std;
template<typename T1,typename T2,typename T3>
T1 sum(T2 t2, T3 t3) { return t2 + t3; }
// 糟糕的设计 用户必须指定所有三个模板参数
template<typename T1, typename T2, typename T3>
T3 alternative_sum(T2 t2, T1 t1) { return t2 + t1; }
int main()
{
	// explicit template argument 
	double d = std::max<double>(1,2.3);
	cout << d << endl;
	sum<long>(1, 3);	// T1是显式指定的 T2和T3是从函数实参类型推断而来的
	alternative_sum<long,long,long>(1, 3);
	long lng = 100;
	//compare(lng, 1024);		// 错误:模板参数不匹配
	//compare<long>(lng, 1024);	// 正确:生成compare(long,long)
	//compare<int>(lng, 1024);	// 正确:生成compare(int,int)
	system("pause");
	return 0;
}