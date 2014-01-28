#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<cstdlib>
using namespace std;
class codegen{
	short int i,y,n,w;
	char t,z[10];
	string line[30][20],var;
	public:
		codegen()
		{
			w=i=0;
			y=n=1;
		}
		short int header(string);
		short int datyp(string);
		short int vnam(string);
		void typret(string);
		short int arychk(string);
		void read();
};
short int codegen::header(string a)
{
	short int f=0;
	if(a=="conio.h")
	f=1;
	else if(a=="iomanip.h")
	f=1;
	else if(a=="stdio.h")
	f=1;
	else if(a=="string.h")
	f=1;
	else if(a=="math.h")
	f=1;
	else
	f=0;
	return f;
}
short int codegen::datyp(string a)
{
	short int f=0;
	if(a=="int")
	{
		t='d';
		f=1;
	}
	else if(a=="float")
	{
		t='f';
		f=1;
	}
	else if(a=="char")
	{
		t='c';
		f=1;
	}
	else if(a=="double")
	{
		t='f';
		f=1;
	}
	else if(a=="string")
	{
		t='s';
		f=1;
	}
	else
		f=0;
	return f;
}
short int codegen::vnam(string a)
{
	short int i,f;
	if(!isalpha(a[0])&&a[0]!='_')
		return 0;
	for(i=1;i<a.length();i++)
	{
		if(isalnum(a[i])||a[i]=='_')
			f=1;
		else
		{
			f=0;
			break;
		}
	}
	return f;
}
short int codegen::arychk(string a)
{
	var='\0';
	short int i=0;
	for(short int r=0;r<a.length();r++)
	{
	if(a[r]!='[')
	var=a[r];
	if(a[r]=='[')
	{
	r++;
	while(a[r]!=']')
	{
	z[i]=a[r];
	r++;
	i++;
	}
	return 1;
	}
	}
	return 0;
}
void codegen::typret(string a)
{
	short int x,l=0,flag=0;
	for(x=0;x<i-1;x++)
	{
	if(line[x][0]=="Variables")
	{ l++;
	while(line[x][l]!=" ")
	{
	if(line[x][l]==a)
	{
	flag=1;
	break;
	}
	l++;
	}
	}
	if(flag==1)
	{
	x--;
	break;
	}
	}
	l=datyp(line[x][1]);
}
void codegen::read()
{
	char ch;
	short int j,k,l,m,flag;
	i=0,j=0,n=1;
	ifstream fin;
	fin.open("input3.txt",ios::in);
	while(!fin.eof())
	{
	fin.get(ch);
	while(ch!=':'&&!fin.eof())
	{
	line[i][j]=line[i][j]+ch;
	fin.get(ch);
	}
	j++;
	while(ch!=';'&&!fin.eof())
	{
	fin.get(ch);
	while(ch!=','&&ch!=';')
	{
	line[i][j]=line[i][j]+ch;
	fin.get(ch);
	}
	j++;
	}
	fin.get(ch);
	line[i][j]=" ";
	i++;
	j=0;
	if(fin.eof())
	{
	break;
	}
	}
	ofstream fout;
	fout.open("1.c",ios::trunc);
	for(k=0;k<i;k++)
	{
	l=0;
	if(line[k][0]=="Header")
	{
	l++;
	while(line[k][l]!=" ")
	{
	if(header(line[k][l]))
	{
	flag=1;
	cout<<"#include<"<<line[k][l]<<">"<<endl;
	fout<<"#include<"<<line[k][l]<<">"<<endl;
	}
	l++;
	}
	if(flag==1)
	{
	cout<<"int main()\n{"<<endl;
	fout<<"int main()\n{"<<endl;
	}
	l=0;
	}
	else if(line[k][0]=="Type")
	{
	l++;
	cout<<"\n\t"<<line[k][l]<<" ";
	fout<<"\n\t"<<line[k][l]<<" ";
	}
	else if(line[k][0]=="Variables")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<",";
	fout<<line[k][l]<<",";
	l++;
	}
	cout<<"\b"<<";";
	fout.seekp(-1,ios::cur);
	fout<<";";
	}
	else if(line[k][0]=="Input")
	{
	l++;
	while(line[k][l]!=" ")
	{
	typret(line[k][l]);
	if(arychk(line[k][l]))
	{
	cout<<"\n\tfor(i=0;i<"<<atoi(z)<<";i++)\n\t{\n\t\t";
	fout<<"\n\tfor(i=0;i<"<<atoi(z)<<";i++)\n\t{\n\t\t";
	cout<<"printf(\"Enter the value :\");\n\t\t";
	fout<<"printf(\"Enter the value :\");\n\t\t";
	cout<<"scanf(\"%"<<t<<"\",&"<<var<<"[i]);\n\t}";
	fout<<"scanf(\"%"<<t<<"\",&"<<var<<"[i]);\n\t}";
	}
	else
	{
	cout<<"\n\tprintf(\"\\nEnter "<<line[k][l]<<":\");";
	fout<<"\n\tprintf(\"\\nEnter "<<line[k][l]<<":\");";
	cout<<"\n\tscanf(\"%"<<t<<"\",&"<<line[k][l]<<");";
	fout<<"\n\tscanf(\"%"<<t<<"\",&"<<line[k][l]<<");";
	}
	l++;
	}
	}
	else if(line[k][0]=="Operation")
	{
	l++;
	while(line[k][l]!=" ")
	{
	cout<<"\n\t"<<line[k][l]<<";";
	fout<<"\n\t"<<line[k][l]<<";";
	l++;
	}
	}
	else if(line[k][0]=="Loop")
	{
	L1:if(line[k][1]=="for")
	{
	cout<<"\n\t"<<line[k][1]<<"(";
	fout<<"\n\t"<<line[k][1]<<"(";
	k++;
	if(line[k][0]=="Loop init")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<",";
	fout<<line[k][l]<<",";
	l++;
	}
	cout<<"\b;";
	fout.seekp(-1,ios::cur);
	fout<<";";
	k++;
	}
	if(line[k][0]=="Loop cont")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<"&&";
	fout<<line[k][l]<<"&&";
	l++;
	}
	cout<<"\b\b;";
	fout.seekp(-2,ios::cur);
	fout<<";";
	k++;
	}
	if(line[k][0]=="Loop op")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<",";
	fout<<line[k][l]<<",";
	l++;
	}
	cout<<"\b";
	fout.seekp(-1,ios::cur);
	k++;
	}
	cout<<")\n\t{\n\t";
	fout<<")\n\t{\n\t";
	if(line[k][0]=="Loop")
	{
	n++;
	goto L1;
	}
	if(line[k][0]=="Operation")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<"\n\t"<<line[k][l]<<";";
	fout<<"\n\t"<<line[k][l]<<";";
	l++;
	}
	}
	}
	L2:if(line[k][1]=="while")
	{
	k++;
	if(line[k][0]=="Loop init")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<"\n\t"<<line[k][l]<<";";
	fout<<"\n\t"<<line[k][l]<<";";
	l++;
	}
	k++;
	}
	cout<<"\n\twhile"<<"(";
	fout<<"\n\twhile"<<"(";
	if(line[k][0]=="Loop cond")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l];
	fout<<line[k][l];
	l++;
	}
	k++;
	}
	cout<<")\n\t{\n\t";
	fout<<")\n\t{\n\t";
	if(line[k][0]=="Loop op")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<";";
	fout<<line[k][l]<<";";
	l++;
	}
	k++;
	}
	if(line[k][0]=="Loop")
	{
	y++;
	goto L2;
	}
	if(line[k][0]=="Operation")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<"\n\t"<<line[k][l]<<";";
	fout<<"\n\t"<<line[k][l]<<";";
	l++;
	}
	}
	}
	}
	else if(line[k][0]=="Loop end")
	{
	for(int x=0;x<n;x++)
	{
	cout<<"\n\n\t}";
	fout<<"\n\n\t}";
	}
	}
	else if(line[k][0]=="Loop ter")
	{
	for(int x=0;x<y;x++)
	{
	cout<<"\n\t}";
	fout<<"\n\t}";
	}
	}
	else if(line[k][0]=="Cond ter")
	{
	for(int x=0;x<w;x++)
	{
	cout<<"\n\t}";
	fout<<"\n\t}";
	}
	}
	else if(line[k][0]=="Output")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	typret(line[k][l]);
	if(arychk(line[k][l]))
	{
	cout<<"\n\tfor(i=0;i<"<<atoi(z)<<";i++)\n\t{\n\t\t";
	fout<<"\n\tfor(i=0;i<"<<atoi(z)<<";i++)\n\t{\n\t\t";
	cout<<"printf(\"Output :\");\n\t\t";
	fout<<"printf(\"Output :\");\n\t\t";
	cout<<"printf(\"%"<<t<<"\","<<var<<"[i]);\n\t}";
	fout<<"printf(\"%"<<t<<"\","<<var<<"[i]);\n\t}";
	}
	else
	{
	cout<<"\n\tprintf(\"\\nOutput : "<<line[k][l]<<":\");";
	fout<<"\n\tprintf(\"\\nOutput : "<<line[k][l]<<":\");";
	cout<<"\n\tprintf(\"%"<<t<<"\","<<line[k][l]<<");";
	fout<<"\n\tprintf(\"%"<<t<<"\","<<line[k][l]<<");";
	}
	l++;
	}
	}
	else if(line[k][0]=="Condition")
	{
	if(line[k][0]==line[k-1][0])
	w++;
	l=0;
	l++;
	cout<<"\n\tif("<<line[k][l]<<")\n\t{\n\t";
	fout<<"\n\tif("<<line[k][l]<<")\n\t{\n\t";
	if(line[k][0]!=line[k+1][0])
	{
	k++;
	}
	if(line[k][0]=="True")
	{
	l=1;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<";\n\t";
	fout<<line[k][l]<<";\n\t";
	l++;
	}
	k++;
	if(line[k][0]=="Print")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<"printf(\"\\n "<<line[k][l]<<"\");\n\t";
	fout<<"printf(\"\\n "<<line[k][l]<<"\");\n\t";
	l++;
	}k++;
	}
	cout<<"}";
	fout<<"}";
	}
	if(line[k][0]=="False")
	{
	l=0;
	l++;
	cout<<"\n\telse"<<"\n\t{\n\t";
	fout<<"\n\telse"<<"\n\t{\n\t";
	l=1;
	while(line[k][l]!=" ")
	{
	cout<<line[k][l]<<";\n\t";
	fout<<line[k][l]<<";\n\t";
	l++;
	}
	k++;
	if(line[k][0]=="Print")
	{
	l=0;
	l++;
	while(line[k][l]!=" ")
	{
	cout<<"printf(\"\\n "<<line[k][l]<<"\");\n\t";
	fout<<"printf(\"\\n "<<line[k][l]<<"\");\n\t";
	l++;
	}
	}
	cout<<"}";
	fout<<"}";
	}
	}
	else if(line[k][0]=="Sort")
	{
	l=0;
	l++;
	if(line[k][l]=="Selection")
	{
	cout<<"\n\tfor(i=0;i<"<<atoi(z)<<";i++)\n\t{";
	fout<<"\n\tfor(i=0;i<"<<atoi(z)<<";i++)\n\t{";
	cout<<"\n\tfor(j=i+1;j<"<<atoi(z)<<";j++)\n\t{";
	fout<<"\n\tfor(j=i+1;j<"<<atoi(z)<<";j++)\n\t{";
	cout<<"\n\t\tif("<<var<<"[i]>"<<var<<"[j])\n\t\t{t="<<var<<"[i];\n\t\t"<<var<<"[i]="<<var<<"[j];\n\t\t"<<var<<"[j]=t;\n\t}}}";
	fout<<"\n\t\tif("<<var<<"[i]>"<<var<<"[j])\n\t\t{t="<<var<<"[i];\n\t\t"<<var<<"[i]="<<var<<"[j];\n\t\t"<<var<<"[j]=t;\n\t}}}";
	}
	else if(line[k][l]=="Bubble")
	{
	cout<<"\n\tfor(i="<<atoi(z)<<"-1"<<";i>0;i--)\n\t{\n\tfor(j=0;j<i;j++)\n\t{\n\tif("<<var<<"[j]>"<<var<<"[j+1])";
	fout<<"\n\tfor(i="<<atoi(z)<<"-1"<<";i>0;i--)\n\t{\n\tfor(j=0;j<i;j++)\n\t{\n\tif("<<var<<"[j]>"<<var<<"[j+1])";
	cout<<"{\n\tt="<<var<<"[j];\n\t"<<var<<"[j]="<<var<<"[j+1];\n\t"<<var<<"[j+1]=t;\n\t}\n\t}\n\t}";
	fout<<"{\n\tt="<<var<<"[j];\n\t"<<var<<"[j]="<<var<<"[j+1];\n\t"<<var<<"[j+1]=t;\n\t}\n\t}\n\t}";
	}
	}
	}
	cout<<"\ngetch();\nreturn 0;\n}";
	fout<<"\ngetch();\nreturn 0;\n}";
	fin.close();
	fout.close();
}
int main()
{
	codegen c;
	c.read();
	return 0;
}
