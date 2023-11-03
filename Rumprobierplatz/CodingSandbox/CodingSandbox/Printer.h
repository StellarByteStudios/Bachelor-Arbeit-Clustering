#pragma once

#include <string>

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
	* @param msg: The Message given as const char* is printed with counter
	*
	* @return void
	*/
	void printnl(const char*);
};

