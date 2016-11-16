#include <stdlib.h> /* NULL */

#include <uninorm.h>
#include <unicase.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"

static const uninorm_t uninorms[] = {UNINORM_NFD, UNINORM_NFC, UNINORM_NFKD, UNINORM_NFKC};
static const char *const uninormnames[] = {"NFD", "NFC", "NFKD", "NFKC", NULL};
#define lunistring_checkuninorm(L, arg) (uninorms[luaL_checkoption((L), (arg), NULL, uninormnames)])
#define lunistring_optuninorm(L, arg) (lua_isnoneornil(L,(arg))?NULL:lunistring_checkuninorm((L), (arg)))


static int lunistring_normalize(lua_State *L) {
	uninorm_t nf = lunistring_optuninorm(L, 1);
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 2, &n);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	uint8_t *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = (uint8_t*)luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_normalize(nf, s, n, resultbuf, &lengthp))) {
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


static int lunistring_toupper(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 3);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	uint8_t *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = (uint8_t*)luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_toupper(s, n, iso639_language, nf, resultbuf, &lengthp))) {
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


static int lunistring_tolower(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 3);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	uint8_t *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = (uint8_t*)luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_tolower(s, n, iso639_language, nf, resultbuf, &lengthp))) {
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


static int lunistring_totitle(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 3);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	uint8_t *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = (uint8_t*)luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_totitle(s, n, iso639_language, nf, resultbuf, &lengthp))) {
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


static int lunistring_casefold(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 3);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	uint8_t *resultbuf, *tmp;

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = (uint8_t*)luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_casefold(s, n, iso639_language, nf, resultbuf, &lengthp))) {
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


static int lunistring_is_uppercase(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	bool resultp;
	int res;

	if (-1 == (res = u8_is_uppercase(s, n, iso639_language, &resultp))) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushboolean(L, resultp);
	return 1;
}


static int lunistring_is_lowercase(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	bool resultp;
	int res;

	if (-1 == (res = u8_is_lowercase(s, n, iso639_language, &resultp))) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushboolean(L, resultp);
	return 1;
}


static int lunistring_is_titlecase(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	bool resultp;
	int res;

	if (-1 == (res = u8_is_titlecase(s, n, iso639_language, &resultp))) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushboolean(L, resultp);
	return 1;
}


static int lunistring_is_casefolded(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	bool resultp;
	int res;

	if (-1 == (res = u8_is_casefolded(s, n, iso639_language, &resultp))) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushboolean(L, resultp);
	return 1;
}


static int lunistring_is_cased(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	bool resultp;
	int res;

	if (-1 == (res = u8_is_cased(s, n, iso639_language, &resultp))) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushboolean(L, resultp);
	return 1;
}


int luaopen_unistring(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"normalize", lunistring_normalize},
		{"toupper", lunistring_toupper},
		{"tolower", lunistring_tolower},
		{"totitle", lunistring_totitle},
		{"casefold", lunistring_casefold},
		{"is_uppercase", lunistring_is_uppercase},
		{"is_lowercase", lunistring_is_lowercase},
		{"is_titlecase", lunistring_is_titlecase},
		{"is_casefolded", lunistring_is_casefolded},
		{"is_cased", lunistring_is_cased},
		{NULL, NULL}
	};
	luaL_newlib(L, lib);
	return 1;
}
