#include "University.h"


void University::setType(int _type)
{

	type = _type;
}



int University::getType()
{

	return type;
}



bool University::isError()
{

	return this->error;
}



void University::setError(bool _error)
{

	this->error = _error;
}

University::~University()
{
}
