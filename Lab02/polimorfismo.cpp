class Base
{
public:
	virtual void msg() {};
};

class Derivada : public Base
{
public:
	virtual void msg() {};
};

void func(Base & obj)
{
	obj.msg();
}

int main()
{
	Base b;
	Derivada d;
	func(b);
	func(d);
}

