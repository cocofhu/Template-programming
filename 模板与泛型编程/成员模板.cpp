#include "iostream"
#include "memory"
#include "vector"
using namespace std;
// 一个类(无论是普通类还是类模板)可以包含本身是模板的成员函数.
// 这种成员被称为成员模板(member template).成员模板不能是虚函数
template<typename TYPE>
class DebugDelete {
public:
	explicit DebugDelete(ostream &os = cerr) :os(os) {}
	template<typename T> 
	void operator()(T *p);
private:
	ostream& os; 
};
// 与类模板的普通函数成员不同,成员模板是函数模板.当我们在类模板外定义一个成员
// 模板时,必须同时为类模板和成员模板提供模板参数列表.类模板的参数列表在前,后跟
// 成员自己的参数列表
template<typename M>
template<typename T>
void DebugDelete<M>::operator() < T > (T *p) {
	os << "delete ..." << typeid(T).name() << endl;
	delete p;
}
template<typename It>
void foreach(It b, It e) {
	for (; b != e; ++b) {
		cout << *b << endl;
	}
}
#define macro_foreach(begin,end)	\
		{	auto b = begin, e = end ;\
			for (; (b) != (e); ++(b)) { \
				cout << *(b) << endl; \
			}\
		}


int main()
{

	double *p1 = new double;
	int *p2 = new int;
	DebugDelete<int> d;
	d(p1);
	DebugDelete<int>()(p2);
	unique_ptr<int, DebugDelete<int>> p(new int, DebugDelete<int>());
	int arr[10] = { 12,22,3,4,5,6,1,2,4,5 };
	
	macro_foreach(begin(arr), end(arr));
	foreach(begin(arr), end(arr));
	system("pause");
	return 0 ; 
}