#include <iostream>
using namespace std;

template <typename T>
struct LinkNode //链队数据结点类型
{
	T data; //结点数据域
	LinkNode* next; //指向下一个结点
	LinkNode() :next(NULL) {} //构造函数
	LinkNode(T d) :data(d), next(NULL) {} //重载构造函数
};

template <typename T>
class LinkQueue //链队类模板
{
public:
	LinkNode<T>* front; //队头指针
	LinkNode<T>* rear; //队尾指针
	//队列的基本运算算法
	LinkQueue() //构造函数
	{
		front = NULL; //置为不带头结点的空单链表
		rear = NULL;
	}
	~LinkQueue() //析构函数
	{
		LinkNode<T>* pre = front, * p;
		if (pre != NULL) //非空队的情况
		{
			if (pre == rear) //只有一个数据结点的情况
				delete pre; //释放pre结点
			else //有两个或多个数据结点的情况
			{
				p = pre->next;
				while (p != NULL)
				{
					delete pre; //释放pre结点
					pre = p; p = p->next; //pre、p同步后移
				}
				delete pre; //释放尾结点
			}
		}
	}
	bool push(T e) //进队运算
	{
		LinkNode<T>* p = new LinkNode<T>(e);
		if (rear == NULL) //若链队为空的情况
			front = rear = p; //新结点既是队首结点又是队尾结点
		else //若链队不空的情况
		{
			rear->next = p; //将p结点链到队尾,并将rear指向它
			rear = p;
		}
		return true;
	}
	bool pop(T& e) //出队运算
	{
		if (rear == NULL) //队列为空
			return false;
		LinkNode<T>* p = front; //p指向首结点
		if (front == rear) //队列中只有一个结点时
			front = rear = NULL;
		else //队列中有多个结点时
			front = front->next;
		e = p->data;
		delete p; //释放出队结点
		return true;
	}
	bool gethead(T& e) //取队头运算
	{
		if (rear == NULL) //队列为空
			return false;
		e = front->data; //取首结点值
		return true;
	}
};

int Jsequence(int n, int m)
{
	int x = 0;
	LinkQueue<int> qu; //定义一个链队
	for (int i = 1; i <= n; i++) //进队编号为1到n的n个
		qu.push(i);
	for (int i = 1; i <= n; i++) //共出列n个
	{
		int j = 1;
		while (j <= m - 1) //出队m-1个，并将他们进队
		{
			qu.pop(x);
			qu.push(x);
			j++;
		}
		qu.pop(x); //出队第m个
		cout << x << " ";
	}
	cout << endl;
	return x;
}

int main()
{
	int n;
	int m;
	cout << "约瑟夫问题：小孩数量n（number of kids）：";
	cin >> n;
	cout << "约瑟夫问题：报数m（number for cycle）：";
	cin >> m;
	cout << "出队序列(The sequence of exiting the queue)：";
	int Lastkid = Jsequence(n, m);
	printf("最后出队的小孩(The last child to leave the queue)：%d", Lastkid);
}