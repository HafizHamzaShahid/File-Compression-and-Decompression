//Huffman Coding
//             Input file name === input.txt
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<map>
using namespace std;

struct Huffmanode
{
	int freq;
	char data;
	string code;
	Huffmanode* Left;
	Huffmanode* Right;

	Huffmanode()
	{
		freq = 0;
		data = '0';
		code = '0';
		Left = Right = NULL;
	}
	Huffmanode(char s)
	{
		this->data = s;
		this->freq = 0;
		code = '0';
		Left = Right = NULL;
	}
	char getdata()
	{
		return data;
	}
	Huffmanode(int f, char s)
	{
		this->data = s;
		this->freq = f;
		code = '0';
		Left = Right = NULL;
	}
	Huffmanode(char s, string c)
	{
		this->data = s;
		code = c;
		Left = Right = NULL;
	}
};
class Huffman
{
public:
	class compare
	{
		//a object funtion to set comparing rule of priority queue
	public:
		bool operator()(const Huffmanode* c1, const Huffmanode* c2) const
		{
			return c1->freq > c2->freq;
		}
	};

	Huffmanode* root;
	priority_queue<Huffmanode*, vector<Huffmanode*>, compare> q;

	Huffman()
	{
		root = NULL;
	}
	vector<pair<int, char>> CalFreq(string s)
	{
		map<char, int> m1;
		for (int i = 0; i < s.size(); i++)
		{
			m1[s[i]]++;
		}
		vector<pair<int, char>> v1;
		for (int i = 0; i < s.size(); i++)
		{
			if (m1[s[i]] != 0)
			{
				v1.push_back(make_pair(m1[s[i]], s[i]));
				m1[s[i]] = 0;
			}
		}
		return v1;
	}
	vector<pair<int, char>> CalFreq()
	{
		map<char, int> m1;
		string s;
		fstream in_file;
		char id;
		in_file.open("input.txt", ios::in);
		in_file.get(id);
		while (!in_file.eof())
		{
			m1[id]++;
			in_file.get(id);
		}
		in_file.close();
		vector<pair<int, char>> v1;
		for (int i = 0; i < 128; i++)
		{
			if (m1[i] != 0)
			{
				v1.push_back(make_pair(m1[i], i));
				m1[i] = 0;
			}
		}
		return v1;
	}
	void PrintFreq()
	{
		map<char, int> m1;
		string s;
		fstream in_file;
		char id;
		in_file.open("input.txt", ios::in);
		in_file.get(id);
		while (!in_file.eof())
		{
			m1[id]++;
			in_file.get(id);
		}
		in_file.close();
		vector<pair<int, char>> v1;
		for (int i = 0; i < 128; i++)
		{
			if (m1[i] != 0)
			{
				v1.push_back(make_pair(m1[i], i));
				m1[i] = 0;
			}
		}
		cout << "Frequencies are Given Below \n";
		cout << endl;
		cout << "----------------------------------" << endl;
		for (int i = 0; i < v1.size(); i++)
		{
			if (v1[i].second == '\n')
			{
				cout << v1[i].first << "NewLineCharacter ";
			}
			else if (v1[i].second == ' ')
			{
				cout << v1[i].first << "Space ";
			}
			else
				cout << v1[i].first << v1[i].second;
			cout << endl;
		}
		cout << "----------------------------------" << endl;
	}
	void Print(priority_queue<Huffmanode*, vector<Huffmanode*>, compare>& q)
	{
		while (q.size() > 1)
		{
			cout << q.top()->data << " " << q.top()->freq << endl;
		}
	}
	Huffmanode* BuildTree(vector<pair<int, char>>& f)
	{
		//push into priority quee
		for (int i = 0; i < f.size(); i++)
		{
			q.push(new Huffmanode(f[i].first, f[i].second));
		}
		//Print(q);
		while (q.size() > 1)
		{
			Huffmanode* left = q.top();
			q.pop();
			Huffmanode* right = q.top();
			q.pop();

			Huffmanode* sum = new Huffmanode(left->freq + right->freq, '$');
			//sum->data = left->data + right->data;
			sum->Left = left;
			sum->Right = right;
			q.push(sum);
		}

		return q.top();
	}
	void InOrderTraversal(Huffmanode* root)
	{
		if (root)
		{
			InOrderTraversal(root->Left);
			cout << root->freq << endl;
			InOrderTraversal(root->Right);
		}
	}
	int TotalElement()
	{
		int k = 0;
		fstream in_file;
		in_file.open("input.txt", ios::in);
		char id;
		in_file.get(id);
		while (!in_file.eof())
		{
			k++;
			in_file.get(id);
		}
		in_file.close();
		return k;
	}
	string TotalElementAccess()
	{
		string s = "";
		fstream in_file;
		in_file.open("input.txt", ios::in);
		char id;
		in_file.get(id);
		while (!in_file.eof())
		{
			s = s + id;
			in_file.get(id);
		}
		in_file.close();
		return s;
	}
	void PrintLevelOrder(Huffmanode* root)
	{
		if (!root) {
			return;
		}
		queue<Huffmanode*> queue;
		queue.push(root);

		ofstream file;
		file.open("tree.txt");
		while (queue.empty() == false) {

			int size = queue.size();
			
			while (size > 0)
			{
				Huffmanode* curr = queue.front();
				queue.pop();

				file << curr->data << " " << curr->freq << " ";

				if (curr->Left) {
					queue.push(curr->Left);
				}

				if (curr->Right) {
					queue.push(curr->Right);
				}
				size--;
			}
			file << endl;
		}
		file.close();
	}
	char Converter(string ch)
	{
		int x = 0, sum = 0;
		for (int i = 0, j = 0; i < ch.size(); i++, j--)
		{
			x = x + (int)ch[i];
			x = x - 48;
			if (i != 7)
			{
				x = x << 1;
			}

		}
		return (char)x;
	}
	char DeConverter(string ch)
	{
		int x = 0, sum = 0;
		for (int i = 0, j = 0; i < ch.size(); i++, j--)
		{
			x = x + (int)ch[i];
			x = x - 48;
			if (i != 7)
			{
				x = x >> 1;
			}

		}
		return (char)x;
	}
	int Binary_Decimal(string& ch)
	{
		int result = 0;
		for (int i = 0; i < ch.size(); i++)
			result = result * 2 + ch[i] - '0';
		return result;
	}
	string Decimal_Binary(char data)
	{
		string temp = "";
		string result = "";
		int in = data;
		while (in)
		{
			temp += ('0' + in % 2);
			in /= 2;
		}
		result.append(8 - temp.size(), '0');													//append '0' ahead to let the result become fixed length of 8
		for (int i = temp.size() - 1; i >= 0; i--)
		{
			result += temp[i];
		}
		return result;
	}
	void GenCode(Huffmanode* node, string s, vector<pair<char, string>>& f)
	{
		if (!node)
			return;
		if (node->data != '$')
		{
			f.push_back(make_pair(node->data, s));
			return;
		}
		else
		{
			GenCode(node->Left, s + "0", f);
			GenCode(node->Right, s + "1", f);
		}
	}
	void PrintCode()
	{
		int totalelemnt = TotalElement();
		string input = TotalElementAccess();
		vector<pair<int, char>> Freq = CalFreq();
		sort(Freq.begin(), Freq.end());

		Huffmanode* Tree = BuildTree(Freq);
		vector<pair<char, string>> v2;
		GenCode(Tree, "", v2);
		string res = "";
		cout << "Code are \n";
		cout << endl;
		cout << "---------------------" << endl;
		for (int i = 0; i < v2.size(); i++)
		{
			cout << v2[i].first << " " << v2[i].second << " " << endl;
		}
		cout << "---------------------" << endl;
	}
	string Decod(Huffmanode* root1, string s, int& i)
	{
		string str = "";
		while (i <= s.size())
		{
			if (root1->data != '$')
			{
				str += root1->data;
				return str;
			}
			else if (s[i] == '0')
			{
				if (root1->Left)
				{
					root1 = root1->Left;
					i++;
				}
				else
				{
					return str;
				}
			}
			else if (s[i] == '1')
			{
				if (root1->Right)
				{
					root1 = root1->Right;
					i++;
				}
				else
				{
					return str;
				}
			}
		}
		return ""; //""
	}
	void Encode()
	{
		cout << endl;
		int totalelemnt = TotalElement();
		string input = TotalElementAccess();
		vector<pair<int, char>> Freq = CalFreq();
		sort(Freq.begin(), Freq.end());
	    Huffmanode* Tree = BuildTree(Freq);
		vector<pair<char, string>> v2;
		PrintLevelOrder(Tree);
		GenCode(Tree, "", v2);
		string res = "";
		cout << endl;
		for (int i = 0; i < totalelemnt; i++)
		{
			int k = 0;
			for (int j = 0; j < v2.size(); j++)
			{
				if (input[i] == v2[j].first && k != 1)
				{
					res += v2[j].second;
					k++;
				}
			}
		}
		cout << endl;
		ofstream save;
		save.open("Use.txt");
		save << res;
		cout << endl;
		save.close();

		string finalr = "";
		string temp;
		string ch = "";
		int p = 0;
		int q = 8;
		while (p <= res.size() + 8)
		{
			ch = "";
			for (int j = p; j < q && j < res.size(); j++)
			{
				ch +=  res[j];
			}
			p += 8;
			q += 8;

			temp = Converter(ch);

			finalr +=  temp;

		}
		cout << "\nCompressed form is\n";
		cout << "-------------------------" << endl;
		cout << finalr;
		cout << "\n-------------------------" << endl;
		cout << endl;
		ofstream sav;
		sav.open("Bin.bin");
		sav << finalr;
		cout << endl;
		sav.close();
	}
	void Decode()
	{
		string in;
		ifstream open;
		open.open("Use.txt");
		string res = "";
		string inp;
		if (open.is_open())
		{
			while (!open.eof())
			{
				open >> inp;
				res = res + inp;
			}
			open.close();
		}
		else
		{
			cout << "File Not Open" << endl;
		}
		int totalelemnt = TotalElement();
		string input = TotalElementAccess();
		vector<pair<int, char>> Freq = CalFreq();
		sort(Freq.begin(), Freq.end());
		Huffmanode* Tree = BuildTree(Freq);

		cout << endl << "Decompress Form Is \n";
		cout << "---------------------" << endl;
		string Decompress = "";
		for (int i = 0; i < res.size(); )
		{
			Decompress += Decod(Tree, res, i);
		}
		cout << Decompress << endl;
		cout << "---------------------" << endl;
		ofstream save1;
		save1.open("Decompress.txt");
		save1 << Decompress;
		cout << endl;
		save1.close();
	}
};

int main()
{
	cout << "Compression And Decompression by using Huffman Coding\n";
	cout << endl;
	cout << "Input Filename is 'input.txt' and   Bin  Filename is 'Bin.bin' \n";
	cout << "Tree  Filename is 'Tree.txt'  and Decompress File is 'Decompress.txt' ";
	cout << endl << endl << endl << endl;

	Huffman h1;

	cout << "-------------------MENU----------------" << endl;

	char opt;
	cout << "Enter 'C' for Compression      Enter 'D' for DeCompression \n";
	cout << "Enter 'F' for Frequency        Enter 'G' for Generated Code \n";
	cin >> opt;

	if (opt == 'c' || opt == 'C')
	{
		h1.Encode();
	}
	if (opt == 'D' || opt == 'd')
	{
		h1.Decode();
	}
	if (opt == 'G' || opt == 'g')
	{
		h1.PrintCode();
	}
	if (opt == 'F' || opt == 'f')
	{
		h1.PrintFreq();
	}


	system("pause");
}