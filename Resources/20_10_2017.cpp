#include <iostream>

using namespace std;

int main()
{
	int a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44;
	cin >> a11 >> a12 >> a13 >> a14
		>> a21 >> a22 >> a23 >> a24
		>> a31 >> a32 >> a33 >> a34
		>> a41 >> a42 >> a43 >> a44;

	bool f1 = !a14 || (!a11&&!a12&&!a13&&!a21&&!a32&&!a43);
	bool f2 = !a24 || (!a21&&!a22&&!a23&&!a31&&!a42&&!a13);
	bool f3 = !a34 || (!a31&&!a32&&!a33&&!a41&&!a12&&!a23);
	bool f4 = !a44 || (!a41&&!a42&&!a43&&!a11&&!a32&&!a43);

	if (f1&&f2&&f3&&f4)
	{
		cout << "Safe";
	}
	else
	{
		cout << "Unsafe";
	}

	int a = 101;

	if (a>100)
	{
		cout << a*a;
	}
	if (a > 40)
		cout << a;

	if (a > 100)
	{
		a = 1;
	}
	else if (a > 40)
	{
		a = 2;
	}
	else
		a = 3;
	
	cout << a;
	
	
	switch (a)
	{
	case(3) :
		
	case(1) :
	{
		a += 3;//a=a+3;
		break;
	}
	case(4) :
		a += 2 * a;
	case(101):
			a += 3;
			break;
	default:
		a += a;//a=a+a;
	}

	//пробвайте да решите 2 задача, за да си упражните if-else и switch
	
	return 0;
}
