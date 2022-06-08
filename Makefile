CC = g++

OBJECT = ./bin/main.o ./bin/Game.o \
         ./bin/Resource.o ./bin/SoundManager.o ./bin/InputHandler.o ./bin/base64.o \
		 ./bin/Level.o ./bin/LevelParser.o ./bin/ObjectLayer.o ./bin/TileLayer.o \
		 ./bin/AnimatedGraphic.o ./bin/Enemy.o ./bin/Player.o ./bin/GameObjectFactory.o \
		 ./bin/SDLGameObject.o ./bin/MenuButton.o \
		 ./bin/GameStateMachine.o ./bin/MainMenuState.o ./bin/StateParser.o ./bin/GameOverState.o \
		 ./bin/PauseState.o ./bin/PlayState.o ./bin/BetweenLevelState.o \
		 ./bin/tinystr.o ./bin/tinyxml.o ./bin/tinyxmlerror.o ./bin/tinyxmlparser.o
     
LIBRARY = ./lib/SDL2/SDL2.lib ./lib/SDL2/SDL2main.lib ./lib/SDL2/SDL2.dll \
          ./lib/SDL2/SDL2_image.lib ./lib/SDL2/SDL2_image.dll ./lib/SDL2/libpng16-16.dll \
		  ./lib/SDL2/mixer/SDL2_mixer.dll ./lib/SDL2/mixer/libogg-0.dll ./lib/SDL2/mixer/libFLAC-8.dll \
		  ./lib/SDL2/mixer/libmodplug-1.dll ./lib/SDL2/mixer/libmpg123-0.dll ./lib/SDL2/mixer/libopus-0.dll \
		  ./lib/SDL2/mixer/libopusfile-0.dll ./lib/SDL2/mixer/libvorbis-0.dll ./lib/SDL2/mixer/libvorbisfile-3.dll \
		  ./lib/zlib/zlib1.dll

INCLUDE = -I ./include/ -I ./include/SDL2/ -I ./include/Foundation/ -I ./include/Object/ -I ./include/State/ \
          -I ./include/Layer/ -I ./include/TinyXml/ -I ./include/Compress/ -I ./include/SDL2/mixer/

HEADFILE = ./include/Game.h \
           ./include/Foundation/InputHandler.h ./include/Foundation/Resource.h ./include/Foundation/Vector2D.h \
		   ./include/Foundation/log.h ./include/Foundation/SoundManager.h \
		   ./include/Object/GameObjectFactory.h ./include/Object/GameObject.h ./include/Object/SDLGameObject.h \
		   ./include/Object/MenuButton.h ./include/Object/Player.h ./include/Object/Enemy.h \
		   ./include/Object/AnimatedGraphic.h \
		   ./include/State/GameState.h ./include/State/GameStateMachine.h ./include/State/MenuState.h \
		   ./include/State/MainMenuState.h ./include/State/StateParser.h ./include/State/GameOverState.h \
		   ./include/State/PauseState.h ./include/State/PlayState.h ./include/State/BetweenLevelState.h \
		   ./include/TinyXml/tinystr.h ./include/TinyXml/tinyxml.h \
		   ./include/Layer/Layer.h ./include/Layer/Level.h ./include/Layer/LevelParser.h \
		   ./include/Layer/ObjectLayer.h ./include/Layer/TileLayer.h

beginner : $(OBJECT)
	$(CC) -o beginner -Wl,-rpath ./lib/SDL2/ $(OBJECT) $(LIBRARY) -Og


./bin/main.o : $(HEADFILE) ./src/main.cpp
	$(CC) $(INCLUDE) -o ./bin/main.o -c ./src/main.cpp

./bin/Game.o : $(HEADFILE) ./src/Game.cpp
	$(CC) $(INCLUDE) -o ./bin/Game.o -c ./src/Game.cpp


./bin/InputHandler.o : $(HEADFILE) ./src/Foundation/InputHandler.cpp
	$(CC) $(INCLUDE) -o ./bin/InputHandler.o -c ./src/Foundation/InputHandler.cpp

./bin/Resource.o : $(HEADFILE) ./src/Foundation/Resource.cpp
	$(CC) $(INCLUDE) -o ./bin/Resource.o -c ./src/Foundation/Resource.cpp

./bin/base64.o : $(HEADFILE) ./src/Foundation/base64.cpp
	$(CC) $(INCLUDE) -o ./bin/base64.o -c ./src/Foundation/base64.cpp

./bin/SoundManager.o : $(HEADFILE) ./src/Foundation/SoundManager.cpp
	$(CC) $(INCLUDE) -o ./bin/SoundManager.o -c ./src/Foundation/SoundManager.cpp


