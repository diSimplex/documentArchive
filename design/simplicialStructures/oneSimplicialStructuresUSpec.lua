--[[

 This is an initial sketch of an interface to oneSimplicialStructures.

 WARNING: I do NOT know how to do this!  ;-(

--]]


disitt = require 'disittRaw'
local simplex = disitt.simplex
local word    = disitt.word
local object  = disitt.object

describe("RAW one simplicial structures", function()

  before_each(function()
    local a = object
    local b = object
    local c = object
    local d = object

    local f = word{ 
      simplex{ a, b }
    }

    local g = word{
      simplex{ c, d }
    }

    local bEQc = word {
      simplex{ b, c }
    }

    -- here be dragons!
    -- local fg = 0
    -- what do we mean by composition?!
  end)

  it("should have zero simplicies", function()
    
    assert.is_true(false)

  end)

end)
