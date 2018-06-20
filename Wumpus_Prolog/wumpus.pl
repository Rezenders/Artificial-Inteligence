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
breeze(X,Y) :- at(X,Y), config_breeze(X,Y).
stench(X,Y) :- at(X,Y), config_stench(X,Y).
not_breeze(X,Y) :- at(X,Y), \+ config_breeze(X,Y).
not_stench(X,Y) :- at(X,Y), \+ config_stench(X,Y).

%breeze([]).
%breeze([[H1,H2]|T]) :- breeze(H1,H2), breeze(T).
%not_breeze([]).
%not_breeze([[H1,H2]|T]) :- not_breeze(H1,H2), not_breeze(T).
%stench([]).
%stench([[H1,H2]|T]) :- stench(H1,H2), stench(T).
%not_stench([]).
%not_stench([[H1,H2]|T]) :- not_stench(H1,H2), not_stench(T).

%Deductions
%pit(X,Y) :- findall([X2,Y2], adj(X,Y,X2,Y2),P), breeze(P).
%not_pit(X,Y) :- findall([X2,Y2], adj(X,Y,X2,Y2), P), not_breeze(P).
not_pit(X,Y) :- at(X2,Y2), not_breeze(X2,Y2), adj(X2,Y2,X,Y).

%wumpus(X,Y) :- findall([X2,Y2], adj(X,Y,X2,Y2),P), stench(P).
%not_wumpus(X,Y) :- findall([X2,Y2], adj(X,Y,X2,Y2), P), not_stench(P).
not_wumpus(X,Y) :- at(X2,Y2), not_stench(X2,Y2), adj(X2,Y2,X,Y).

ok(X,Y) :- not_wumpus(X,Y),!, not_pit(X,Y),!, write(X),write(Y).

at(X,Y) :- init(X,Y).
at(X,Y) :- at(X2,Y2), adj(X2,Y2,X,Y), ok(X,Y).
