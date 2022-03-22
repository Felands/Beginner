CC = g++

OBJECT = ./bin/main.o ./bin/Game.o \
         ./bin/Resource.o ./bin/InputHandler.o \
		 ./bin/Player.o ./bin/Enemy.o ./bin/SpecialEffect.o\
         
LIBRARY = ./lib/SDL2/SDL2.lib ./lib/SDL2/SDL2main.lib ./lib/SDL2/SDL2.dll \
          ./lib/SDL2/SDL2_image.lib ./lib/SDL2/SDL2_image.dll ./lib/SDL2/libpng16-16.dll

INCLUDE = -I ./include/SDL2/ -I ./include/ -I ./include/Foundation/ -I ./include/Object/

HEADFILE = ./include/Game.h \
		   ./include/Foundation/InputHandler.h ./include/Foundation/Resource.h\
		   ./include/Foundation/Vector2D.h \
	       ./include/Object/GameObject.h ./include/Object/Player.h ./include/Object/Enemy.h ./include/Object/SpecialEffect.h

beginner : $(OBJECT)
	$(CC) -o beginner -Wl,-rpath ./lib/SDL2/ $(OBJECT) $(LIBRARY)

./bin/main.o : $(HEADFILE) ./src/main.cpp
	$(CC) $(INCLUDE) -o ./bin/main.o -c ./src/main.cpp

./bin/Game.o : $(HEADFILE) ./src/Game.cpp
	$(CC) $(INCLUDE) -o ./bin/Game.o -c ./src/Game.cpp

./bin/InputHandler.o : $(HEADFILE) ./src/Foundation/InputHandler.cpp
	$(CC) $(INCLUDE) -o ./bin/InputHandler.o -c ./src/Foundation/InputHandler.cpp

./bin/Resource.o : $(HEADFILE) ./src/Foundation/Resource.cpp
	$(CC) $(INCLUDE) -o ./bin/Resource.o -c ./src/Foundation/Resource.cpp

./bin/Player.o : $(HEADFILE) ./src/Object/Player.cpp
	$(CC) $(INCLUDE) -o ./bin/Player.o -c ./src/Object/Player.cpp

./bin/Enemy.o : $(HEADFILE) ./src/Object/Enemy.cpp
	$(CC) $(INCLUDE) -o ./bin/Enemy.o -c ./src/Object/Enemy.cpp

./bin/SpecialEffect.o : $(HEADFILE) ./src/Object/SpecialEffect.cpp
	$(CC) $(INCLUDE) -o ./bin/SpecialEffect.o -c ./src/Object/SpecialEffect.cpp

clean:
	rm ./bin/*.o beginner
