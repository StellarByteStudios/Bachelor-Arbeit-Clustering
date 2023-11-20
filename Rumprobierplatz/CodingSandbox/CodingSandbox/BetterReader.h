#pragma once

#include <string>

using namespace std;

class BetterReader
{
private:
	string path;
	//const char* readLine(ifstream*);

public:
	/* Konstruktor
	* @param path: Path of File to be read
	*/
	BetterReader(string path);

	/* Destruktor
	* Prints death Message
	*/
	~BetterReader();


	/* Reads File
	* reads komplete File and konverts into
	* a char*
	*
	* @return char* of File-content
	*/
	string readFile();
};

