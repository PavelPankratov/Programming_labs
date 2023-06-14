#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char** argv) {
	float a,b, total;
	int c,d;
	
	cout<<"Enter a, b, c, d: \n" ;
	cin>>a>>b>>c>>d;
	if (a*a-1!= 0 && c>0){	
		total = (4*log10(c) - (d /2) + 23 ) / (a*a-1);
		cout << "Result: " << total;
	} else {
		cout <<"Net resultata";
	}
	return 0;
}
