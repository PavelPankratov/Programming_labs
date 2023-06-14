#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char** argv) {
	double x;
	cout<<"Enter x: ";
	cin>>x;
	if (2 > x){
		if((x*x-4*x-5)>=0){
			cout<<"Result: "<<sqrt(x*x-4*x-5);
		}
	  	else cout<<"ERROR: "<< endl;
	}
	if (2 <= x && x < 6){
		if((x*x-4*x-5)>0){
			cout<<"Result: "<<log(1/(x*x-4*x-5));
		}
	  	else cout<<"ERROR: "<< endl;
	}
	if (6 <= x){
		if(sin(x*x-4*x-5)!=0){
			cout<<"Result: "<<tan(x*x-4*x-5);
		}
	  	else cout<<"ERROR: "<< endl;
	}
	return 0;
}
