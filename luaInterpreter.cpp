#include "luaInterpreter.h"
#include <lauxlib.h>

/*CONSTRUCTORS*/
lab309::LuaInterpreter::LuaInterpreter (void) {
	this->l = lua_open();
	luaL_openlibs(l);
}

lab309::LuaInterpreter::~LuaInterpreter (void) {
	lua_close(this->l);
}

/*METHODS*/
void lab309::LuaInterpreter::execute (void) {

}

void lab309::LuaInterpreter::setFunction (const char *function) {

}
