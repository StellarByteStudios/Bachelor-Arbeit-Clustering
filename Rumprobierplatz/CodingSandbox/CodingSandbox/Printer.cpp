#include "Printer.h"

#include <cstdio>

Printer::Printer()
{
	this->printcounts = 0;
	printf("I'm spawned\n");
}

Printer::~Printer()
{
	printf("I'm destructed after being called %d times\n", this->printcounts);
}

void Printer::printWithCounter(const char* msg)
{
	this->printcounts++;
	printf("I printet %d times. My String wars %s\n", this->printcounts, msg);
}

void Printer::printnl(const char* msg)
{
	this->printcounts++;
	printf("%s\n", msg);
}


