#include "manager.h"

Manager::Manager(int id,string name,int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

void Manager::Show_Info()
{
	cout<<"ְ�����: "<<this->m_Id
		<<"\tְ������: "<<this->m_Name
		<<"\t��λ: "<<this->Get_Dept_Name()<<endl;
}

string Manager::Get_Dept_Name()
{
	return string("����");
}