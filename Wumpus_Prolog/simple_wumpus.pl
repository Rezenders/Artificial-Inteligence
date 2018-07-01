%Adjacent positions
adj(X1,Y,X2,Y) :- X2 is X1+1, X2 > 0, X2 < 5.
adj(X1,Y,X2,Y) :- X2 is X1-1, X2 > 0, X2 < 5.
adj(X,Y1,X,Y2) :- Y2 is Y1+1, Y2 > 0, Y2 < 5.
adj(X,Y1,X,Y2) :- Y2 is Y1-1, Y2 > 0, Y2 < 5.

not_pit(1,1).
not_pit(X,Y) :- not_breezy(X2,Y2), 
			adj(X2,Y2,X,Y).

not_wumpus(1,1).
not_wumpus(X,Y) :-  not_stenchy(X2,Y2), 
			adj(X2,Y2,X,Y).

sure_wumpus(X,Y,WX,WY) :-  findall([X2,Y2],(adj(X,Y,X2,Y2),\+not_wumpus(X2,Y2)),R),
			count(R,N),
			N is 1,
			[F] = R, 
			[WX,WY]= F. 

sure_pit(X,Y,WX,WY) :-  findall([X2,Y2], (adj(X,Y,X2,Y2),\+not_pit(X2,Y2)),R),
			count(R,N),
			N is 1,
			[F] = R, 
			[WX,WY]= F. 

possible_pit(X,Y) :- breezy(X2,Y2), 
			adj(X2,Y2,X,Y), 
			\+safe(X,Y), 
			\+not_pit(X,Y).

pit(X,Y) :- breezy(X2,Y2), 
			adj(X2,Y2,X,Y), 
			sure_pit(X2,Y2,X,Y).

possible_wumpus(X,Y) :- stenchy(X2,Y2), 
			adj(X2,Y2,X,Y), 
			\+safe(X,Y), 
			\+not_wumpus(X,Y).

wumpus(X,Y) :-  stenchy(X2,Y2), 
		adj(X2,Y2,X,Y), 
		sure_wumpus(X2,Y2,X,Y).

safe(X,Y) :- not_pit(X,Y), 
		not_wumpus(X,Y).

not_stenchy(1,1).
not_stenchy(2,1).
not_stenchy(2,2).
not_stenchy(3,2).

stenchy(1,2).
stenchy(2,3).

not_breezy(1,1).
not_breezy(1,2).
not_breezy(2,2).

breezy(2,1).
breezy(3,2).
breezy(2,3).
count([],0).
count([H|T],N) :- count(T,N1) , N is N1+1.

