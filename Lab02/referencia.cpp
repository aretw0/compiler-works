#include <iostream>
using namespace std;

void func(int * v)
{
	*v = 2;
	cout << "Ptr: " << *v << endl;
}

void func(int & v)
{
	v = 3;
	cout << "Ref: " << v << endl;
}

int main()
{
	int val = 1;
	func(&val);
	func(val);
}
