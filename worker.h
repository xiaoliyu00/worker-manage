#pragma once//��ֹͷ�ļ��ظ�����
#ifndef _WORKER_
#define _WORKER_

#include <iostream>
using namespace std;

//ְ��������
//���ö�̬����ְͬ������
//��λְ����Ϣ��������ȡ��λ����

class Worker
{
public:
	//���캯��
	//Worker();

	//��ʾ������Ϣ
	virtual void Show_Info() = 0;

	//��ȡְ����λ����
	virtual string Get_Dept_Name() = 0;

public:
	int m_Id;//ְ�����

	string m_Name;//ְ������

	int m_DeptId;//ְ�����ڲ��ű��

	//virtual ~Worker();
};
#endif //_WORKER_