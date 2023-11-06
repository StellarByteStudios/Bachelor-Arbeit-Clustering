#pragma once
class BetterReader
{
private:
	const char* path;
	//const char* readLine(ifstream*);

public:
	/* Konstruktor
	* @param path: Path of File to be read
	*/
	BetterReader(const char* path);

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
	char* readFile();
};

