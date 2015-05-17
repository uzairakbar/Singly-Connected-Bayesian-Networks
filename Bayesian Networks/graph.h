#ifndef GRAPH_H
#define GRAPH_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include "linkedlist.h"
#include "bayes.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*The graph class. Makes use of the vertices and edges classes.*/
class Graph
{
	//Because we will need random access to the Edges
	//We will use an ArrayList to hold them
private:
	string name;
	LinkedList< Vertex * > *vertices;

public:

	Graph(string);

	/*add a Vertice to the Graph to the List*/
	bool addVertex(Vertex &vertex);

	bool addVertex(Vertex *vertex);

	bool addVertex(string name, int weight, int num_of_States);

	bool contains(Vertex *vertex);

	void displayVerticeNames();

	void getVertice(int index, Vertex &t);

	/*returns number of vertices in Graph*/
	int countVertices();

	string getName()
	{
		return this->name;
	}

	bool equals(const Graph *other);

	void displayGraph();

	Vertex* findByName(string);

	void observe(Vertex *vertex, int state)
	{
		vertex->observe(state);
	}

	void resetTable(Vertex *vertex)
	{
		vertex->resetTable();
		initialize();
	}

	void displayStates(Vertex *vertex)
	{
		vertex->displayStates();
	}

	void initialize()
	{
		Node<Vertex *> *ptr = vertices->getHead();

		while (ptr)
		{
			ptr->data->initialize();
			ptr = ptr->next;
		}

		ptr = vertices->getHead();
		while (ptr)
		{
			if (ptr->data->isRoot())
				ptr->data->piMessage();
			ptr = ptr->next;
		}
	}

	void connect(int parent, int child)
	{
		Node<Vertex *> *ptr = vertices->getHead(), *p = vertices->getHead();

		while (parent--)
		{
			ptr = ptr->next;
		}

		while (child--)
		{
			p = p->next;
		}

		ptr->data->connectTo(p->data);

		initialize();
	}

	void connect(Vertex *parent, Vertex*child)
	{
		parent->connectTo(child);

		initialize();
	}

	void setMontyTable(Vertex*p);

