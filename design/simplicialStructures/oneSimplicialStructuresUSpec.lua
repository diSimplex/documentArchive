--[[

 This is an initial sketch of an interface to oneSimplicialStructures.

--]]

disitt = require 'disittRaw'
local simplex  = disitt.simplex
local universe = disitt.universe
local word     = disitt.word
local object   = disitt.object

describe("RAW zero simplicies", function()

  it("should be zero simplex", function()
    local a = simplex({})

    assert.is_equal(a:dimension(), 0)
  end)

end)

describe("RAW one simplicies", function()

  it("should be a one simplex", function()
    local a = simplex({})
    local b = simplex({})
    local c = simplex({a, b})

    assert.is.equal(c:dimension(), 1)
    assert.is.equal(c:side(0), a)
    assert.is.equal(c:side(1), b)
    assert.is_not.equal(c:side(0), c:side(1))
  end)

  it("one simplicies should only contain zero simplicies", function()
    local a = simplex({})
    local b = simplex({})
    local c = simplex({a, b})

    assert.has_error(function() simplex({a, c}) end)
  end)

  it("one simplicies can be built out of an array", function()
    local a = simplex({})
    local b = simplex({})
    simplicies = { a, b }
    local c = simplex(simplicies)

    assert.is.equal(c:dimension(), 1)
    assert.is.equal(c:side(0), a)
    assert.is.equal(c:side(1), b)
    assert.is_not.equal(c:side(0), c:side(1))
  end)

  it("one simplicies can only be built out of zero simplicies", function()

    assert.has_error(function() simplex({'silly'}) end)

  end)

end)

describe("universe", function()

  it("should have a unique zero simplex", function()
    local uni0 = universe(0)
    assert.is.truthy(uni0)
    assert.is.equal(uni0:dimension(), 0)
    assert.is.equal(uni0, universe(0))
    assert.is.equal(uni0:side(0), nil)
  end)

  it("should have a unique one simplex", function()
    local uni0 = universe(0)
    local uni1 = universe(1)
    assert.is.truthy(uni1)
    assert.is.equal(uni1:dimension(), 1)
    assert.is.equal(uni1, universe(1))
    assert.is.equal(uni1:side(0), uni0)
    assert.is.equal(uni1:side(1), uni0)
  end)

end)
