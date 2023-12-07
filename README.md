# FlappyBird

The Flappy Bird project was implemented using the C++ language and the SFML (Simple and Fast Multimedia Library). Before starting the project, the functionality and key elements of the game were defined. Using the SFML library, the following elements were implemented:

* Game logic, including bird control, obstacle generation, and score tracking.
* Event handling, such as key presses, mouse button clicks, or game window closure.
* Addition of graphics and sounds.

## Functionalities


* Bird Control

  The player can control the bird using the keyboard (SPACE bar), allowing it to move upward.

* Scoring Mechanism
  
  The game tracks the number of points scored based on the obstacles successfully avoided by the bird.

* Obstacle Generation
  
  Automatic generation of obstacles at random heights that the player needs to avoid to prevent collisions.

* Collision Detection
  
  The game detects collisions with:
  
  * Obstacles
  
  * Bottom of the screen
  
  * Top of the screen

* Start Screen

  Before the game starts, a start screen is displayed. The game begins by pressing the start button.

* Sound Effects
  
  The game includes the following sound effects:

  * Flapping wings sound triggered by pressing the corresponding key on the keyboard
    
  * Collision sound with an obstacle
  
  * Collision sound with the top/bottom of the screen

  * Button clicking sound triggered by hovering the mouse over the button

  * Sound indicating the acquisition of a point
