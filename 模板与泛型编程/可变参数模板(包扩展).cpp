#include "iostream"
#include "numeric"
#include "vector"
#include "algorithm"
#include "tuple"
// 对于一个参数包,除了获取其大小之外,我们能对它做的唯一的事情就是
// 扩展(expand)它.当扩展一个包时,我们还要提供用于每个扩展元素的模
// 式(pattern).扩展一个包就是将它分解为构成的元素,对每个元素应用模
// 式,获得扩展后的列表.
using namespace std;

template<typename T,typename...Args>
// Args 扩展Args,编译器将Args&应用到Args的每个元素
int f(T& t,Args&... args)
{	
	// Args expand
	tuple<T,Args...> tup;
	// args expand and Args expand
	// { f<Args[0]>(args[0]),f<Args[1]>(args[1]),... };
	initializer_list<T> tmp = { f<Args>(args)... };
	// args expand
	initializer_list<T> v = { t++, args++...};
	for_each(v.begin(), v.end(), [](const T& a) {cout << a << endl; });
	return 0;
}

int main()
{
	int i, j, k; 
	i = 1;
	j = 2;
	k = 3;
	f(i, j, k);
	cout << "i:" << i << "j:" << j << "k:" << k << endl;
	system("pause");
	return 0; 
}