	~Graph();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Constructor for Graph class

@param	name	name of the Graph instance
*/
Graph::Graph(string name)
{
	vertices = new LinkedList < Vertex *>();
	this->name = name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	delete this->vertices;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Adds a vertex to the Graph instance

@param	vertex	the reference of Vertex object to be added to the graph
@return			true if the vertex doesn't already exists within the graph, otherwise false
*/
bool Graph::addVertex(Vertex &vertex)
{
	if (vertices->find(&vertex))
		return false;
	vertices->append(&vertex);
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Adds a vertex to the Graph instance

@param	vertex	Pointer to the Vertex object to be added to the graph
@return			true if the vertex doesn't already exists within the graph, otherwise false
*/
bool Graph::addVertex(Vertex *vertex)
{
	if (vertices->find(vertex))
		return false;
	vertices->append(vertex);
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Creats the required Vertex instance and adds it to the graph

@param	name			name of the Vertex object to be added
@param	weight			weight of the Vertex object to be added
@param	num_of_states	required number of states for the Vertex object
@return					false if the vertex to be added already exists within the graph, otherwise false
*/
bool Graph::addVertex(string name, int weight, int num_of_states)
{
	Vertex* v = new Vertex(name, weight, num_of_states);
	if (vertices->find(v))
		return false;
	(this->vertices)->append(v);
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Checks if the Graph contains a Vertex

@param	vertex	pointer to the Vertex object to be checked
@return			true if the Vertex object exists within the Graph, otherwise false
*/
bool Graph::contains(Vertex *vertex)
{
	return (this->vertices)->find(vertex);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Finds a Vertex object within the Graph by name

@param	name	the name of the Vertex to be found
@return			pointer to the required Vertex
*/
Vertex* Graph::findByName(string name)
{
	for (Node<Vertex*> *temp = this->vertices->getHead(); temp != NULL; temp = temp->next)
	{
		if (temp->data->getName() == name)
		{
			return temp->data;
		}
	}
	return NULL;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Accessor of a Vertex within a Graph

@param	index	Index of the Vector to be accessed
@param	vertex	A dummy variable reference to be assigned the required Vertex
*/
void Graph::getVertice(int index, Vertex &vertex)
{
	Vertex *temp = new Vertex();
	vertices->getData(index, temp);
	vertex = *temp;
	return;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Displays names of the Vertices contained in the Graph
*/
void Graph::displayVerticeNames()
{
	if (this->countVertices() == 0)
	{
		cout << "THERE ARE NO NODES IN THE GRAPH !!\n\n";
		return;
	}
	for (Node<Vertex*>* temp = this->vertices->getHead(); temp != NULL; temp = temp->next)
	{
		cout << temp->data->getName();
		cout << endl;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
counts the number of Vertices in the Graph

@return            number of vertices
*/
int Graph::countVertices()
{
	return (this->vertices)->getSize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Checks if two graphs are equal

@param	other	the graph which is to be compared
@return			true if both Graphs are equal
*/
bool Graph::equals(const Graph *other)
{
	if (other->vertices->getSize() != this->vertices->getSize())
		return false;
	//store all of Edges of larger Graph 
	//LinkedList< Vertex > *temp = new LinkedList < Vertex >(other->vertices);
	//if temp changed, then the Graphs are not equal
	return *(other->vertices) == *(this->vertices);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------


void Graph::setMontyTable(Vertex* p)
{
	CPD *monty_table = new CPD(p);

	monty_table->setValue(0, 0, 0);
	monty_table->setValue(1, 0, 0.5);
	monty_table->setValue(2, 0, 0.5);

	monty_table->setValue(0, 1, 0);
	monty_table->setValue(1, 1, 0);
	monty_table->setValue(2, 1, 1);

	monty_table->setValue(0, 2, 0);
	monty_table->setValue(1, 2, 1);
	monty_table->setValue(2, 2, 0);

	monty_table->setValue(0, 3, 0);
	monty_table->setValue(1, 3, 0);
	monty_table->setValue(2, 3, 1);

	monty_table->setValue(0, 4, 0.5);
	monty_table->setValue(1, 4, 0);
	monty_table->setValue(2, 4, 0.5);

	monty_table->setValue(0, 5, 1);
	monty_table->setValue(1, 5, 0);
	monty_table->setValue(2, 5, 0);

	monty_table->setValue(0, 6, 0);
	monty_table->setValue(1, 6, 1);
	monty_table->setValue(2, 6, 0);

	monty_table->setValue(0, 7, 1);
	monty_table->setValue(1, 7, 0);
	monty_table->setValue(2, 7, 0);

	monty_table->setValue(0, 8, 0.5);
	monty_table->setValue(1, 8, 0.5);
	monty_table->setValue(2, 8, 0);



	p->setMontyTable(monty_table);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Displays the Graph as an adjency list along with each vertice's children and parents(if any)
*/
void Graph::displayGraph()
{
	cout << "GRAPH : " << this->name << "\n\n";
	cout << "ID\tName\tConnected to ( IDs )\n\n";

	Node< Vertex *> *ptr = vertices->getHead();
	for (int i = 0; i < countVertices(); i++)
	{
		cout << ptr->data->getId() << "\t" << ptr->data->getName() << "\t";
		Node< Edge * > *p = ((ptr->data)->getConnections())->getHead();
		while (p)
		{
			if (((p->data)->getDestination()) != ptr->data)
				cout << "Parent of : " << ((p->data)->getDestination())->getId() << " ";
			if (((p->data)->getOrigin()) != ptr->data)
				cout << "Child of : " << ((p->data)->getOrigin())->getId() << " ";
			p = p->next;
		}
		cout << endl;
		ptr = ptr->next;
	}
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif