#pragma once//��ֹͷ�ļ��ظ�����
#ifndef _BOSS_
#define _BOSS_

#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

//Ա���� 
class Boss:public Worker
{
public:
	//���캯��
	Boss(int id,string name,int dId);

	//��ʾ������Ϣ
	virtual void Show_Info();

	//��ȡְ����λ����
	virtual string Get_Dept_Name();

};


#endif //_BOSS_