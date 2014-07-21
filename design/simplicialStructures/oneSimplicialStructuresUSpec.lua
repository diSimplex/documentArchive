--[[

 This is an initial sketch of an interface to oneSimplicialStructures.

--]]

disitt = require 'disittRaw'
local simplex = disitt.simplex
local word    = disitt.word
local object  = disitt.object

describe("RAW zero simplicies", function()

  it("should be zero simplex", function()
    local a = simplex(10)

    assert.is_equal(a:dimension(), 0)
    assert.is_equal(a:name(), 10)
  end)

  it("two zero simplicies with the same name should be identical", function()
    local a = simplex(10)
    local b = simplex(10)

    assert.are.equal(a, b)
  end)

end)

describe("RAW one simplicies", function()

  it("should be a one simplex", function()
    local a = simplex(10)
    local b = simplex(12)
    local c = simplex(11, a, b)

    assert.is.equal(c:name(), 11)
    assert.is.equal(c:dimension(), 1)
  end)

  it("one simplicies should only contain zero simplicies", function()
    local a = simplex(10)
    local b = simplex(12)
    local c = simplex(11, a, b)

    assert.has_error(function() simplex(13, a, c) end)
  end)

  it("one simplicies can only be built out of zero simplicies", function()

    assert.has_error(function() simplex(14, 'silly') end)

  end)

end)
