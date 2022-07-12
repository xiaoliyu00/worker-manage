#include "workManager.h"

workManager::workManager()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	
	//1.�ļ����������
	if(!ifs.is_open())
	{
		cout<<"�ļ�������"<<endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//2.�ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		cout<<"�ļ�Ϊ�գ�"<<endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ���ʶ
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�����ļ����ļ��������ݣ������Ա����
	int num = this->Get_EmpNum();
	cout<<"ְ������Ϊ�� "<<num<<endl;
	this->m_EmpNum = num;
	//��ʼ����Ϣ
	this->Init_Worker();
}

void workManager::Show_Menu()
{
	cout<<"*******************************"<<endl;
	cout<<"******��ӭʹ��ְ������ϵͳ******"<<endl;
	cout<<"******0.�˳�����******"<<endl;
	cout<<"******1.����ְ����Ϣ******"<<endl;
	cout<<"******2.��ʾְ����Ϣ******"<<endl;
	cout<<"******3.ɾ����ְְ��******"<<endl;
	cout<<"******4.�޸�ְ����Ϣ******"<<endl;
	cout<<"******5.����ְ����Ϣ******"<<endl;
	cout<<"******6.���ձ������******"<<endl;
	cout<<"******7.�����������******"<<endl;
	cout<<"*******************************"<<endl;
	cout<<endl;
}

//ѡ��
void workManager::Choice_Putton()
{
	int choice = 0;//�洢�û�ѡ��
	while(true)
	{
		this->Show_Menu();
		cout<<"����������ѡ�񣡣���"<<endl;
		cin >> choice;//����ѡ��
		//m_choice = choice;
		switch(choice)
		{
		case 0://�˳�ϵͳ
			this->Exit_System();
			break;
		case 1://����ְ��
			this->Add_Worker();
			break;
		case 2://��ʾְ��
			this->Display_Information();
			break;
		case 3://ɾ��ְ��
			this->Remove_Worker();
			break;
		case 4://�޸�ְ��
			this->Mod_Worker();
			break;
		case 5://����ְ��
			this->Find_Worker();
			break;
		case 6://����ְ��
			this->Sort_Worker();
			break;
		case 7://����ļ�
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
	cout<<"��ѡ���˳�ϵͳ������"<<endl;
	system("pause");
	exit(0);
}

void workManager::Add_Worker()
{
	cout<<"����������ְ������:  "<<endl;

	int addNum = 0;
	cin>>addNum;

	if(addNum > 0)
	{
		//�����µĿռ��С
		int newSize = 0;
		if (this->m_EmpNum > 0 )
		{
			newSize = this->m_EmpNum + addNum;
		}else{
			newSize = addNum;
		}
		

		//�����¿ռ�
		// ** ��ʾָ���ָ�룬*��ʾָ��
		Worker ** newSpace = new Worker*[newSize];

		//��ԭ�ռ������ݴ�ŵ��¿ռ���
		if(this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for(int i = 0; i < addNum;i++)
		{
			
			int id;
			string name;
			int dSelect;

			cout<<"������� "<<i + 1<<" ����Ա�����: "<<endl;
			cin >>id;

			//����
			for (int j = 0; j < (this->m_EmpNum+i); j++)
			{
				if(id == newSpace[j]->m_Id)
				{
					cout<<"��Ա������ظ�"<<endl;
					cout<<"�����������Ա�����"<<endl;
					cin>>id;
				}
			}

			cout<<"������� "<<i + 1<<" ����ְ������: "<<endl;
			cin >>name;
			
			//����
			for (int j = 0; j < (this->m_EmpNum+i); j++)
			{
				if(name == newSpace[j]->m_Name)
				{
					cout<<"��Ա�������ظ�"<<endl;
					cout<<"�����������Ա������"<<endl;
					cin>>name;
				}
			}

			cout<<"��ѡ���Ա���ĸ�λ:  "<<endl;
			cout<<"1.��ְͨ��"<<endl;
			cout<<"2.����"<<endl;
			cout<<"3.�ϰ�"<<endl;

			cin>>dSelect;
			Worker * worker = NULL;
			switch(dSelect)
			{
				//���ö�̬���ŵ�
			case 1://��ͨԱ��
				worker = new Employee(id,name,1);
				break;
			case 2://����
				worker = new Manager(id,name,2);
				break;
			case 3://�ϰ�
				worker = new Boss(id,name,3);
				break;
			}

			newSpace[this->m_EmpNum+i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����¿ռ�Ĵ�С
		this->m_EmpNum = newSize;

		//�ļ��Ƿ����
		this->m_FileIsEmpty = false;

		//������Ϣ
		this->Save_Data();

		//��ʾ��Ϣ
		cout<<"�ɹ����"<<addNum<<"��Ա��"<<endl;
	}
	else
	{
		cout<<"��������"<<endl;
	}
	
	system("pause");
	system("cls");
}

void workManager::Save_Data()
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out);//д�ļ�

	//��ÿ��������д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum;i++)
	{
		ofs<<this->m_EmpArray[i]->m_Id << " "
			<<this->m_EmpArray[i]->m_Name<< " "
			<<this->m_EmpArray[i]->m_DeptId<<endl;
	}

	//�ر�
	ofs.close();

}

int workManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//���ļ�

	int id;
	string name;
	int dId;

	int num = 0;
	while(ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ����������
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
		case 1://��ͨԱ��
			worker = new Employee(id,name,dId);
			break;
		case 2://����
			worker = new Manager(id,name,dId);
			break;
		case 3://�ϰ�
			worker = new Boss(id,name,dId);
			break;
		}

		newSpace[num++] = worker;
	}

	//�����¿ռ��ָ��
	this->m_EmpArray = newSpace;

}

void   workManager::Display_Information()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"�ļ������ڻ��ļ�Ϊ�գ�����"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"��ʾԱ����Ϣ"<<endl;
		//��ÿ��������д�뵽�ļ���
		for (int i = 0; i < this->m_EmpNum;i++)
		{
			cout<<"Ա����ţ�"<<this->m_EmpArray[i]->m_Id << " "
				<<"Ա��������"<<this->m_EmpArray[i]->m_Name<< " "
				<<"Ա��ְλ�ȼ���"<<this->m_EmpArray[i]->m_DeptId<<endl;
		}
		system("pause");
		system("cls");
	}
}

