#include "iostream"
#include "type_traits"
#include "string"
template<typename T>	
inline
typename std::remove_reference<T>::type&& move(T&& t) {
	// 从一个左值static_cast到一个右值引用是允许的(C++11)
	// 虽然不能隐式地将一个左值转换为右值引用,但可以用static_cast显式进行转换

	return static_cast<typename std::remove_reference<T>::type&&>(t);
}
int main()
{
	decltype(move(1)) i = move(1);
	
	return 0; 
}