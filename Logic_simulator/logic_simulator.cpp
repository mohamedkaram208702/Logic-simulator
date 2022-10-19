/*
 * logic_simulator.cpp
 *
 *  Created on: Sep 24, 2022
 *      Author: Mohamed Karam Fouad
 */
#include<string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Node {
public :
	Node();  //  default constructor
	Node(std:: string name);
	Node(std:: string name , int value);
	void setname(std:: string name);  // set node name
	void setvalue(int v);  // set node value
	std::string getname();   // return node name
	int getvalue();
	void print_node();
private:
	std::string Node_name; // node name
	int Node_value;		// value that is holded by this node
};

Node::Node():Node_name(""),Node_value(0){

}

Node::Node(std:: string name):Node_name(name),Node_value(0){

}

Node::Node(std:: string name , int value):Node_name(name),Node_value(value){

}
// setters and getters
void Node::setname(std:: string name){
	Node_name=name;
}
void Node::setvalue(int v){
	Node_value=v;
}
std::string Node::getname(){
	return Node_name;
}
int Node::getvalue(){
	return Node_value;
}
void Node::print_node()
{
	cout << Node_name << ": " << Node_value << endl;
}
/*class Gate is an abstract class that represent Logic gate
 *		 Each Gate has two input and one output
 *		 Both input and output could be a value or another combination of Nodes
 */
class Gate{
public:
	Gate(); // default constructor
	virtual ~Gate();// default destructor
	void set_input1(Node * FirstInput);	// set the first input
	void set_input2(Node * SecondInput);	// set the second input
	void set_output(Node * Out); // out is the output of the gate
	Node * get_input1(); // represents the first input of the gate
	Node * get_input2();	// represents the second input of the gate
	Node * get_output();	// represents the output of the gate
	virtual void calculation_ouput()=0;	/* pure virtual function
										   the calculation of each gate differs between gates
										   ( the implementation of each gate is different )*/
protected:
	Node * Node_input1;  // first input to gate
	Node * Node_input2;	// second input to gate
	Node * Node_output;	// output from gate
};

Gate::Gate():Node_input1(nullptr),Node_input2(nullptr),Node_output(nullptr){

}
Gate::~Gate(){
}
// setters and getters
void Gate:: set_input1(Node * FirstInput){
	Node_input1=FirstInput;
}
void Gate:: set_input2(Node * SecondInput){
	Node_input2=SecondInput;
}
void Gate:: set_output(Node * Out){
	Node_output=Out;
}
Node * Gate:: get_input1(){
	return Node_input1;
}
Node * Gate:: get_input2(){
	return Node_input2;
}
Node * Gate:: get_output(){
	return Node_output;
}
// AND Gate
class AND_gate : public Gate{
public:
	AND_gate();
	void calculation_ouput();
};

AND_gate::AND_gate():Gate(){
}

void AND_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == 1 && Node_input2->getvalue() == 1)
		Node_output->setvalue(1);

	else
		Node_output->setvalue(0);
}
// NAND Gate
class NAND_gate: public Gate{
public:
	NAND_gate();
	void calculation_ouput();
};

NAND_gate::NAND_gate():Gate(){
}

void NAND_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == 1 && Node_input2->getvalue() == 1)
		Node_output->setvalue(0);

	else
		Node_output->setvalue(1);
}
// OR Gate
class OR_gate : public Gate{
public:
	OR_gate();
	void calculation_ouput();
};

OR_gate::OR_gate():Gate(){
}

void OR_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == 0 && Node_input2->getvalue() == 0)
		Node_output->setvalue(0);

	else
		Node_output->setvalue(1);
}
// NOR Gate
class NOR_gate : public Gate{
public:
	NOR_gate();
	void calculation_ouput();
};

NOR_gate::NOR_gate():Gate(){
}
void NOR_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == 0 && Node_input2->getvalue() == 0)
		Node_output->setvalue(1);

	else
		Node_output->setvalue(0);
}
// XOR Gate
class XOR_gate : public Gate{
public:
	XOR_gate();
	void calculation_ouput();
};

XOR_gate::XOR_gate():Gate(){
}
void XOR_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == Node_input2->getvalue())
		Node_output->setvalue(0);

	else
		Node_output->setvalue(1);
}
// XNOR Gate
class XNOR_gate : public Gate{
public:
	XNOR_gate();
	void calculation_ouput();
};

