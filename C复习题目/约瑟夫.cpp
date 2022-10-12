#include <iostream>
#include <string>
using namespace std;

class Josephus
{
public:
	Josephus(int n, bool d, Josephus* nx) : num(n), isdead(d), next(nx) {}

	int num;
	bool isdead;
	Josephus* next;
};

void CreateJosephus(Josephus* head, int personnum)
{
	Josephus* cur = head;
	for(int i = 2; i <= personnum; i++)
	{
		Josephus* newnode = new Josephus(i, 0, NULL);
		cur -> next = newnode;
		cur = cur -> next;
	}
	cur -> next = head;
}

void KillMan(Josephus* head, int killstep, int personnum, int killnum)
{
	Josephus* cur = head;
	int cnt = 1, stepcnt = 0;
	while(cnt <= killnum)
	{
		if(cur -> isdead == 0)
		{
			stepcnt++;
			if(stepcnt == killstep)
			{
				cur -> isdead = 1;
				stepcnt = 0;
				cnt++;
			}
		}
		cur = cur -> next;
	}
}

void CheckAlive(Josephus* head, int personnum, int playernum)
{
	Josephus* cur = head;
	for(int i = 1; i <= personnum; i++)
	{
		string tmp = (cur -> isdead == 0) ? "没死" : "死了";
		if(i == playernum) cout << endl << "你：" << endl;
		printf("%d号位置的人 ", cur -> num);
		cout << tmp << endl;
		cur = cur -> next;
	}
}

int main()
{
	int personnum = 41, killstep = 3, killnum = 39, playernum = 0;
    while(1){
 	cout << "----约瑟夫游戏----" << endl;
 	cout << "------------------" << endl << endl;
	cout << "几个人参与游戏" << endl;
	cin >> personnum;
	cout << "你打算站在几号位置" << endl;
	cin >> playernum;
	cout << "一共杀几个人" << endl;
	cin >> killnum;
	cout << "隔几个人杀一个人" << endl;
	cin >> killstep;
	
	Josephus* head = new Josephus(1, 0, NULL);
	CreateJosephus(head, personnum);
	KillMan(head, killstep, personnum, killnum);
	CheckAlive(head, personnum, playernum);
}
	system("pause");

	return 0;
}





class LinkedList
{
public:
	LinkedList(int v, LinkedList* nx) : val(v), next(nx) {}

	int val;
	LinkedList* next;
};

void CreateLinkedList(LinkedList* head)
{
	LinkedList* cur = head;
	for(int i = 2; i <= 10; i++)
	{
		LinkedList* newnode = new LinkedList(i, NULL);
		cur -> next = newnode;
		cur = cur -> next;
	}
}

LinkedList* ReverseLinkedList(LinkedList* head)
{
	if(!head) return head;
	LinkedList* newhead = head;
	LinkedList* oldhead = head -> next;
	newhead -> next = NULL;
	
	while(oldhead)
	{
		LinkedList* tmpold = oldhead -> next;
		oldhead -> next = newhead;
		newhead = oldhead;
		oldhead = tmpold;
	}
	return newhead;
}

void CoutLinkedList(LinkedList* head)
{
	LinkedList* cur = head;
	while(cur)
	{
		cout << cur -> val << endl;
		cur = cur -> next;
	}
}

//int main()
//{
//	LinkedList* head = new LinkedList(1, NULL);
//	CreateLinkedList(head);
//	head = ReverseLinkedList(head);
//	CoutLinkedList(head);
//}
