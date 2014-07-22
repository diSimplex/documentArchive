package.cpath = package.cpath .. ";" .. os.getenv("HOME") .. "/.luarocks/lib/lua/5.2/?.so"

print(package.cpath)

local ds = require 'diSimplexLuaC'
print( ds )
print( ds.new() )
