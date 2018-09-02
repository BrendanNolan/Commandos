#ifndef GUARD_BLOTTO_H
#define GUARD_BLOTTO_H

#include <vector>
#include <ctime>

class Player {
    // a vector of integers describing the strategy for sending troops
    // to castles
    std::vector<int> troop_deployment;
    
    // a double to keep track of the score after (possibly) many battles 
    double total_score;

public:
    const std::vector<int>& get_troops() const {return troop_deployment;}
    double get_score() const {return total_score;}

    // add n to total_score member
    void change_score(int n) {total_score += n;}
    
    // set total_score member to 0
    void zero() {total_score = 0;}

    // Take an integer n and construct a Player object with 
    // n troops, but not in a stupid way (so it doesn't waste large numbers of 
    // troops on low-value castles.)
    Player(int n = 100);
    
    // Create a Player object by providing a troop_deployment member
    // (the Player object will have total_score member equal to 0)
    Player(std::vector<int> vec) : troop_deployment(vec), total_score(0)           
    {}
};

// return a unif random variable in the range [0, n]
int gen_unif_rv(int);

// Compare Player objects by their total_score members.
// Will be useful for ordering vectors of Player objects.
bool compare(const Player&, const Player&);

// Have a battle and add to score of Player a only.
void make_one_sided_war(Player&, const Player&);

// Put a Player object called contestant into battle against every member of a 
// vector of Player objects called field.
// Calling the make_one_sided_war function updates the total_score member
// of contestant after each battle, so that the total_score member of 
// contestant contains the final score of contestant after battling every member 
// of field
void play_all(Player&, const std::vector<Player>&);

// Take a vector of Player objects and play num_iterations of "round-robin" 
// tournaments between them, where the worst-performing 50% of Player objects
// in each tournament are disqualified from the next tournament. Return 
// a vector of Player objects which contains the surviving PLayer objects,
// sorted by their score in the final tournament. Note that this function
// makes every Player object battle itself during the tournament; this is 
// harmless since the result of this battle adds zero to the total_score member
// of that Player object.
std::vector<Player> play_recursive_round_robin(
    const std::vector<Player>&, int);

#endif