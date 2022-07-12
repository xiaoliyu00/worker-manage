#pragma once//防止头文件重复包含
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
*功能:
*与用户的沟通菜单界面
*对职工增删改查的操作
*与文件的读写交互
*/
//class Employee;
class workManager
{
public:
	//无参数构造函数
	workManager();

	//菜单展示函数
	void Show_Menu();
	
	//选项
	void Choice_Putton();

	//退出系统
	void Exit_System();

	//添加员工
	void Add_Worker();

	//保存数据到文本文档
	void Save_Data();

	//获取当前文件中员工人数
	int Get_EmpNum();

	//初始化信息，将文件中内容保存到指定数组
	void Init_Worker();

	//显示信息
	void   Display_Information();

	//删除员工
	void Remove_Worker();

	//修改员工信息
	void Mod_Worker();

	//查找指定员工信息
	void Find_Worker();

	//按照编号排序
	void Sort_Worker();

	//清空数据
	void Clear_Worker();

	//析构函数
   ~workManager();

public:
	//记录职工人数
	 int m_EmpNum;

	 //职工数组指针
	 //注意指针类型需要释放
	Worker ** m_EmpArray;

	//标志文件是否为空
	bool m_FileIsEmpty;
};


#endif