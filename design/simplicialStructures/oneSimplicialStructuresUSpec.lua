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
    assert.is.equal(c:side(0), a)
    assert.is.equal(c:side(1), b)
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

describe("universe", function()

  it("should have a unique zero simplex", function()
    local uni0 = disitt:universe(0)
    assert.is.truthy(uni0)
    assert.is.equal(uni0:dimension(), 0)
    assert.is.equal(uni0, disitt:universe(0))
    local uniM1 = disitt:universe(-1)
    assert.is.equal(uni0:side(0), uniM1)
  end)

  it("should have a unique one simplex", function()
    local uni0 = disitt:universe(0)
    local uni1 = disitt:universe(1)
    assert.is.truthy(uni1)
    assert.is.equal(uni1:dimension(), 1)
    assert.is.equal(uni1, disitt:universe(1))
    assert.is.equal(uni1:side(0), uni0)
    assert.is.equal(uni1:side(1), uni0)
  end)

end)

describe("structure", function()

  it("should have two zero simplicies", function()
    local struct = disitt:structure()
    local a = disitt:simplex({})
    local b = disitt:simplex({})
    assert.is.equal(struct:size(0),0)
    struct:add(a)
    assert.is.equal(struct:size(0),1)
    struct:add(b)
    assert.is.equal(struct:size(0),2)
    assert.is.equal(struct:simplex(0,0), a)
    assert.is.equal(struct:simplex(0,1), b)
  end)

end)
