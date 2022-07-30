# SolvedTicTacToe

This is just a tic-tac-toe game that will always win or always tie. Tic-Tac-Toe is a more or less "solved" game. I spent a week working out the logic myself, just as a mental excercise and then programmed it. I was a freshman CS student when I made it so I was just dipping my toe into the creation of a large project. Tic-Tac-Toe is really one of those "everybody does it" programs, so I figured it was good to get under my belt. 

## Instructions
In this Tic-Tac-Toe game, the player is up against the computer. The player can select what letter they want and whether they want to go first or second. The computer will get either 'X', 'O', whatever the user did not pick. As the game is played in terminal, the user must select the square they wish by number. Each cell will denote 'X', 'O', or a number. After the user selects their square, the computer will run automatically.

## The Computer
The computer will always win or tie. It does this by looking several moves ahead. It will stifle any attempt to outwit it and can seize a definite capture in as little as three moves. The computer may have won before the player even realizes.

## Lessons Learnt
1. C++ practice is always valuable.
2. Error checking for the player input is very necessary, even if only due to fumble fingers on the keyboard.
3. Tracking duplicative possibilities makes the code easier. For example, starting at any diagonal square makes no difference to the computer. One diagonal "X" is one digaonal "X".
