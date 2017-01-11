describe("unilbrk", function()
	local unilbrk = require "unistring.unilbrk"
	it("possible_linebreaks works", function()
		assert.same({
			"prohibited";
			"prohibited";
			"prohibited";
			"prohibited";
			"possible";
			"prohibited";
			"prohibited";
			"mandatory";
			"prohibited";
			"prohibited";
			"prohibited";
		}, unilbrk.possible_linebreaks("foo bar\nbaz", ""))
	end)
	it("width_linebreaks works", function()
		assert.same({
			"prohibited";
			"prohibited";
			"prohibited";
			"prohibited";
			"prohibited";
			"prohibited";
			"prohibited";
			"mandatory";
			"prohibited";
			"prohibited";
			"prohibited";
		}, unilbrk.width_linebreaks("foo bar\nbaz", 80, 0, 80, nil, ""))
		assert.same({
			"prohibited";
			"prohibited";
			"prohibited";
			"prohibited";
			"possible";
			"prohibited";
			"prohibited";
			"mandatory";
			"prohibited";
			"prohibited";
			"prohibited";
		}, unilbrk.width_linebreaks("foo bar\nbaz", 5, 0, 5, nil, ""))
	end)
end)
