#pragma once

#include <string>

/*
 *	Abstract class for all CL readers
 */
class IReaderBase
{
	//-Lifecycle-----------------------------------
public:
	virtual ~IReaderBase() = default;

	//-Methods-------------------------------------
public:
	virtual std::string read_input() = 0;
};