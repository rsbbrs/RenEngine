# RenEngine
Prototype game engine built for CS425 at George Mason University.

## Author
Renato Scudere

## About
This game engine, named RenEngine, is a simple game engine written from 
scratch to learn the aspects of game engine design and construction. The 
engine contains multiple components that are in charge of managing the 
different aspects of the engine. These components are: 
- Graphics manager.
- Input manager.
- Sound manager.
- Resource manager.
- Script manager.
- Entity component system.

The Engine itself is responsible for instantiating and tracking these
components as a game runs. It also manages the main game loop that 
is responsible for running a game. Finally, it also provdes an API
so that a programmer can access the engine's functionality with ease.

## Starting the Engine
First, create a file named `main.cpp`, this will contain
the main instance of the engine. Make sure to add `#include "Engine.h"`
to have access to it. To start the engine, simply create an engine object
with one of two constructors:
```
RenEngine::Engine engine();
RenEngine::Engine engine(name, width, height, fullscreen);
```
The default constructor will have a window name RenEngine, width of 1280,
height of 720, and will not be fullscreen `(fullscreen = false)`.
Finally, start the main game loop by calling the game loop function
with a callback function:
```
engine.gameLoop([&](){ ... callback function ...});
```
The callback function allows you to add any extra code necessary to run
your game. It will execute as part of the main game loop.

To exit the engine, either close the main game window or hit the escape
hey on the keyboard, which is used to close the main game loop. No further
action is necessary, the engine will handle closing all of its components,
(unless you dynamically allocated the engine, in which case you can call
`delete`).

Using xmake, you can run the code using the command `xmake run main`.

## Engine API
This section contains documentation for the API functions the engine provides.

### `bool queryInput(input_code key)`
Queries the window for a key press. 
#### Parameters
`key`: The keyboard key code being queried.
#### Returns
True if the key has been pressed.
False if the key was not pressed or released.

### `void loadSound(const std::string& name, const std::string& path)`
Loads a sound effect into the engine. 
If sound doesn't play, loading failed.
If the sound already exists in the engine,
loading is skipped.
#### Parameters
`name`: The desired name of the sound effect.

`path`: The path to the sound file.

### `void playSound(const std::string& name)`
Plays a sound effect.
#### Parameters
`name`: The designated name of the sound effect.

### `void closeSound(const std::string& name)`
Removes a sound effect.
#### Parameters
`name`: The designated name of the sound effect.

### `void clearAllSounds()`
Removes all sound effects.
























