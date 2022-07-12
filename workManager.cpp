#include "workManager.h"

workManager::workManager()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	
	//1.文件不存在情况
	if(!ifs.is_open())
	{
		cout<<"文件不存在"<<endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//2.文件存在，内容为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout<<"文件为空！"<<endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件标识
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.存在文件，文件中有内容，输出人员个数
	int num = this->Get_EmpNum();
	cout<<"职工人数为： "<<num<<endl;
	this->m_EmpNum = num;
	//初始化信息
	this->Init_Worker();
}

void workManager::Show_Menu()
{
	cout<<"*******************************"<<endl;
	cout<<"******欢迎使用职工管理系统******"<<endl;
	cout<<"******0.退出程序******"<<endl;
	cout<<"******1.增加职工信息******"<<endl;
	cout<<"******2.显示职工信息******"<<endl;
	cout<<"******3.删除离职职工******"<<endl;
	cout<<"******4.修改职工信息******"<<endl;
	cout<<"******5.查找职工信息******"<<endl;
	cout<<"******6.按照编号排序******"<<endl;
	cout<<"******7.清空所有数据******"<<endl;
	cout<<"*******************************"<<endl;
	cout<<endl;
}

//选项
void workManager::Choice_Putton()
{
	int choice = 0;//存储用户选项
	while(true)
	{
		this->Show_Menu();
		cout<<"请输入您的选择！！！"<<endl;
		cin >> choice;//接受选项
		//m_choice = choice;
		switch(choice)
		{
		case 0://退出系统
			this->Exit_System();
			break;
		case 1://增加职工
			this->Add_Worker();
			break;
		case 2://显示职工
			this->Display_Information();
			break;
		case 3://删除职工
			this->Remove_Worker();
			break;
		case 4://修改职工
			this->Mod_Worker();
			break;
		case 5://查找职工
			this->Find_Worker();
			break;
		case 6://排序职工
			this->Sort_Worker();
			break;
		case 7://清空文件
			this->Clear_Worker();
			break;
		default:
			system("cls");
			break;
		}
	}
}

void workManager::Exit_System()
{
	cout<<"您选择退出系统！！！"<<endl;
	system("pause");
	exit(0);
}

void workManager::Add_Worker()
{
	cout<<"请输入增加职工数量:  "<<endl;

	int addNum = 0;
	cin>>addNum;

	if(addNum > 0)
	{
		//计算新的空间大小
		int newSize = 0;
		if (this->m_EmpNum > 0 )
		{
			newSize = this->m_EmpNum + addNum;
		}else{
			newSize = addNum;
		}
		

		//开辟新空间
		// ** 表示指针的指针，*表示指针
		Worker ** newSpace = new Worker*[newSize];

		//将原空间下内容存放到新空间下
		if(this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for(int i = 0; i < addNum;i++)
		{
			
			int id;
			string name;
			int dSelect;

			cout<<"请输入第 "<<i + 1<<" 个新员工编号: "<<endl;
			cin >>id;

			//查重
			for (int j = 0; j < (this->m_EmpNum+i); j++)
			{
				if(id == newSpace[j]->m_Id)
				{
					cout<<"该员工编号重复"<<endl;
					cout<<"请重新输入该员工编号"<<endl;
					cin>>id;
				}
			}

			cout<<"请输入第 "<<i + 1<<" 个新职工姓名: "<<endl;
			cin >>name;
			
			//查重
			for (int j = 0; j < (this->m_EmpNum+i); j++)
			{
				if(name == newSpace[j]->m_Name)
				{
					cout<<"该员工姓名重复"<<endl;
					cout<<"请重新输入该员工姓名"<<endl;
					cin>>name;
				}
			}

			cout<<"请选择该员工的岗位:  "<<endl;
			cout<<"1.普通职工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;

			cin>>dSelect;
			Worker * worker = NULL;
			switch(dSelect)
			{
				//利用多态的优点
			case 1://普通员工
				worker = new Employee(id,name,1);
				break;
			case 2://经理
				worker = new Manager(id,name,2);
				break;
			case 3://老板
				worker = new Boss(id,name,3);
				break;
			}

			newSpace[this->m_EmpNum+i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更改新空间的大小
		this->m_EmpNum = newSize;

		//文件是否存在
		this->m_FileIsEmpty = false;

		//保存信息
		this->Save_Data();

		//提示信息
		cout<<"成功添加"<<addNum<<"名员工"<<endl;
	}
	else
	{
		cout<<"输入有误"<<endl;
	}
	
	system("pause");
	system("cls");
}

void workManager::Save_Data()
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out);//写文件

	//将每个人数据写入到文件中
	for (int i = 0; i < this->m_EmpNum;i++)
	{
		ofs<<this->m_EmpArray[i]->m_Id << " "
			<<this->m_EmpArray[i]->m_Name<< " "
			<<this->m_EmpArray[i]->m_DeptId<<endl;
	}

	//关闭
	ofs.close();

}

int workManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//打开文件

	int id;
	string name;
	int dId;

	int num = 0;
	while(ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	return  num;
}

void workManager::Init_Worker()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	Worker ** newSpace = new Worker*[this->m_EmpNum];
	while(ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;
		switch(dId)
		{
		case 1://普通员工
			worker = new Employee(id,name,dId);
			break;
		case 2://经理
			worker = new Manager(id,name,dId);
			break;
		case 3://老板
			worker = new Boss(id,name,dId);
			break;
		}

		newSpace[num++] = worker;
	}

	//更改新空间的指向
	this->m_EmpArray = newSpace;

}

