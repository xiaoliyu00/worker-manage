#pragma once//��ֹͷ�ļ��ظ�����
#ifndef _EMPLOYEE_
#define _EMPLOYEE_

#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

//Ա���� 
class Employee:public Worker
{
public:
	//���캯��
	Employee(int id,string name,int dId);
	
	//��ʾ������Ϣ
	virtual void Show_Info();

	//��ȡְ����λ����
	virtual string Get_Dept_Name();

	//virtual ~Employee();
};


#endif //_EMPLOYEE_