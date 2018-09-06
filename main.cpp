#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "blotto.h"


int main(int argc, char** argv)
{

    if (argc != 5) 
    {
        throw std::invalid_argument("Usage ./<file name>"
                                " random-number-seed"
                                " number-of-bots" 
                                " number-of-round-robin-rounds"
                                " number-of-trials-to-find-unfair-strategy");              
    }    

    srand(atoi(argv[1]));

    typedef std::vector<Player>::iterator iter;
    typedef std::vector<Player>::const_iterator const_iter;
    typedef std::vector<Player>::size_type sz_tp;

    sz_tp num_bots = atoi(argv[2]);
    int num_rounds = atoi(argv[3]);
    int num_trials = atoi(argv[4]);

    std::vector<Player> Player_vec(num_bots);

    // Beware that the upcoming call to recursive_play_round_robin will alter
    // Player_vec. In order to avoid confusion, we define a const reference
    // competent_bot_Player_vec to the nonconst ref returned by
    // recursive_play_round_robin.
    const std::vector<Player>& competent_bot_Player_vec = 
        recursive_play_round_robin(Player_vec, num_rounds);                         

    std::clog << competent_bot_Player_vec.size() 
              << " competent bots were chosen."  << std::endl << std::endl;    
                                                                              
    Player chosen_one = competent_bot_Player_vec[0];
    
    std::cout << "When I have 100 soldiers, I will use this strategy: ";
    chosen_one.print_soldiers(); 
    std::cout << std::endl;         

    // create a vector which will hold our chosen Players for the 90- and 100-
    // soldier scenarios. Initialise them both to hold no soldiers (they will be 
    // oberwritten anyway). 
    std::vector<Player> unfair_Players(2, Player({ 0, 0, 0, 0, 0, 
                                                 0, 0, 0, 0, 0 }));

    // for the 90- and 110-soldier scenarios, test 
    std::vector<int> soldier_counts = { 90, 110 };

    for (sz_tp i = 0; i < 2; ++i)
    {
        int max_score = 0;
        for (int j = 0; j < num_trials; ++j)
        {
            Player plyr(soldier_counts[i]);
            battle_all(plyr, competent_bot_Player_vec);    

            if (plyr.get_score() > max_score)
            {
                max_score = plyr.get_score();
                unfair_Players[i] = plyr;
            }
        }
    }         
                        
    std::cout << std::endl << "When I have 90 soldiers, "
                              " I will use this strategy: ";
    unfair_Players[0].print_soldiers();
    std::cout << std::endl;           
    std::cout << std::endl << "When I have 110 soldiers, "
                              "I will use this strategy: ";               
    unfair_Players[1].print_soldiers();
    std::cout << std::endl; 
                                                                              
                                                                           
    return 0;
}