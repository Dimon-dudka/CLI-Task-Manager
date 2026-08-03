
#include "CLApplication.h"
/*	TODO for future
*	arg variants:
*	-l username password - for auto login
*	--no-log - do not log actions
*	--no-save - do not save tasks in db or file(no need in connection)
*/
int main(int argc, char* argv[])
{
	CLApplication app;
	app.start();
}