Dank Squad Contributions.

Firstly, I'd like to dedicate this AI to the dankest of the dank. I hope the simple abilities of this reversi-wrecking MACHINE inspires my future progeny to become the best of the best, like no one ever was.

Now, for acknowledgements:

Jonathan Joo - He completed the first half of assignment one, setting up the initial board/player/game files and getting a heuristic function such that the AI can beat simplePlayer a majority of the time.

Kevin Ye - This grandmaster implemented the Minimax Decision tree, and worked on improving the heuristic function. Essentialy, finished up the second half of assignment 2. 


Improvements to heuristic function:
The idea was to make it such that certain areas of the board are more valuable than others. Thus, we made a heuristic function that looked a few moves into the future, and found the best move that minimized the opponent's score/maximized our score. Then, based off this number, if the final location is a corner, we increased the value of this move, since corner moves are more valuable than other moves. (Corner pieces can't be taken by the opponent.) For a similar reason, edge moves were given slightly more weight, but less than the corners, while moves that are directly adjacent to corners were given less value, since it allows the opponent to get a corner move. 
In addition, we worked on a minimax algorithm that looks into all possible moves, and returns the best move up to a certain depth. This allows us to idealize our output so that it considers the opponent's moves, and still returns the best value. 


