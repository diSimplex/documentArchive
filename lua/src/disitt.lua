-- This is the DiSitt module

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
function M.simplex(values)
end

function M.word(values)
end

function M.object(values)
end

return M
