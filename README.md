# Tic-Tac-Toe
A C++ project for implementing Tic-Tac-Toe game using OpenGL 
The game is played between two players --> Player A and Player B, and both are assigned either 'X' or 'O' as their respective symbols.
The program automatically shifts the turns between both the users and message is displayed accordingly using glutStrokeCharacter.
The player who is having the turn currently can click any of the 9 boxes of the grid to mark it with his symbol. The program displays his symbol inside the box. This functionality is added using glutMouseFunc.
As and when either of the player wins, a message is displayed showing the name of the winner. If the match is a draw, a message is displayed accordingly.
User can restart the game at any point of time.
User can hover over the specific column of the tic-tac-toe grid to change the color of the box. This functionality is added using glutPassiveFunction og OpenGL.
