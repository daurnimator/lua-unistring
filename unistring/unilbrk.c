#include <stdlib.h> /* NULL */

#include <unilbrk.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"


static int lunistring_possible_linebreaks(lua_State *L) {
	size_t n, i;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *encoding = luaL_checkstring(L, 2);
	char *p = lua_newuserdata(L, n);

	u8_possible_linebreaks(s, n, encoding, p);

	lua_createtable(L, n, 0);
	for (i = 0; i < n; i++) {
		switch(p[i]) {
		case UC_BREAK_MANDATORY:
			lua_pushliteral(L, "mandatory");
			break;
		case UC_BREAK_POSSIBLE:
			lua_pushliteral(L, "possible");
			break;
		case UC_BREAK_HYPHENATION:
			lua_pushliteral(L, "hyphenation");
			break;
		case UC_BREAK_PROHIBITED:
			lua_pushliteral(L, "prohibited");
			break;
		default:
			return luaL_error(L, "unknown UC_BREAK type");
		}
		lua_rawseti(L, -2, i+1);
	}

	return 1;
}


static int lunistring_width_linebreaks(lua_State *L) {
	size_t n, i;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	int width = luaL_checkinteger(L, 2);
	int start_column = luaL_checkinteger(L, 3);
	int at_end_columns = luaL_checkinteger(L, 4);
	/* TODO: support override argument */
	const char *override = (luaL_checktype(L, 5, LUA_TNIL), NULL);
	const char *encoding = luaL_checkstring(L, 6);
	char *p = lua_newuserdata(L, n);

	int end_column = u8_width_linebreaks(s, n, width, start_column, at_end_columns, override, encoding, p);

	lua_createtable(L, n, 0);
	for (i = 0; i < n; i++) {
		switch (p[i]) {
		case UC_BREAK_MANDATORY:
			lua_pushliteral(L, "mandatory");
			break;
		case UC_BREAK_POSSIBLE:
			lua_pushliteral(L, "possible");
			break;
		case UC_BREAK_HYPHENATION:
			lua_pushliteral(L, "hyphenation");
			break;
		case UC_BREAK_PROHIBITED:
			lua_pushliteral(L, "prohibited");
			break;
		default:
			return luaL_error(L, "unknown UC_BREAK type");
		}
		lua_rawseti(L, -2, i+1);
	}

	lua_pushinteger(L, end_column);

	return 2;
}


int luaopen_unistring_unilbrk(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"possible_linebreaks", lunistring_possible_linebreaks},
		{"width_linebreaks", lunistring_width_linebreaks},
		{NULL, NULL}
	};
	luaL_newlib(L, lib);
	return 1;
}
