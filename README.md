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
- Physics manager.
- GUI manager.

The Engine itself is responsible for instantiating and tracking these
components as a game runs. It also manages the main game loop that 
is responsible for running a game. Finally, it also provdes an API
so that a programmer can access the engine's functionality with ease.

## Engine Architecture
The Engine class contains all the necessary components necessary
for the engine to run. It contains an instance of each of the game
managers. The constructor sets the window parameters and calls the
startup function. The startup function calls the startup function 
for each manager, and finally starts the main game loop. This loop
runs at approx. 60 iterations per second. The game loop steps are:
- Get and update the input state.
- Update game managers.
- Draw the new frame on the screen.

The graphics manager utilizes the GLFW and Sokol GFX libraries and
is responsible for creating the engine's main window, load and delete 
sprites, and draw to the main window. Sprites are stored in an unordered
map where the key is its name and the value is the corresponding sprite.

The input manager uses GLFW poll events to see if a key was pressed. 
The key codes used are stored in a struct of GLFW key codes.

The sound manager uses the soloud library to load, play and delete
sounds. An unordered map is used to store the sounds; the key is a name
and the value is a sound in the form of a soloud WAV file (soloud::WAV).

The physics manager is divided into two parts:
- Calculating object motion using kinematic equations.
- Collision detection using box colliders.
- Collision resolution with the following steps:
  - Update impulses and velocities of objects in collision.
  - Move objects apart in the direction of their new velocities
    until a collision is no longer detected.
  - Resume the simulation.


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

## Bugs
- There is an issue with the Lua scripting subsystem which prevents the
  engine from running. 

## Engine API
This section contains documentation for the API functions the engine provides.

### `bool queryInput(input_code key)`
Queries the window for a key press. 
#### Parameters
- `key`: The keyboard key code being queried.
#### Returns
- `True` if the key has been pressed.
- `False` if the key was not pressed or released.

### `void loadSound(const std::string& name, const std::string& path)`
Loads a sound effect into the engine. 
If sound doesn't play, loading failed.
If the sound already exists in the engine,
loading is skipped.
#### Parameters
- `name`: The desired name of the sound effect.

- `path`: The path to the sound file.

### `void playSound(const std::string& name)`
Plays a sound effect.
#### Parameters
- `name`: The designated name of the sound effect.

### `void closeSound(const std::string& name)`
Removes a sound effect.
#### Parameters
- `name`: The designated name of the sound effect.

### `void clearAllSounds()`
Removes all sound effects.

### `std::string filePath(const std::string& path)`
Constructs a file path starting at the
engine's "assets" directory. This is necessary
since the engine will look for files to load
starting from the "assets" directory.
#### Parameters
- `path`: The path to the file inside the assets directory.
### Returns
- The full path name starting from assets directory.

### `bool loadSpriteImage(const std::string& name, const std::string& path)`
Loads an image file to be used as a sprite image.
#### Parameters
- `name`: The desired name for the sprite image.
- `path`: The path to the image file.
#### Returns
`True` if the image file was successfully loaded.
`False` otherwise. 

### `void destroySpriteImage(const std::string& name)`
Removes a sprite image.
#### Parameters
- `name`: The designated name for the image file.

### `void clearAllImages()`
Removes all sprite images.

### `EntityID createEntity()`
Create a new entity.
#### Returns
The designated entity ID for the new entity.
The user should store these to access the
created entities. There is no other way
to get an entity's ID.

### `void destroyEntity(EntityID e)`
Removes an entity and all related components.
#### Parameters
- `e`: The entity ID of the desired entity.

### `template< typename T > T& getComponent(EntityID e)`
Get a component assigned to an entity.
#### Parameters
- `T`: The data type of the desired component.
- `e`: The entity ID of the desired entity.
#### Returns
- A reference to the desired component.

### `template< typename EntityComponents > void forEach(const ForEachCallback& callback)`
Iterates over all entities that contain a particular component(s).
#### Parameters
- `EntityComponents`: Specify the desired component 
- `callback`: Can be used to pass custom code that will execute on all entities with the desired components.

### `bool loadScript(const std::string& name, const std::string& path)`
Loads a Lua script into the engine.
#### Parameters
- `name`: The desired name for the script.
- `path`: The path to the script.
#### Returns
- `True` if the script was successfully loaded. False` otherwise.

### `double radians(const float degrees), double radians(const Rotation degrees)`
Converts degrees to radians. The engine stores 
angles in degrees, but many trig. functions in, c++ require radians.
#### Parameters
- `degrees`: The desired angle in degrees, or the Rotation component.
#### Returns
- The angle converted to radians.
