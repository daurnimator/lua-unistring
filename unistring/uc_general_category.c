#include <stdlib.h> /* NULL */

#include <unictype.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"


static void lunistring_pushucgeneralcategory(lua_State *L, uc_general_category_t category) {
	uc_general_category_t *ud = lua_newuserdata(L, sizeof(uc_general_category_t));
	*ud = category;
	luaL_setmetatable(L, "uc_general_category_t");
}


static int lunistring_uc_general_category(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	uc_general_category_t res = uc_general_category(uc);
	lunistring_pushucgeneralcategory(L, res);
	return 1;
}


static int lunistring_uc_general_category_and(lua_State *L) {
	uc_general_category_t res = *(uc_general_category_t*)luaL_checkudata(L, 1, "uc_general_category_t");
	int n = lua_gettop(L);
	int i;
	for (i=2; i<=n; i++) {
		res = uc_general_category_and(res, *(uc_general_category_t*)luaL_checkudata(L, i, "uc_general_category_t"));
	}
	lunistring_pushucgeneralcategory(L, res);
	return 1;
}


static int lunistring_uc_general_category_or(lua_State *L) {
	uc_general_category_t res = *(uc_general_category_t*)luaL_checkudata(L, 1, "uc_general_category_t");
	int n = lua_gettop(L);
	int i;
	for (i=2; i<=n; i++) {
		res = uc_general_category_or(res, *(uc_general_category_t*)luaL_checkudata(L, i, "uc_general_category_t"));
	}
	lunistring_pushucgeneralcategory(L, res);
	return 1;
}


static int lunistring_uc_general_category_and_not(lua_State *L) {
	uc_general_category_t *category1 = luaL_checkudata(L, 1, "uc_general_category_t");
	uc_general_category_t *category2 = luaL_checkudata(L, 2, "uc_general_category_t");
	uc_general_category_t res = uc_general_category_and_not(*category1, *category2);
	lunistring_pushucgeneralcategory(L, res);
	return 1;
}


static int lunistring_uc_general_category_name(lua_State *L) {
	uc_general_category_t *category = luaL_checkudata(L, 1, "uc_general_category_t");
	lua_pushstring(L, uc_general_category_name(*category));
	return 1;
}


static int lunistring_uc_general_category_byname(lua_State *L) {
	const char *name = luaL_checkstring(L, 1);
	uc_general_category_t res = uc_general_category_byname(name);
	lunistring_pushucgeneralcategory(L, res);
	return 1;
}


static int lunistring_uc_is_general_category(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	uc_general_category_t *category = luaL_checkudata(L, 2, "uc_general_category_t");
	bool res = uc_is_general_category(uc, *category);
	lua_pushboolean(L, res);
	return 1;
}


int luaopen_unistring_ctype_general_category(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"of", lunistring_uc_general_category},
		{"byname", lunistring_uc_general_category_byname},
		{"is", lunistring_uc_is_general_category},
		{NULL, NULL}
	};
	static const luaL_Reg uc_general_category_methods[] = {
		{"and", lunistring_uc_general_category_and},
		{"or", lunistring_uc_general_category_or},
		{"and_not", lunistring_uc_general_category_and_not},
		{"name", lunistring_uc_general_category_name},
		/* aliases as 'and' and 'or' are reserved words in lua */
		{"And", lunistring_uc_general_category_and},
		{"Or", lunistring_uc_general_category_or},
		{NULL, NULL}
	};

	luaL_newmetatable(L, "uc_general_category_t");
	luaL_newlib(L, uc_general_category_methods);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);

	luaL_newlib(L, lib);
	luaL_setfuncs(L, uc_general_category_methods, 0); // add methods to lib too

	return 1;
}
