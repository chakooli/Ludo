# 3D Ludo
An intelligent, single-player classic ludo game 
## Rules
1. The game can be played by only one user at a time.
2. The user will play against computer players.
3. The user will start the game by making the first move.
4. All the classic rules of Ludo Game will be followed during the game. They are stated as follows:
   - Any player can only initialise their tokens, i.e, bring them out of their houses on the roll of 1 or 6 on the dice.
   - Once initialised, the player can move only one of its active tokens (initialised tokens) at a time.
   - The token can take as many steps forward on the board as the number on the dice.
   - If a token is present on the safe zone (marked by start) or initialising position (marked by the same color as the color of the house), it cannot be destroyed by any other token.
   - If a token is not present on the safe zone, it can be destroyed by the token of some other player if the other player lands on the that position on its turn.
   - To win, the player has to move all its tokens to the winning house. 
   - Once a token is on the path to the winning home, it can only enter if it gets the exact number on the dice as the number of steps required to reach the winning home.   

![alt text](screenshots/overview.png "Description goes here")

## How to play
1. Keyboard keys:
   - Token 1, user : Press 1
   - Token 2, user : Press 2
   - Token 3, user : Press 3
   - Token 4, user : Press 4
   - Computer player : Press 5 

![alt text](screenshots/movedtokens2.png "Description goes here")

## Installation
1. Requirements for executing the code:
   - Dev C++ IDE
   - glutMINGW32 folder (http://chortle.ccsu.edu/bloodshed/howtogl.html)
2. Configure Dev C++ to use glut libraries using the the instructions given here : (http://chortle.ccsu.edu/bloodshed/howtogl.html)
3. Create a new OpenGL project in Dev C++.
4. Change the properties of the project by adding the following libraries: 
   - libopengl32
   - libglu32
   - libglut32
5. Add a blank file to the project and copy the code in LudoCode.cpp
6. Run it.

![alt text](screenshots/rotation.png "Description goes here")

