#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#include "blotto.hpp"

typedef std::vector<Player>::iterator iter;
typedef std::vector<Player>::const_iterator const_iter;

// return a unif random variable in the range [0, n]
int gen_unif_rv(int n)
{
    const int bin_capacity = RAND_MAX / n;
    int rn;
    
    do rn = rand() / bin_capacity;
    while(rn > n);

    return rn;
}


// Have a battle and add to score of Player a only.
void make_one_sided_war(Player& a, const Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_troops().begin();
    std::vector<int>::const_iterator iter_b = b.get_troops().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_troops().end();

    int counter = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.change_score(counter);

        ++iter_a;
        ++iter_b;
        ++counter;
    }
}

Player::Player(): total_score(0)
{
    int troops_added_so_far = 0;

    while (troops_added_so_far <= 100 && troop_deployment.size() < 9)
    {
        int to_add = gen_unif_rv(100 - troops_added_so_far);
        troop_deployment.push_back(to_add);
        troops_added_so_far += to_add;
    }

    troop_deployment.push_back(100 - troops_added_so_far);

    std::random_shuffle(troop_deployment.begin(), troop_deployment.end());
} 

bool compare(Player& a, Player& b)
{
    return a.get_score() > b.get_score();
}

// This function takes a const ref to a vector<Player> vec, then one at a time 
// it copies a Player from vec, zeroes it, and pits it against every 
// Player in vec using the make_one_sided_war function. If the copied player 
// finishes with score >= desired_score, it is pushed back onto the
// vector<Player> to be returned. 
// We could add something like sort(ret.begin(), ret.end(), compare) if we 
// wanted round_robin to sort the vector in order of total_score, so that the 
// highest scoring Player is at position 0 in the vector. 
std::vector<Player> round_robin(const std::vector<Player>& vec, 
                                double desired_score, 
                                std::vector<Player>::size_type desired_size)
{
    std::vector<Player> ret;

    std::vector<Player>::size_type length = vec.size();

    for (std::vector<Player>::size_type i = 0; i < length; ++i)
    {
        Player plyr = vec[i];
        plyr.zero();

        for (const_iter i = vec.begin(); i != vec.end(); ++i)
            make_one_sided_war(plyr, *i);

        // The -1 below is there because plyr played one game against himself 
        if (plyr.get_score() / (length - 1) >= desired_score) 
            ret.push_back(plyr);

        if (ret.size() == desired_size)
            break;     
    }    

    return ret;
}

/* Have a battle and assign players their scores (works but commented out 
because not needed)
void make_war(Player& a, Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_troops().begin();
    std::vector<int>::const_iterator iter_b = b.get_troops().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_troops().end();

    int counter = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.change_score(counter);
        else if (*iter_a < *iter_b)      
            b.change_score(counter);

        ++iter_a;
        ++iter_b;
        ++counter;
    }
}
*/



























/*
int Player::compete(std::vector<Player> all_Players)
{
    find(all_Players.begin(), all_Players.end(), );
}
*/

/*
The thing to do seems to be:
creata a Player class with two (private) data members (an vector<int> and a 
int to track how successful the Player was) and
an accessor function to give read-only access to that data member. We should 
give the Player class an initialiser function that initialises the vector<int> 
to contain ten random numbers (constrained to sum to exactly 100) and 
initialises the int to 0 (I should note 
in my write-up that there can be no possible advantage to sending fewer than 100 
troops into battle). There should also be a member function called play that 
takes a vector of Players and returns the sum of its own Player's scores of its 
own Player's scores against the other Players. 

We should then create a vector<Player> (or some other container<Player>) that 
contains and initialise it to contain, say, a million, Player objects (which 
will hopefully be initialised immediately in the random fashion stipulated). It 
should then be possible (see the end of the Cherno's function pointer video) to 
pit all the Players against eachother and store each Player's final score in the 
int data member.  
*/

/*
void Player::initialise()
{
    total_score = 0;

    int troops_added_so_far = 0;

    while (troops_added_so_far <= 100 && troop_deployment.size() < 9)
    {
        int to_add = gen_unif_rv(100 - troops_added_so_far);
        troop_deployment.push_back(to_add);
        troops_added_so_far += to_add;
    }

    troop_deployment.push_back(100 - troops_added_so_far);

    std::random_shuffle(troop_deployment.begin(), troop_deployment.end());
}
*/
