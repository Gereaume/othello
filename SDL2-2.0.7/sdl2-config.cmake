# sdl2 cmake project-config input for ./configure scripts

set(prefix "/info/etu/l2info/l2info022/Projet/othello/SDL2-2.0.7/bin") 
set(exec_prefix "${prefix}")
set(libdir "${exec_prefix}/lib")
set(SDL2_PREFIX "/info/etu/l2info/l2info022/Projet/othello/SDL2-2.0.7/bin")
set(SDL2_EXEC_PREFIX "/info/etu/l2info/l2info022/Projet/othello/SDL2-2.0.7/bin")
set(SDL2_LIBDIR "${exec_prefix}/lib")
set(SDL2_INCLUDE_DIRS "${prefix}/include/SDL2")
set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lSDL2 ")
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
