#ifndef LAB309_LUAINTERPRETER_H
#define LAB309_LUAINTERPRETER_H

#include <lua.h>
#include <lualib.h>

namespace lab309 {
	class LuaInterpreter {
		/*ATTRIBUTES*/
		private:
			lua_State *l;
			
		public:
			/*CONSTRUCTORS*/
			LuaInterpreter (void);
			~LuaInterpreter (void);
			
			/*METHODS*/
			void execute (void);
			void setFunction (const char *function);
			void newTable (void);
	};
};

#endif
