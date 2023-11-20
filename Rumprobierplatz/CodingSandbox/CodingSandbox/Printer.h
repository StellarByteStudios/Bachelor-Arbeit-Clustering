#pragma once

#include <string>

using namespace std;

class Printer
{
private:
	// Wie oft wurde schon was ausgegeben, seid die Klasse erstellt wurde
	int printcounts;

public:
	/* Konstruktor
	*/
	Printer();

	/* Destruktor
	* Prints death Message
	*/
	~Printer();


	/* Printer Method
	* Prints given String and says how often
	* this Method was called in this Instance
	* of the Object
	*
	* @param msg: The Message given as const char* is printed with counter
	* 
	* @return void
	*/
	void printWithCounter(const char*);

	/* Printer Method
	* Simply Prints given String with a
	* new Line
	*
	* @param msg: The Message given as const char* is printed with new Line
	*
	* @return void
	*/
	void printnl(const char*);

	/* Printer Method - string
	* Prints given String and says how often
	* this Method was called in this Instance
	* of the Object
	*
	* @param msg: The Message given as std::string is printed with counter
	*
	* @return void
	*/
	void printWithCounter(string);

	/* Printer Method - string
	* Simply Prints given String with a
	* new Line
	*
	* @param msg: The Message given as std::string is printed with new Line
	*
	* @return void
	*/
	void printnl(string);
};

