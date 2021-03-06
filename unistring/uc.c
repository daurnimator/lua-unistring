#include <stdlib.h> /* NULL */

#include <unictype.h>
#include <uniwbrk.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"


static int lunistring_uc_wordbreak_property(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	int res = uc_wordbreak_property(uc);
	lua_pushinteger(L, res);
	return 1;
}


static int lunistring_uc_decimal_value(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	int res = uc_decimal_value(uc);
	if (res == -1) {
		lua_pushnil(L);
	} else {
		lua_pushinteger(L, res);
	}
	return 1;
}


static int lunistring_uc_digit_value(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	int res = uc_digit_value(uc);
	if (res == -1) {
		lua_pushnil(L);
	} else {
		lua_pushinteger(L, res);
	}
	return 1;
}


static int lunistring_uc_numeric_value(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	uc_fraction_t res = uc_numeric_value(uc);
	if (res.numerator == 0 && res.denominator == 0) {
		lua_pushnil(L);
		return 1;
	} else {
		lua_pushinteger(L, res.numerator);
		lua_pushinteger(L, res.denominator);
		return 2;
	}
}


static int lunistring_uc_mirror_char(lua_State *L) {
	ucs4_t uc = luaL_checkinteger(L, 1);
	ucs4_t puc;
	bool res = uc_mirror_char(uc, &puc);
	lua_pushboolean(L, res);
	lua_pushinteger(L, puc);
	return 2;
}


int luaopen_unistring_ctype(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"wordbreak_property", lunistring_uc_wordbreak_property},
		{"decimal_value", lunistring_uc_decimal_value},
		{"digit_value", lunistring_uc_digit_value},
		{"numeric_value", lunistring_uc_numeric_value},
		{"mirror_char", lunistring_uc_mirror_char},
		{NULL, NULL}
	};

	luaL_newlib(L, lib);

	lua_createtable(L, 0, 13);
	lua_pushinteger(L, WBP_OTHER);
	lua_setfield(L, -2, "OTHER");
	lua_pushinteger(L, WBP_CR);
	lua_setfield(L, -2, "CR");
	lua_pushinteger(L, WBP_LF);
	lua_setfield(L, -2, "LF");
	lua_pushinteger(L, WBP_NEWLINE);
	lua_setfield(L, -2, "NEWLINE");
	lua_pushinteger(L, WBP_EXTEND);
	lua_setfield(L, -2, "EXTEND");
	lua_pushinteger(L, WBP_FORMAT);
	lua_setfield(L, -2, "FORMAT");
	lua_pushinteger(L, WBP_KATAKANA);
	lua_setfield(L, -2, "KATAKANA");
	lua_pushinteger(L, WBP_ALETTER);
	lua_setfield(L, -2, "ALETTER");
	lua_pushinteger(L, WBP_MIDNUMLET);
	lua_setfield(L, -2, "MIDNUMLET");
	lua_pushinteger(L, WBP_MIDLETTER);
	lua_setfield(L, -2, "MIDLETTER");
	lua_pushinteger(L, WBP_MIDNUM);
	lua_setfield(L, -2, "MIDNUM");
	lua_pushinteger(L, WBP_NUMERIC);
	lua_setfield(L, -2, "NUMERIC");
	lua_pushinteger(L, WBP_EXTENDNUMLET);
	lua_setfield(L, -2, "EXTENDNUMLET");
	lua_setfield(L, -2, "WBP");

	return 1;
}
