#include "head.h"

int main()
{
	while (true)
	{
		FileCompress test;
		string name;
		cout << "#########################################################################" << endl;
		cout << "������Ҫ�������ļ����������β׺���ɹ�ѡ����ļ�����test1��test2��test3����";
		cin >> name;
		if (name != "test1" && name != "test2" && name != "test3")
		{
			cout << "��Ч���ļ���, ����������\n" << endl;
			continue;
		}
		test.Init(name);

		string OPTR;
		cout << "���������(Compress, Uncompress, Exit)��" ;
		cin >> OPTR;
		if (OPTR == "Compress")
			test.Compress();
		else if (OPTR == "Uncompress")
			test.UnCompress();
		else if (OPTR == "Exit")
			break;
		else
			cout << "��Ч�Ĳ���" << endl;
	}

	return 0;
}