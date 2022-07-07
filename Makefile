all: flat.c
	gcc flat.c MLX42/libmlx42.a -I MLX42/include/ -ldl -lglfw \
		-L /sgoinfre/goinfre/Perso/jarredon/homebrew/Cellar/glfw/3.3.7/lib -o main

prueba: prueba.c
	gcc prueba.c MLX42/libmlx42.a -I MLX42/include/ -ldl -lglfw \
		-L /sgoinfre/goinfre/Perso/jarredon/homebrew/Cellar/glfw/3.3.7/lib \
		-o prueba

cpp:
	c++ raycaster_flat.cpp quickcg.cpp -lSDL \
		-I /sgoinfre/goinfre/Perso/jarredon/homebrew/Cellar/sdl12-compat/1.2.52_1/include \
		-L /sgoinfre/goinfre/Perso/jarredon/homebrew/Cellar/sdl12-compat/1.2.52_1/lib/
