
file(GLOB Lua_SOURCES src/*.c)
add_library(lua STATIC  ${Lua_SOURCES})