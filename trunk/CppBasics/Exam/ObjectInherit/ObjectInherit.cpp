// ObjectInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "InheritTest.h"

using namespace std;
void Fun(Base);
void Fun2(Base *);

int _tmain(int argc, _TCHAR* argv[])
{
	C c(10);
	cout<<c.GetData()<<endl;
	cout<<c.A::GetData()<<endl;
	cout<<c.B::GetData()<<endl;
	cout<<c.C::GetData()<<endl;
	cout<<c.doGetData()<<endl;
	cout<<c.A::doGetData()<<endl;
	cout<<c.B::doGetData()<<endl;
	cout<<c.C::doGetData()<<endl;

	Base b;
	Child child;
	Fun(b);
	Fun(child);
	Base cc = child;//�൱������������ֵ��������һ������Ķ��������������Ķ���
	cout<<"------Fun2------"<<endl;
	Fun2(&b);
	Fun2(&child);
	return 0;
}

void Fun(Base o)
{
	o.fun();
	o.vfun();
}

void Fun2(Base * o)
{
	o->fun();
	o->vfun();
}