FIGHT   = fight.cpp
PLAYER1 = AI.cpp
PLAYER2 = AI.cpp
REFREE  = refree.cpp

all : fight player1 player2 refree

fight : $(FIGHT)
	g++ -o fight $(FIGHT)

player1 : $(PLAYER1)
	g++ -std=c++11 -o player1 $(PLAYER1)

player2 : $(PLAYER2)
	g++ -std=c++11 -o player2 $(PLAYER2)

refree : $(REFREE)
	g++ -std=c++11 -o refree $(REFREE)

clean :
	rm fight player1 player2 refree
