#include <stdlib.h> /* NULL */

#include <uniconv.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"


static enum iconv_ilseq_handler iconvehs[] = {iconveh_error, iconveh_question_mark, iconveh_escape_sequence};
static const char *const iconvehnames[] = {"error", "question_mark", "escape_sequence", NULL};
#define lunistring_checkiconveh(L, arg) (iconvehs[luaL_checkoption((L), (arg), NULL, iconvehnames)])
#define lunistring_opticonveh(L, arg, d) (lua_isnoneornil(L,(arg))?(d):lunistring_checkiconveh((L), (arg)))


static int lunistring_conv_from_encoding(lua_State *L) {
	const char *fromcode = luaL_checkstring(L, 1);
	enum iconv_ilseq_handler handler = lunistring_opticonveh(L, 2, iconveh_error);
	size_t srclen;
	const char *src = luaL_checklstring(L, 3, &srclen);
	/* TODO: support offsets */
	luaL_Buffer b;
	size_t lengthp = srclen; /* starting guess of equal length */
	uint8_t *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = (uint8_t*)luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_conv_from_encoding(fromcode, handler, src, srclen, NULL, resultbuf, &lengthp))) {
			return luaL_fileresult(L, 0, NULL);
		}
		if (tmp != resultbuf) {
			free(tmp);
		} else {
			break;
		}
	}

	luaL_pushresultsize(&b, lengthp);
	return 1;
}


static int lunistring_conv_to_encoding(lua_State *L) {
	const char *tocode = luaL_checkstring(L, 1);
	enum iconv_ilseq_handler handler = lunistring_opticonveh(L, 2, iconveh_error);
	size_t srclen;
	const uint8_t *src = (const uint8_t*)luaL_checklstring(L, 3, &srclen);
	/* TODO: support offsets */
	luaL_Buffer b;
	size_t lengthp = srclen; /* starting guess of equal length */
	char *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_conv_to_encoding(tocode, handler, src, srclen, NULL, resultbuf, &lengthp))) {
			return luaL_fileresult(L, 0, NULL);
		}
		if (tmp != resultbuf) {
			free(tmp);
		} else {
			break;
		}
	}

	luaL_pushresultsize(&b, lengthp);
	return 1;
}


int luaopen_unistring_uniconv(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"from_encoding", lunistring_conv_from_encoding},
		{"to_encoding", lunistring_conv_to_encoding},
		{NULL, NULL}
	};

	luaL_newlib(L, lib);

	return 1;
}
