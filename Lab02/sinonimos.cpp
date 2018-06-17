#include <iostream>
using namespace std;

void func(int & a, int & b)
{
	a = a + 5;
	int c = b + 10;
	// se a e b não fossem sinônimos, o resultado seria 20
	cout << c << endl;
}

int main()
{
	int x = 10;
	func(x, x);
}
