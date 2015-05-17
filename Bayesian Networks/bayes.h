#ifndef BAYES_H
#define BAYES_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "linkedlist.h"
#include "vector.h"
#include "state.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vertex;

class CPD
{
private:

	Vector< Vector<float> > table;//for the 2-d array
	Vertex *vertex;
	int height, width;//height and width of the table

public:

	CPD(Vertex *);

	void setValues();

	void initialize();

	void generateStates(Node<Vertex *> *, int &, LinkedList<State *> *, LinkedList<State *> *, bool &);

	void display();

	void displayRow(int);

	void displayTable();

	void print(Node<Vertex *> *, LinkedList<State *> *);

	void updateTable();

	void setHeight();

	void setWidth();

	int column(State *);

	int row(LinkedList<State *> *);

	float p(int n, int *combo);

	float p(int n, LinkedList<State *> *combo);

	void resetTable();

	void resetTable(CPD* new_table);
	
	void reset(Node<Vertex *> *ptr, LinkedList<State *> *combo);

	void setValue(int, int, float);

	~CPD();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*declaration of the Edges class*/
class Edge
{

private:

	Vertex *origin, *destination;
	int distance;

public:

	Edge();

	Edge(Vertex *origin, Vertex *destination);

	Edge(Vertex *origin, Vertex *destination, int distance);

	Vertex* getOrigin();

	Vertex* getDestination();

	int getDistance();

	void setDistance(int distance);

	string toString();
	
	int compareTo(const Edge &EDGE);

	bool operator == (const Edge &EDGE); 

	~Edge();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*the Vertices class for a DAG*/
class Vertex
{
private:

	/*counts how
	many Edges exist*/
	static int count;

	/*name of the bayesian
	Node*/
	string name;

	/*the unique id of the vertice
	.... individual Edge identifier*/
	int id;

	int weight;

	/*holds Pointer objects,
	which reference other Edges*/
	LinkedList< Edge* > *pointers;

	/*the array for the 
	States the variable can have*/
	LinkedList<State> *states;

	/*the conditional probability distribution table*/
	CPD *table;

	bool flag;//true if the node is observed...

	Vector<float> lambda_evidence; 

	Vector<float> pi_evidence; 

	Vector< Vector<float> > lambda_messages;//the message from the child to the parent

	Vector< Vector<float> > pi_messages;//the evidence from the parent to the child

public:

	Vertex();

	Vertex(string name, int weight, int num_of_states);

	string getName();

	int getId();

	CPD * getCPD();

	void setTable();

	int getWeight();

	void setWeight(int weight);

	void connectTo(Vertex *child);

	void connectTo(Vertex *child, int weight);

	LinkedList< Edge * > * getConnections();

	void displayStates();

	void display();

	void displayTable();

	LinkedList<State> * getStates();

	void getParents(LinkedList< Vertex *> *parents);

	void getChildren(LinkedList< Vertex *> * children);

	bool operator == (const Vertex& VERTEX);

	void observe(int state);

	void resetTable();

	float p(int n, LinkedList<State *> *combo);

	float p(State *state, LinkedList<State *> *combo);

	float p(int n, int *combo);

	float p(State *state, int *combo);

	void piEvidence();

	float piEvidence(int n);

	float piEvidence(State *state);

	void piEvidence(Node<Vertex *> *ptr, LinkedList<State *> *combo, float &sum, int &n);

	float piEvidence(State state);

	void piMessages();

	float piMessage(int parent, int state);

	float piMessage(Vertex *parent, State *state);

	float piMessage(int parent, State *state);

	float piMessage(Vertex *parent, int state);

	void piMessage();

	void piMessage(Vertex *parent);

	void piMessage(int parent);

	void lambdaMessage(Vertex *child);

	void lambdaMessage(int child);

	void observe(State *state);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	void lambdaMessages();

	float lambdaMessage(int child, int state);

	void lambdaMessage(Node<Vertex *> *ptr, LinkedList<State *> *combo, Vertex *my_child, State *my_state, float &sum);

	float lambdaMessage(Vertex *child, State *state);

	float lambdaMessage(Vertex *child, int state);

	float lambdaMessage(int child, State *state);

	void lambdaEvidence();

	float lambdaEvidence(int state);

	float lambdaEvidence(State *state);

	float lambdaEvidence(State state);

	bool isObserved();

	bool isRoot();

	bool isObserved(int state);

	bool isObserved(State *state);

	void posteriorProbabilities();

	void initialize();

	void setMontyTable(CPD *monty_hall_table)
	{
		this->table->resetTable(monty_hall_table);
	}

