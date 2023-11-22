#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

struct HNode
{
	int weight; // ���Ȩֵ
	int parent; // ˫�������±�
	int LChild; // ���������±�
	int RChild; // �Һ��������±�
};

struct HCode
{
	char data{};
	string code;
};

class HuffmanTree {
private:
	HNode* HTree; // ��������
	HCode* HCodeTable; // �洢�����
	int N; // Ҷ�ӽ������
	void code(int i, string newcode); // �ݹ麯�����Ե�i��������
	void SelectMin(int* px, int* py, int i);
public:
	void CreateHTree(int weight[], int n, char ch[]); // ������������
	void CreateCodetable(); // ���������
	void Encode(char* strcode, char* strch); // ����
	string Encode(string strch); // ����
	void Decode(char* s, char* d); // ����
	string Decode(string strcode); // ����
	void DisplayTable();
	void DisplayTree();
	~HuffmanTree();
};

void HuffmanTree::SelectMin(int* px, int* py, int num)
{
	int min1 = -1;
	int pmin = 0;
	for (int i = 0; i < num; i++)
	{
		if (HTree[i].parent == -1 && min1 == -1) {
			min1 = HTree[i].weight;
			pmin = i;
		}
		if (HTree[i].weight < min1 && HTree[i].parent == -1)
		{
			pmin = i;
			min1 = HTree[i].weight;
		}
	}
	*px = pmin;
	min1 = -1;
	for (int i = 0; i < num; i++)
	{
		if (HTree[i].parent == -1 && min1 == -1 && i != *px) {
			min1 = HTree[i].weight;
			pmin = i;
		}
		if (HTree[i].weight < min1 && HTree[i].parent == -1 && i != *px)
		{
			pmin = i;
			min1 = HTree[i].weight;
		}
	}
	*py = pmin;
}

void HuffmanTree::CreateHTree(int weight[], int n, char ch[])
{
	N = n;
	HCodeTable = new HCode[N];
	HTree = new HNode[2 * N - 1];
	for (int i = 0; i < N; i++)
	{
		HTree[i].weight = weight[i];
		HTree[i].LChild = HTree[i].RChild = HTree[i].parent = -1;
		HCodeTable[i].data = ch[i];
	}
	int x, y;
	for (int i = n; i < 2 * N - 1; i++)
	{
		SelectMin(&x, &y, i);
		HTree[x].parent = HTree[y].parent = i;
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].LChild = x;
		HTree[i].RChild = y;
		HTree[i].parent = -1;
	}
}

void HuffmanTree::code(int i, string newcode)
{
	if (HTree[i].LChild == -1)
	{
		HCodeTable[i].code = newcode;
		return;
	}
	code(HTree[i].LChild, newcode + "0");
	code(HTree[i].RChild, newcode + "1");
}

void HuffmanTree::CreateCodetable()
{
	code(2 * N - 2, "");
}

void HuffmanTree::Encode(char* strcode, char* strch)
{
	string str = "";
	while (*strch != '\0')
	{
		int j = 0;
		while (HCodeTable[j].data != *strch)
		{
			j++;
			if (j >= N)throw"error!";
		}
		strch++;
		str = str + HCodeTable[j].code;
	}
	strcpy(strcode, str.c_str());
}

string HuffmanTree::Encode(string strch)
{
	string str = "";
	for (int i = 0; i < int(strch.size()); i++)
	{
		int j = 0;
		while (HCodeTable[j].data != strch[i])
		{
			j++;
			if (j >= N)throw"error!";
		}
		str = str + HCodeTable[j].code;
	}
	return str;
}

void HuffmanTree::Decode(char* strcode, char* strch)
{
	while (*strcode != '\0')
	{
		int parent = 2 * N - 2;
		while (HTree[parent].LChild != -1)
		{
			if (*strcode == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			strcode++;
		}
		*strch = HCodeTable[parent].data;
		strch++;
	}
	*strch = '\0';
}

string HuffmanTree::Decode(string strcode)
{
	string str = "";
	int i = 0;
	while (i < int(strcode.size()))
	{
		int parent = 2 * N - 2;
		while (HTree[parent].LChild != -1)
		{
			if (strcode[i] == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			i++;
		}
		str = str + HCodeTable[parent].data;
	}
	return str;
}

void HuffmanTree::DisplayTable()
{
	for (int i = 0; i < N; i++)
	{
		cout << "data:" << HCodeTable[i].data << ' ' << "code:" << HCodeTable[i].code << endl;
	}
}

void HuffmanTree::DisplayTree()
{
	for (int i = 0; i < 2 * N - 1; i++)
	{
		cout << "LChild:" << HTree[i].LChild << ' ' << "RChild:" << HTree[i].RChild << ' '
			<< "parent:" << HTree[i].parent << ' ' << "weight:" << HTree[i].weight << endl;
	}
}

HuffmanTree::~HuffmanTree()
{
	delete[]HTree;
	delete[]HCodeTable;
}

#endif
