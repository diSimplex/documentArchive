package.cpath = package.cpath .. ";" .. os.getenv("HOME") .. "/.luarocks/lib/lua/5.2/?.so"

print(package.cpath)

local ds = require 'diSimplexLuaC'
print( ds )
disitt = ds.new()
print( disitt )
uni1 = disitt:universe(1)
print( uni1 )
