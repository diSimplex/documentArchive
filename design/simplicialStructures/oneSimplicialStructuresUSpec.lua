--[[

 This is an initial sketch of an interface to oneSimplicialStructures.

--]]

local disitt = (require 'diSimplexLuaC').new()

describe("RAW zero simplicies", function()

  it("should be zero simplex", function()
    local a = disitt:simplex({})
    assert.is_equal(a:dimension(), 0)
  end)

end)

describe("RAW one simplicies", function()

  it("should be a one simplex", function()
    local a = disitt:simplex({})
    local b = disitt:simplex({})
    local c = disitt:simplex({a, b})

    assert.is.equal(c:dimension(), 1)
    print("side0 =?= a")
    assert.is.equal(c:side(0), a)
    print("side1 =?= b")
    assert.is.equal(c:side(1), b)
    print("side0 == side1")
    print(c:side(0))
    print(c:side(1))
    assert.is_false(c:side(0) == c:side(1))
    assert.is_not.equal(c:side(0), c:side(1))
  end)

  it("one simplicies should only contain zero simplicies", function()
    local a = disitt:simplex({})
    local b = disitt:simplex({})
    local c = disitt:simplex({a, b})

    assert.has_error(function() disitt:simplex({a, c}) end)
  end)

  it("one simplicies can be built out of an array", function()
    local a = disitt:simplex({})
    local b = disitt:simplex({})
    simplicies = { a, b }
    local c = disitt:simplex(simplicies)

    assert.is.equal(c:dimension(), 1)
    assert.is.equal(c:side(0), a)
    assert.is.equal(c:side(1), b)
    assert.is_not.equal(c:side(0), c:side(1))
  end)

  it("one simplicies can only be built out of zero simplicies", function()

    assert.has_error(function() disitt:simplex({'silly'}) end)

  end)

end)

describe("terminal", function()

  it("should have a unique zero simplex", function()
    local term0 = disitt:terminal(0)
    assert.is.truthy(term0)
    assert.is.equal(term0:dimension(), 0)
    assert.is.equal(term0, disitt:terminal(0))
    local termM1 = disitt:terminal(-1)
    assert.is.equal(term0:side(0), termM1)
  end)

  it("should have a unique one simplex", function()
    local term0 = disitt:terminal(0)
    local term1 = disitt:terminal(1)
    assert.is.truthy(term1)
    assert.is.equal(term1:dimension(), 1)
    assert.is.equal(term1, disitt:terminal(1))
    assert.is.equal(term1:side(0), term0)
    assert.is.equal(term1:side(1), term0)
  end)

end)

describe("structure", function()

  it("should have two zero simplicies", function()
    local struct = disitt:initial()
    local a = disitt:simplex({})
    local b = disitt:simplex({})
    assert.is.equal(struct:size(0),0)
    assert.is.equal(struct:size(1),0)
    struct:add(a)
    assert.is.equal(struct:size(0),1)
    assert.is.equal(struct:size(1),0)
    struct:add(b)
    assert.is.equal(struct:size(0),2)
    assert.is.equal(struct:size(1),0)
    assert.is.equal(struct:simplex(0,0), a)
    assert.is.equal(struct:simplex(0,1), b)
  end)

end)

