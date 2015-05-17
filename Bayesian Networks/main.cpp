//DSA project: MODELING WITH BAYESIAN NETWORKS
/*Brief Description :
We first make a Graph ADT implemented with loads of pointers
(This is neither adjacency list nor adjacency matrix implementation)
and then convert it into a DAG. Bayesian Networks can
be modeled with probabalistic graphical models such as this one.*/
//Authors: Osama Waqar, Uzair Akbar
//Starting date: 13/12/2014.
//Submission date: 21/12/2014.
//How will we do it ? Ans: We won't.
#include <iostream>
#include <string>
#include "graph.h"
#include "bayes.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testProgram();
void montyHallProblem();

int main(void)
{
	montyHallProblem();

	system("PAUSE");
	return 0;
}

void montyHallProblem()
{
	//creating the graph
	Graph g("------ MONTY HALL PROBLEM ----");

	//creatng all the nodes
	Vertex car("CAR", 0, 3);
	Vertex player("PLAYER", 2, 3);
	Vertex host("HOST", 7, 3);

	//adding the nodes to the graph
	g.addVertex(&car);
	g.addVertex(&player);
	g.addVertex(&host);

	//adding edges
	g.connect(&car, &host);
	g.connect(&player, &host);

	//displaying the graph
	g.displayGraph();
	cout << "-------------------------------------------------\n";
	
	//prompts for the CPD of the host
	g.setMontyTable(&host);
	cout << "-------------------------------------------------\n\n";

	host.displayTable();

	//displaying all the states of all the nodes
	g.displayStates(&player);
	g.displayStates(&car);
	g.displayStates(&host);

	//player choses door 2
	g.observe(&player, 3);

	//displaying all the states of all the nodes
	g.displayStates(&player);
	g.displayStates(&car);
	g.displayStates(&host);

	//host tells you the car is NOT behind door 1
	g.observe(&host, 2);

	//displaying all the states of all the nodes
	g.displayStates(&player);
	g.displayStates(&car);
	g.displayStates(&host);
}

void testProgram()
{
	Graph g(" MY GRAPH ");
	Vertex s("S", 0, 2);
	Vertex t("T", 0, 2);
	Vertex u("U", 0, 2);
	Vertex v("V", 0, 2);
	Vertex w("W", 0, 2); 
	
	g.addVertex(&s);
	g.addVertex(&t);
	g.addVertex(&u);
	g.addVertex(&v);
	g.addVertex(&w);
	
	g.connect(&s, &u);
	g.connect(&t, &u);
	g.connect(&u, &v);
	g.connect(&u, &w);

	g.resetTable(&s);
	g.resetTable(&t);
	g.resetTable(&u);
	g.resetTable(&v);
	g.resetTable(&w);
	
	g.observe(&u, 2);
	
	cout << "-------------------------------------------------\n";
	
	g.displayGraph();
	
	g.displayStates(&s);
	g.displayStates(&t);
	g.displayStates(&u);
	g.displayStates(&v);
	g.displayStates(&w);
	
	cout << "-------------------------------------------------\n";
	
	s.displayTable();
	t.displayTable();
	u.displayTable();
	v.displayTable();
	w.displayTable();

}