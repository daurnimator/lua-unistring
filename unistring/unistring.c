#include <stdlib.h> /* NULL */

#include <unistring/version.h>
#include <unicase.h>
#include <uninorm.h>
#include <uniwidth.h>

#include <lua.h>
#include <lauxlib.h>

#include "compat-5.3.h"


static const uninorm_t uninorms[] = {UNINORM_NFD, UNINORM_NFC, UNINORM_NFKD, UNINORM_NFKC};
static const char *const uninormnames[] = {"NFD", "NFC", "NFKD", "NFKC", NULL};
#define lunistring_checkuninorm(L, arg) (uninorms[luaL_checkoption((L), (arg), NULL, uninormnames)])
#define lunistring_optuninorm(L, arg, d) (lua_isnoneornil(L,(arg))?(d):lunistring_checkuninorm((L), (arg)))


static int lunistring_width(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *encoding = luaL_checkstring(L, 2);
	int res = u8_width(s, n, encoding);
	lua_pushinteger(L, res);
	return 1;
}


static int lunistring_normalize(lua_State *L) {
	uninorm_t nf = lunistring_optuninorm(L, 1, NULL);
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


static int lunistring_normxfrm(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	uninorm_t nf = lunistring_checkuninorm(L, 2);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	char *resultbuf, *tmp;
	luaL_argcheck(L, nf == UNINORM_NFC || nf == UNINORM_NFKC, 2, "must be either \"NFC\" or \"NFKC\"");


	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_normxfrm(s, n, nf, resultbuf, &lengthp))) {
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


static int lunistring_uc_locale_language(lua_State *L) {
	lua_pushstring(L, uc_locale_language());
	return 1;
}


static int lunistring_toupper(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 3, NULL);
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
	uninorm_t nf = lunistring_optuninorm(L, 3, NULL);
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
	uninorm_t nf = lunistring_optuninorm(L, 3, NULL);
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
	uninorm_t nf = lunistring_optuninorm(L, 3, NULL);
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


static int lunistring_casexfrm(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 3, NULL);
	luaL_Buffer b;
	size_t lengthp = n; /* starting guess of equal length */
	char *resultbuf, *tmp;
	luaL_argcheck(L, nf == UNINORM_NFC || nf == UNINORM_NFKC || nf == NULL, 3, "must be either \"NFC\", \"NFKC\", or nil");

	luaL_buffinit(L, &b);

	while (1) {
		resultbuf = luaL_prepbuffsize(&b, lengthp);
		if (!(tmp = u8_casexfrm(s, n, iso639_language, nf, resultbuf, &lengthp))) {
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


static int lunistring_casecoll(lua_State *L) {
	size_t n1, n2;
	const uint8_t *s1 = (const uint8_t*)luaL_checklstring(L, 1, &n1);
	const uint8_t *s2 = (const uint8_t*)luaL_checklstring(L, 2, &n2);
	const char *iso639_language = luaL_optstring(L, 3, NULL);
	uninorm_t nf = lunistring_optuninorm(L, 4, NULL);
	int resultp;
	luaL_argcheck(L, nf == UNINORM_NFC || nf == UNINORM_NFKC || nf == NULL, 3, "must be either \"NFC\", \"NFKC\", or nil");

	if (-1 == u8_casecoll(s1, n1, s2, n2, iso639_language, nf, &resultp)) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushinteger(L, resultp);
	return 1;
}


static int lunistring_is_uppercase(lua_State *L) {
	size_t n;
	const uint8_t *s = (const uint8_t*)luaL_checklstring(L, 1, &n);
	const char *iso639_language = luaL_optstring(L, 2, NULL);
	bool resultp;

	if (-1 == u8_is_uppercase(s, n, iso639_language, &resultp)) {
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

	if (-1 == u8_is_lowercase(s, n, iso639_language, &resultp)) {
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

	if (-1 == u8_is_titlecase(s, n, iso639_language, &resultp)) {
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

	if (-1 == u8_is_casefolded(s, n, iso639_language, &resultp)) {
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

	if (-1 == u8_is_cased(s, n, iso639_language, &resultp)) {
		return luaL_fileresult(L, 0, NULL);
	}

	lua_pushboolean(L, resultp);
	return 1;
}


int luaopen_unistring(lua_State *L) {
	static const luaL_Reg lib[] = {
		{"width", lunistring_width},
		{"normalize", lunistring_normalize},
		{"normxfrm", lunistring_normxfrm},
		{"locale_language", lunistring_uc_locale_language},
		{"toupper", lunistring_toupper},
		{"tolower", lunistring_tolower},
		{"totitle", lunistring_totitle},
		{"casefold", lunistring_casefold},
		{"casexfrm", lunistring_casexfrm},
		{"casecoll", lunistring_casecoll},
		{"is_uppercase", lunistring_is_uppercase},
		{"is_lowercase", lunistring_is_lowercase},
		{"is_titlecase", lunistring_is_titlecase},
		{"is_casefolded", lunistring_is_casefolded},
		{"is_cased", lunistring_is_cased},
		{NULL, NULL}
	};

	luaL_newlib(L, lib);

	lua_pushinteger(L, _libunistring_version);
	lua_setfield(L, -2, "libunistring_version");
	lua_pushinteger(L, _LIBUNISTRING_VERSION);
	lua_setfield(L, -2, "LIBUNISTRING_VERSION");

	return 1;
}
