#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

#include "blotto.h"

// Print elements of a container in the range [a, b). Enclose
// output in parentheses and separate elements by commas. 
template <class It>
void iter_print(It a, It b)
{
    std::cout << "( " << *a;
    for (It i = ++a; i != b; ++i)
        std::cout << ", " << *i;
    std::cout << " )" << std::endl;

    return;
}

int main(int argc, char* argv[])
{

    if (argc != 4) 
    {
        throw std::domain_error("Usage ./<file name>"
            " number-of-bots" 
            " number-of-round-robin-rounds"
            " number-of-trials-to-find-unfair-strategy");              
    }    

    typedef std::vector<Player>::iterator iter;
    typedef std::vector<Player>::const_iterator const_iter;
    typedef std::vector<Player>::size_type sz_tp;

    sz_tp num_bots = atoi(argv[1]);
    int num_rounds = atoi(argv[2]);
    int num_trials = atoi(argv[3]);

    srand(75);

    std::vector<Player> Player_vec(num_bots);

    std::vector<Player> elite_Player_vec = play_recursive_round_robin(
                                               Player_vec, num_rounds);                                                           

    Player chosen_one = elite_Player_vec[0];
    
    std::cout << "Chosen 100-soldier strategy: ";
    iter_print((chosen_one.get_soldiers()).begin(), 
             (chosen_one.get_soldiers()).end()); 

    // create a vector which will hold our chosen Players for the 90- and 100-
    // soldier scenarios. Initialise them both to hold no soldiers (they will be 
    // oberwritten anyway). 
    std::vector<Player> unfair_Players(2, Player({ 0, 0, 0, 0, 0, 
                                                   0, 0, 0, 0, 0 }));

    // for the 90- and 110-soldier scenarios, test 
    std::vector<int> soldier_counts = { 90, 110 };

    for (int i = 0; i < 2; ++i)
    {
        int max_score = 0;
        for (int j = 0; j < num_trials; ++j)
        {
            Player plyr(soldier_counts[i]);
            play_all(plyr, elite_Player_vec);    

            if (plyr.get_score() > max_score)
            {
                max_score = plyr.get_score();
                unfair_Players[i] = plyr;
            }
        }
    }         

    std::cout << std::endl << "Chosen 90-soldier  strategy: ";
    iter_print((unfair_Players[0].get_soldiers()).begin(),
               (unfair_Players[0].get_soldiers()).end());
    std::cout << std::endl << "Chosen 110-soldier strategy: ";               
    iter_print((unfair_Players[1].get_soldiers()).begin(),
               (unfair_Players[1].get_soldiers()).end());

    return 0;
}