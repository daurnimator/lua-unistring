describe("general categories", function()
	local general_category = require "unistring.ctype.general_category"
	it("has working .is()", function()
		assert.same(true, general_category.is(string.byte("f"), general_category.byname("LETTER")))
		assert.same(true, general_category.is(string.byte("F"), general_category.byname("LETTER")))
		assert.same(false, general_category.is(string.byte("1"), general_category.byname("LETTER")))
		assert.same(false, general_category.is(string.byte("-"), general_category.byname("LETTER")))
	end)
	it("can be combined with 'or'", function()
		local alnum = general_category.Or(general_category.byname("LETTER"), general_category.byname("NUMBER"))
		assert.same(true, general_category.is(string.byte("f"), alnum))
		assert.same(true, general_category.is(string.byte("F"), alnum))
		assert.same(true, general_category.is(string.byte("1"), alnum))
		assert.same(false, general_category.is(string.byte("-"), alnum))
	end)
	it("can be combined with 'and'", function()
		local upper = general_category.And(general_category.byname("LETTER"), general_category.byname("UPPERCASE_LETTER"))
		assert.same(false, general_category.is(string.byte("f"), upper))
		assert.same(true, general_category.is(string.byte("F"), upper))
		assert.same(false, general_category.is(string.byte("1"), upper))
		assert.same(false, general_category.is(string.byte("-"), upper))
	end)
	it("has a working :name()", function()
		assert.same("L", general_category.byname("L"):name())
		assert.same("L", general_category.byname("LETTER"):name())
	end)
	it("has working .of()", function()
		assert.same("Ll", general_category.of(string.byte("f")):name())
	end)
end)