# Colonel Blotto Game

This is the readme file for my round-robin search for a reasonable strategy 
to play a particular variant of the famous Colonel Blotto game.

## Rules and background

(INSERT RULES OF GAME HERE)

Let us refer to a single match between any two players as a *battle*. 
I assume that I am about to enter a tournament where I am allowed only one troop
deployment decision which I must use in all of my battles. So I am trying to maximise the expected points gain from a single battle  (rather than trying to maximise the probability of winning more points than an opponent 
in a single battle).

## Plan to find a good strategy

My plan is as follows:

1. Randomly create `num_bots` "*bot*" players (each having 100 soldiers), contstrained by the rule that the no group of soldiers sent to a castle of value 4 or lower is larger than any group of soldiers sent to a castle of value 5 or higher (this will rule out bots who do unwise things like sending all of their soldiers to Castle 1, which is worth only 1 point).
1. Have these bots play a round-robin tournament, where each bot battles every other bot. Disqualify the lowest-scoring half of the bots according to their total score (or equivalently according to their average score) in the most recent round-robin tournament.
1. Repeat step 2 a further (`num_rounds` - 1) times (making for `num_rounds` round-robin rounds in total). 
1. This leaves me with a selection of bot players which can be considered as reasonably good; let me call these the *competent bots*. For my 100-soldier strategy, I simply pick the competent bot which performed best in the final (`num_rounds`th) round of the round-robin tournement.
1. There is still the question of what to do in the cases where I have 90 and 110 soldiers but everyone else still has 100 soldiers. 
Assuming that the huundreds of other contestants in the tournament do not adjust their strategies to account for a single player who has more/fewer soldiers, the competent bots will serve well as opponents against which to test 90- and 110-soldier strategies.
I randomly create `num_trials` 90- and 110-soldier bots (using the same constraints mentioned in step 1 to avoid bots that do unwise things). For my 90- and 110-soldier strategies, I simply pick the 90- and 110-soldier bots which perform best against the competent bots. 

## Pros and cons of this strategy

### Cons
* Blotto games are non-transitivie in nature, by which I mean that if Player A beats Player B and Player B beats Player C, then this is not very strong evidence that Player A will beat Player C. 
* My chosen strategies are sensitive to the random number generator. However this is not a huge problem since there are probably many possible strategies which have roughly equal probability of winning the tournament. 
* The number of possible strategies is so large that, at least with my code, it is not feasible to have `num_bots` be even close to the number of possible strategies (unless the code is to run for eons). 
 
### Pros
My strategy is surprisingly stable: often the bot which wins one round of a round-robin tournament will also win the following round (where half of the bots have been disqualified). You can see an example of this by compiling my code with the provided makefile to get an executable called **blotto** and then entering <br/>
`./blotto 147 10000 1 10000` <br/>
and  <br/>
`./blotto 147 10000 2 10000` <br/>
at the command line. The meanings of these command-line arguments are described below. 

## Usage Instructions

Usage: `./executable_name` `seed` `num_bots` `num_rounds` `num_trials`

(If you use my makefile, your `executable_name` will be `blotto`.)

Entering `./blotto 147 10000 6 10000` at the command line produces the following output: 

`157 competent bots were chosen.`

`When I have 100 soldiers, I will use this strategy: ( 0, 3, 4, 3, 8, 14, 19, 5, 21, 23 )`

`When I have 90 soldiers,  I will use this strategy: ( 0, 3, 4, 3, 12, 13, 17, 18, 15, 5 )`

`When I have 110 soldiers, I will use this strategy: ( 0, 3, 5, 2, 13, 15, 21, 12, 7, 32 )`


