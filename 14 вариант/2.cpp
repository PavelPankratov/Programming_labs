#include <iostream>
#include <math.h>
using namespace std;



int main(int argc, char** argv) {
	int a, b;
	long int X;
	cout<<"Enter a, b: ";
	cin>>a>>b;
	
	if (a > b){
		if(b!=0){
			X = (a/b)-37;
			cout<<"Result: "<< X;
		}
		else cout<<"ERROR: "<< endl;
	}
	if ( a == b){
		X = 3;
		cout<<"Result: "<< X;
	}
	if (a < b){
		if(a!=0){
			X = (pow(a, 3)-b)/(a);
			cout<<"Result: "<< X;
		}
		else cout<<"ERROR: "<< endl;
	}
	return 0;
}
