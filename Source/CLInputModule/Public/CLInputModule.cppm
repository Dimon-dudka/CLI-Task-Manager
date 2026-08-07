module;

#include "ParserBase.h"
#include "ReaderBase.h"
#include <memory>

export module CLInputModule;

/*
 *	Composition root class for all classes in CLModule
 */
export class CLInputComponent
{
	//-Lifecycle-----------------------------------
public:
	explicit CLInputComponent(const std::shared_ptr<IParserBase>& _in_new_parser_input);

	//-Methods-------------------------------------
public:
	void handle_input();

private:
	void handle_work_result(const ParserResultHandle& _parser_result);

	//-Variables-----------------------------------
private:
	bool _is_reading = false;

	//-Internal components-------------------------
	std::unique_ptr<IReaderBase> _input_reader;

	//-Out Ports ----------------------------------
	std::shared_ptr<IParserBase> _parser_adapter;
};