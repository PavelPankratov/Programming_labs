#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;
struct pointer
{ int d;
  pointer *p;
};

//===================== 
void FormSt(pointer **ph, int data)
{
 *ph = new pointer;
 (*ph) -> d = data;
 (*ph)->p = NULL;
}

//====================== 
void DobSt (pointer **ph, int data)
      { 
      pointer *px=new pointer;
	 px->d=data;
	 px->p=*ph;
	 *ph=px;
       }


//====================== 
void IskSt (pointer **ph, int &data)
{ data = (*ph)->d;
  *ph = (*ph)->p;
}

//======================
int main()
{
system("cls");
int i;
// =============

 pointer *ph=NULL;

 cout<<"Vvedite 1 element -->" ;
 int data;
 cin >> data ;

 FormSt(&ph,data);

 do
 {
	cout<<"Vvedite sled element -->" ;
	cin >> data;
	DobSt(&ph,data);

 }
 while (data!=0);
 
//Оработка стека в соответствии с вариантом
 
 i=0;
 pointer *pc = ph;
 cout <<"Data ->"<<(*pc).d<<endl;
 cout<<"\nVivod stack: \n\n";
  while (ph!=NULL)    
  {
      IskSt(&ph,data);
      //int data = ph->d;
      //ph=ph->p;
      cout<<(i+1)<<" element  = "<<data<<"\n";
      i++;
   }
   ph = pc;
cout<<"\nVivod stack: \n\n";
  while (ph!=NULL)    
  {
      IskSt(&ph,data);
      //int data = ph->d;
      //ph=ph->p;
      cout<<(i+1)<<" element  = "<<data<<"\n";
      i++;
   }
  
 
   
getch();
}

