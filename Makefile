CC = g++
OBJECT = ./bin/main.o ./bin/Game.o ./bin/TextureManager.o ./bin/InputHandler.o
LIBRARY = ./lib/SDL2/SDL2.lib ./lib/SDL2/SDL2main.lib ./lib/SDL2/SDL2.dll \
          ./lib/SDL2/SDL2_image.lib ./lib/SDL2/SDL2_image.dll ./lib/SDL2/libpng16-16.dll

beginner:$(OBJECT) $(LIBRARY)
	$(CC) -o beginner -Wl,-rpath ./lib/SDL2/ $(OBJECT) $(LIBRARY)

./bin/main.o:./src/main.cpp ./include/Game.h
	$(CC) -o ./bin/main.o -c ./src/main.cpp -I ./include/SDL2/ -I ./include/

./bin/Game.o:./src/Game.cpp ./include/Game.h ./include/TextureManager.h ./include/InputHandler.h
	$(CC) -o ./bin/Game.o -c ./src/Game.cpp -I ./include/SDL2/ -I ./include/

./bin/TextureManager.o:./src/TextureManager.cpp ./include/TextureManager.h
	$(CC) -o ./bin/TextureManager.o -c ./src/TextureManager.cpp -I ./include/SDL2/ -I ./include/

./bin/InputHandler.o:./src/InputHandler.cpp ./include/InputHandler.h ./include/Game.h ./include/Vector2D.h
	$(CC) -o ./bin/InputHandler.o -c ./src/InputHandler.cpp -I ./include/SDL2/ -I ./include/

#./bin/SDLGameObject.o:./src/SDLGameObject.cpp ./include/Game.h ./include/Resource.h \
                      ./include/GameObject.h ./include/LoaderParams.h ./include/SDLGameObject.h \
	$(CC) -o ./bin/SDLGameObject.o -c ./src/SDLGameObject.cpp -I ./include/SDL2/ -I ./include/

#./bin/Player.o:./src/Player.cpp ./include/SDL2/SDL.h ./include/LoaderParams.h ./include/SDLGameObject.h \
               ./include/Player.h \
	$(CC) -o ./bin/Player.o -c ./src/Player.cpp -I ./include/SDL2/ -I ./include/

#./bin/Enemy.o:./src/Enemy.cpp ./include/SDL2/SDL.h ./include/LoaderParams.h ./include/SDLGameObject.h \
               ./include/Enemy.h \
	$(CC) -o ./bin/Enemy.o -c ./src/Enemy.cpp -I ./include/SDL2/ -I ./include/

clean:
	rm ./bin/*.o beginner