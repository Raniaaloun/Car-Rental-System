#pragma once
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

class CarType {
public:
	string make, model, color;
	int manufacture_year, rate;
	bool rented_out;
	CarType();  //constructor initialize class members
	CarType(string Make, string Model, string Color, int Manu_year, int Rate, bool rented = false); //para constructor, assigns data to members
	void printCarInfo(); //prints data of a car -> Toyota, Corolla, white, 2020, JD50, Rented Out
};
//------------------------------
//functions of CarType class ---
//O(1)
CarType::CarType()
{
	make = model = color = "";
	manufacture_year = 2001;
	rate = 0;
	rented_out = false;
}
//O(1)
CarType::CarType(string Make, string Model, string Color, int Manu_year, int Rate, bool rented)
{
	make = Make;
	model = Model;
	color = Color;
	manufacture_year = Manu_year;
	rate = Rate;
	rented_out = rented;
}
//O(1)
void CarType::printCarInfo()
{
	cout << make << ", " << model << ", "
	<< color << ", " << manufacture_year << ", JD"
	<< rate << ", ";
	if (rented_out == false)
		cout << "not rented out." << endl;
	else
		cout << "Rented Out." << endl;

}
//--------------------------------------------------------------------------------------------------------
class CarNode {
public:
	CarType car;
	CarNode *link;
};
//---------------------------------------------------------------------------------------------------------
class SortedCarListType {
private:
	CarNode *first, *last;  //pointers to first & last node in the list
	int counter; //number of nodes in the list
public:
	SortedCarListType();//sets counter to zero, pointers to null
	~SortedCarListType();//calls destroyList()
	void destroyList();//deletes all nodes from list
	CarType front();//return first node
	CarType back();//returns last node
	void print();//prints all nodes in list(calls the carType print()
	void insertCar(const CarType newCar);//insert a node to the list, in order, based on rental rate
	void deleteCar(CarType deleteCarNode);//deletes a node based on passed data
	bool searchByMake_and_model(string mk, string md);//stops searching when found
	bool searchByRate(int renRate);//stops searching when found
	void rentCarOut(string mk, string md, int my);//look for the node,change rented to true
	void returnCar(string mk, string md, string clr, int my);//look for the node, change rented to false
	int CountRentedOut();//returns num of nodes with rented==true
	int CountRateLessThan(int cost);//return num of nodes with rate <cost, stops at threshold
};
//O(1)
SortedCarListType:: SortedCarListType() {
	counter = 0;
	first = last = NULL;
}
//O(n)
SortedCarListType::~SortedCarListType() {
	destroyList();
}
//O(n)
void SortedCarListType:: destroyList() {
	CarNode *current = first;
	while (first != NULL)
	{
		first = first->link;
		delete current;
		current = first;
	}
	first = last = NULL;
	counter = 0;
}
//O(1)
CarType SortedCarListType:: front() {
	if (first != NULL) {
		return first->car;
	}
	else
		cout << "List is empty." << endl;
}
//O(1)
CarType SortedCarListType:: back() {
	if (first != NULL) {
		return last->car;
	}
	else
		cout << "List is empty." << endl;
}
//O(N)
void SortedCarListType::print() {
	if (first == NULL)
		cout << "list is empty." << endl;
	else
	{
		int index = 1;
		CarNode *pointer = first;
		cout << "  *********The contents of the car list" << endl;
		while (pointer != NULL)//keep moving till the end
		{
			cout << "  car # " << index << ":   ";
			index++;
			pointer->car.printCarInfo();//endl is in printCarInfo, it will do (y)
			pointer = pointer->link;// move to nxt node
		}
		cout << "  *********************************" << endl;

	}
}
//O(n)
void SortedCarListType::insertCar(const CarType newCar) {
	
	CarNode *current; //pointer to traverse the list
	CarNode *trailCurrent; //pointer just before current
	CarNode *newNode; //pointer to create a node
	bool found;
	newNode = new CarNode; //create the node
	newNode->car = newCar; //store newItem in the node
	newNode->link = NULL; //set the link field of the node
	//to NULL

	cout << "   inserting the info of the car ";
	cout << newNode->car.make << ", " << newNode->car.model << ", "
	<< newNode->car.color << ", " << newNode->car.manufacture_year << ", " << newNode->car.rate << endl;
	if (first == NULL) //for the first insertion
	{
		first = newNode;
		last = newNode;
		counter++;
	}
	else
	{
		current = trailCurrent = first;
		found = false;
		while (current != NULL && !found) //search the list, breaks when a greater node is found or if all are less
		{
			if (current->car.rate >= newCar.rate)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}
		}
		if (current == first) //only one node in list, and it's greater 
		{
			newNode->link = first;
			first = newNode;
			counter++;
		}
		else //insert before the found node
		{
			trailCurrent->link = newNode;
			newNode->link = current;
			if (current == NULL)
				last = newNode;
			counter++;
		}
	}

}
//O(n)
void SortedCarListType:: deleteCar(CarType deleteCarNode) {
	
	CarNode *current; //pointer to traverse the list
	CarNode *trailCurrent; //pointer just before current
	bool found;
	if (first == NULL)
		cout << "List is empty." << endl;
	else
	{
		current = trailCurrent = first;
		found = false;
		while (current != NULL && !found) //search the list
		{
			if (current->car.rate >= deleteCarNode.rate)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}
		}
		if (current == NULL) //we reached the last node & didn't find it nor found a node with greater rate
		{
			cout << "  The car to be deleted with info: " << endl;
			cout << "  ";  deleteCarNode.printCarInfo();
			cout << "  is not in the list." << endl;
			cout << endl << endl;
		}
		else
		{
			if (current->car.make.compare(deleteCarNode.make) == 0
				&& current->car.model.compare(deleteCarNode.model) == 0
				&& current->car.color.compare(deleteCarNode.color) == 0
				&& current->car.rate == deleteCarNode.rate
				&& current->car.manufacture_year == deleteCarNode.manufacture_year)
			{
				if (first == current) //item to be deleted is node 1
				{
					first = first->link;
					if (first == NULL)
						last = NULL;
					delete current;
					cout << "  The car to be deleted with info: " << endl;
					cout << "  ";  deleteCarNode.printCarInfo();
					cout << "  is succesfully deleted." << endl;
					cout << endl << endl;
				}
				else //other place in list
				{
					trailCurrent->link = current->link; //move the link of the prev node to the node after node to be deleted
					if (current == last) //if the node to be deleted happened to be the last node
						last = trailCurrent;
					delete current;
					cout << "  The car to be deleted with info: " << endl;
					cout << "  ";  deleteCarNode.printCarInfo();
					cout << "  is succesfully deleted." << endl;
					cout << endl << endl;

				}
				counter--;
			}
			else
			{
				cout << "  The car to be deleted with info: " << endl;
				cout << "  ";  deleteCarNode.printCarInfo();
				cout << "  is not in the list." << endl;
				cout << endl << endl;
			}

		}
	}

}
//O(n)
bool SortedCarListType::searchByMake_and_model(string mk, string md) {

	CarNode *current; //pointer to traverse the list 
	bool found = false;

	current = first;
	while (current != NULL && !found) //search the list
	{
		if (current->car.make == mk && current->car.model == md)
		{
			found = true;
			cout << "car with make: " << mk << ", and model: " << md << " is in the list" << endl;
		}
		else
		{
			current = current->link;
		}

	}
	if (found == false)
		cout << "car with make: " << mk << ", and model: " << md << " is not in the list" << endl;
	

	return found;

}
//O(n)
bool SortedCarListType::searchByRate(int renRate) {

	CarNode *current; //pointer to traverse the list
	bool found = false;

	current = first;
	while (current != NULL && !found) //search the list
	{
		if (current->car.rate <= renRate)
		{
			found = true;
			cout << "car/s with rate: " << renRate << " or less is/are in the list" << endl;
		}
		else
		{
			current = current->link;
		}

	}
	if (found == false)
		cout << "car/s with rate: " << renRate << " or less is/are not in the list" << endl;
	else 


	return found;
}
//O(n)
void SortedCarListType::rentCarOut(string mk, string md, int my) {

	CarNode *current; //pointer to traverse the list
	bool found = false;

	current = first;
	while (current != NULL && !found) //search the list
	{
		if (current->car.make == mk &&
			current->car.model == md &&
			current->car.manufacture_year == my
			)
		{
			current->car.rented_out = true;
			cout << "the car you are looking for is";
			cout << " successfully booked and the cost is ";
			cout << "JD" << current->car.rate << endl;
			found = true;
		}
		else
		{
			current = current->link;
		}
	}
	if (current == NULL)
		cout << "No car with the required specifications is available" << endl;

}
//O(n)
void SortedCarListType::returnCar(string mk, string md, string clr, int my)
{

	CarNode *current; //pointer to traverse the list
	bool found = false;

	current = first;
	while (current != NULL && !found) //search the list
	{
		if (current->car.make == mk &&
			current->car.model == md &&
			current->car.color == clr &&
			current->car.manufacture_year == my)
		{
			current->car.rented_out = false;
			cout << "the car has been returned successfully" << endl;
			found = true;
		}
		else
		{
			current = current->link;
		}
	}
	if (current == NULL)
		cout << "No car with the entered specifications is rented out" << endl;

}
//O(n)
int SortedCarListType::CountRentedOut() { 	// returns how many cars are currently rent out

	int Counter = 0;
	CarNode *current;
	current = first;
	while (current != NULL)
	{
		if (current->car.rented_out == true)
			Counter++;
		current = current->link;
	}
	return Counter;
}
//O(n)
int SortedCarListType:: CountRateLessThan(int cost) {
	/*
	Returns how many cars in the list with rate less than 
	the value of the parameter cost, this function
	also should benefit from the ordered property of the list
	*/
	int Counter = 0;
	bool flag = false;
	CarNode *current;
	current = first;
	while (current != NULL && !flag)
	{
		if (current->car.rate <= cost)
			Counter++;
		else
		{
			flag = true;
			//cout << "stop";
		}

		current = current->link;
	}
	return Counter;
}