void workManager::Remove_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"�ļ������ڻ��ļ�Ϊ�գ�����"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"�������ɾ��Ա������:  "<<endl;
		int removeNum = 0;
		cin>>removeNum;

		//��֤ɾ���������ܴ���ԭ�����ݸ���
		if(removeNum > 0 && this->m_EmpNum >= removeNum)
		{
			//ɾ������
			for(int i = 0; i < removeNum;i++)
			{
				cout<<"������� "<<i + 1<<" ����ɾ��Ա����Ϣ��ʶ: "<<endl;
				cout<<"1.Ա�����"<<endl;
				cout<<"2.Ա������"<<endl;
				bool flag = false;
				int choice; 
				cin>>choice;
				switch(choice)
				{
				case 1://Ա�����
					cout<<"�������ɾ��Ա�����"<<endl;
					int id;
					cin>>id;
					for (int i = 0; i < this->m_EmpNum;i++)
					{
						if(id == this->m_EmpArray[i]->m_Id)
						{
							while (i < this->m_EmpNum-1)
							{
								this->m_EmpArray[i] = this->m_EmpArray[i+1];//�����ú���һ��Ԫ�ظ���ǰһ��Ԫ�أ�ֱ������β��
								i++;
							}
							flag = true;
							this->m_EmpNum--;
						}
					}
					if (flag == false)
					{
						cout<<"û�и�Ա����ţ���˶Ժ��������룡����"<<endl;
						return;
					}
					break;
				case 2://Ա������
					cout<<"�������ɾ��Ա������"<<endl;
					string name; 
					cin>>name;
					for (int i = 0; i < this->m_EmpNum; i++)
					{
						if(name == this->m_EmpArray[i]->m_Name)
						{
							while (i < this->m_EmpNum-1)
							{
								this->m_EmpArray[i] = this->m_EmpArray[i+1];//�����ú���һ��Ԫ�ظ���ǰһ��Ԫ�أ�ֱ������β��
								i++;
							}
							flag = true;
							this->m_EmpNum--;
						}
					}
					if (flag == false)
					{
						cout<<"û�и�Ա����������˶Ժ��������룡����"<<endl;
						return;
					}
					break;
				}
			}
			//������Ϣ
			this->Save_Data();

			//��ʾ��Ϣ
			cout<<"�ɹ�ɾ��"<<removeNum<<"��Ա��"<<endl;	
		}
		else
		{
			cout<<"��������"<<endl;
		}
		system("pause");
		system("cls");
	}

}

