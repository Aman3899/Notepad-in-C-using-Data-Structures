#include<iostream>
#include<string>
using namespace std;
//Node for Linked List to Store the data and its code
class LL_node {
public:
	char data;
	string encode;
	LL_node* next;
	LL_node() {
		data = '\0';
		encode = "\0";
		next = NULL;
	}
};

//Linked List ADT
class Linked_List {
private:
	LL_node* head, * tail;
public:
	Linked_List() {
		head = tail = NULL;
	}

	bool isEmpty() {
		if (head == NULL) { return true; }
		else { return false; }
	}

	bool Insert(char data, string encode) {
		LL_node* newNode = new LL_node;
		newNode->data = data;
		newNode->encode = encode;
		if (isEmpty()) {
			head = tail = newNode;
			newNode->next = NULL;
			return true;
		}
		tail->next = newNode;
		tail = tail->next;
		return true;
	}

	string Search(char Data) {
		if (isEmpty()) {
			return "\0";
		}
		else {
			LL_node* Curr = head;
			while (Curr != NULL) {
				if (Curr->data == Data) {
					return Curr->encode;
				}
				Curr = Curr->next;
			}
		}
	}

	LL_node* getHead() {
		return head;
	}
};

//Node for Priority Queue
class node {
public:
	char data;//Alphabet
	int freq;
	node* Next;
	node* Left;
	node* Right;
	node()
	{
		data = 0;
		freq = 0;
		Next = NULL;
		Left = NULL;
		Right = NULL;
	}
};

//Priority Queue Class
class Priority_Queue {
private:
	node* front;//head 
	Linked_List Encoding;
public:
	Priority_Queue() {
		front = NULL;
	}

	node* getFront() { return front; }

	//isEmpty Function to Check the Queue is Empty or Not
	bool isEmpty() {
		if (front == NULL) { return true; }
		else { return false; }
	}
	//Insertion of Character and its frequency in priority queue
	void EnQueue(char Val, int frequency)
	{
		node* newNode = new node;
		newNode->data = Val;
		newNode->freq = frequency;
		// if the queue is empty
		if (isEmpty()) {
			front = newNode;
			newNode->Next = NULL;
		}
		Add_Node(newNode);

	}
	void Add_Node(node* newNode)
	{
		//if the frequency of charatcer is greater than the front(head) of priority_queue
		if (newNode->freq < front->freq) {
			newNode->Next = front;
			front = newNode;
		}
		else {
			//Adding Node By function
			node* temp = NULL;  //Temprarity Variable for the inserting Node
			node* curr = front;
			//check the priority of counts of Sequence charatcer
			while (curr->Next != NULL && curr->Next->freq < newNode->freq) {
				curr = curr->Next;
			}
			temp = curr->Next;
			curr->Next = newNode;
			newNode->Next = temp;
		}
	}

	bool DeQueue() {
		if (isEmpty()) {
			return false;
		}
		front = front->Next;
		return true;
	}

	void Making_Huffman_Tree_Step_by_Step(node* temp1, node* temp2)
	{
		node* New_Node = new node();
		New_Node->freq = (temp1->freq) + (temp2->freq);
		New_Node->Left = temp1;
		New_Node->Right = temp2;

		DeQueue();
		if (front->Next != NULL) {
			DeQueue();
			Add_Node(New_Node);
		}
		else {
			front = New_Node;
		}
	}

	void Huffmain_conding()
	{
		node* curr = NULL;
		while (front->Next != NULL)
		{
			curr = front;
			node* temp1 = curr;
			node* temp2 = curr->Next;
			Making_Huffman_Tree_Step_by_Step(temp1, temp2);           //Adding data in Root Node and return the single Node
		}
	}

	void Storing_Encode(node* node, string str) {
		if (node) {
			/* first recur on left child */
			Storing_Encode(node->Left, str + "0");
			/* then print the data of node */
			if (node->data != NULL) {
				LL_node* curr = Encoding.getHead();
				while (curr != NULL) {
					if (curr->data == node->data) {
						curr->encode = str;
					}
					curr = curr->next;
				}
			}
			/* now recur on right child */
			Storing_Encode(node->Right, str + "1");
		}
	}

	void SetLinkedList(string a) {
		for (int i = 0; i < a.length(); i++) {
			Encoding.Insert(a[i], "0");
		}
	}

	LL_node* getLinkedList() {
		return Encoding.getHead();
	}
};

class Huffman {
private:
	Priority_Queue q;
public:
	Huffman(string Str) {
		int* Counts = new int[127];// int array to store the counts of each character
		//initializztion the arrays of characters and their counts
		for (int i = 0; i < 127; i++) {
			Counts[i] = 0;
		}
		for (int i = 0; i < Str.length(); i++) {
			Counts[Str[i]] = Counts[Str[i]] + 1;//storing counts of their character
		}
		for (int i = 0; i < 127; i++) {
			if (Counts[i] != 0) {
				q.EnQueue(char(i), Counts[i]);
			}
		}
		q.SetLinkedList(Str);
		q.Huffmain_conding();
		string String = "";
		q.Storing_Encode(q.getFront(), String);
	}

	LL_node* getList() {
		return q.getLinkedList();
	}
};

//int main()
//{
//
//	string Text;
//	cout << " Enter the Text  :  ";
//	getline(cin, Text);
//	Huffman h(Text);
//
//	system("pause");
//	return 0;
//}