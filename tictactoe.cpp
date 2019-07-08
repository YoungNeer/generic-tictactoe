#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int getPosition(char A[][10],char ch,int n){
	int ri=0,rj=0;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			if(A[i][j]==ch){
				ri=i;rj=j;break;}
	 return (ri*10)+rj;}
int diagonalCheck(char A[][10],int n,int ch,int dig){
	int sum=0;
	//dig will be a constant and the conditions are not goin' to overlap
	for (int i=0;i<n;++i)
	  if ((!dig)&&A[i][i]==ch)
		++sum;
	  else if (dig&&A[i][n-1-i]==ch)
		++sum;
	return sum;}
int horCheck(char A[][10],int n,int ch,int row){
	//I'm using j because usually i indicates row and j -column
	int sum=0;
	for (int j=0;j<n;++j)
		if (A[row][j]==ch)
			++sum;
	return sum;}
int verCheck(char A[][10],int n,int ch,int col){
	int sum=0;
	for (int i=0;i<n;++i)
		if (A[i][col]==ch)
			++sum;
	return sum;}
bool winsGame(char A[][10],int n,int ch){
	bool win=false;
	//There's no sp. reason for using bool, I don't know why i like to use it
	if (diagonalCheck(A,n,ch,0)==n||diagonalCheck(A,n,ch,1)==n)
			win=true;
	for (int i=0;i<n&&win!=1;++i)
		if (horCheck(A,n,ch,i)==n)
			win=true;
		else if (verCheck(A,n,ch,i)==n)
			win=true;
	return win;}
int strlen(string s)
  {
    int l=0;
    for (l=0;(s[l]!='\0'||s[l]==32);++l);
    return l;
  }

int getOption(string s,string op)
  {
    retry:
      cout<<s<<endl;
      string a;
      cout<<op<<endl;
      printf("\nHit what's in your mind_>");
      cin>>a;
    if (strlen(a)>1){
      cout<<"\nInvalid Option! ";
      goto retry;
    }
    if (a[0]!=49&&a[0]!=50){
      cout<<"\nInvalid option! ";
      goto retry;
    }
    return a[0]-48;
  }
int gInteger(int pos,int n){
	//This will give the greatest integer (not exactly)
	//I exactly know how many time I have to loop
	int r=0;
	for (int i=pos;i<pos+n;++i)
		if (i%n==0&&n<=i){
			r=i/n;break;}
	if (pos%n==0)
		return pos/n;
	else
		return r;}
string rc(char c,int times){
	string str="";
	for (int i=0;i<times;++i)
		str+=c;
	return str;}
int arrayNotFull(char A[][10],int n,int spec=0){
	/*This function can be used for three purpose:
		a) to check if array is not full, as the name suggests(spec=0)
		b) to check the no of vacant spaces in board (spec=1)
		c) to check the no of 0 or X in matrix(spec=2 and spec=3)
		d) to check if an array is full, opp of what the name suggests (spec=3)
		*/
	int flag=0;
	if (spec==4) flag=1;
	for (int i=0;i<n;++i){
		for (int j=0;j<n;++j){
			if (A[i][j]==32&&spec==0){
				flag=1;break;}
			else if (A[i][j]==' '&&spec==1)
				++flag;
			else if (A[i][j]=='0'&&spec==2)
				++flag;
			else if (A[i][j]=='X'&&spec==3)
				++flag;
			else if (A[i][j]==32&&spec==4)
				flag=0;
		}
	}
	return flag;
}
void printScreen(char A[][10],int n,int player){
  system("clear");
  cout<<rc(32,13+(n*4))<<rc('-',16)<<endl;
  string s=rc(32,8);
	for (int i=0;i<n;++i,s=rc(32,8)){
		for (int j=0;j<n;++j){
			if (j!=0) cout<<"|"; else cout<<rc(32,8);
			cout<<" "<<A[i][j]<<" ";
			s+="---";
			if (j!=n-1) s+="|";
			if (j==n-1) 
			{
				cout<<rc(32,5)<<"|";
				s+=rc(32,5)+"|";
				if (i==0)
					cout<<"   Player A: 0";
				if (i==n-1)
					cout<<"   Player B: X";
			}
		}
		cout<<"\n";
		if (i!=n-1)
			cout<<s<<"\n";
		}
	cout<<rc(32,13+(n*4))<<rc('-',16)<<endl;
	}
void enterPosition(char A[][10],int pos,char c,int n,int plyr){
	retry:
		cout<<"Enter position Player "<<plyr<<": ";
		cin>>pos;;
	if (pos<=0||pos>n*n){
		cout<<"Try Again! ";
		goto retry;
	}
	int i;
	i=(gInteger(pos,n))-1;
	int j=(pos%n)-1;
	if (j<0)
		j=n-1;
	if (i<0) i=-i;
	if (A[i][j]==32)
		A[i][j]=c;
	else{
		cout<<"Try Again! ";
		goto retry;}
}
int main(void){
	int toss=1;
	//int play1win,play2win,draw;
	//toss=getOption("Who will toss first?\n","1. Player A\n2. Player B\n");
	rtry:
		cout<<"Enter the no of gridsheet: ";
		int n; cin>>n;
		if (n>10) 
		{
			cout<<"Cannot generate such a huge game!\n\n";
			goto rtry;
		}
	char A[10][10];
	if (rand()%10+toss<5) 
		toss=1;
	else
		toss=2;
	
	for (int i=0;i<10;++i)
	for (int j=0;j<10;++j)
		A[i][j]=32;
	printScreen(A,n,toss);
	while(arrayNotFull(A,n)){
		int pos,pos2;
		switch (arrayNotFull(A,n,1)) {
			case 1:
			A[getPosition(A,32,n)/10][getPosition(A,32,n)%10]='0';
			break;
		    case 2:
			//cout<<"condition fullfiled";
			if (diagonalCheck(A,n,'0',0)!=n-1&&diagonalCheck(A,n,'0',1)!=n-1&&
				verCheck(A,n,'0',getPosition(A,32,n)%10)!=n-1&&horCheck(A,n,'0',getPosition(A,32,n)/10)!=n-1&&
				verCheck(A,n,'0',getPosition(A,32,n-1)%10)!=n-1&&horCheck(A,n,'0',getPosition(A,32,n-1)/10)!=n-1)
				cout<<"Game Draw";break;
			break;
			default:
			enterPosition(A,pos,'0',n,toss);}
			
		printScreen(A,n,toss);
		if (winsGame(A,n,'0')){
			cout<<"Player "<<toss<<" wins the game!\n";
			break;
		} 
			if (arrayNotFull(A,n,1)!=1) 
				enterPosition(A,pos,'X',n,((toss==1)?2:1));
			else //if n is even
				A[getPosition(A,32,n)/10][getPosition(A,32,n)%10]='X';
		//toss in nxt line has remained the same here because the toss winner hasnt changed
		printScreen(A,n,toss);
		if (winsGame(A,n,'X')){
			cout<<"Player "<<( (toss==1)?2:1)<<" wins the game!\n";
			break;
		}

	}

	/*
	     0 |   | X      |   Player A: 0
        ---|---|---     |
         X | X | 0      |
        ---|---|---     |
         0 |   |        |   Player B: X
              
	*/

	}
