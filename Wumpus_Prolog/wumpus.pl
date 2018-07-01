%Adjacent positions
adj(X1,Y,X2,Y) :- X2 is X1+1, X2 > 0, X2 < 5.
adj(X1,Y,X2,Y) :- X2 is X1-1, X2 > 0, X2 < 5.
adj(X,Y1,X,Y2) :- Y2 is Y1+1, Y2 > 0, Y2 < 5.
adj(X,Y1,X,Y2) :- Y2 is Y1-1, Y2 > 0, Y2 < 5.

%World configuration
config_pit(3,1).
config_pit(3,3).
config_pit(4,4).
config_w(1,3).
config_g(2,3).

%initial position
init(1,1).

%World rules
config_breeze(X,Y) :- config_pit(X1,X2),adj(X1,X2,X,Y).
config_stench(X,Y) :- config_w(X1,X2),adj(X1,X2,X,Y).

%perceptions
not_breeze(X,Y) :- \+ config_breeze(X,Y).
not_stench(X,Y) :- \+ config_stench(X,Y).

%Deductions
not_pit(Xi,Yi,Xf,Yf) :- not_breeze(Xi,Yi),!, adj(Xi,Yi,Xf,Yf).

not_wumpus(Xi,Yi,Xf,Yf) :- not_stench(Xi,Yi),!, adj(Xi,Yi,Xf,Yf).

ok(Xi,Yi,Xf,Yf,NW,NP) :- adj(Xi,Yi,Xf,Yf), member([Xf,Yf],NW) , member([Xf,Yf],NP).

%check if it possible to find the gold
find_gold:- 
	findall([X,Y], not_wumpus(1,1,X,Y),NW),
	findall([X,Y], not_pit(1,1,X,Y),NP),
	findall([X,Y], ok(1,1,X,Y,NW,NP), OKS),
	move(OKS,NW,NP).

move([[Xi,Yi]|T],NW,NP):-
	findall([X,Y], not_wumpus(Xi,Yi,X,Y),NW2),
	append(NW,NW2,NW3),unique_list(NW3,UNW),
	findall([X,Y], not_pit(Xi,Yi,X,Y),NP2),
	append(NP,NP2,NP3),unique_list(NP3,UNP),
	findall([X,Y], ok(Xi,Yi,X,Y,UNW,UNP), OKS),
	append(T,OKS,OKS2),unique_list(OKS2,UOK),
	config_g(X,Y),\+member([X,Y],UOK)->move(UOK,UNW,UNP);true.


unique_list([],[]).
unique_list([H|T],L) :-
        unique_list(T,L2), ensure(H,L2,L).

% If X is already a member of L, then the result is L
ensure(X, L, L) :-
    member(X, L), !.

% If not, the result is X appended to L
ensure(X, L, [X | L]).



