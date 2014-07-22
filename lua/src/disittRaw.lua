-- This is the DiSitt module

local pp = require 'pl.pretty'

local M = {}

-- need ordinals
-- need simplices
-- need structures
-- need ability to access all simplices of a given order
-- need includes simplex 
-- need rules
-- need rule inference?
-- definitional structure
-- theorem structure
-- example structure
-- reguirement infrastructure
-- distribution infrastructure
-- dependency analysis

--[[

A Simplex consists of an ordered collection of simplicies of lower orders.

Can it in fact be reconstructed simply from an ordered collection of 
zero order simplicies and the face maps?

An examplar is an (open?) cover of the definition of a co-algebraic 
object. SO we ensure all simplicies contain this cover. SO every 
simplex has a link/reference to a simplex in its definitional object.  
This essentially is its "type".

This suggests that checking rule inference is "simply" type-checking. 
This suggests that any inference which type checks computes the 
"correct" "value".  How do we deal with the halting problem?  Do we 
even have the "halting problem" but we are not total since we allow for 
directed limits.

--]]

local Simplex = {}

Simplex.instances = {}

function Simplex:dimension()
  return #(self.myValues) - 1
end

function Simplex:name()
  return self.myName
end

function Simplex:side(i)
  return self.myValues[i+1]
end

Simplex.__index = Simplex
Simplex.type = "Simplex"
Simplex.nextName = 100

function M.simplex(simplicies)
  local numSimplicies = 0
  for i, v in ipairs(simplicies) do
    if v.type ~= "Simplex" then
      error("Trying to create a simplex using nonsimplicies")
    end
    if v:dimension() ~= #simplicies-2 then
      error("Using simplicies of the wrong dimension")
    end
    numSimplicies = numSimplicies + 1
  end
  simplicies.n = numSimplicies

  obj = {myId = #(Simplex.instances), myValues = simplicies }
  setmetatable(obj, Simplex)
  if #(obj.myValues) == 0 then
    obj.myValues[1] = obj
  end
  table.insert(Simplex.instances, obj)
  return obj
end

local Universe = {}

function M.universe(dimension)
  if dimension < 1 then
    if Universe.instances[0] == nil then
      Universe.instances[0] = M.simplex('any', {})
    end
    return Universe.instances[0]
  end

  if Universe.instances[dimension] == nil then
    subDim = M.universe(dimension - 1)
    simplicies = {}
    for i = 1, dimension+1 do
      simplicies[i] = subDim
    end
    Universe.instances[dimension] = M.simplex('any', simplicies)
  end
  return Universe.instances[dimension]
end


function M.word(values)
end

return M
