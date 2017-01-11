package = "unistring"
version = "scm-0"
source = {
	url = "git+https://github.com/daurnimator/lua-unistring.git";
}
description = {
	detailed = "Bindings to libunistring, a C library for handling unicode.";
	homepage = "https://github.com/daurnimator/lua-unistring";
	license = "MIT";
}
dependencies = {}
external_dependencies = {
	UNISTRING = {
		header = "unistr.h";
		library = "unistring";
	};
}
build = {
	type = "builtin";
	modules = {
		unistring = {
			sources = {
				"unistring/unistring.c";
				"unistring/uniconv.c";
				"unistring/unilbrk.c";
				"unistring/uc.c";
				"unistring/uc_bidi_category.c";
				"unistring/uc_general_category.c";
				"unistring/uc_property.c";
			};
			libraries = {
				"unistring";
			};
			incdirs = {
				"vendor/compat-5.3/c-api/";
				"$(UNISTRING_INCDIR)";
			};
			libdirs = {
				"$(UNISTRING_LIBDIR)";
			};
		};
	};
}
