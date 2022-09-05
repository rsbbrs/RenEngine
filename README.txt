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
		   unordered map. It also clears it out before exiting
		   in the smShutdown function.