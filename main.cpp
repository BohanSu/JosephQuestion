#include <iostream>
using namespace std;

template <typename T>
struct LinkNode //�������ݽ������
{
	T data; //���������
	LinkNode* next; //ָ����һ�����
	LinkNode() :next(NULL) {} //���캯��
	LinkNode(T d) :data(d), next(NULL) {} //���ع��캯��
};

template <typename T>
class LinkQueue //������ģ��
{
public:
	LinkNode<T>* front; //��ͷָ��
	LinkNode<T>* rear; //��βָ��
	//���еĻ��������㷨
	LinkQueue() //���캯��
	{
		front = NULL; //��Ϊ����ͷ���Ŀյ�����
		rear = NULL;
	}
	~LinkQueue() //��������
	{
		LinkNode<T>* pre = front, * p;
		if (pre != NULL) //�ǿնӵ����
		{
			if (pre == rear) //ֻ��һ�����ݽ������
				delete pre; //�ͷ�pre���
			else //�������������ݽ������
			{
				p = pre->next;
				while (p != NULL)
				{
					delete pre; //�ͷ�pre���
					pre = p; p = p->next; //pre��pͬ������
				}
				delete pre; //�ͷ�β���
			}
		}
	}
	bool push(T e) //��������
	{
		LinkNode<T>* p = new LinkNode<T>(e);
		if (rear == NULL) //������Ϊ�յ����
			front = rear = p; //�½����Ƕ��׽�����Ƕ�β���
		else //�����Ӳ��յ����
		{
			rear->next = p; //��p���������β,����rearָ����
			rear = p;
		}
		return true;
	}
	bool pop(T& e) //��������
	{
		if (rear == NULL) //����Ϊ��
			return false;
		LinkNode<T>* p = front; //pָ���׽��
		if (front == rear) //������ֻ��һ�����ʱ
			front = rear = NULL;
		else //�������ж�����ʱ
			front = front->next;
		e = p->data;
		delete p; //�ͷų��ӽ��
		return true;
	}
	bool gethead(T& e) //ȡ��ͷ����
	{
		if (rear == NULL) //����Ϊ��
			return false;
		e = front->data; //ȡ�׽��ֵ
		return true;
	}
};

int Jsequence(int n, int m)
{
	int x = 0;
	LinkQueue<int> qu; //����һ������
	for (int i = 1; i <= n; i++) //���ӱ��Ϊ1��n��n��
		qu.push(i);
	for (int i = 1; i <= n; i++) //������n��
	{
		int j = 1;
		while (j <= m - 1) //����m-1�����������ǽ���
		{
			qu.pop(x);
			qu.push(x);
			j++;
		}
		qu.pop(x); //���ӵ�m��
		cout << x << " ";
	}
	cout << endl;
	return x;
}

int main()
{
	int n;
	int m;
	cout << "Լɪ�����⣺С������n��number of kids����";
	cin >> n;
	cout << "Լɪ�����⣺����m��number for cycle����";
	cin >> m;
	cout << "��������(The sequence of exiting the queue)��";
	int Lastkid = Jsequence(n, m);
	printf("�����ӵ�С��(The last child to leave the queue)��%d", Lastkid);
}