XNOR_gate::XNOR_gate():Gate(){
}
void XNOR_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == Node_input2->getvalue())
		Node_output->setvalue(1);

	else
		Node_output->setvalue(0);
}
// NOT Gate
class NOT_gate : public Gate{
public:
	NOT_gate();
	void calculation_ouput();
};

NOT_gate::NOT_gate():Gate(){
}
void NOT_gate::calculation_ouput()
{
	if (Node_input1->getvalue() == 1)
		Node_output->setvalue(0);

	else
		Node_output->setvalue(1);
}
class Simulate
{
	vector<Gate*>gates;
	vector<Node*>nodes;
public:
	Simulate();
	short get_gates_size();
	short get_nodes_size();
	Node* find_node(string s);
	Node* add_node(string s);
	Node* find_or_add_node(string s);
	Gate* add_gate(string name);
	void print_all_nodes();
	void sim();
	void parseInput();
	~Simulate();
};
Simulate::Simulate()
{

}

short Simulate::get_gates_size()
{
	return gates.size();
}

short Simulate::get_nodes_size()
{
	return nodes.size();
}

Node* Simulate::find_node(string s)
{
	for (unsigned int i = 0; i<nodes.size(); i++)
	{
		if (nodes[i]->getname() == s)
		{
			return nodes[i];
		}
	}
	return NULL;
}

Node* Simulate::add_node(string s)
{
	Node *n_node = new Node();
	nodes.push_back(n_node);
	n_node->setname(s);
	return n_node;
}

Node* Simulate::find_or_add_node(string s)
{
	Node *ptr = find_node(s);
	if (ptr != NULL)
	{
		return ptr;
	}
	else
	{
		return add_node(s);
	}
}

Gate* Simulate::add_gate(string name)
{
	if (name == "AND")
	{
		Gate *p = new AND_gate();
		gates.push_back(p);
	}
	else if (name == "OR")
	{
		gates.push_back(new OR_gate());
	}
	else if (name == "NOR")
	{
		gates.push_back(new NOR_gate());
	}
	else if (name == "XNOR")
	{
		gates.push_back(new XNOR_gate());
	}
	else if (name == "XOR")
	{
		gates.push_back(new XOR_gate());
	}
	else if (name == "NOT")
	{
		gates.push_back(new NOT_gate());
	}
	else if (name == "NAND")
	{
		gates.push_back(new NAND_gate());
	}
	return gates[gates.size() - 1];
}

void Simulate::print_all_nodes()
{
	for (unsigned int i = 0; i<nodes.size(); i++)
	{
		nodes[i]->print_node();
	}
}

void Simulate::sim()
{
	for (unsigned int j = 0; j<gates.size(); j++)
	{
		for (unsigned int i = 0; i<gates.size(); i++)
		{
			gates[i]->calculation_ouput();
		}
	}
}
void Simulate::parseInput()
{
	string inp;
	while (1)
	{
		cin >> inp;
		if (inp == "SET")
		{
			string n;
			short v;
			cin >> n >> v;
			find_node(n)->setvalue(v);
		}
		else if (inp == "SIM")
		{
			sim();
		}
		else if (inp == "OUT")
		{
			string n;
			cin >> n;
			if (n == "ALL")
			{
				print_all_nodes();
				break;
			}
			else
			{
				find_node(n)->print_node();

			}
		}
		else if(inp == "NOT")
		{
			Gate *ngate = add_gate(inp);
			string i1, o1;
			cin >> i1 >> o1;
			ngate->set_input1(find_or_add_node(i1));
			ngate->set_output(find_or_add_node(o1));
		}
		else{
            Gate *ngate = add_gate(inp);
            string i1, i2, o1;
            cin >> i1 >> i2 >> o1;
            ngate->set_input1(find_or_add_node(i1));
            ngate->set_input2(find_or_add_node(i2));
            ngate->set_output(find_or_add_node(o1));
		}
	}
}
Simulate::~Simulate()
{
	for (unsigned int i = 0; i<gates.size(); i++)
	{
		delete gates[i];
	}
	for (unsigned int i = 0; i<nodes.size(); i++)
	{
		delete nodes[i];
	}
}
int main(void)
{
	Simulate a;
	a.parseInput();
	return 0;
}

