#ifndef NODE_H
#define NODE_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Node class*/
template < class T >
struct Node
{
	T data;
	Node<T>* next;

	Node();

	Node(T data);

	Node(Node<T>* ptr);

	Node(T data, Node<T>* ptr);

	bool operator == (const Node<T> &NODE);

	~Node();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Constructor for the node class

*/
template < class T > Node<T>::Node()
{
	next = NULL;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
A constructor for the node class.

@param data		the input data of the node
*/
template < class T > Node<T>::Node(T data)
{
	this->data = data;
	next = NULL;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Constructor for the node class

@param	 ptr		a pointer to the node.

*/
template < class T > Node<T>::Node(Node<T>* ptr)
{
	this->next = ptr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Constructor for the node class

@param data		data for the node
@param ptr		pointer to a node which will be its next.

*/
template < class T > Node<T>::Node(T data, Node<T>* ptr)
{
	this->data = data;
	next = ptr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Overloaded equality operator

@param NODE		A const node reference

checks if the data are equal.

@return         true if NODE is equal to *this.
*/
template < class T > bool Node<T>::operator == (const Node<T> &NODE)
{
	return data == NODE.data;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*a 
destructor*/
template < class T > Node<T>::~Node()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif