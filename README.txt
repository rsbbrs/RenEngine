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