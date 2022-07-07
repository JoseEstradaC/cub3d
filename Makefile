all: flat.c
	gcc flat.c MLX42/libmlx42.a -I MLX42/include/ -ldl -lglfw -o main

prueba: prueba.c
	gcc prueba.c MLX42/libmlx42.a -I MLX42/include/ -ldl -lglfw -o prueba
