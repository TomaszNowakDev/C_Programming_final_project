# C Programming

### C Programming module taught at MTU, project name "Snakes and Ladders".

The goal of this project is to implement a C application which can simulate a game of snakes and
ladders. Snakes and ladders is a board game based on random chance. The player must navigate
from the start of the board (square 1) to the final square (square n). The player can move forward
a fixed number of squares based on the outcome of a single die roll; moves between 1 and 6 steps
forward are possible with a 6-sided die.
Along the path there are a fixed number of snakes and ladders. If a player moves to a space
with a foot of ladder they can move directly forward to the space at the other side of the ladder. This
brings them closer to the final square. If a player moves to a space with the head of a snake they must move
directly back to the space at the other side of the snake. This brings them further away from the
nal square.

The application should be started from the command line by entering two arguments, the first is the number of snakes on the board, the second is the number of ladders that will be on the board. The number of snakes and ladders must be less than 1 and more than 5 each, whole numbers only, as in the picture below.

![](images/arguments.jpg)

After starting the application, we get information whether the arguments have been correctly entered.

A few basic specs of the game: 
* Each square on the game board should be a user-defined structure which holds informa-
  tion about the current position on the game board. The program should check if it is
  the final square on the game board, or if it is the bottom of a ladder, or if it is the head
  of a snake.
* The game board size should be randomly set each time the application is run, minimum
  size 32, maximum size 64.
* The entire game board must be represented by a data structure of game square structures
  which you can traverse along, this can be implemented either using an array or a linked
  list.

![](images/start.jpg)