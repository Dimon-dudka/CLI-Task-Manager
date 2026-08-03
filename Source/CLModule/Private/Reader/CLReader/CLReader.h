#pragma once

#include "ReaderBase.h"

class CLReader final : public IReaderBase
{
	//-Lifecycle-----------------------------------
	//-Methods-------------------------------------
public:
	virtual std::string read_input() override;

	//-Variables-----------------------------------
};
