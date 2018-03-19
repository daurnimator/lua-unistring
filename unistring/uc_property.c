#include <stdlib.h> /* NULL */

#include <unictype.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"


static void lunistring_pushucproperty(lua_State *L, uc_property_t property) {
	uc_property_t *ud;

	lua_pushlstring(L, (const char*)&property, sizeof(uc_property_t));
	if (lua_rawget(L, lua_upvalueindex(1)) == LUA_TUSERDATA)
		return;
	lua_pop(L, 1);

	ud = lua_newuserdata(L, sizeof(uc_property_t));
	*ud = property;
	luaL_setmetatable(L, "uc_property_t");

	lua_pushlstring(L, (const char*)&property, sizeof(uc_property_t));
	lua_pushvalue(L, -2);
	lua_rawset(L, lua_upvalueindex(1));
}


static int lunistring_uc_property_byname(lua_State *L) {
	const char *name = luaL_checkstring(L, 1);
	uc_property_t res = uc_property_byname(name);
	lunistring_pushucproperty(L, res);
	return 1;
}


static int lunistring_uc_property_is_valid(lua_State *L) {
	uc_property_t *property = luaL_checkudata(L, 1, "uc_property_t");
	lua_pushboolean(L, uc_property_is_valid(*property));
	return 1;
}


static int lunistring_uc_is_property(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	uc_property_t *property = luaL_checkudata(L, 2, "uc_property_t");
	bool res = uc_is_property(uc, *property);
	lua_pushboolean(L, res);
	return 1;
}


int luaopen_unistring_ctype_property(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"byname", lunistring_uc_property_byname},
		{"is", lunistring_uc_is_property},
		{NULL, NULL}
	};
	static const luaL_Reg uc_property_methods[] = {
		{"is_valid", lunistring_uc_property_is_valid},
		{NULL, NULL}
	};

	luaL_checkversion(L);
	lua_settop(L, 0);

	/* create weak table to dedupe uc_property_t */
	lua_newtable(L);
	lua_createtable(L, 0, 1);
	lua_pushliteral(L, "kv");
	lua_setfield(L, -2, "__mode");
	lua_setmetatable(L, -2);

	luaL_newmetatable(L, "uc_property_t");
	luaL_newlib(L, uc_property_methods);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);

	lua_createtable(L, 0, sizeof(lib)/sizeof((lib)[0]) - 1
		+ sizeof(uc_property_methods)/sizeof((uc_property_methods)[0]) - 1);
	lua_pushvalue(L, 1);
	luaL_setfuncs(L, lib, 1);
	luaL_setfuncs(L, uc_property_methods, 0); // add methods to lib too

	return 1;
}
