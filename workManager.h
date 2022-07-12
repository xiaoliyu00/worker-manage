#pragma once//��ֹͷ�ļ��ظ�����
#ifndef _WORKMANAGER_
#define _WORKMANAGER_
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#include <ostream>
using namespace std;

#define FILENAME "E:\\c++_workspace\\code_practice\\empFile.txt"

/*
*����:
*���û��Ĺ�ͨ�˵�����
*��ְ����ɾ�Ĳ�Ĳ���
*���ļ��Ķ�д����
*/
//class Employee;
class workManager
{
public:
	//�޲������캯��
	workManager();

	//�˵�չʾ����
	void Show_Menu();
	
	//ѡ��
	void Choice_Putton();

	//�˳�ϵͳ
	void Exit_System();

	//���Ա��
	void Add_Worker();

	//�������ݵ��ı��ĵ�
	void Save_Data();

	//��ȡ��ǰ�ļ���Ա������
	int Get_EmpNum();

	//��ʼ����Ϣ�����ļ������ݱ��浽ָ������
	void Init_Worker();

	//��ʾ��Ϣ
	void   Display_Information();

	//ɾ��Ա��
	void Remove_Worker();

	//�޸�Ա����Ϣ
	void Mod_Worker();

	//����ָ��Ա����Ϣ
	void Find_Worker();

	//���ձ������
	void Sort_Worker();

	//�������
	void Clear_Worker();

	//��������
   ~workManager();

public:
	//��¼ְ������
	 int m_EmpNum;

	 //ְ������ָ��
	 //ע��ָ��������Ҫ�ͷ�
	Worker ** m_EmpArray;

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
};


#endif