	~Vertex();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static variable initialization*/
int Vertex::count = 0;

//--------------------------------------------------------------------------------------------------------------------------------------------------


Vertex::Vertex() : Vertex("NULL", 0, 0)
{
	//invoke constructor to initialize elem to null pointer
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

Vertex::Vertex(string name, int weight, int num_of_states)
{
	this->name = name;
	id = count++; //assign individual id and increment static count counter
	pointers = new LinkedList< Edge * >();//the vertex formed will be independent
	states = new LinkedList<State>();
	State s(1, (float) 1.00f / num_of_states);
	//cout << "Enter the values for " << num_of_states << " States.\n\n";

	for (int i = 0; i < num_of_states; i++)
	{
		//cout << "State " << i + 1 << " : ";
		//cout << endl;
		states->append(s);
		s.id++;
		s.setState("State" + to_string(s.id), (float) 1.00f / num_of_states);
	}
	this->weight = weight;
	table = new CPD(this);

	initialize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

string Vertex::getName()
{
	return name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*get the count
of the given vertice*/
int Vertex::getId()
{
	return id;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*get the data stored
inside the vertice*/
CPD * Vertex::getCPD()
{
	return table;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*set the
data of the vertice*/
void Vertex::setTable()
{
	//allow the user to alter the CPD table...
	table->setValues();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*gives the
weight of the given vertice*/
int Vertex::getWeight()
{
	return weight;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*sets the weight given by the user
@param	weight		the number to be assigned as the weight
*/
void Vertex::setWeight(int weight)
{
	this->weight = weight;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*add a connection not
taking distances into account*/
void Vertex::connectTo(Vertex *child)
{
	child->table->initialize();
	this->piMessage();

	connectTo(child, 0);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*connects *this to a child with a weight
@param	child		a pointer to the child vertex
@param	weight		the weight of the new child
*/
void Vertex::connectTo(Vertex *child, int weight)
{
	Edge *edge = new Edge(this, child, weight);
	//if edge doesn't already exist
	if (!pointers->find(edge))
	{
		this->pointers->append(edge);
		(child->pointers)->append(edge);
	}
	child->table->initialize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
gives all the edges

@return		the pointer to the linked list of the edges of the vertex.
*/
LinkedList< Edge * > * Vertex::getConnections()
{
	return pointers;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
display all the states with their probabilities
*/
void Vertex::displayStates()
{
	cout << "\nStates of Vertex :\t" << getName() << endl;
	Node<State> *ptr = states->getHead();

	cout << "ID\tName\tProbability\n";
	while (ptr)
	{
		cout << ptr->data.id << "\t";
		cout << ptr->data.name << "\t";
		cout << setprecision(2) << ptr->data.probability << endl;
		ptr = ptr->next;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*displays
everything a vertex has to offer*/
void Vertex::display()
{
	cout << " ID :     " << this->id << endl;
	cout << " Name :   " << this->name << endl;
	cout << " Weight : " << this->weight << endl;
	cout << "States     Probability \n";
	displayStates();
	table->displayTable();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
displays the CPD table
*/
void Vertex::displayTable()
{
	table->displayTable();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
@return		a pointer to the states linked list 
*/
LinkedList<State> * Vertex::getStates()
{
	return states;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
gives a linked list consisting of the parents of the current node
@param	parents		the linked list be filled
*/
void Vertex::getParents(LinkedList< Vertex *> *parents)
{
	Node<Edge *> *ptr = pointers->getHead();
	parents->clear();
	while (ptr)
	{
		if (ptr->data->getOrigin() != this && ptr->data->getDestination() == this)
		{
			parents->append(ptr->data->getOrigin());
		}
		ptr = ptr->next;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
gives a linked list consisting of the children of the current node
@param	children	the linked list be filled
*/
void Vertex::getChildren(LinkedList< Vertex *> * children)
{
	Node<Edge *> *ptr = pointers->getHead();
	children->clear();
	while (ptr)
	{
		if (ptr->data->getOrigin() == this && ptr->data->getDestination() != this)
		{
			children->append(ptr->data->getDestination());
		}
		ptr = ptr->next;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*one Vertex is equal to another if its weight are equal to each other
and they have the same Connections*/
bool Vertex::operator == (const Vertex& VERTEX)
{
	return  (weight == VERTEX.weight) && (*pointers == *(VERTEX.pointers));
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
sets the given index of the state's probability to 1
and updates all the probability propagation to ancestors and 
the descendents of the current node.....

@param	state	the index of the linked list of the states

*/
void Vertex::observe(int state)
{
	if (state < 1 || state > states->getSize())
		throw - 1;

	Node<State> *ptr = states->getHead();

	while (ptr)
	{
		if (--state)
		{
			ptr->data.probability = 0;
		}
		else
		{
			ptr->data.probability = 1;
		}

		ptr = ptr->next;
	}

	flag = true;

	lambdaEvidence();

	for (int i = 0; i < this->getStates()->getSize(); i++)
		cout << lambda_evidence[i] << endl;

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *parent = parents->getHead(), *child = children->getHead();

	while (parent)
	{
		parent->data->lambdaMessage(this);
		parent = parent->next;
	}

	while (child)
	{
		child->data->piMessage(this);
		child = child->next;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
resets the table.
please refer to 
void CPD::resetTable()
*/
void Vertex::resetTable()
{
	table->resetTable();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*

please refer to 

void CPD::p(int n, Linkedlist<State*> *combo)

@param	n	an index to the state linkedlist
@param	combo	a linked list of the combinations

@return		the probability
*/
float Vertex::p(int n, LinkedList<State *> *combo)
{
	return table->p(n, combo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*

please refer to

void CPD::p(State*, Linkedlist<State*> *combo)

@param	state	a pointer to the state of the current vertex
@param	combo	a linked list of the combinations

@return		the probability
*/
float Vertex::p(State *state, LinkedList<State *> *combo)//**********
{
	return table->p(table->column(state) + 1, combo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*

please refer to

void CPD::p(int n, Linkedlist<State*> *combo)

@param	n		an index to the state linkedlist
@param	combo	an array to store the indecies of the parents'combinations

@return		the probability
*/
float Vertex::p(int n, int *combo)
{
	return table->p(n, combo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*

please refer to

void CPD::p(State*, Linkedlist<State*> *combo)

@param	state	a pointer to the state of the current vertex
@param	combo	an array to store the indecies of the parents'combinations

@return		the probability
*/
float Vertex::p(State *state, int *combo)
{
	return p(table->column(state) + 1, combo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
fills all the pi_evidence vector with valid values...
*/
void Vertex::piEvidence()
{
	int size = getStates()->getSize();
	for (int i = 0; i < size; i++)
	{
		pi_evidence[i] = piEvidence(i + 1);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates a value for the pi-evidence

please refer to 

void Vertex::piEvidence(Node<Vertex *> *ptr, LinkedList<State *> *combo, float &sum, int &n)

@param	n	an index to the linkedlist<state>

@return		the pi evidence as shown in the formula.

*/
float Vertex::piEvidence(int n)
{
	float sum = 0;

	LinkedList<Vertex *> *parent = new LinkedList<Vertex *>();
	getParents(parent);
	Node<Vertex *> *ptr = parent->getHead();
	LinkedList<State *> *combo = new LinkedList<State *>();

	piEvidence(ptr, combo, sum, n);
	return sum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates a value for the pi-evidence

please refer to

void Vertex::piEvidence(Node<Vertex *> *ptr, LinkedList<State *> *combo, float &sum, int &n)

@param	state	a pointer to the state whose piEvidence is to be calculates

@return		the pi evidence as shown in the formula.

*/
float Vertex::piEvidence(State *state)
{
	return piEvidence(table->column(state) + 1);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the piEvidence for a node

@param	ptr		a pointer to the parents linkedlist
@param	combo	an initially empty linked list to be filled later with combinations
@param	sum		the probability to be calculated
@param	n		the index of the state. gives how much are the levels of recursion

*/
void Vertex::piEvidence(Node<Vertex *> *ptr, LinkedList<State *> *combo, float &sum, int &n)
{
	if (!ptr)
	{
		Node<State *> *s = combo->getHead();

		float num = p(n, combo);

		int i = 1;
		while (s)
		{
			num *= pi_messages[i - 1][s->data->id - 1];
			s = s->next;
			i++;
		}

		sum += num;
	}
	else
	{
		Node<State> *p = ptr->data->getStates()->getHead();
		while (p)
		{
			combo->append(&(p->data));
			piEvidence(ptr->next, combo, sum, n);
			combo->removeLast();
			p = p->next;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates a value for the pi-evidence

please refer to

void Vertex::piEvidence(Node<Vertex *> *ptr, LinkedList<State *> *combo, float &sum, int &n)

@param	state	a state whose piEvidence is to be calculates

@return		the pi evidence as shown in the formula.

*/
float Vertex::piEvidence(State state)	//may not work!!!!!!!!!!
{
	return piEvidence(table->column(&state) + 1);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
fills the messages from the paents to the children for this node

please refer to 
float Vertex::piMessage(Vertex *parent, State *state)

*/
void Vertex::piMessages()
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	Node<Vertex *> *ptr = parents->getHead();
	Node<State> *state;

	int i = 0, j;
	while (ptr)
	{
		state = ptr->data->getStates()->getHead();
		j = 0;
		while (state)
		{
			pi_messages[i][j] = piMessage(ptr->data, &(state->data));
			state = state->next;
			j++;
		}
		ptr = ptr->next;
		i++;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the probability - the message from the parent to the child

@param	parent		the index of the parent in the parents' linked list
@param	state		the index of the state in the states' linked list

@return		the piMessage
*/
float Vertex::piMessage(int parent, int state)
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	Node<Vertex *> *ptr = parents->getHead();

	if (parent < 1 || parent > parents->getSize() || state < 1)
		throw - 1;


	int par = parent;
	while (--par)
	{
		ptr = ptr->next;
	}

	if (state > ptr->data->getStates()->getSize())
		throw - 1;

	if (ptr->data->isObserved())
	{
		if (ptr->data->isObserved(state))
			return 1;
		else
			return 0;
	}

	Node<State> *p = ptr->data->getStates()->getHead();

	int s = state;

	while (--s)
	{
		p = p->next;
	}

	return p->data.probability / lambda_messages[parent - 1][state - 1];
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
please refer to 

float Vertex::piMessage(int parent, int state)

@param	parent		a pointer to the parent vertex
@param	state		a pointer to the state of this node

@return		the piMessage
*/
float Vertex::piMessage(Vertex *parent, State *state)//******************************************************
{
	return piMessage(parent, state->id);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the message from the parent to the child.
*/
float Vertex::piMessage(int parent, State *state)/////***************************************
{
	return state->probability / lambda_messages[parent][state->id - 1];
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*an overloaded function for 
the piMessage*/
float Vertex::piMessage(Vertex *parent, int state)
{
	Node<State> *p = parent->getStates()->getHead();

	if (state < 1 || state > parent->getStates()->getSize())
		throw - 1;

	int s = state;
	while (--s)
	{
		p = p->next;
	}

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	Node<Vertex *> *ptr = parents->getHead();

	int parent_ = 0;
	while (ptr->data != parent)
	{
		parent_++;
		ptr = ptr->next;
	}

	return p->data.probability / lambda_messages[parent_][state - 1];//****************************************
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates te piMessage for a parent for all of its children.
*/
void Vertex::piMessage()//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
{
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *child = children->getHead();

	while (child)
	{
		child->data->piMessage(this);
		child = child->next;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the piMessage accordin to the formula 

@param	parent	a pointer to the parent Vertex

*/
void Vertex::piMessage(Vertex *parent)//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *ptr = parents->getHead();
	Node<Vertex *> *child = children->getHead();

	int j = 0;
	while (ptr->data != parent)
	{
		j++;
		ptr = ptr->next;
	}

	for (int i = parent->states->getSize(); i; i--)
	{
		pi_messages[j][i - 1] = piMessage(parent, i);
	}

	if (!flag)
	{
		piEvidence();
		posteriorProbabilities();

		while (child)
		{
			child->data->piMessage(this);
			child = child->next;
		}
	}
	else if (true)//////////////////////////////////////////???
	{
		parents->findAndRemove(parent);
		ptr = parents->getHead();

		while (ptr)
		{
			ptr->data->lambdaMessage(this);
			ptr = ptr->next;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------


void Vertex::piMessage(int parent)
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------


/*
calculates the lambdaMessage - the message a child vertex passed to it to the parents

@param	child		the pointer to a single child node
*/
void Vertex::lambdaMessage(Vertex *child)
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *ptr = parents->getHead();
	Node<Vertex *> *p = children->getHead();

	int j = 0;
	while (p->data != child)
	{
		j++;
		p = p->next;
	}

	for (int i = states->getSize(); i; i--)
	{
		lambda_messages[j][i-1] = lambdaMessage(child, i);
	}

	if (!flag)
	{
		lambdaEvidence();
		posteriorProbabilities();

		while (ptr)
		{
			ptr->data->lambdaMessage(this);
			ptr = ptr->next;
		}

		children->findAndRemove(child);
		p = children->getHead();
		while (p)
		{
			p->data->piMessage(this);
			p = p->next;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
an overloaded function . please refer to 

void Vertex::lambdaMessage(Vertex* child)
*/
void Vertex::lambdaMessage(int child)
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
responsible for probability propagation
makes the probability of the state of the vertex equal to 1
and updates all other nodes (ancestors and descendents)
*/
void Vertex::observe(State *state)
{
	state->probability = 1;

	Node<State> *s = states->getHead();
	while (s)
	{
		if (&(s->data) != state)
		{
			s->data.probability = 0;
		}
	}
	lambdaEvidence();

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *ptr = parents->getHead();
	Node<Vertex *> *p = children->getHead();

	while (ptr)
	{
		ptr->data->lambdaMessage(this);
		ptr = ptr->next;
	}

	while (p)
	{
		p->data->piMessage(this);
		p = p->next;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
fills all the lamda messages
for a single parent from all the children
please refer to

float Vertex::lambdaMessage(Vertex *child, int state)
*/
void Vertex::lambdaMessages()
{
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *ptr = children->getHead();
	int states = getStates()->getSize();

	int i = 0;
	while (ptr)
	{
		for (int j = 0; j < states; j++)
		{
			lambda_messages[i][j] = lambdaMessage(ptr->data, j + 1);
		}
		ptr = ptr->next;
		i++;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
please refer to 

float Vertex::lambdaMessage(int child, State *state)

gives the lamdaMessage for the child for the given state

@param	child		the index of the children linked list
@param	state		the index of the state linked list

@return the message from the parent to the child for the given state
*/
float Vertex::lambdaMessage(int child, int state)
{
	Node<State> *p = getStates()->getHead();

	if (child < 1 || state < 1 || state > getStates()->getSize())
		return -1;

	while (--state)
	{
		p = p->next;
	}

	return lambdaMessage(child, &(p->data));
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
does all the work
calculates a message for all the children to the parents

@param	ptr			the pointer to the head of the siblings linked list
@param	combo		the initially empty linkedlist later to be filled with the combinations of the parents
@param	my_child	the pointer to the current child
@param	my_state	the pointer to the current state
@param	sum			the sum i.e. the actual lambda message
*/
void Vertex::lambdaMessage(Node<Vertex *> *ptr, LinkedList<State *> *combo, Vertex *my_child, State *my_state, float &sum)
{
	if (!ptr)
	{
		Node<State *> *node;

		float num = 0;

		for (int i = 1, j = 1; i <= my_child->states->getSize(); i++)
		{
			j = 1;
	
			num += ((my_child->p(i, combo)) * (my_child->lambda_evidence[i - 1]) );
			node = combo->getHead();
			while (node)
			{
				if (node->data != my_state)
				{
					num *= my_child->pi_messages[j - 1][node->data->id - 1];
				}	
				node = node->next;
				j++;

			}
		}

		sum += num;
	}
	else
	{
		Node<State> *p = ptr->data->getStates()->getHead();
		if (ptr->data == this)
		{
			combo->append(my_state);
			lambdaMessage(ptr->next, combo, my_child, my_state, sum);
			combo->removeLast();
		}
		else
		{
			while (p)
			{
				combo->append(&(p->data));
				lambdaMessage(ptr->next, combo, my_child, my_state, sum);
				combo->removeLast();
				p = p->next;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
please refer to the function
void Vertex::lambdaMessage(Node<Vertex *> *ptr, LinkedList<State *> *combo, Vertex *my_child, State *my_state, float &sum)

@param	child	the pointer to the child node
@param	state	the pointer to the state of the parent

@return		the lambdaMessage (actual value)
*/
float Vertex::lambdaMessage(Vertex *child, State *state)
{
	float sum = 0;
	LinkedList<State *> *combo = new LinkedList<State *>();

	LinkedList<Vertex *> *siblings = new LinkedList<Vertex *>();
	child->getParents(siblings);
	Node<Vertex *> *ptr = siblings->getHead();

	lambdaMessage(ptr, combo, child, state, sum);
	return sum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
please refer to the function
float Vertex::lambdaMessage(Vertex *child, State *state)

@param	child	the pointer to the child node
@param	state	the index to the state linked list

@return			the message from the child to the parents
*/
float Vertex::lambdaMessage(Vertex *child, int state)
{
	if (state < 1 || state > getStates()->getSize())
		throw - 1;

	Node<State> *p = getStates()->getHead();

	while (--state)
	{
		p = p->next;
	}

	return lambdaMessage(child, &(p->data));
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
please refer to the function
float Vertex::lambdaMessage(Vertex *child, State *state)

@param	child	the index to the schild linked list
@param	state	the pointer to the state

@return			the message from the child to the parents
*/
float Vertex::lambdaMessage(int child, State *state)
{
	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	Node<Vertex *> *ptr = children->getHead();

	if (child < 1 || child > children->getSize())
		throw - 1;

	while (--child)
	{
		ptr = ptr->next;
	}

	return lambdaMessage(ptr->data, state);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
fills all the vector with valid values
*/
void Vertex::lambdaEvidence()
{
	for (int i = getStates()->getSize() - 1; i >= 0; i--)
	{
		lambda_evidence[i] = lambdaEvidence(i + 1);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the evidence for the given state

@param	state	the index of the state linked list.

*/
float Vertex::lambdaEvidence(int state)
{
	if (state < 1 || state > getStates()->getSize())
		throw - 1;

	if (isObserved())
	{
		if (isObserved(state))
		{
			return 1;
		}
		return 0;
	}

	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	float product = 1;

	/*Node<Vertex *> *ptr = children->getHead();
	while (ptr)
	{
	product *= lambdaMessage(ptr->data, state);
	}*/

	for (int i = children->getSize() - 1; i >= 0; i--)
	{
		product *= lambda_messages[i][state - 1];
	}

	return product;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the evidence for the given state

@param	state	the pointer to the state linked list.

*/
float Vertex::lambdaEvidence(State *state)
{
	return lambdaEvidence(table->column(state) + 1);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
please refer to the function
float Vertex::lambdaEvidence(int state)
*/
float Vertex::lambdaEvidence(State state)
{
	return lambdaEvidence(table->column(&state) + 1);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*validates
if observed
@return	true if the vertex is observed
*/
bool Vertex::isObserved()
{
	return flag;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
tells whether if the node has no parents

@return		true if the node is the root node
*/
bool Vertex::isRoot()
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);

	if (!(parents->getSize()))
		return true;
	else
		return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
validates if the state of the vertex is observed

@param	state	the index of the state linked list

@return		true if the state is observed by the user.
*/
bool Vertex::isObserved(int state)
{
	if (state < 1 || state > getStates()->getSize())
		throw - 1;

	if (isObserved())
	{
		Node<State> *s = getStates()->getHead();
		while (--state)
		{
			s = s->next;
		}
		return s->data.probability == 1;
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
validates if the state of the vertex is observed

@param	state	the pointer to the state linked list

@return		true if the state is observed by the user.
*/
bool Vertex::isObserved(State *state)
{
	return isObserved(table->column(state) + 1);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates all the posterior probabilities of the vertex
*/
void Vertex::posteriorProbabilities()
{

	float sum = 0;

	for (int i = getStates()->getSize() - 1; i >= 0; i--)
	{
		sum += lambda_evidence[i] * pi_evidence[i];
	}
	float Alpha = (float) 1.00 / sum;

	Node<State> *state = getStates()->getHead();
	int i = 0;
	while (state)
	{
		state->data.probability = Alpha * lambda_evidence[i] * pi_evidence[i];
		state = state->next;//////////////////////////////////////////////////
		i++;//////////////////////////////////////////////////////////////////
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/*
initializes the vertex...
sets the default values
*/
void Vertex::initialize()
{
	flag = false;

	LinkedList<Vertex *> *children = new LinkedList<Vertex *>();
	getChildren(children);
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	getParents(parents);
	Node<Vertex *> *ptr = parents->getHead();

	lambda_evidence = Vector<float>(getStates()->getSize(), 1);
	lambda_messages = Vector< Vector<float> >(children->getSize(), Vector<float>(getStates()->getSize(), 1));
	pi_messages = Vector< Vector<float> >(parents->getSize());

	int i = 0;
	while (ptr)
	{
		pi_messages[i++] = Vector<float>(ptr->data->getStates()->getSize(), 1);
		ptr = ptr->next;
	}

	if (!parents->getSize())
	{

		int arr[] = { 1 };
		for (int i = states->getSize() - 1; i >= 0; i--)
		{
			pi_evidence[i] = table->p(i + 1, arr);
		}

		pi_messages.clear();
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

Vertex::~Vertex()
{
	delete pointers;
	delete states;
	delete table;
//	lambda_evidence.~Vector();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
class copy constructor

@param	vertex		a pointer to a vertex to be copied.

*/
CPD::CPD(Vertex *vertex)
{
	/*copying the contents*/
	this->vertex = vertex;
	initialize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
sets the height of the table which
will be equal to the product of all the combinations of its parents
*/
void CPD::setHeight()
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	vertex->getParents(parents);
	Node<Vertex *> *ptr = parents->getHead();
	int H = 1;
	while (ptr)
	{
		H *= ptr->data->getStates()->getSize();
		ptr = ptr->next;
	}
	height = H;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
sets the width of the table
considering the size of the vertex states.
*/
void CPD::setWidth()
{
	width = vertex->getStates()->getSize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
prompts the user to enter values for each entry in the table

*/
void CPD::setValues()
{
	cout << "Enter the value for table :\n";
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cout << "(" << i << " , " << j << ") : "; cin >> table[i][j];
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void CPD::setValue(int i, int j, float k)
{
	this->table[i][j] = k;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
initializes the table, sets its dimensions
and equals distributes all probabilities
*/
void CPD::initialize()
{
	width = vertex->getStates()->getSize();
	setHeight();
	table = Vector< Vector<float> >(width);
	for (int i = 0; i < width; i++)
		table[i] = Vector<float>(height);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			table[i][j] = (float) 1.00f / width;
		}
	}

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	vertex->getParents(parents);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
displays all the entries of the table in a tradional fashion.
*/
void CPD::display()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cout << table[i][j] << "\t";
		}
		cout << endl;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
displays a rows of the table given its column index
*/
void CPD::displayRow(int i)
{
	for (int j = 0; j < width; j++)
	{
		cout << setprecision(2) << table[j][i] << "\t";
	}
	cout << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
displays the table in a formal fashion
with the name of the Vertex and its parent states.*/
void CPD::displayTable()
{
	cout << "CPT for vertex :\t" << vertex->getName() << endl;

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	vertex->getParents(parents);
	Node<Vertex *> *p = parents->getHead();

	Node<State> *ptr = vertex->getStates()->getHead();
	if (parents->getSize())
	{
		for (int i = 0; p; i++)
		{
			cout << p->data->getName() << "\t";
			p = p->next;
		}

		for (int i = 0; ptr; i++)
		{
			cout << ptr->data.name << "\t";
			ptr = ptr->next;
		}
		cout << endl;

		print(parents->getHead(), &LinkedList<State *>());
	}
	else
	{
		for (int i = 0; ptr; i++)
		{
			cout << ptr->data.name << "\t";
			ptr = ptr->next;
		}
		cout << endl;
		displayRow(0);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
generates the combinations and prints them.

@param	ptr		pointer to a node containing a vertex pointer as data.
used to traverse the linked list of parents.
@param	combo	a pointer to a linkedlist containing state pointer as data.
an empty list which is populated by the combinations of the parent states.

*/
void CPD::print(Node<Vertex *> *ptr, LinkedList<State *> *combo)
{
	if (!ptr)
	{
		Node<State *> *s = combo->getHead();
		while (s)
		{
			cout << s->data->name << "\t";
			s = s->next;
		}
		displayRow(row(combo));
	}
	else
	{
		Node<State> *p = ptr->data->getStates()->getHead();
		while (p)
		{
			combo->append(&(p->data));
			print(ptr->next, combo);
			combo->removeLast();
			p = p->next;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
updates the table considering its parent and children (if there are new ones).
*/
void CPD::updateTable()
{
	initialize();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
a function which calculates what row the given States are in, in the table.

@param	S		a pointer to a linked list containg State pointer as data.
(given by user)

@return			the number of rows the given S is present in.
*/
int CPD::row(LinkedList<State *> *S)
{
	bool flag = true;
	int row = 0;

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	vertex->getParents(parents);

	generateStates(parents->getHead(), row, &LinkedList<State *>(), S, flag);

	return row;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
a recursive function which generates the combinations from the parent states

@param	ptr		pointer to node containing vertex pointer as data type. generally contains the parent linked list.
@param	row		a int passed by reference to count the levels of recursion
@param	combo	a pointer to a linked list populated with the combinations of the parent sates
@param	S		a pointer to a linked list given by the user to check if it is equal to the combo states
*/
void CPD::generateStates(Node<Vertex *> *ptr, int &row, LinkedList<State *> *combo, LinkedList<State *> *S, bool &flag)
{
	if (!ptr)
	{
		if ((!(*combo == *S)) && flag)
		{
			row++;
		}
		else
			flag = false;
	}
	else
	{
		Node<State> *p = ptr->data->getStates()->getHead();
		while (p)
		{
			combo->append(&(p->data));
			generateStates(ptr->next, row, combo, S, flag);
			combo->removeLast();
			p = p->next;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the number of the column for which this->vertex has state S

@param	S	the pointer to state of the vertex.

@return		the one-indexed column number conatining S.


*/
int CPD::column(State * S)
{
	Node<State> *s = vertex->getStates()->getHead();
	int i = 0;
	while (s)
	{
		if ((&(s->data)) == S)
		{
			return i;
		}
		s = s->next;
		i++;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the probability given its indices from the table.

@param	n		one-based row number
@param	combo	an array of indices of the parents' states.

@return		the probability of the state at nth row and combo's column
*/
float CPD::p(int n, int *combo)
{
	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	vertex->getParents(parents);
	Node<Vertex *> *ptr = parents->getHead();
	LinkedList<State *> *s = new LinkedList<State *>();

	Node<State> *node;
	int i = 0, j = 0, num_states;
	while (ptr)
	{
		node = ptr->data->getStates()->getHead();
		num_states = ptr->data->getStates()->getSize();

		while (combo[i] != j + 1 && combo[i] <= num_states)
		{
			node = node->next;
			j++;
		}

		if (combo[i] == j + 1 && combo[i] <= num_states)
		{
			j = 0;
			s->append(&node->data);
		}
		else
			throw - 5;

		i++;
		ptr = ptr->next;
	}

	return table[n - 1][row(s)];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
calculates the prbability of the given address

@param	n		the one-based column index of the table
@param	combo	the list consisting of the combination of the certain row

@return		the probability of the table forthe given setof indices
*/
float CPD::p(int n, LinkedList<State *> *combo)
{
	int NUM = row(combo);
	float num = table[n - 1][NUM];
	return num;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
prompts the user for filling the table

please refer to the function

void CPD::reset(Node<Vertex *> *ptr, LinkedList<State *> *combo)

*/
void CPD::resetTable()
{
	cout << "Reset CPT for vertex :\t" << vertex->getName() << endl;

	LinkedList<Vertex *> *parents = new LinkedList<Vertex *>();
	vertex->getParents(parents);
	Node<Vertex *> *p = parents->getHead();

	Node<State> *ptr = vertex->getStates()->getHead();

	for (int i = 0; p; i++)
	{
		cout << p->data->getName() << "\t";
		p = p->next;
	}

	for (int i = 0; ptr; i++)
	{
		cout << ptr->data.name << "\t";
		ptr = ptr->next;
	}
	cout << endl;

	reset(parents->getHead(), &LinkedList<State *>());

	if (!(parents->getSize()))
	{
		int i = 0;
		ptr = vertex->getStates()->getHead();
		while (ptr)
		{
			ptr->data.probability = table[i][0];
			i++;
			ptr = ptr->next;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void CPD::resetTable(CPD* new_table)
{
	table = new_table->table;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
the function to be called for all vertices

@param	ptr		the pointer to the parents linkedlist
@param	combo	the initially empty linked list later to be filled with the all possible parent combinations
*/
void CPD::reset(Node<Vertex *> *ptr, LinkedList<State *> *combo)
{
	if (!ptr)
	{
		Node<State *> *s = combo->getHead();
		while (s)
		{
			cout << s->data->name << "\t";
			s = s->next;
		}

		int j = row(combo);
		for (int i = 0; i < vertex->getStates()->getSize(); i++)
		{
			cin >> table[i][j];
		}
		cout << endl;
	}
	else
	{
		Node<State> *p = ptr->data->getStates()->getHead();
		while (p)
		{
			combo->append(&(p->data));
			reset(ptr->next, combo);
			combo->removeLast();
			p = p->next;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

CPD::~CPD(){}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*the Edges class to
go with our Vertices class..*/
Edge::Edge() : Edge(NULL, NULL, 0)
{}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*a constructor
@param	origin			the pointer to the parent vertex
@param	destination		the pointer to the child vertex
*/
Edge::Edge(Vertex *origin, Vertex *destination) : Edge(origin, destination, 0)
{}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*a constructor
@param	origin			the pointer to the parent vertex
@param	destination		the pointer to the child vertex
@param	weight			the weight in the edge
*/
Edge::Edge(Vertex *origin, Vertex *destination, int distance)
{
	this->origin = origin;
	this->destination = destination;
	this->distance = distance;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

//accessors and mutators

/*
gives back the origin vertex

@return the pointer to the parent vertex
*/
Vertex * Edge::getOrigin()
{
	return origin;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
gives back the destination vertex

@return the pointer to the child vertex
*/
Vertex * Edge::getDestination()
{
	return destination;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
@return		the weight of the edge
*/
int Edge::getDistance()
{
	return distance;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
prompts the user to set the weight of the edge

@param	distance	the new weight of the edge
*/
void Edge::setDistance(int distance)
{
	this->distance = distance;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
converts all the data to string for displaying
*/
string Edge::toString()
{
	return "(" + origin->getName() + ", " + destination->getName() + "): ";
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*gives the difference
of the *this and other edges' distances...*/
int Edge::compareTo(const Edge &EDGE)
{
	return distance - EDGE.distance;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*the overloaded 
equality operator*/
bool Edge::operator == (const Edge &EDGE)
{
	return (distance == EDGE.distance) && (origin == EDGE.origin) && (destination == EDGE.destination);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*class 
destructor*/
Edge::~Edge(){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif