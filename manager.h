#pragma once//��ֹͷ�ļ��ظ�����
#ifndef _MANAGER_
#define _MANAGER_

#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

//Ա���� 
class Manager:public Worker
{
public:
	//���캯��
	Manager(int id,string name,int dId);

	//��ʾ������Ϣ
	virtual void Show_Info();

	//��ȡְ����λ����
	virtual string Get_Dept_Name();

};


#endif //_MANAGER_