#ifndef VECTOR_H
#define VECTOR_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Vector
{

private:
	unsigned int size, capacity, Log;
	T* arr;

public:

	Vector();

	Vector(const Vector<T> &VECTOR);

	Vector(unsigned int size);

	Vector(unsigned int size, const T &initial);

	~Vector();

	Vector<T> & operator = (const Vector<T> &VECTOR);

	T * begin();

	T * end();

	T & front();

	T & back();

	void pushBack(const T &VECTOR);

	void popBack();

	void reserve(unsigned int capacity);

	unsigned int getSize() const;

	void resize(unsigned int size);

	T & operator[](unsigned int index);

	bool isEmpty() const;

	unsigned int getCapacity() const;

	void clear();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Default constructor
*/
template < typename T >
Vector<T>::Vector()
{
	capacity = size = Log = 0;
	arr = NULL;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Vector class copy constructor

@param	VECTOR	Vector object to create a siminal instance
*/
template < typename T >
Vector<T>::Vector(const Vector<T> &VECTOR)
{
	size = VECTOR.size;
	Log = VECTOR.Log;
	capacity = VECTOR.capacity;
	arr = new T[size];
	for (int i = 0; i < size; i++)
		arr[i] = VECTOR.arr[i];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Vector class constructor

creats an object of the required size

@param	size	the size of Vector object required
*/
template < typename T >
Vector<T>::Vector(unsigned int size)
{
	this->size = size;
	Log = ceil(log((double)size) / log(2.0));
	capacity = 1 << Log;
	arr = new T[capacity];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Vector class constructor

Creats a Vector object of the raquired size and fills it with an initial value

@param	size		required size of the object
@param	initial		initial value to be allotted to all elements

*/
template < typename T >
Vector<T>::Vector(unsigned int size, const T &initial)
{
	this->size = size;
	Log = ceil(log((double)size) / log(2.0));
	capacity = 1 << Log;
	arr = new T[capacity];
	for (int i = 0; i < size; i++)
		arr[i] = initial;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Vector class destructor

deletes all the allocated heap memory to prevent memory leakage
*/
template < typename T >
Vector<T>::~Vector() {
	delete[] arr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Overlaoded assignment operator

Assigns the data members of one Vector object to another

@param VECTOR	the Vector object to be copied
@return			reference of the object itself for cascading assignments
*/
template < typename T >
Vector<T> & Vector<T>::operator = (const Vector<T> &VECTOR)
{
	delete[] arr;
	size = VECTOR.size;
	Log = VECTOR.Log;
	capacity = VECTOR.capacity;
	arr = new T[capacity];
	for (unsigned int i = 0; i < size; i++)
		arr[i] = VECTOR.arr[i];
	return *this;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Head of a Vector Object

@return            pointer to the starting entry
*/
template < typename T >
T * Vector<T>::begin()
{
	return arr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Tail of a Vector object

@return            pointer to the last entry
*/
template < typename T >
T * Vector<T>::end()
{
	return arr + getSize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Accessor of top most value

@return            reference of the top most entry
*/
template < typename T >
T & Vector<T>::front()
{
	return arr[0];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Accessor of the bottom most value

@return            reference of the bottom most entry
*/
template < typename T >
T & Vector<T>::back()
{
	return arr[size - 1];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Pushes the value at the end of an object

@param	VALUE	the item to be added
*/
template < typename T >
void Vector<T>::pushBack(const T &VALUE)
{
	/*
	A common way of regrowing an array is to double the size as needed.
	This is so that if you are inserting n items at most only O(log n) regrowths are performed
	and at most O(n) space is wasted.
	*/
	if (size >= capacity)
	{
		reserve(1 << Log);
		Log++;
	}
	arr[size++] = VALUE;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Pops a value from the back of an object
*/
template < typename T >
void Vector<T>::popBack()
{
	size--;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Reserves memory to be used later

@param	capacity	the capacity of the Vector object
*/
template < typename T >
void Vector<T>::reserve(unsigned int capacity)
{
	T *newarr = new T[capacity];

	for (unsigned int i = 0; i < size; i++)
		newarr[i] = arr[i];

	this->capacity = capacity;
	delete[] arr;
	arr = newarr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Accessor of the size of a Vector object

@return            the size of the object
*/
template < typename T >
unsigned int Vector<T>::getSize() const
{
	return size;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Resizes the Vector object as desired

@param	size	the new size of the Vector object
*/
template < typename T >
void Vector<T>::resize(unsigned int size)
{
	Log = ceil(log((double)size) / log(2.0));
	reserve(1 << Log);
	this->size = size;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Square braces operator overloaded for accessing & setting data

@param	index	the index of the required data
@return			the reference of the required data
*/
template < typename T >
T & Vector<T>::operator[](unsigned int index)
{
	if (index < size)
		return arr[index];
	else
	{

		if (size >= capacity) {
			reserve(1 << ++Log);
		}
		return arr[size++];
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Checks if the object is empty

@return		true if the object is empty, otherwise false
*/
template < typename T >
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Accessor of the capacity of the Vector object

@return		the capacity of the Vector object
*/
template < typename T >
unsigned int Vector<T>::getCapacity() const
{
	return capacity;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Clears all the data from the Vector object
*/
template < typename T >
void Vector<T>::clear()
{
	capacity = size = Log = 0;
	delete[] arr;
	arr = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif