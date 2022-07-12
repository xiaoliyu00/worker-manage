#pragma once//防止头文件重复包含
#ifndef _WORKER_
#define _WORKER_

#include <iostream>
using namespace std;

//职工抽象类
//利用多态管理不同职工种类
//岗位职责信息描述，获取岗位名称

class Worker
{
public:
	//构造函数
	//Worker();

	//显示个人信息
	virtual void Show_Info() = 0;

	//获取职工岗位名称
	virtual string Get_Dept_Name() = 0;

public:
	int m_Id;//职工编号

	string m_Name;//职工姓名

	int m_DeptId;//职工所在部门编号

	//virtual ~Worker();
};
#endif //_WORKER_