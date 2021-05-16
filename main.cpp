#include "pch.h"
#include <iostream>
#include <string>;
#include "SortedCarListr.h"
using namespace std;


void main()
{
	//creating objects of cars
	CarType obj1("Mercedes-Benz", "A220", "black", 2016, 120, false);  
	CarType obj2("Mitsubishi", "Lancer", "silver", 2010, 40, false);
	CarType obj3("Toyota", "Yaris", "White", 2011, 35, false);
	CarType obj4("Mitsubishi", "Lancer", "red", 2012,60,false);
	SortedCarListType list; //created an object of listType
	

	//inserting cars into list
	cout << "  (( test insert function ))" << endl;
	list.insertCar(obj1); 
	list.insertCar(obj2);
	list.insertCar(obj3);
	list.insertCar(obj4);
	cout << "____________________________________________________________" << endl;
	cout << endl << endl;

	//printing list
	cout << "  Print the car list ----" << endl;
	list.print(); 
	cout << "____________________________________________________________" << endl;
	cout << endl << endl;


	//renting out a car
	cout << " ((test rentCarOut function ))" << endl;
	cout << " Enter the make, model and manufacture year of";
	cout << " the car you want to rent:" << endl;
	string make, model, color = "";

	int m_year = 0;
	cin >> make >> model >> m_year;
	list.rentCarOut(make, model, m_year);
	cout << "____________________________________________________________" << endl;
	cout << endl << endl;

	
	//deleting two cars, one inserted(obj2), and one not inserted(obj5)
	cout << " ((test delete function ))" << endl;
	cout << " deleting the car {Mitsubishi Lancer, silver, 2010, 60:" << endl;
	list.deleteCar(obj2);
	CarType obj5("Mitsubishi", "Lancer", "silver", 2012, 300, false);
	list.deleteCar(obj5);
	cout << "____________________________________________________________" << endl;
	 


	//find out how many cars are rented and are in list
	cout <<endl<< " ((test CountRentedOut function ))" << endl;
	cout << " The number of the rented cars in the list is: ";
	cout << list.CountRentedOut() << endl << endl;
	cout << "____________________________________________________________" << endl;



	//find out how many cars have rate less than 80 and are in the list
	cout << endl << " ((test CountLessThan function ))" << endl;
	cout << " The number of the cars with rates less than JD80 in the list is ";
	cout << list.CountRateLessThan(80) << endl << endl;
	cout << "____________________________________________________________" << endl;


	//return a car
	cout << endl << " ((test return car function ))" << endl;
	cout << " Enter the make, model, color, and manufacture year of ";
	cout << "the car you want to return:" << endl;
	cin >> make >> model >> color>> m_year;
	list.returnCar(make, model, color, m_year);
	cout << endl;
	list.print();
	cout << "____________________________________________________________" << endl;
	cout << endl << endl;


	//search by make and model, two tests
	cout << " <<testing searchByMake_and_model>>" << endl;
	bool found = list.searchByMake_and_model("Mitsubishi", "Lancer");
	found = list.searchByMake_and_model("Ford", "4x4");
	cout << "____________________________________________________________" << endl;
	cout << endl << endl;


	//search by rate, two tests, if cars with rate or less in list, return true
	found = list.searchByRate(40); //in list
	found = list.searchByRate(5); //not in list
	cout << "____________________________________________________________" << endl;
	cout << endl << endl;


}
 
