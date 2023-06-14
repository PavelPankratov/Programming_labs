#include <iostream>

using namespace std;

int main(){
	int x,sum=0;
	cout<<"Enter your numbers\n";
	do {
		cin>>x;	 
		if(x>0 && x%2==0){
			sum+=x;
		}
	} while (x!=0);
	cout << "Result sum is equal "<< sum;
}
