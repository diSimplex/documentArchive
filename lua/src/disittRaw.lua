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
  return self.myValues.n - 1
end

function Simplex:name()
  return self.myName
end

Simplex.__index = Simplex
Simplex.type = "Simplex"

function M.simplex(aName, ...)
  local someValues =  table.pack(...)
  for i, v in ipairs{...} do
    if v.type ~= "Simplex" then
      error("Trying to created a simplex using nonsimplicies")
    end
    if v:dimension() ~= someValues.n-2 then
      error("Using simplicies of the wrong dimension")
    end
  end
  if Simplex.instances[aName] ~= nil then
    return Simplex.instances[aName]
  end
  obj = {myName = aName, myValues = someValues }
  setmetatable(obj, Simplex)
  if someValues.n == 0 then
    someValues.n = 1
    someValues[0] = obj
  end
  Simplex.instances[aName] = obj
  return obj
end

function M.word(values)
end

return M
