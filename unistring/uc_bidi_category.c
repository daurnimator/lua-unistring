#include <stdlib.h> /* NULL */

#include <unictype.h>

#include <lua.h>
#include <lauxlib.h>


static int lunistring_uc_bidi_category_name(lua_State *L) {
	int category = luaL_checkinteger(L, 1);
	lua_pushstring(L, uc_bidi_category_name(category));
	return 1;
}


static int lunistring_uc_bidi_category_byname(lua_State *L) {
	const char *name = luaL_checkstring(L, 1);
	int res = uc_bidi_category_byname(name);
	lua_pushinteger(L, res);
	return 1;
}


static int lunistring_uc_bidi_category(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	int res = uc_bidi_category(uc);
	lua_pushinteger(L, res);
	return 1;
}


static int lunistring_uc_is_bidi_category(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	int category = luaL_checkinteger(L, 2);
	bool res = uc_is_bidi_category(uc, category);
	lua_pushboolean(L, res);
	return 1;
}


int luaopen_unistring_ctype_bidi_category(lua_State *L) {
	static const luaL_Reg category_lib[] = {
		{"name", lunistring_uc_bidi_category_name},
		{"byname", lunistring_uc_bidi_category_byname},
		{"of", lunistring_uc_bidi_category},
		{"is", lunistring_uc_is_bidi_category},
		{NULL, NULL}
	};
	luaL_newlib(L, category_lib);
	return 1;
}
