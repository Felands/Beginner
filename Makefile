CC = g++

OBJECT = ./bin/main.o ./bin/Game.o \
         ./bin/Resource.o ./bin/InputHandler.o \
		 ./bin/SDLGameObject.o ./bin/Player.o ./bin/Enemy.o ./bin/AnimatedGraphic.o ./bin/MenuBotton.o \
		 ./bin/GameStateMachine.o ./bin/PlayState.o ./bin/PauseState.o ./bin/GameOverState.o ./bin/MainMenuState.o
         
LIBRARY = ./lib/SDL2/SDL2.lib ./lib/SDL2/SDL2main.lib ./lib/SDL2/SDL2.dll \
          ./lib/SDL2/SDL2_image.lib ./lib/SDL2/SDL2_image.dll ./lib/SDL2/libpng16-16.dll

INCLUDE = -I ./include/SDL2/ -I ./include/ -I ./include/Foundation/ -I ./include/Object/ -I ./include/State/

HEADFILE = ./include/Game.h \
		   ./include/Foundation/InputHandler.h ./include/Foundation/LoaderParams.h ./include/Foundation/Resource.h\
		   ./include/Foundation/Vector2D.h \
	       ./include/Object/AnimatedGraphic.h ./include/Object/Enemy.h ./include/Object/GameObject.h \
		   ./include/Object/MenuBotton.h ./include/Object/Player.h ./include/Object/SDLGameObject.h \
	       ./include/State/GameOverState.h ./include/State/GameState.h ./include/State/GameStateMachine.h \
		   ./include/State/MainMenuState.h ./include/State/PauseState.h ./include/State/PlayState.h

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

./bin/SDLGameObject.o : $(HEADFILE) ./src/Object/SDLGameObject.cpp
	$(CC) $(INCLUDE) -o ./bin/SDLGameObject.o -c ./src/Object/SDLGameObject.cpp

./bin/Player.o : $(HEADFILE) ./src/Object/Player.cpp
	$(CC) $(INCLUDE) -o ./bin/Player.o -c ./src/Object/Player.cpp

./bin/Enemy.o : $(HEADFILE) ./src/Object/Enemy.cpp
	$(CC) $(INCLUDE) -o ./bin/Enemy.o -c ./src/Object/Enemy.cpp

./bin/AnimatedGraphic.o : $(HEADFILE) ./src/Object/AnimatedGraphic.cpp
	$(CC) $(INCLUDE) -o ./bin/AnimatedGraphic.o -c ./src/Object/AnimatedGraphic.cpp

./bin/MenuBotton.o : $(HEADFILE) ./src/Object/MenuBotton.cpp
	$(CC) $(INCLUDE) -o ./bin/MenuBotton.o -c ./src/Object/MenuBotton.cpp

./bin/GameStateMachine.o : $(HEADFILE) ./src/State/GameStateMachine.cpp
	$(CC) $(INCLUDE) -o ./bin/GameStateMachine.o -c ./src/State/GameStateMachine.cpp

./bin/GameOverState.o : $(HEADFILE) ./src/State/GameOverState.cpp
	$(CC) $(INCLUDE) -o ./bin/GameOverState.o -c ./src/State/GameOverState.cpp

./bin/MainMenuState.o : $(HEADFILE) ./src/State/MainMenuState.cpp
	$(CC) $(INCLUDE) -o ./bin/MainMenuState.o -c ./src/State/MainMenuState.cpp

./bin/PauseState.o : $(HEADFILE) ./src/State/PauseState.cpp
	$(CC) $(INCLUDE) -o ./bin/PauseState.o -c ./src/State/PauseState.cpp

./bin/PlayState.o : $(HEADFILE) ./src/State/PlayState.cpp
	$(CC) $(INCLUDE) -o ./bin/PlayState.o -c ./src/State/PlayState.cpp

clean:
	rm ./bin/*.o beginner