void   workManager::Display_Information()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"文件不存在或文件为空！！！"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"显示员工信息"<<endl;
		//将每个人数据写入到文件中
		for (int i = 0; i < this->m_EmpNum;i++)
		{
			cout<<"员工编号："<<this->m_EmpArray[i]->m_Id << " "
				<<"员工姓名："<<this->m_EmpArray[i]->m_Name<< " "
				<<"员工职位等级："<<this->m_EmpArray[i]->m_DeptId<<endl;
		}
		system("pause");
		system("cls");
	}
}

void workManager::Remove_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"文件不存在或文件为空！！！"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"请输入待删除员工数量:  "<<endl;
		int removeNum = 0;
		cin>>removeNum;

		//保证删除个数不能大于原有数据个数
		if(removeNum > 0 && this->m_EmpNum >= removeNum)
		{
			//删除数据
			for(int i = 0; i < removeNum;i++)
			{
				cout<<"请输入第 "<<i + 1<<" 名待删除员工信息标识: "<<endl;
				cout<<"1.员工编号"<<endl;
				cout<<"2.员工姓名"<<endl;
				bool flag = false;
				int choice; 
				cin>>choice;
				switch(choice)
				{
				case 1://员工编号
					cout<<"请输入待删除员工编号"<<endl;
					int id;
					cin>>id;
					for (int i = 0; i < this->m_EmpNum;i++)
					{
						if(id == this->m_EmpArray[i]->m_Id)
						{
							while (i < this->m_EmpNum-1)
							{
								this->m_EmpArray[i] = this->m_EmpArray[i+1];//依次用后续一个元素覆盖前一个元素，直到数组尾。
								i++;
							}
							flag = true;
							this->m_EmpNum--;
						}
					}
					if (flag == false)
					{
						cout<<"没有该员工编号，请核对后重新输入！！！"<<endl;
						return;
					}
					break;
				case 2://员工姓名
					cout<<"请输入待删除员工姓名"<<endl;
					string name; 
					cin>>name;
					for (int i = 0; i < this->m_EmpNum; i++)
					{
						if(name == this->m_EmpArray[i]->m_Name)
						{
							while (i < this->m_EmpNum-1)
							{
								this->m_EmpArray[i] = this->m_EmpArray[i+1];//依次用后续一个元素覆盖前一个元素，直到数组尾。
								i++;
							}
							flag = true;
							this->m_EmpNum--;
						}
					}
					if (flag == false)
					{
						cout<<"没有该员工姓名，请核对后重新输入！！！"<<endl;
						return;
					}
					break;
				}
			}
			//保存信息
			this->Save_Data();

			//提示信息
			cout<<"成功删除"<<removeNum<<"名员工"<<endl;	
		}
		else
		{
			cout<<"输入有误"<<endl;
		}
		system("pause");
		system("cls");
	}

}

