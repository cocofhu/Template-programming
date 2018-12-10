#include "iostream"
#include "vector"
#include "initializer_list"
#include "stdexcept"
#include "memory"
#include "utility"
using namespace std;

namespace Test1 {
	// 模板函数
	// 模板定义以关键字template开始,后跟一个模板参数列表(template parameter list)
	// 这是一个逗号分隔的一个或多个模板参数(template parameter)的列表,用小于号(<)和大于号(>)包围起来
	// 模板参数表示在类或函数定义中用到的类型或值,当使用模板时,我们(隐式地或显式地)指定模板实参(template argument),将其绑定到模板参数上
	// T是模板类型参数(type parameter).一般来说,我们可以将类型参数看作类型说明符,就像内置类型或类型说明符一样使用
	// 类型参数前必须使用关键字class或typename.用typename来指定模板类型参数比用class更为直观
	template<typename T>
	int compare(const T& v1,const T& v2) 
	{
		// 都使用小于降低了对处理类型的要求
		if (v1 < v2) return -1;
		if (v2 < v1) return 1;
		return 0; 
	}
	
	// 在模板定义中,模板参数列表不能为空
	// template<>	void fun() {}
	
	// 除了定义类型参数,还可以在模板中定义非类型参数(nontype parameter).
	// 一个非类型参数表示一个值而非一个类型，我们通过一个特定的类型名而非
	// 关键字class或typename来指定非类型参数
	// 绑定到非类型整型参数的实参必须是一个常量表达式
	// 绑定到指针或引用非类型参数的实参必须具有静态的生存期
	// 指针参数也可以用nullptr或一个值为0的常量表达式来初始化 
	template<typename T,size_t len>
	inline constexpr size_t length(const T(&arr)[len]) {
		return len; 
	}
	// 当编译器遇到一个模板定义时,它并不生成代码.
	// 只有当我们实例化出模板的一个特定版本时,编译器才生成代码
	// 模板的头文件通常既包括声明也包括定义
	// 大多数编译错误在实例化期间报告
	// 保证传递给模板的实参支持模板所要求的操作,以及这些操作在模板中能正确的工作,是调用者的责任
}
namespace Test2 {
	
	// 前置声明
	template<typename> class Blob;
	template<typename T>
	bool operator==(const Blob<T>& b1, const Blob<T>& b2) {
		//Blob<long> b; b.data;
		return false;
	}
	template<typename T>
	class Pal {
	public:	
		void f() {
			//Blob<char> c; c.data;
			//Blob<Pal> c1; c1.data;
		}
	};

	// 类模板
	template <typename T> class Blob {
	public:
		// 当一个类包含一个友元声明时,类与友元各自是否是模板是相互无关的
		// 如果一个类模板包含一个非模板友元,则友元被授权可以访问所有模板实例
		// 如果友元自身是模板,类可以授权给所有友元模板实例,也可以授权给特定实例
		
		// 一对一友好关系:类模板与另一个(类或函数)模板间友好关系的最常见的形式
		// 是建立对应实例及其友元间的的友好关系



		// 每个Blob实例将访问权限授予用相同类型实例化的相等运算符
		//template <typename>
		friend bool operator==<>(const Blob<T>&, const Blob<T>&);
		// Blob<T> can refer to the full specialization of 
		// operator<< for its T
		template <typename X>	// 这里用X 不然G++编译不过
		//template <typename>
		friend ostream& operator<<(ostream& os, const Blob<X>&);
		//template<typename>
		//friend ostream& operator<<(ostream& os, const Blob&);
		//friend ostream& operator<< (ostream& os, const Blob&) {
		//	return os << "nothing";
		//}

		// 一个类也可以将另一个模板的每个实例都声明为自己的友元,或者
		// 限定特定的实例为友元

		// Blob的每个实例都将是Pal<int>的友元
		// friend class Pal<int> ;
		// Blob的每个实例将相同实例化的Pal声明为友元
		// friend class Pal<T>;
		// Pal的所有实例都是Blob的每个实例的友元,不需要前置声明
		template<typename X>
		friend class Pal;	//不要<X>
		// Pen是一个非模板类,他是Blob所有实例的友元
		friend class Pen;

		//typedef T value_type; 
		using value_type = T;
		//typedef typename std::vector<T>::size_type size_type;
		using size_type = typename std::vector<T>::size_type;
		// 在类模板自己的作用域中,我们可以直接使用模板名而不提供实参
		// Blob<T>();
		Blob() ;
		Blob(std::initializer_list<T>);
		size_type size() const { return data->size(); }
		bool empty() const { return data->empty(); }
		void push_back(const T& t) { data->push_back(t); }
		void push_back(T&& t) { data->push_back(std::move(t)); }
		typename std::vector<T>::iterator begin() { return data->begin(); }
		typename std::vector<T>::iterator end() { return data->end(); }
		void pop_back();
		T& back();
		T& operator[](size_type i);
	private:
		std::shared_ptr<std::vector<T> > data; 
		void check(size_type i,const std::string &msg) const ;
	};
	template <typename T>
	void Blob<T>::check(size_type i, const std::string &msg) const {
		if (i < 0 || i >= size()) {
			throw std::out_of_range(msg);
		}
	};
	template <typename T>
	T& Blob<T>::back() {
		check(0, "back on empty Blob");
		return data->back();
	}
	template <typename T>
	T& Blob<T>::operator[](size_type i) {
		// 类模板作用域内 可以不必指定实参 
		// 下面代码等价于Blob<T> &b = *this;
		Blob &b = *this;
		check(i, "subscript out of range");
		return (*b.data)[i];
	}
	template <typename T>
	void Blob<T>::pop_back() {
		check(0, "pop_back on empty Blob");
		data->pop_back();
	}
	template <typename T>
	Blob<T>::Blob():data(std::make_shared<std::vector<T>>()) {}
	template <typename T>
	Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T> >(il)) {}
	template<typename T>
	ostream& operator<< (ostream& os, const Blob<T>&) {
		Blob<long> b; b.data;
		return os << "nothing";
	}
	typedef Blob<string> StrBlob;
	// C++11
	template <typename T> using twin = pair<T, T>;
	template <typename T> using PairNo = pair<T, unsigned>;
}
namespace Test3 {
	
