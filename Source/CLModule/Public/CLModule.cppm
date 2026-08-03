module;

#include "ReaderBase.h"
#include <memory>

export module CLModule;


/*
 *	Composition root class for all classes in CLModule
 */
export class CLComponent
{
	//-Lifecycle-----------------------------------
public:
	CLComponent(/*TODO Out port*/);

	//-Methods-------------------------------------
public:
	void handle_input();

	//-Variables-----------------------------------
private:
	//-Internal components-------------------------
	std::unique_ptr<IReaderBase> _input_reader;

	//-Out Ports ---------------------------------
	// TODO add out port
};