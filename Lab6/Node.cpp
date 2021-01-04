#include <Node.h>;

Node::Node(int data)
{
	this->data = data;
	this->next = nullptr;
	this->prev = nullptr;
}

Node::~Node()
{
// not needed I think
}

int Node::getData()
{
	return this->data;
}

void Node::setData(int data)
{
	this->data = data;
}

Node* Node::getNext()
{
	return this->next;
}

void Node::setNext(Node* next)
{
	this->next = next;
}

Node* Node::getPrev()
{
	return this->prev;
}

void Node::setPrev(Node* prev)
{
	this->prev = prev;
}
