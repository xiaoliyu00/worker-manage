#pragma once//防止头文件重复包含
#ifndef _BOSS_
#define _BOSS_

#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

//员工类 
class Boss:public Worker
{
public:
	//构造函数
	Boss(int id,string name,int dId);

	//显示个人信息
	virtual void Show_Info();

	//获取职工岗位名称
	virtual string Get_Dept_Name();

};


#endif //_BOSS_