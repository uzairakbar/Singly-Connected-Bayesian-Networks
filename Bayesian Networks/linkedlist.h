#ifndef LINKEDLIST_H
#define LINKEDLIST_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "node.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Linked list class*/
template < typename T >
class LinkedList
{
	Node<T> *head, *curr, *tail;
	int left, right, size;

public:

	LinkedList();

	LinkedList(const LinkedList *LIST);

	void initialize();

	void insert(const T& DATA);

	void insertAtBeginning(const T& DATA);

	void append(const T& DATA);

	void clear();

	T& remove();

	T& removeFirst();

	T& removeLast();

	bool find(const T& DATA);

	bool findAndRemove(const T& DATA);

	int getSize() const;

	void movePointerForward();

	void movePointerBackward();

	int getCurrentPosition();

	void goToStart();

	void goToEnd();

	void operator = (const LinkedList *LIST);

	bool getData(int index, T &DATA);

	Node<T> * getHead();

	bool operator == (const LinkedList<T> &LIST);

	~LinkedList();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

A constructor for the Linked list class
*/
template < typename T > LinkedList<T>::LinkedList()
{
	initialize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
A copy constructor

@param LIST		pointer to another linked list
*/
template < typename T >
LinkedList<T>::LinkedList(const LinkedList *LIST)
{
	initialize();
	for (Node<T> *temp = LIST->head; temp; temp = temp->next)
		append(temp->data);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
initializes all pointers to NULL
*/
template < typename T >
void LinkedList<T>::initialize()
{
	head = curr = tail = NULL;
	left = right = size = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Inserts data into the linkedlist at current position.

@param DATA		the data of the new node to be inserted.

*/
template < typename T >
void LinkedList<T>::insert(const T& DATA)
{
	if (!head)
	{
		head = curr = tail = new Node<T>(DATA, NULL);
		size++;
	}
	else if (!curr->next)
	{
		Node<T> *node = new Node<T>(DATA, curr->next);
		tail = curr->next = node;
		right++;
		size++;
	}
	else
	{
		Node<T> *node = new Node<T>(DATA, curr->next);
		curr->next = node;
		right++;
		size++;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Inserts a node to the beginning.

@param DATA		the data of the new node to be inserted

*/
template < typename T >
void LinkedList<T>::insertAtBeginning(const T& DATA)
{
	size++;
	Node<T> *node = new Node<T>(DATA, NULL);
	if (!head)
	{
		head = curr = tail = node;
	}
	else
	{
		node->next = head;
		head = node;
		left++;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------


/*
Inserts a new node at the end.

@param DATA		the data of the new node to be appended.

*/
template < typename T >
void LinkedList<T>::append(const T& DATA)
{
	size++;
	if (!tail)
	{
		head = curr = tail = new Node<T>(DATA, NULL);
	}
	else
	{
		tail = tail->next = new Node<T>(DATA, NULL);
		right++;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Deletes all the nodes from the linked list.
*/
template < typename T >
void LinkedList<T>::clear()
{
	while (head)
	{
		curr = head;
		head = curr->next;
		delete curr;
	}
	initialize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Removes a node pointed to by the current pointer

@return		the reference of the removed data
*/
template < typename T >
T& LinkedList<T>::remove()
{
	if (!curr)
		throw - 1;

	T data;
	if (!head->next)
	{
		data = curr->data;
		clear();
	}
	else
	{
		data = curr->next->data; // Remember value
		Node<T> *node = curr->next; // Remember link Node
		curr->next = node->next; // Remove from list
		if (tail == node) tail = curr; // Reset tail
		delete node; // Reclaim space
		right--; // Decrement the count
		size--;
	}

	return data;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Removes the node pointed to by the head pointer.

@return		the reference of the data of the deleted node
*/
template < typename T >
T& LinkedList<T>::removeFirst()
{
	if (!head)
		throw - 2;

	T data = head->data; // Remember value
	if (!head->next)
	{
		clear();
	}
	else
	{
		Node<T>* node = head; // Remember link Node
		head = node->next; // Remove from list
		if (curr == node) { curr = head; left++; } // Reset tail
		delete node; // Reclaim space
		left--; // Decrement the count
		size--;
	}

	return data;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Removes the node pointed to by the tail pointer.

@return		the reference of the data of the deleted node
*/
template < typename T >
T& LinkedList<T>::removeLast()
{
	if (!tail)
		throw - 3;

	T data = tail->data; // Remember value
	if (tail == head)
	{
		clear();
	}
	else
	{
		Node<T>* node = head; // Remember link Node
		while (node->next != tail)
			node = node->next;
		tail = node; // Remove from list
		if (curr == node->next) { curr = tail; right++; } // Reset tail
		node = node->next;
		delete node; // Reclaim space
		tail->next = NULL;
		right--; // Decrement the count
		size--;
	}
	return data;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
A linear search for the data in the linked list. O(n) time.

@param DATA		the data to be searched in the linked list.

@return		true if DATA is found in the list.
*/
template < typename T >
bool LinkedList<T>::find(const T& DATA)
{
	for (Node<T> *ptr = head; ptr; ptr = ptr->next)
	{
		if (ptr->data == DATA)
			return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Performs a linear search in the list for the DATA and deletes it if found.

@param	DATA	the data to be searched and removed.

@return		true if DATA is found and safely removed.
*/
template < typename T >
bool LinkedList<T>::findAndRemove(const T& DATA)
{
	if (!head)
		return false;

	if (!head->next)
	{
		if (head->data == DATA)
		{
			remove();
			return true;
		}
		else
			return false;
	}

	if (head->data == DATA)
	{
		removeFirst();
		return true;
	}

	for (Node<T> *ptr = head; ptr->next; ptr = ptr->next)
	{
		if (ptr->next->data == DATA)
		{
			curr = ptr;
			remove();
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
counts the number of nodes in the list

@return		the size of the list
*/
template < typename T >
int LinkedList<T>::getSize() const
{
	return size;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Moves the current pointer one position forward i.e it points to the next node.
*/
template < typename T >
void LinkedList<T>::movePointerForward()
{
	if (curr != tail)
	{
		curr = curr->next;
		left++;
		right--;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Moves the current pointer to the previous node.
*/
template < typename T >
void LinkedList<T>::movePointerBackward()
{
	if (curr != head)
	{
		Node<T> *ptr = head;
		while (ptr->next != curr)
		{
			ptr = ptr->next;
		}
		curr = ptr;
		left--; right++;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the position of the current pointer from the head pointer.
counts how many nodes it is far from the head pointer.

@return		the number of nodes between the head and the current pointer.
*/
template < typename T >
int LinkedList<T>::getCurrentPosition()
{
	if (!head)
		return 0;

	int position = 0;
	Node<T> *ptr = head;
	while (ptr != curr)
	{
		ptr = ptr->next;
		position++;
	}
	return position;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
positions the current pointer to the head pointer
*/
template < typename T >
void LinkedList<T>::goToStart()
{
	curr = head;
	right += left;
	left = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
positions the current pointer to the tail pointer.
*/
template < typename T >
void LinkedList<T>::goToEnd()
{
	curr = tail;
	left += right;
	right = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*the overloaded
assignment operator*/
template < typename T >
void LinkedList<T>::operator = (const LinkedList *LIST)
{
	clear();
	for (Node<T>* ptr = LIST->head; ptr; ptr = ptr->next)
		append(temp->data);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*

DATA is reset to the data of the index given from the head node.

@param	index		the number of nodes from the head nodes.
@param	DATA		to be assigned the value at the index.

@return		true if the index is valid
*/
template < typename T >
bool LinkedList<T>::getData(int index, T &DATA)
{
	int i = 0;
	if (index >= size || !head)
		return false;

	Node<T> *ptr;
	for (ptr = head; ptr; ptr = ptr->next)
	{
		if (i == index)
			break;
		i++;
	}
	DATA = ptr->data;
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
gives the head pointer

@return		the head pointer
*/
template < typename T >
Node<T> * LinkedList<T>::getHead()
{
	return head;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
the overloaded equality operator.

@param		if all the data is same.

@return		true if the linked lists are equal
*/
template < typename T >
bool LinkedList<T>::operator == (const LinkedList<T> &LIST)
{
	if (size == LIST.size)
	{
		for (Node<T> *ptr1 = head, *ptr2 = LIST.head; ptr1 && ptr2; ptr1 = ptr1->next, ptr2 = ptr2->next)
		{
			if (!(ptr1->data == ptr2->data))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/* a destructor 
for our linked list class*/
template < typename T > LinkedList<T>::~LinkedList()
{
	this->clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif