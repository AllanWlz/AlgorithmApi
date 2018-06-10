#include <stdio.c>

__int64 power2BF(int n){
	return (1 > n) ? 1 : power2BF( n - 1) << 1;
}

inline __int64 sqr (__int64 a) {return a * a}

__int64 power2(int n){

	__int64 pow = 1;

	__int64 p = 2;

	 while( 0 < n )
	 {

	 	if( n & 1)
	 	{

	 		pow *= p;

	 	}

	 	n >>= 1;

	 	p *= p;

	 }

}



int main(){
	
	

}
