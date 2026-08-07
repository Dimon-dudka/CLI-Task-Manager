module;

#include "ParserBase.h"
#include <memory>

export module CLParserModule;

export class CLParserModule
{
public:
	// TODO Add pointer to appcore port
	CLParserModule();

	[[nodiscard]] std::shared_ptr<IParserBase> get_input_port() const;

private:
	std::shared_ptr<IParserBase> _primary_port;
};