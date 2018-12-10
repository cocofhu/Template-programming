#include "iostream"
#include "vector"
#include "algorithm"
#include "functional"
template<typename T>
void g(T&& val) {}
template<typename T>
void f(T val) {}
template<typename T>
void u(const T& val) {}

template<typename T>
void v(T&& val) {}
template<typename T>
void v(T val) {}
template<typename T>
void v(const T& val) {}

template<typename T>
void w(T &&val) { std::vector<T> v; }
int main()
{
	int i = 0; 
	const int ci = i;
	g(i);		// T被推断为 int&
	g(ci);		// T被推断为 const int&
	g(i*ci);	// 右值 T被推断为int
	g( i = ci );// T被推断为 int&
	f(i);		// T被推断为 int
	f(ci);		// T被推断为 int
	u(i);		// T被推断为 int
	u(ci);		// T被推断为 int
	u(100);		// T被推断为 int
	//v(ci);		// ambiguous
	//v(100);		// ambiguous

	// ERROR
	//std::vector<int&> v;
	//v.push_back(i);
	// ERROR
	//w(i); 
	return 0;
}