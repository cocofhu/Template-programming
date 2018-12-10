#include "iostream"
#include "memory"
using namespace std;
template<typename T>
class Bug {
public:
	~Bug() {
		T()();
	}
};
struct Del {
	void operator()() {
		cout << "Del" << endl;
	}
};
int main()
{
	// 运行时绑定 效率高 可能编译成内联形式
	Bug<Del> b();
	// 通过在编译时绑定删除器,unique_ptr避免了间接调用删除器的运行时开销
	// 通过运行时绑定删除器,shared_ptr使用户重载删除器更为方便
	return 0; 
}