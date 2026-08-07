module;

#include "CLParser.h"
#include <cassert>
#include <memory>

module CLParserModule;

CLParserModule::CLParserModule()
{
	_primary_port = std::make_shared<CLParser>();
}

std::shared_ptr<IParserBase> CLParserModule::get_input_port() const
{
	assert(_primary_port);
	return _primary_port;
}