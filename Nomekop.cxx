#include <iostream>
#include "game.h"

bool nomekop(game<int> init);


int main(){
    int next;
    game<int> theGame;
    
    std::cout << "Please enter the number of caps at each position.";
    std::cout << "\nNote that the value must be an integer >= 0;";
    std::cout << "\nanything decimals will be rounded down, and";
    std::cout << "\nplease terminate your game entry with a -1" << std::endl;
    
    std::cin >> next;
    while(next != -1){
	if(next < 0){
	    std::cout << "Invalid Input: Enter integers > 0." << std::endl;
	}else{
	    theGame.addPlayer(next);
	    std::cin >> next;
	}
    }

    theGame.sort();
    
    do {
	std::cout << theGame << '\n';
	if(nomekop(theGame)){
	    std::cout << "The game ends!" << std::endl;
	}else{
	    std::cout << "The game is infinite." << std::endl;
	}
    } while(theGame.nextPermutation());
    
    return EXIT_SUCCESS;
}

bool nomekop(game<int> theGame){
    while(!theGame.isGameOver()){
	theGame.update();
    }
    return theGame.getIsWin();
}
