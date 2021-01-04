
#include <Node.h>
#include <iostream>

using namespace std;

class DoublyLinkedList
{
private:
	Node* head;
	Node* tail;
	int elements;
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	bool add(Node* data, int pos);
	bool remove(int pos);
	bool replace(Node* old, Node* newValue);
	int  search(Node* data);
	Node* nodeAt(int pos);
	void display_forward();
	void display_backward();
	int size();
};

int main()
{
	DoublyLinkedList object;
	Node* data = new Node(1);
	Node* data2 = new Node(2);
	Node* data3 = new Node(3);
	Node* data4 = new Node(5);
	object.add(data, 1);
	object.add(data2, 2);
//	object.add(data3, 3);
	object.add(data4, 3);
	cout << "Forward:" << endl;
	object.display_forward();
	cout << "Search for not added node3:" << endl;
	cout << object.search(data3) << endl;
	cout << "Replace node2 with node 3:" << endl;
	cout << object.replace(data,data3) << endl;
	cout << "Remove node at index 1:" << endl;
//	cout << object.remove(1) << endl;
	cout << "Forward:" << endl;
	object.display_forward();
	cout << "Backwards:" << endl;
	object.display_backward();

	return 0;
}


DoublyLinkedList::DoublyLinkedList()
{
	this->elements = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* currentNode = this->head;
	Node* nextNode;
	while (currentNode != nullptr)
	{
		nextNode = currentNode->getNext();
		delete currentNode;
		currentNode = nextNode;
	}
}

bool DoublyLinkedList::add(Node* data, int pos)
{
	Node *positionPointerLeading = this->head;
	Node* positionPointerTrailing = nullptr;

	if (data == nullptr || pos - 1 > this->elements)
		return false;
	else if (this->elements == 0)
	{
		this->head = data;
		this->tail = data;
		this->elements += 1;
		return true;
	}else 
	{
		if (pos != 1)
		{
			for (int i = 0; i < pos - 1; i++)
			{
				positionPointerTrailing = positionPointerLeading;
				positionPointerLeading = positionPointerLeading->getNext();
			}
			if (positionPointerLeading != nullptr)
			{
				data->setPrev(positionPointerTrailing);
				data->setNext(positionPointerLeading);
				if (positionPointerTrailing != nullptr)
				{
					positionPointerTrailing->setNext(data);
					positionPointerLeading->setPrev(data);
				}
			}
			else
			{
				data->setPrev(positionPointerTrailing);
				positionPointerTrailing->setNext(data);
			}
		}
		else
		{
			this->head->setPrev(data);
			data->setNext(this->head);
			this->head = data;
		}
		this->elements += 1;
		this->tail = this->nodeAt(this->size());
		return true;
	}	
}

bool DoublyLinkedList::remove(int pos)
{
	if (pos <= this->size())
	{
		Node* positionPointerLeading = this->head;
		Node* positionPointerTrailing = nullptr;
		Node* postionToDelete = nullptr;

		// item in the middle
		if (pos < this->size() && pos != 1)
		{
			for (int i = 0; i + i < pos; i++)
			{
				positionPointerTrailing = positionPointerLeading;
				positionPointerLeading = positionPointerLeading->getNext();
			}
			postionToDelete = positionPointerLeading;
			positionPointerLeading = positionPointerLeading->getNext();
			positionPointerLeading->setPrev(positionPointerTrailing);
			positionPointerTrailing->setNext(positionPointerLeading);
			delete postionToDelete;
		}
		// item last
		else if (pos == this->size())
		{
			postionToDelete = this->tail;
			positionPointerTrailing = postionToDelete->getPrev();
			positionPointerTrailing->setNext(nullptr);
			this->tail = positionPointerTrailing;
			delete postionToDelete;
		}
		// item first
		else
		{
			postionToDelete = this->head;
			this->head = postionToDelete->getNext();
			this->head->setPrev(nullptr);
			delete postionToDelete;
		}
		this->elements -= 1;
		return true;
	}else return false;
}

bool DoublyLinkedList::replace(Node* old, Node* newValue)
{
	int index = this->search(old);
	if (index != -1 && index != 1)
	{
		this->remove(index);
		this->add(newValue,index);
		return true;
	}
	else if (index != -1 && index == 1)
	{
		this->add(newValue, index);
		this->remove(2);
	}
	else return false;
}

int DoublyLinkedList::search(Node* data)
{
	Node* positionPointer = this->head;
	for (int i = 0; i < this->size(); i++)
	{
		if (positionPointer == data)
			return i + 1;
		else positionPointer = positionPointer->getNext();
	}
	return -1;
}

Node* DoublyLinkedList::nodeAt(int pos)
{
	Node* positionPointer = this->head;
	if (pos > this->elements)
	{
		return nullptr;
	}
	else
	{
		for (int i = 0; i + 1 < pos; i++)
		{
			positionPointer = positionPointer->getNext();
		}
		return positionPointer;
	}
}

void DoublyLinkedList::display_forward()
{
	Node* positionPointer = this->head;
	cout << positionPointer->getData() << endl;
	while (positionPointer->getNext() != nullptr)
	{
		positionPointer = positionPointer->getNext();
		cout << positionPointer->getData() << endl;
	}
}

void DoublyLinkedList::display_backward()
{
	Node* positionPointer = this->tail;
	cout << positionPointer->getData() << endl;
	while (positionPointer->getPrev() != nullptr)
	{
		positionPointer = positionPointer->getPrev();
		cout << positionPointer->getData() << endl;
	}
}

int DoublyLinkedList::size()
{
	return this->elements;
}
