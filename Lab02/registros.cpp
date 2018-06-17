#include <iostream>
using namespace std;

struct A
{
	int a;
	int b;

	A() : a(1), b(2)
	{
	}
};

struct B : A
{
	int b;
	int c;

	B() : b(3), c(4)
	{
		// para alterar o b herdado de A
		// A::b = 5;
	}
};

int main()
{
	B b;
	cout << b.a << b.b << b.c << endl;

	A a = b;
	cout << a.a << a.b << endl;

	cout << "B tem " << sizeof(b) << " bytes\n" ;
}
