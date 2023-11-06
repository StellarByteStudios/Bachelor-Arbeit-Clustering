#pragma once

#include <fstream>

using namespace std;

class Reader
{
	private:
		const char* path;
		const char* readLine(ifstream*);

	public:
		/* Konstruktor
		* @param path: Path of File to be read
		*/
		Reader(const char* path);

		/* Destruktor
		* Prints death Message
		*/
		~Reader();


		/* Reads File
		* reads komplete File and konverts into
		* a char*
		* 
		* @return char* of File-content
		*/
		const char* readFile();
};
