#ifndef GUARD_COMMANDO_H
#define GUARD_COMMANDO_H

#include <iostream>
#include <vector>

// Print elements of a container in the range [a, b). Enclose
// output in parentheses and separate elements by commas. 
template <class It>
void iter_print(It a, It b)
{
    std::cout << "( " << *a;
    for (It i = ++a; i != b; ++i)
        std::cout << ", " << *i;
    std::cout << " )";

    return;
}

class Player {
    // A vector of integers describing the strategy for sending commandos
    // to towns.
    std::vector<int> commando_deployment;
    
    // A double to keep track of the score after (possibly) many battles. 
    // We could use an int here but, in case we ever want to do something 
    // like computing an average score without losing precision, we use 
    // a double.
    double total_score;

public:
    const std::vector<int>& get_commandos() const {return commando_deployment;}
    void print_commandos() const {iter_print(get_commandos().begin(),
        get_commandos().end());}
    double get_score() const {return total_score;}

    // add n to total_score member
    void increase_score(int n) {total_score += n;}
    
    // set total_score member to 0
    void zero() {total_score = 0;}

    // Take an integer n (with default value of 100) and construct a Player 
    // object with n commandos, but not in a stupid way (so it doesn't waste 
    // large numbers of commandos on low-value towns.)
    Player(int n = 100);
    
    // Create a Player object by providing a commando_deployment member
    // (the Player object will have total_score member equal to 0)
    Player(std::vector<int> vec) : commando_deployment(vec), total_score(0) {}
};



// return a unif random variable in the range [0, n]
int gen_unif_rv(int);

// Compare Player objects by their total_score members.
// Will be useful for ordering vectors of Player objects,
// placing the highest-scoring Player in position 0.
bool compare(const Player&, const Player&);

void make_battle(Player&, Player&);

// Have a battle and add to score of Player a only.
void make_one_sided_battle(Player&, const Player&);

// Put a Player object called contestant into battle against every member of a 
// vector of Player objects called field.
// Calling the make_one_sided_battle function updates the total_score member
// of contestant after each battle, so that the total_score member of 
// contestant contains the final score of contestant after battling every member 
// of field
void battle_all(Player&, const std::vector<Player>&);



// new improved round robin that doesn't play every battle twice
template <class it, class ptee>
void play_round_robin(it beg_iter, it end_iter, 
                               void head_to_head(ptee, ptee))
{    
    // could use some sanity check to make sure there are at least two objects 
    // contestants in the competition
    
    while(beg_iter != end_iter)
    {
        it trav = beg_iter;
        ++trav;
        while(trav != end_iter)    
            head_to_head(*beg_iter, *(trav++));
        
        ++beg_iter;
    }

    return;
}

// the only way that this is not better than play_recursive_round_robin is that
// it changes its first argument. But even if you didn't want this, a similar
// function that copied its first argument would probably still be faster 
// than play_recursive_round_robin. It might be best to have this function 
// return a std::vector<Player> instead of a std::vector<Player>& 
std::vector<Player>& recursive_play_round_robin(
    std::vector<Player>& vec, int num_rounds);

#endif