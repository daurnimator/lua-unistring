describe("uniconv", function()
	local uniconv = require "unistring.uniconv"
	it("from_encoding works", function()
		assert.same("foo", uniconv.from_encoding("UCS2", nil, "f\0o\0o\0"))
	end)
	it("to_encoding works", function()
		assert.same("f\0o\0o\0", uniconv.to_encoding("UCS2", nil, "foo"))
	end)
end)