void workManager::Mod_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"文件不存在或文件为空！！！"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"请输入待修改员工数量:  "<<endl;
		int modNum = 0;
		cin>>modNum;

		//保证修改个数不能大于原有数据个数
		if(modNum > 0 && this->m_EmpNum >= modNum)
		{
			//修改数据
			for(int i = 0; i < modNum;i++)
			{
				int id;
				string name;
				int dId;
				bool flag = false;
				int choice;
				cout<<"请输入第 "<<i + 1<<" 名待修改员工信息标识: "<<endl;
				cout<<"1.员工编号"<<endl;
				cout<<"2.员工姓名"<<endl;
				cin>>choice;
				switch(choice)
				{
				case 1://员工编号
					{
						cout<<"请输入待修改员工编号"<<endl;

						int id;
						cin>>id;
						for (int i = 0; i < this->m_EmpNum;i++)
						{
							if(id == this->m_EmpArray[i]->m_Id)
							{

								cout<<"请输入待修改员工信息"<<endl;
								cout<<"请输入修改后员工编号:"<<endl;
								cin>>id;
								cout<<"请输入修改后员工姓名:"<<endl;
								cin>>name;
								cout<<"请输入修改后员工职位:"<<endl;
								cin>>dId;

								//判断编号姓名是否重复
								for (int j = 0; j < this->m_EmpNum; ++j)
								{
									if(id != this->m_EmpArray[j]->m_Id || name != this->m_EmpArray[j]->m_Name)
									{
										this->m_EmpArray[i]->m_Id = id;
										this->m_EmpArray[i]->m_Name = name;
										this->m_EmpArray[i]->m_DeptId = dId;
										flag = true;
									}else{
										if(name == this->m_EmpArray[j]->m_Name)
										{
											cout<<"该员工姓名重复"<<endl;
											cout<<"请重新输入该员工姓名"<<endl;
											cin>>name;
										}
										else if(id == this->m_EmpArray[j]->m_Id)
										{
											cout<<"该员工编号重复"<<endl;
											cout<<"请重新输入该员工编号"<<endl;
											cin>>id;
										}else{
											cout<<"该员工编号姓名均重复"<<endl;
											cout<<"请重新输入该员工编号"<<endl;
											cin>>id;
											cout<<"请重新输入该员工姓名"<<endl;
											cin>>name;
										}
									}
								}
							}
						}
						if (flag == false)
						{
							cout<<"没有该员工编号，请核对后重新输入！！！"<<endl;
							return;
						}
					}				
					break;
				case 2://员工姓名
					{
						cout<<"请输入待修改员工姓名"<<endl;
						string name; 
						cin>>name;
						for (int i = 0; i < this->m_EmpNum; i++)
						{
							if(name == this->m_EmpArray[i]->m_Name)
							{
								cout<<"请输入待修改员工信息"<<endl;
								cout<<"请输入修改后员工编号:"<<endl;
								cin>>id;
								cout<<"请输入修改后员工姓名:"<<endl;
								cin>>name;
								cout<<"请输入修改后员工职位:"<<endl;
								cin>>dId;

								//判断编号姓名是否重复
								for (int j = 0; j < this->m_EmpNum; ++j)
								{
									if(id != this->m_EmpArray[j]->m_Id || name != this->m_EmpArray[j]->m_Name)
									{
										this->m_EmpArray[i]->m_Id = id;
										this->m_EmpArray[i]->m_Name = name;
										this->m_EmpArray[i]->m_DeptId = dId;
										flag = true;
									}else{
										if(name == this->m_EmpArray[j]->m_Name)
										{
											cout<<"该员工姓名重复"<<endl;
											cout<<"请重新输入该员工姓名"<<endl;
											cin>>name;
										}
										else if(id == this->m_EmpArray[j]->m_Id)
										{
											cout<<"该员工编号重复"<<endl;
											cout<<"请重新输入该员工编号"<<endl;
											cin>>id;
										}else{
											cout<<"该员工编号姓名均重复"<<endl;
											cout<<"请重新输入该员工编号"<<endl;
											cin>>id;
											cout<<"请重新输入该员工姓名"<<endl;
											cin>>name;
										}
									}
								}
							}
						}
						if (flag == false)
						{
							cout<<"没有该员工姓名，请核对后重新输入！！！"<<endl;
							return;
						}
					}
					break;
				}
			}
			//保存信息
			this->Save_Data();

			//提示信息
			cout<<"成功修改"<<modNum<<"名员工"<<endl;	
		}
		system("pause");
		system("cls");
	}
}

