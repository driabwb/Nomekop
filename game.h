//Developed by David Baird
#include <deque>
#include <algorithm>

template<class T>
class game{
public:
    //Constructor - Destructors
    game();
    game(const game& src);//Makes a shallow copy
    ~game();

    //Member functions
    bool isGameOver() const{ return gameOver; };
    bool update();
    void addPlayer(const T& newPlayer);
    void sort() { std::sort(players.begin(), players.end()); }
    bool nextPermutation() {
	return std::next_permutation(players.begin(),players.end());
    }
    friend std::ostream& operator<<<>(std::ostream&, const game);

    bool getIsWin() const{ return isWin; }
    std::deque<T> getPlayers()const{ return players; }
    std::size_t getRounds()const { return rounds; }
    std::deque<std::deque<T> > getPreviousStates()const{ return previousStates; }

private:
    //member data
    bool gameOver;
    bool isWin;
    std::deque<T> players;
    std::size_t rounds;
    std::deque<std::deque<T> > previousStates;
};

template<class T>
game<T>::game():gameOver(false),players(),rounds(0),previousStates(){}

template<class T>
game<T>::game(const game<T>& src):
    gameOver(src.isGameOver()),
    players(src.getPlayers()),
    rounds(src.getRounds()),
    previousStates(src.getPreviousStates()){
}

template<class T>
game<T>::~game(){
    players.clear();
    previousStates.clear();
}

template<class T>
bool game<T>::update(){
    previousStates.push_back(players);
    std::deque<T> b(players);
    int n = players.size();
    for(int i=0; i < n; ++i){
	if(i == 0 || i == (n-1)){
	    if(i==0){
		if(b[i+1] >= 2)
		    ++players[i];
		if(b[n-1] >= 2)
		    ++players[i];
	    }else{
		if(b[i-1] >= 2)
		    ++players[i];
		if(b[0] >= 2)
		    ++players[i];
	    }
	}else{
	    if(b[i+1] >= 2)
		++players[i];
	    if(b[i-1] >= 2)
		++players[i];
	}
	if(b[i] >= 2)
	    players[i] -= 2;
    }

    
    bool prevReached = std::count(previousStates.begin(),
				  previousStates.end(),
				  players) > 0;
    std::deque<T>* tmp = new std::deque<T>(players.size(),1); 
    gameOver = (players == *tmp ||prevReached);
    isWin = gameOver && !prevReached;
    return isWin;
}

template<class T>
void game<T>::addPlayer(const T& newPlayer){
    players.push_back(newPlayer);
}

template<class T>
std::ostream& operator<<(std::ostream& out, const game<T> g){
    typename std::deque<T>::const_iterator it = g.players.begin();
    for(;it != g.players.end(); it++)
	out << *it << " ";
    return out;
}
