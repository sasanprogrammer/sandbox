#include <iostream>
#include <windows.h>
#include <functional>
#include <string>
using namespace std;
HANDLE hn = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cr;
CONSOLE_CURSOR_INFO inf;
char CURSOR='?';
/* Functions */
void y1();
void y2();
void x1();
void x2();
void ch1();
void ch2();
void ch3();
void ch4();
void ch5();
void cm1();
void cm2();
void cm3();
void cm4();
void cm5();
int speed=10;
int main(){
	GetConsoleCursorInfo(hn , &inf);
	//inf.dwSize=2;
	SetConsoleCursorInfo(hn , &inf);
	cr.X=1;
	cr.Y=1;
	int x[]={0x27 , 0x28 , 0x26 , 0x25 , 0x4a , 0x4b , 0x20 , 0x44 , 0x46};
	
	//LST: LF RH DW UP J K D F
	function<void()> pos[]={x2,y2,y1,x1 , ch1 , ch2 , ch3 , ch4  , ch5 , cm1 , cm2 , cm3 , cm4 , cm5};
	//indices: 0 1 2 3 4 5 6 7 8 9 10 11 12 13
	SetConsoleCursorPosition(hn , cr);
	while(true){
		cout<<CURSOR;
		/*Check for every movement*/
		for(int i=0; i<=sizeof(x); i++){
			if (GetKeyState(x[i]) & 0x8000){
				pos[i]();
			} else if(GetKeyState('E')&0x8000){
				int index;
				cout<<"Enter the command INDEX: ";
				cin>>index;
				pos[index]();
			}
		}
		if(cr.X < 0){
			cr.X=0;
		}
		/*Save every changes*/
		SetConsoleCursorInfo(hn , &inf);
		SetConsoleCursorPosition(hn , cr);
		Sleep(speed);
		fflush(stdout);
	}
}
void y1(){
	cr.Y-=2;
}
void y2(){
	cr.Y+=2;
}
void x1(){
	cr.X-=2;
}
void x2(){
	cr.X+=2;
}
void ch1(){
	CURSOR='*';
}
void ch2(){
	CURSOR='?';
}
void ch3(){
	inf.bVisible=0;
}
void ch4(){
	CURSOR=' ';
}
void ch5(){
	inf.bVisible=1;
}
void cm1(){
	int xy;
	int in;
	cout<<"Enter the mode: ";
	cin>>xy;
	cout<<"Enter the number: ";
	cin>>in;
	switch(xy){
		case 1:cr.X=in;break;
		case 2:cr.Y=in;break;
	}
}
void cm2(){
	cout<<"X:"<<cr.X<<endl<<"Y:"<<cr.Y<<endl;
}
void cm3(){
	string inp;
	cin>>inp;
}
void cm4(){
	int x;
	cin>>x;
	speed=x;
}
void cm5(){
	char *txt;
	cin>>txt;
	system(txt);
}