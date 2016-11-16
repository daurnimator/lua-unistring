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
	end)
end)
