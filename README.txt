Checkpoint 2:
	- Implemented the game loop running at 60 lps (loops per second)
	- Implemented the graphics manager class. Currently only opens
	  the window and does nothing.
	- Modified helloworld.cpp to start the engine, start the graphics
	  manager, run the game loop, and shut the graphics manager after
	  10 seconds.
	  
	Notes: The way I programmed the engine for this checkpoint is
		   to activate the graphics manager and run it for 10 seconds
		   before shutting it down. When you run it, you will see the
		   window pop up for 9-10 seconds and report the loops per second
		   to the commmand line, then shut down and terminate the program.
		   
		   I implemented a way to tell the engine how to format the 
		   graphics manager. When running the helloworld program
		   you need to pass the width, height, window name and 
		   fullscreen decision as command line arguments, in 
		   that order.
		   Example: xmake run helloworld 800 600 RenEngine false
					This will create an 800x600 window titled
					RenEngine that isn't fullscreen.
					
			The way I got the 60 lps for the game loop was a bit strange.
			I noticed on the discord and in my testing that when trying
			to make the thread sleep for the remainder of the 1/60th of
			a second left after the loop, it doubled the time slept, thus
			I would consistently get 30 lps. Since it's doubling the 
			sleep time, I halved the loop time to 1/120th of a second,
			which sure enough, the sleep function doubled. By doing this,
			the game loop runs from 9-10 seconds and produces approx. 60-66.7
			lps.

Checkpoint 3 and 4
	- Input manager created.
	- User callback in helloworld.cpp created
	  * Prints "Keyboad input working" and plays
	    success.mp3 whenever the enter key is
		pressed.
	- Program terminates when close button is
	  pressed or when the escape key is pressed.
	
	- Sound manager created.
	  * Can load and store, play and destroy sounds.
	- Resource manager created.
	  * Simply returns the input string of the path.
	    Will need to be worked on more later.
		
	Notes: Implemented a pimpl pattern in the graphics
		   manager in order to protect the implementation
		   detais of glfw from the header file. The friend
		   input manager class can access the private 
		   pimpl class so it can access the window to detect
		   user input.
		   
		   The sound manager class stores the sounds in an 
		   unordered map. A special clearSoundsList
		   function was created to clear the sounds list
		   in case the user wants to get rid of all sounds stored.
		   It's also called in the shutdown function for the 
		   sound manager.
		   
		   The engine currently only has keyboard input for the enter
		   and escape keys. The enter key is used in the callback
		   function to print a message and play a sound,
		   while the escape key closes the engine. I have defined more
		   key codes in my Types.h file, in the input_code enum.

		   I also implemented an API in the Engine class that allows
		   a user to call certain functions such as input checking and
		   sound management. Mostly, these functions are just pass
		   through functions that functions from the different
		   managers. This way, the user can specify custom
		   engine behaviour without having access to the managers
		   directly.

Checkpoint 5
	- Finished implementing graphics manager to allow drawing images
	  on screen.
	- Loaded a "Sprite" and drew it on screen with the callback function.

	Notes: I had to add the rotation transformation to the transform matrix
		   so that the image would be rotated along the z axis. For some
		   reason, the image is drawn flipped along the y-axis. I tried to
		   fix it using the same rotation transformation, but if I do, the
		   sprite either disapears or half the image gets cut off. I ended
		   up reflecting the image in GIMP, and then the engine flips it
		   so it appears in the correct order. I need to understand the 
		   system better in order to fix this issue without having to flip
		   every image outside the engine.
		   
Checkpoint 6
	- Implemented the entity component system and its respective functions.
	- Modified the graphics manager to draw using ForEach function of
	  the ECS over all entities with a Sprite component.
	- Loaded a sprite and set it up as an entity in helloworld.cpp.
	
	Notes: I moved the entire implementation of the ECS to the header
	       file since most functions were already there (due to templates).
		   I also added the API functions that will allow the user to 
		   access ECS functions without having direct access to the manager.
		   They simply call the ECS functions using the manager inside the
		   engine and return their return values. All other managers have
		   similar functions. Finally, I also added a function that moves,
		   rotates and scales the sprite on screen by updating the entity's
		   position, rotation and scale components. The function is called
		   within the game loop function in helloworld.cpp so that the sprite
		   can be moved in real time. WASD change the sprite's position.
		   Up and down arrow keys scale the sprite. Left and right arrow
		   keys rotate the sprite.

Checkpoint 7
	- Implemented the script manager.
	- Engine now capable of loading and running Lua scripts via the ECS.
	- Exposed functionality to the script manager, including graphics,
	  input, sound and ECS functionality.
	- Created a simple script to test functionality.

	Notes: My script manager is loaded as the last manager, so that the other
	       managers can expose their functionality to it. I also exported
		   all my component structs and the input_code struct. The update 
		   function is called within the engine's main game loop. It uses
		   the ECS's ForAll function to iterate over all entities with scripts
		   attached to them. The only problem the function has is that it's supposed
		   to reload the script again so it can run any changes on the fly, but
		   it's not working. I have to recompile the engine so that the scripts
		   can be re-imported, and only then wll script changes be run.

Build Week
	- Made a simple asteroids demo, without any kind of health or combat.

	Things I'd like to work on for rest of the semester:
		- Rigid body physics and (maybe) 3D graphics.
		- GUI components and editors for developers.
		- Text processing and displaying.
		- Procedural content generation.
		- AI and path planning for NPCs and enemies.  