void workManager::Mod_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"�ļ������ڻ��ļ�Ϊ�գ�����"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"��������޸�Ա������:  "<<endl;
		int modNum = 0;
		cin>>modNum;

		//��֤�޸ĸ������ܴ���ԭ�����ݸ���
		if(modNum > 0 && this->m_EmpNum >= modNum)
		{
			//�޸�����
			for(int i = 0; i < modNum;i++)
			{
				int id;
				string name;
				int dId;
				bool flag = false;
				int choice;
				cout<<"������� "<<i + 1<<" �����޸�Ա����Ϣ��ʶ: "<<endl;
				cout<<"1.Ա�����"<<endl;
				cout<<"2.Ա������"<<endl;
				cin>>choice;
				switch(choice)
				{
				case 1://Ա�����
					{
						cout<<"��������޸�Ա�����"<<endl;

						int id;
						cin>>id;
						for (int i = 0; i < this->m_EmpNum;i++)
						{
							if(id == this->m_EmpArray[i]->m_Id)
							{

								cout<<"��������޸�Ա����Ϣ"<<endl;
								cout<<"�������޸ĺ�Ա�����:"<<endl;
								cin>>id;
								cout<<"�������޸ĺ�Ա������:"<<endl;
								cin>>name;
								cout<<"�������޸ĺ�Ա��ְλ:"<<endl;
								cin>>dId;

								//�жϱ�������Ƿ��ظ�
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
											cout<<"��Ա�������ظ�"<<endl;
											cout<<"�����������Ա������"<<endl;
											cin>>name;
										}
										else if(id == this->m_EmpArray[j]->m_Id)
										{
											cout<<"��Ա������ظ�"<<endl;
											cout<<"�����������Ա�����"<<endl;
											cin>>id;
										}else{
											cout<<"��Ա������������ظ�"<<endl;
											cout<<"�����������Ա�����"<<endl;
											cin>>id;
											cout<<"�����������Ա������"<<endl;
											cin>>name;
										}
									}
								}
							}
						}
						if (flag == false)
						{
							cout<<"û�и�Ա����ţ���˶Ժ��������룡����"<<endl;
							return;
						}
					}				
					break;
				case 2://Ա������
					{
						cout<<"��������޸�Ա������"<<endl;
						string name; 
						cin>>name;
						for (int i = 0; i < this->m_EmpNum; i++)
						{
							if(name == this->m_EmpArray[i]->m_Name)
							{
								cout<<"��������޸�Ա����Ϣ"<<endl;
								cout<<"�������޸ĺ�Ա�����:"<<endl;
								cin>>id;
								cout<<"�������޸ĺ�Ա������:"<<endl;
								cin>>name;
								cout<<"�������޸ĺ�Ա��ְλ:"<<endl;
								cin>>dId;

								//�жϱ�������Ƿ��ظ�
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
											cout<<"��Ա�������ظ�"<<endl;
											cout<<"�����������Ա������"<<endl;
											cin>>name;
										}
										else if(id == this->m_EmpArray[j]->m_Id)
										{
											cout<<"��Ա������ظ�"<<endl;
											cout<<"�����������Ա�����"<<endl;
											cin>>id;
										}else{
											cout<<"��Ա������������ظ�"<<endl;
											cout<<"�����������Ա�����"<<endl;
											cin>>id;
											cout<<"�����������Ա������"<<endl;
											cin>>name;
										}
									}
								}
							}
						}
						if (flag == false)
						{
							cout<<"û�и�Ա����������˶Ժ��������룡����"<<endl;
							return;
						}
					}
					break;
				}
			}
			//������Ϣ
			this->Save_Data();

			//��ʾ��Ϣ
			cout<<"�ɹ��޸�"<<modNum<<"��Ա��"<<endl;	
		}
		system("pause");
		system("cls");
	}
}