void workManager::Find_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"文件不存在或文件为空！！！"<<endl;
		system("pause");
		system("cls");
	}

	cout<<"待查找员工信息标识: "<<endl;
	cout<<"1.员工编号"<<endl;
	cout<<"2.员工姓名"<<endl;
	bool flag = false;
	int choice; 
	cin>>choice;
	switch(choice)
	{
	case 1://员工编号
		cout<<"请输入查找员工编号"<<endl;
		int id;
		cin>>id;
		for (int i = 0; i < this->m_EmpNum;i++)
		{
			if(id == this->m_EmpArray[i]->m_Id)
			{
				cout<<"员工编号："<<this->m_EmpArray[i]->m_Id << " "
					<<"员工姓名："<<this->m_EmpArray[i]->m_Name<< " "
					<<"员工职位等级："<<this->m_EmpArray[i]->m_DeptId<<endl;
				flag = true;
			}

		}
		if (flag == false)
		{
			cout<<"没有该员工编号，请核对后重新输入！！！"<<endl;
			return;
		}
		break;
	case 2://员工姓名
		cout<<"请输入查找员工姓名"<<endl;
		string name; 
		cin>>name;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if(name == this->m_EmpArray[i]->m_Name)
			{
				cout<<"员工编号："<<this->m_EmpArray[i]->m_Id << " "
					<<"员工姓名："<<this->m_EmpArray[i]->m_Name<< " "
					<<"员工职位等级："<<this->m_EmpArray[i]->m_DeptId<<endl;
				flag = true;
			}
		}

		if (flag == false)
		{
			cout<<"没有该员工姓名，请核对后重新输入！！！"<<endl;
			return;
		}
		break;
	}

	system("pause");
	system("cls");
}

void workManager::Sort_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"文件不存在或文件为空！！！"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"请选择排序方式："<<endl;
		cout<<"1.按照职工编号升序排列"<<endl;
		cout<<"2.按照职工编号降序排列"<<endl;
		int choice;
		cin>>choice;
		//选择排序
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOriMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (choice == 1)
				{
					if(this->m_EmpArray[minOriMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOriMax = j;
					}
				}
				else//降序
				{
					if(this->m_EmpArray[minOriMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOriMax = j;
					}
				}
			}

			if (i != minOriMax)
			{
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOriMax];
				this->m_EmpArray[minOriMax] = temp;
			}
		}
		cout<<"排序成功！！！"<<endl;
		cout<<"排序后结果为："<<endl;
		this->Save_Data();
		this->Display_Information();
	}
}

void workManager::Clear_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"文件不存在或文件为空！！！"<<endl;
		system("pause");
		system("cls");
	}else{
		
		cout<<"确认将员工数据清空！！！"<<endl;
		cout<<"1.确认"<<endl;
		cout<<"2.返回"<<endl;
	    int choice;
		cin>>choice;
		if (choice == 1)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				Worker * temp = NULL;
				this->m_EmpArray[i] = temp;
			}
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
			cout<<"员工数据已清空！！！"<<endl;
			this->Save_Data();
			system("pause");
			system("cls");
		}
		else
		{
			system("pause");
			system("cls");
		}
	}
}

workManager::~workManager()
{
	//释放内存
	if (this->m_EmpArray != NULL)
	{
		delete [] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}