./bin/Level.o : $(HEADFILE) ./src/Layer/Level.cpp
	$(CC) $(INCLUDE) -o ./bin/Level.o -c ./src/Layer/Level.cpp

./bin/LevelParser.o : $(HEADFILE) ./src/Layer/LevelParser.cpp
	$(CC) $(INCLUDE) -o ./bin/LevelParser.o -c ./src/Layer/LevelParser.cpp

./bin/ObjectLayer.o : $(HEADFILE) ./src/Layer/ObjectLayer.cpp
	$(CC) $(INCLUDE) -o ./bin/ObjectLayer.o -c ./src/Layer/ObjectLayer.cpp

./bin/TileLayer.o : $(HEADFILE) ./src/Layer/TileLayer.cpp
	$(CC) $(INCLUDE) -o ./bin/TileLayer.o -c ./src/Layer/TileLayer.cpp


./bin/AnimatedGraphic.o : $(HEADFILE) ./src/Object/AnimatedGraphic.cpp
	$(CC) $(INCLUDE) -o ./bin/AnimatedGraphic.o -c ./src/Object/AnimatedGraphic.cpp

./bin/Enemy.o : $(HEADFILE) ./src/Object/Enemy.cpp
	$(CC) $(INCLUDE) -o ./bin/Enemy.o -c ./src/Object/Enemy.cpp

./bin/Player.o : $(HEADFILE) ./src/Object/Player.cpp
	$(CC) $(INCLUDE) -o ./bin/Player.o -c ./src/Object/Player.cpp

./bin/GameObjectFactory.o : $(HEADFILE) ./src/Object/GameObjectFactory.cpp
	$(CC) $(INCLUDE) -o ./bin/GameObjectFactory.o -c ./src/Object/GameObjectFactory.cpp

./bin/SDLGameObject.o : $(HEADFILE) ./src/Object/SDLGameObject.cpp
	$(CC) $(INCLUDE) -o ./bin/SDLGameObject.o -c ./src/Object/SDLGameObject.cpp

./bin/MenuButton.o : $(HEADFILE) ./src/Object/MenuButton.cpp
	$(CC) $(INCLUDE) -o ./bin/MenuButton.o -c ./src/Object/MenuButton.cpp


./bin/GameStateMachine.o : $(HEADFILE) ./src/State/GameStateMachine.cpp
	$(CC) $(INCLUDE) -o ./bin/GameStateMachine.o -c ./src/State/GameStateMachine.cpp

./bin/MainMenuState.o : $(HEADFILE) ./src/State/MainMenuState.cpp
	$(CC) $(INCLUDE) -o ./bin/MainMenuState.o -c ./src/State/MainMenuState.cpp

./bin/StateParser.o : $(HEADFILE) ./src/State/StateParser.cpp
	$(CC) $(INCLUDE) -o ./bin/StateParser.o -c ./src/State/StateParser.cpp

./bin/GameOverState.o : $(HEADFILE) ./src/State/GameOverState.cpp
	$(CC) $(INCLUDE) -o ./bin/GameOverState.o -c ./src/State/GameOverState.cpp

./bin/PauseState.o : $(HEADFILE) ./src/State/PauseState.cpp
	$(CC) $(INCLUDE) -o ./bin/PauseState.o -c ./src/State/PauseState.cpp

./bin/PlayState.o : $(HEADFILE) ./src/State/PlayState.cpp
	$(CC) $(INCLUDE) -o ./bin/PlayState.o -c ./src/State/PlayState.cpp

./bin/BetweenLevelState.o : $(HEADFILE) ./src/State/BetweenLevelState.cpp
	$(CC) $(INCLUDE) -o ./bin/BetweenLevelState.o -c ./src/State/BetweenLevelState.cpp


./bin/tinystr.o : $(HEADFILE) ./src/TinyXml/tinystr.cpp
	$(CC) $(INCLUDE) -o ./bin/tinystr.o -c ./src/TinyXml/tinystr.cpp

./bin/tinyxml.o : $(HEADFILE) ./src/TinyXml/tinyxml.cpp
	$(CC) $(INCLUDE) -o ./bin/tinyxml.o -c ./src/TinyXml/tinyxml.cpp

./bin/tinyxmlerror.o : $(HEADFILE) ./src/TinyXml/tinyxmlerror.cpp
	$(CC) $(INCLUDE) -o ./bin/tinyxmlerror.o -c ./src/TinyXml/tinyxmlerror.cpp

./bin/tinyxmlparser.o : $(HEADFILE) ./src/TinyXml/tinyxmlparser.cpp
	$(CC) $(INCLUDE) -o ./bin/tinyxmlparser.o -c ./src/TinyXml/tinyxmlparser.cpp

clean:
	rm ./bin/*.o beginner
