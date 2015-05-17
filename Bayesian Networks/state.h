#ifndef STATE_H
#define STATE_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct State
{
	int id;
	string name;
	float probability;

	State();

	State(int id);

	State(int id, float probability);

	State(int id, string name, float probability);

	void setName(string name);

	void setProability(float probability);

	void setState(string name, float probability);

	~State();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
State class default constructor
*/
State::State() : State(1, "State0", 0)
{}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
State class constructor

@param	id	sets the id of the object
*/
State::State(int id) : State(id, ("State" + to_string(id)), 0)
{}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
State class constructor

@param id			the id of the State object
@param probability	posterior probability of the State object
*/
State::State(int id, float probability) : State(id, ("State" + to_string(id)), probability)
{}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
State class constructor

@param id file		the id of the State object
@param name			name of the State object
@param probability	posterior probability of the State object
*/
State::State(int id, string name, float probability)
{
	this->id = id;
	this->name = name;
	this->probability = probability;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Mutator for name of State object

@param	name	name of the State object
*/
void State::setName(string name)
{
	this->name = name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Mutator for the posterior probability

@param probability posterior probability of the State object
*/
void State::setProability(float probability)
{
	this->probability = probability;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*
Mutator for the name and posterior probability

@param name			name of the State object
@param probability	posterior probability of the State object
*/
void State::setState(string name, float probability)
{
	setName(name);
	setProability(probability);
	//cout << "\nState Name\t: "; fflush(stdin); getline(cin, this->name);
	//cout << "Probability\t: "; cin >> probability;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/*state struct destructor~*/
State::~State() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif 