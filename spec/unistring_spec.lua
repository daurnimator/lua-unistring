local unistring = require "unistring"
describe("casefold", function()
	it("works", function()
		assert.same("foo", unistring.casefold("foo", nil, "NFC"))
		assert.same("foo", unistring.casefold("Foo", nil, "NFC"))
		assert.same("strasse", unistring.casefold("Straße", nil, "NFC"))
		-- Some russian chars (randomly grabbed from https://stackoverflow.com/questions/5777902/converting-russian-characters-from-upper-case-to-lower-case-in-php)
		assert.same("ёйцукенгшщзхъфывапролджэячсмитьбю", unistring.casefold("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ", nil, "NFC"))
		-- Longest decomposition
		assert.same("صلى الله عليه وسلم", unistring.casefold("ﷺ", nil, "NFKD"))
		-- null byte
		assert.same("\0", unistring.casefold("\0", nil, "NFC"))
	end)
	it("handles corrupt unicode", function()
		-- invalid char
		assert.same("�", unistring.casefold("\254", nil, "NFC"))
		-- overlong
		assert.same("��", unistring.casefold("\192\128", nil, "NFC"))
		-- invalid code point
		assert.same(nil, (unistring.casefold("\237\160\128", nil, "NFC")))
	end)
end)
