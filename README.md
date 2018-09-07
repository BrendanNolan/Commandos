# Strategic commando Game

This is the readme file for my round-robin search for a reasonable strategy 
to play a  trsategic commando game.

## Rules 

In this game, a *battle* consists of
* 2 players who have 100 commandos each;
* 10 towns numbered 1,...,10 and worth 1,...,10 points respectively.

Each player decides on the number of commandos to deploy to each town. For each 
i between 1 and 10, the player who sent the greater number of sildiers to town i
will receive the i points for that town (if both players send the same number of commandos to town i, then neither receives the i points from that town).


## Tournament

I assume that I am about to enter a round-robin tournament where I am allowed only one commando deployment decision which I must use in all of my battles. Every other contestant in the tournament must do the same; the winner shall be the contestant who accumulates the most points (or equivalently who achieves the highest average score (per battle)). So I am trying to find a strategy to maximise the expected points gain from a single battle  (rather than trying to maximise the probability of winning more points than an opponent in a single battle).

Moreover, I develop two strategies to play slightly altered versions of the 
same tournament
* The first strategy is for a tournament where I have 90 commandos while all other contestants still have 100.
* The second strategy is for a tournament where I have 110 commandos while all other contestants still have 100.

## Plan to find a good strategy

My plan is as follows:

1. Randomly create `num_bots` "*bot*" players (each having 100 commandos), contstrained by the rule that the no group of commandos sent to a town of value 4 or lower is larger than any group of commandos sent to a town of value 5 or higher (this will rule out bots who do unwise things like sending all of their commandos to town 1, which is worth only 1 point).
1. Have these bots play a round-robin tournament, where each bot battles every other bot. Disqualify the lowest-scoring half of the bots according to their total score (or equivalently according to their average score) in the most recent round-robin tournament.
1. Repeat step 2 a further (`num_rounds` - 1) times (making for `num_rounds` round-robin rounds in total). 
1. This leaves me with a selection of bot players which can be considered as reasonably good; let me call these the *competent bots*. For my 100-commando strategy, I simply pick the competent bot which performed best in the final (`num_rounds`th) round of the round-robin tournement.
1. There is still the question of what to do in the cases where I have 90 and 110 commandos but everyone else still has 100 commandos. 
Assuming that the huundreds of other contestants in the tournament do not adjust their strategies to account for a single player who has more/fewer commandos, the competent bots will serve well as opponents against which to test 90- and 110-commando strategies.
I randomly create `num_trials` 90- and 110-commando bots (using the same constraints mentioned in step 1 to avoid bots that do unwise things). For my 90- and 110-commando strategies, I simply pick the 90- and 110-commando bots which perform best against the competent bots. 

## Pros and cons of this strategy

### Cons
* The game is non-transitivie in nature, by which I mean that if Player A beats Player B and Player B beats Player C, then this is not very strong evidence that Player A will beat Player C. 
* My chosen strategies are sensitive to the random number generator. However this is not a huge problem since there are probably many possible strategies which have roughly equal probability of winning the tournament. 
* The number of possible strategies is so large that, at least with my code, it is not feasible to have `num_bots` be even close to the number of possible strategies (unless the code is to run for eons). 
 
### Pros
My strategy is surprisingly stable: often the bot which wins one round of a round-robin tournament will also win the following round (where half of the bots have been disqualified). You can see an example of this by compiling my code with the provided makefile to get an executable called **commando** and then entering <br/>
`./commando 147 10000 1 10000` <br/>
and  <br/>
`./commando 147 10000 2 10000` <br/>
at the command line. The meanings of these command-line arguments are described below. 

## Usage Instructions

Where
* `executable_name` is the name of your executable file (which will be `commando` if you use my Makefile);
* `seed` is your random number seed to be passed to `srand`;
* `num_bots` is the number of random bot players to be created at Step 1 above;
* `num_rounds` is the number of round-robin rounds in Step 2 and Step 3 above;
* `num_trials` is the number of 90- and 100-commando bots to be created and tested in Step 5 above;

usage of the program is as follows: <br/> 
`./executable_name seed num_bots num_rounds num_trials`

Entering `./commando 147 10000 6 10000` at the command line produces the following output: 

`157 competent bots were chosen.`

`When I have 100 commandos, I will use this strategy: ( 0, 3, 4, 3, 8, 14, 19, 5, 21, 23 )`

`When I have 90 commandos,  I will use this strategy: ( 0, 3, 4, 3, 12, 13, 17, 18, 15, 5 )`

`When I have 110 commandos, I will use this strategy: ( 0, 3, 5, 2, 13, 15, 21, 12, 7, 32 )`


