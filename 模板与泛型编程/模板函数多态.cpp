#include "iostream"
using namespace std;
class Base {
public:
	virtual void f() {
		cout << "..." << endl;
	}
};
class Deriven : public Base {
public:
	void f() {
		cout << ".." << endl;
	}

};
template <typename T>
void f(T &t1,T &t2) {
	t1.f();
	t2.f();
}
int main()
{
	Base b;
	Deriven  d;
	// 不会自动支持多态polymorphism
	f<Base>(b, d);
	system("pause");
	return 0; 
}