void workManager::Find_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"�ļ������ڻ��ļ�Ϊ�գ�����"<<endl;
		system("pause");
		system("cls");
	}

	cout<<"������Ա����Ϣ��ʶ: "<<endl;
	cout<<"1.Ա�����"<<endl;
	cout<<"2.Ա������"<<endl;
	bool flag = false;
	int choice; 
	cin>>choice;
	switch(choice)
	{
	case 1://Ա�����
		cout<<"���������Ա�����"<<endl;
		int id;
		cin>>id;
		for (int i = 0; i < this->m_EmpNum;i++)
		{
			if(id == this->m_EmpArray[i]->m_Id)
			{
				cout<<"Ա����ţ�"<<this->m_EmpArray[i]->m_Id << " "
					<<"Ա��������"<<this->m_EmpArray[i]->m_Name<< " "
					<<"Ա��ְλ�ȼ���"<<this->m_EmpArray[i]->m_DeptId<<endl;
				flag = true;
			}

		}
		if (flag == false)
		{
			cout<<"û�и�Ա����ţ���˶Ժ��������룡����"<<endl;
			return;
		}
		break;
	case 2://Ա������
		cout<<"���������Ա������"<<endl;
		string name; 
		cin>>name;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if(name == this->m_EmpArray[i]->m_Name)
			{
				cout<<"Ա����ţ�"<<this->m_EmpArray[i]->m_Id << " "
					<<"Ա��������"<<this->m_EmpArray[i]->m_Name<< " "
					<<"Ա��ְλ�ȼ���"<<this->m_EmpArray[i]->m_DeptId<<endl;
				flag = true;
			}
		}

		if (flag == false)
		{
			cout<<"û�и�Ա����������˶Ժ��������룡����"<<endl;
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
		cout<<"�ļ������ڻ��ļ�Ϊ�գ�����"<<endl;
		system("pause");
		system("cls");
	}else{
		cout<<"��ѡ������ʽ��"<<endl;
		cout<<"1.����ְ�������������"<<endl;
		cout<<"2.����ְ����Ž�������"<<endl;
		int choice;
		cin>>choice;
		//ѡ������
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
				else//����
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
		cout<<"����ɹ�������"<<endl;
		cout<<"�������Ϊ��"<<endl;
		this->Save_Data();
		this->Display_Information();
	}
}

void workManager::Clear_Worker()
{
	if (this->m_FileIsEmpty == true)
	{
		cout<<"�ļ������ڻ��ļ�Ϊ�գ�����"<<endl;
		system("pause");
		system("cls");
	}else{
		
		cout<<"ȷ�Ͻ�Ա��������գ�����"<<endl;
		cout<<"1.ȷ��"<<endl;
		cout<<"2.����"<<endl;
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
			cout<<"Ա����������գ�����"<<endl;
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
	//�ͷ��ڴ�
	if (this->m_EmpArray != NULL)
	{
		delete [] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}