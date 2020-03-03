#include<iostream>
#include<cstdlib>
#include<cassert>

using namespace std;

template<class T> 
class SA {
private:
	int low, high;
	T* p;
public:

	// default constructor
	// allows for writing things like SA a;

	SA() { low = 0; high = -1; p = NULL; }

	// 2 parameter constructor lets us write
	// SA x(10,20);

	SA(int l, int h) {
		if ((h - l + 1) <= 0) {
			cout << "constructor error in bounds definition" << endl;
			exit(1);
		}
		low = l;
		high = h;
		p = new T[h - l + 1];
	}

	// single parameter constructor lets us
	// create a SA almost like a "standard" one by writing
	// SA x(10); and getting an array x indexed from 0 to 9

	SA(int i) {
		low = 0; high = i - 1;
		p = new T[i];
	}

	// copy constructor for pass by value and
	// initialization

	SA(const SA& s) {
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i < size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
	}
	// destructor

	~SA() {
		delete[] p;
	}
	//overloaded [] lets us write
	//SA x(10,20); x[15]= 100;

	T& operator[](int i) {
		if (i<low || i>high)
		{
			cout << "index " << i << " out of range" << endl;
			exit(1);
		}
		return p[i - low];
	}

	// overloaded assignment lets us assign
	// one SA to another

	SA& operator=(const SA& s) {
		if (this == &s)return *this;
		delete[] p;
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i < size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
		return *this;
	}

	// overloads << so we can directly print SAs
	template <class A>
	friend ostream& operator<<(ostream& os, SA<T> s);
};

template<class T> 
ostream& operator<<(ostream& os, SA<T> s) {
	int size = s.high - s.low + 1;
	for (int i = 0; i < size; i++)
		cout << s.p[i] << endl;
	return os;
};

template <class T>
class SM {
private:
	int lowx, highx, lowy, highy;
	SA<T> *sa;

public:
	
	SM(int n) {
		lowx = lowy = 0;
		highx = highy = n - 1;;
		sa = new SA<T>[n];
		for (int i = 0; i < n; i++) {
			sa[i] = SA<T>(n);
		}
	}

	// Copy constructor
	SM(const SM& sm) {
	

		sa = new SA<T>[sm.highx+1];

		for (int i = 0; i < sm.highx+1; i++) {
			sa[i] = SA<T>(0, sm.highy);
			for (int j = 0; j < sm.highy + 1; j++) {
				sa[i][j] = sm.sa[i][j];
			}
		}

		lowx = 0;
		highx = sm.highx;
		lowy = 0;
		highy = sm.highy;
	}

	// Destructor
	~SM() {
		delete[] sa;
	}

	// Overload [] returns safe array inside of safe array
	SA<T>& operator[](int i) const {
		if (i<lowx || i>highx) {
			cout << "Matrix out of bounds at position " << i << endl;
			exit(1);
		}

		return sa[i];
	}

	
	template <class A>
	friend ostream& operator<<(ostream& os, SM<A>& s);
	
	template <class A>
	friend SM<A> operator*(const SM<A>& sm1, const SM<A>& sm2);
};

template <class T>
ostream& operator<<(ostream& os, SM<T>& s) {
	for (int i = 0; i < s.highx + 1; i++) {
		for (int j = 0 ; j < s.highy + 1; j++) {
			cout << s.sa[i][j] << " ";
		}
		cout << endl;
	}
	return os;
}

template <class T>
SM<T> operator*(const SM<T>& sm1, const SM<T>& sm2) {

	SM<T> matrix(sm1.highx+1);

	// Initialize new matrix
	for (int i = 0; i < sm1.highx + 1; i++) {
		for (int j = 0; j < sm2.highy + 1; j++) {
			matrix[i][j] = 0;
		}
	}

	//Multiplication operation
	for (int i = 0; i < sm1.highx + 1; i++) {
		for (int j = 0; j < sm2.highy + 1; j++) {
			for (int k = 0; k < sm1.highy + 1; k++) {
				matrix[i][j] += sm1[i][k] * sm2[k][j];
			}
		}
	}

	return matrix;
}

int main() {

	SM<int> sm1(4), sm2(4);

	// Initialize sm1
	int c = 0;
	for (int i = 0; i < 4 ; i++) {
		for (int j = 0; j < 4 ; j++) {
			sm1[i][j] = c++;
		}
	}
	//reset counter
	c = 0;

	// Initialize sm2
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sm2[i][j] = c++;
		}
	}

	cout << sm1 << endl; // Output sm1
	cout << sm2 << endl; // Out put sm2

	SM<int> sm3 = sm1 * sm2; //overloaded *
	cout << sm3; //print resulting m3

	return 0;
}