	// 友元声明不能引用偏特例化只能引用全特例化
	template<class T> class A {}; // primary
	template<class T> class A<T*> {}; // partial
	template<> class A<int> {}; // full
	class X {
		//template<class T> friend class A<T*>; // error!
		friend class A<int>; // OK
	};
	// When a friend declaration refers to a full specialization of a 
	// function template, the keyword inline and default arguments cannot
	// be used.
	//template<class T> void f(int);
	//template<> void f<int>(int);
	//class X {
		//friend void f<int>(int x = 1); // error: default args not allowed
	//};
}
namespace Test4 {
	// 值得注意的是,虽然友元通常来说应该是一个类或是一个函数,当我们完全可以
	// 用一个内置类型来实例化Blob,这种内置类型的友好关系是允许的,以便我们能
	// 用内置类型来实例化Bar这样的类
	template <typename T> class Bar {
		friend T; // 此处不能写class
	private:
		int m;
	};
	struct Foo {
		void f() {
			Bar<Foo> b;
			b.m;
		}
	};
}
namespace Test5 {
	template<typename T, int N>
	class Foo {
	public:
		static int k ;
	};
	// 二元组标识 互相独立
	template<typename T,int N>
	int Foo<T,N>::k = N;
}
namespace Test6 {
	template<typename elemType> class ListItem {};
	template<typename elemType> class List {
	private:
		ListItem<elemType> l;
	};
}
int main()
{
	{
		/*
		// 当我们调用一个函数模板时,编译器(通常)用函数实参来为我们推断模板实参.
		// 编译器用推断出的模板参数为我们实例化(instantiate)一个特定版本的函数
		// 当编译器实例化一个模板时,它使用实际的模板实参代替对应的模板参数来创建
		// 出模板的一个新"实例".编译器生成的函数通常称为模板的实例
		cout << Test1::compare(1, 2) << endl;
		int arr[30];
		cout << Test1::length(arr) << endl;
		*/
	}
	{
		// 必须提供额外的参数 显示模板参数(explicit template argument)
		// 一个类模板的每个实例都形成一个独立的类.类型Blob<int>与任何其它
		// Blob类型都没有关联,也不会对任何其它Blob类型的成员有特殊访问权限
		// 默认情况下,对于一个实例化了的类模板,其成员只有在使用时才实例化
		/*
		Test2::Blob<int> b1;
		
		Test2::Blob<long> b2 = {1,2,3,4,5,6};
		Test2::Blob<int> b3;
		for (int s : b2) {
			cout << s << endl;
		}
		cout << b2[1] << endl;
		cout << Test2::operator==(b1,b3) << endl;
		cout << (b1 == b3) << endl;
		cout << b1 << endl;
		Test2::Pal<int> p;
		p.f();
		//test<>();
		//class T {
			// 无法在局部类中声明友元
			//template<typename T>
			//friend class Test2::Blob;
		//};
		*/
	}
	{
		/*
		Test4::Bar<Test4::Foo> b;
		Test4::Foo f;
		f.f();
		*/
	}
	{
		/*
		cout << Test5::Foo<int, 4>::k << endl;
		Test5::Foo<int, 4>::k = 50;
		cout << Test5::Foo<int, 4>::k << endl;

		cout << Test5::Foo<int, 5>::k << endl;
		Test5::Foo<int, 5>::k = 150;
		cout << Test5::Foo<int, 5>::k << endl;

		cout << Test5::Foo<int, 4>::k << endl;
		cout << Test5::Foo<int, 5>::k << endl;
		*/
	}
	{
		Test6::List<int> l;
	}
	system("pause");
	return 0; 
}