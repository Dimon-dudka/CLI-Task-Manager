module;

#include <memory>

export module CLParserModule;

import CLParserAPI;

export class CLParserModule
{
public:
	CLParserModule();

	[[nodiscard]] std::shared_ptr<ICLParserInput> get_input_port() const;

private:
	std::shared_ptr<ICLParserInput> _primary_port;
};