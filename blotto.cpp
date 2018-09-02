#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#include "blotto.h"

typedef std::vector<Player>::iterator iter;
typedef std::vector<Player>::const_iterator const_iter;
typedef std::vector<Player>::size_type sz_tp;

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

/*
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
*/


// Rather than a random shuffle, of all the numbers, it might be best to 
// randomly shuffle the highest 6 castles and put the lowest numbers of 
// troops on castle 1, ..., fourth lowest on castle 4 or something like that. 
Player::Player(int n): total_score(0)
{
    int troops_added_so_far = 0;

    while (troops_added_so_far <= n && troop_deployment.size() < 9)
    {
        int to_add = gen_unif_rv(n - troops_added_so_far);
        troop_deployment.push_back(to_add);
        troops_added_so_far += to_add;
    }

    troop_deployment.push_back(n - troops_added_so_far);

    std::sort(troop_deployment.begin(), troop_deployment.end());

    std::random_shuffle(troop_deployment.begin() + 4, troop_deployment.end());
} 



bool compare(Player& a, Player& b)
{
    return a.get_score() > b.get_score();
}

void play_all(Player& contestant, const std::vector<Player>& field)
{
    for (const_iter i = field.begin(); i != field.end(); ++i)
                make_one_sided_war(contestant, *i);
}
 
std::vector<Player> play_recursive_round_robin(const std::vector<Player>& vec, 
                                               int num_iterations)
{
    if (num_iterations == 0)
    {  
        return vec;
    }
    else
    {    
        if (vec.size() < 2)
            throw std::domain_error("need at least two Player"
                                    " objects for round robin");
        
        std::vector<Player> ret;
        ret.clear(); // prob not necessary

        for (const_iter j = vec.begin(); j != vec.end(); ++j)
        {
            Player plyr = *j;
            plyr.zero();

            play_all(plyr, vec);

            ret.push_back(plyr);
        }    
        
        sort(ret.begin(), ret.end(), compare);

        // remove the latter (lowest-scoring) half of the Players in ret
        sz_tp ret_size = ret.size(); 
        for (sz_tp s = 0; s < ret_size / 2; ++s)
            ret.pop_back();

        return play_recursive_round_robin(ret, num_iterations - 1);
    }    
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
