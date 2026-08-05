#pragma once

#include "ReaderBase.h"

/*
 *	The single responsibility - is to read user input
 */
class CLReader final : public IReaderBase
{
	//-Lifecycle-----------------------------------
	//-Methods-------------------------------------
public:
	[[nodiscard]] virtual std::string read_input() override;

	//-Variables-----------------------------------
};
