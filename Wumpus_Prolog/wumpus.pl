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

%World rules
config_breeze(X,Y) :- config_pit(X1,X2),adj(X1,X2,X,Y).
config_stench(X,Y) :- config_w(X1,X2),adj(X1,X2,X,Y).
