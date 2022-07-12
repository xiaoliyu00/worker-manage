#include "manager.h"

Manager::Manager(int id,string name,int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

void Manager::Show_Info()
{
	cout<<"职工编号: "<<this->m_Id
		<<"\t职工姓名: "<<this->m_Name
		<<"\t岗位: "<<this->Get_Dept_Name()<<endl;
}

string Manager::Get_Dept_Name()
{
	return string("经理");
}