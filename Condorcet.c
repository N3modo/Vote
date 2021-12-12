//
// Created by Antho on 12/12/2021.
//

#include "Condorcet.h"

/*
1.Create the different matrix and compute the total voting matrix
2. Check if there is an immediate Condorcet winner
     if yes, next miner is found
     Else continue
3. Check situation 1 (multiple rows with value > 0
     if yes, apply dictatorial choice = next miner is found
     Else continue
4. Apply Tideman procedure
     Next miner is found
    https://github.com/Perlkonig/Condorcet
*/