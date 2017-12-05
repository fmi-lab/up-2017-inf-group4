#include <iostream>
#include <iomanip>

const double eps = 1e-4;

double mabs(double n)
{
	return n<0 ? -n : n;
}

bool is_zero(double n)
{
	return mabs(n) < eps;
}

void read_array(double *arr,int n)
{
	for(int i=0;i<n;++i)
		std::cin>>arr[i];
}

void problem1()
{
	double a[3],b[3];
	read_array(a,3);
	read_array(b,3);
	
	bool b0_is_zero = is_zero(b[0]);
	
	double k = (b0_is_zero ? a[1]/b[1] : a[0]/b[0]);
	
	if(is_zero(a[0]-k*b[0]) && is_zero(a[1]-k*b[1]))
	{
		if(is_zero(a[2]-k*b[2]))
			std::cout<<"coincide"<<std::endl;
		else
			std::cout<<"parallel"<<std::endl;
		
		return;
	}
	
//  |a0x + a1y + a2 = 0
//	|b0x + b1y + b2 = 0

	double x,y;
	
	if(b0_is_zero)
	{
// 		k=a1/b1
//      a1 - k*b1 == 0
//      (a0 - k*b0)x + (a2 - k*b2) = 0
//		x = (k*b2 - a2)/(a0 - k*b0)
//		b0=0 => (k*b2 - a2)/a0
//      b0x + b1y + b2 = 0
//		y = (-b2 - b0*x)/b1
//      b0=0 => y = - b2/b1
		x = (k*b[2] - a[2]) / a[0];
		y = -b[2]/b[1];
	}
	else
	{
//		k=a0/b0
//      a0 - k*b0 == 0
//		(a1 - k*b1)y + (a2 - k*b2) = 0
// 		(a1 - k*b1)y = (k*b2 - a2)
//      y = (k*b2 - a2)/(a1 - k*b1)
//      b0x + b1y + b2 = 0
//		x = (- b1*y - b2)/b0
		y = (k*b[2] - a[2])/(a[1]-k*b[1]);
		x = (- b[1]*y - b[2])/b[0];
	}
	//отпечатва само до 3 знака след запетаята
	std::cout << std::fixed << std::setprecision(3);

	std::cout<< x << " "<<y<<std::endl;
}

int cnt_digits(int n)
{
	if(n==0) return 1;
	
	int res=0;
	
	while(n!=0)
	{
		++res;
		n/=10;
	}
	return res;
}

int pow(int x,int n)
{
	int res=1;
	while(n--)
		res*=x;
	
	return res;
}

int digit_on_pos(int number,int pos)
{
	return (number/pow(10,pos-1))%10;
}

//отляво надясно => отдясно наляво
void problem2()
{
	int number,pos,digit;
	std::cin>>number>>pos>>digit;
	
	int digs=cnt_digits(number);
	pos=digs-pos+1;//позицията отдясно наляво
	
	int p=pow(10,pos-1);
	number -= p*digit_on_pos(number,pos);
	number += p*digit;
	
	std::cout<<number<<std::endl;
}

void delete_range(double *arr,int begin,int end,int &n)
{
	int len_range = end-begin;
	
	for(int i=begin;i < n-len_range;++i)
		arr[i]=arr[i+len_range];
	
	n-=len_range;
}

double sum_array(double *arr,int n)
{
	double sum=0.0;
	for(int i=0;i<n;++i)
		sum += arr[i];
	
	return sum;
}

void print(double *arr,int n)
{
	std::cout << std::fixed << std::setprecision(3);
	for(int i=0;i<n;++i)
		std::cout << arr[i]<<" ";
	std::cout<<std::endl;
}

const int SIZE=5000;

void problem3()
{
	double arr[SIZE];
	int n;
	std::cin>>n;
	read_array(arr,n);
	
	double average=sum_array(arr,n)/n;
	
	int cnt = 1;
	
	for(int i=1;i<n;++i)
	{
		if(is_zero(arr[i-1]-arr[i]))
		{
			++cnt;
			continue;
		}
		
		if(cnt>=3)
		{
			arr[i-cnt]=average;
			delete_range(arr,i-cnt+1,i,n);
			i=i-cnt+1;
		}
		cnt=1;
	}

	if(cnt>=3)
	{
		arr[n-cnt]=average;
		delete_range(arr,n-cnt+1,n,n);
	}
	
	print(arr,n);
}

void swap(double& a, double& b)
{
	double t = a;
	a = b;
	b = t;
}

int get_min_index(double *a, int begin, int n)
{
	int min = begin;
	
	for(int i=begin+1; i<n; ++i)
	{
		if(a[min] > a[i])
			min=i;
	}
	
	return min;
}

void sort(double *a, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int id = get_min_index(a, i, n);
		swap(a[i], a[id]);
	}
}

const int MATRIX_SIZE=200;

void read_matrix(double mat[MATRIX_SIZE][MATRIX_SIZE],int& n,int& m)
{
	std::cin >> n >> m;

	for(int i=0;i<n;++i)
		read_array(mat[i],m);
}

bool equal_arrays(double *arr1,double *arr2,int m)
{
	for(int i=0;i<m;++i)
	{
		if(!is_zero(arr1[i]-arr2[i]))
			return false;
	}
	return true;
}

void problem4_1()
{
	double mat[MATRIX_SIZE][MATRIX_SIZE];
	int n,m;

	read_matrix(mat,n,m);
	
	for(int i=0;i<n;++i)
		sort(mat[i],m);
	
	bool two_equal_rows=false;
	
	for(int i=0;i<n;++i)
	{
		for(int j=i+1;j<n;++j)
		{
			if(equal_arrays(mat[i],mat[j],m))
			{
				std::cout<<i+1<<" "<<j+1<<std::endl;
				two_equal_rows=true;
			}
		}
	}
	if(two_equal_rows==false)
		std::cout<<"No such rows"<<std::endl;
}

void problem4_2()
{
	double mat[MATRIX_SIZE][MATRIX_SIZE];
	int n,m;
	
	read_matrix(mat,n,m);
	
	bool two_equal_rows=false;
	
	for(int r1=0;r1<n;++r1)
	{
		for(int r2=r1+1;r2<n;++r2)
		{
			for(int pos1=0;pos1<m;++pos1)
			{
				bool match=false;
				
				for(int pos2=pos1;pos2<m;++pos2)
				{
					if(is_zero(mat[r1][pos1]-mat[r2][pos2]))
					{
						match=true;
						swap(mat[r2][pos1],mat[r2][pos2]);
						//гарантираме си, че след позиция "pos1" в ред "r2"
						//имаме само "необработени" елементи
						break;
					}
				}
				if(match==false) break;
				
				if(pos1 == m-1)
				{
					two_equal_rows=true;
					std::cout<<r1+1<<" "<<r2+1<<std::endl;
				}
			}
		}
	}
	
	if(two_equal_rows==false)
		std::cout<<"No such rows"<<std::endl;
}

int main()
{
	
	return 0;
}