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