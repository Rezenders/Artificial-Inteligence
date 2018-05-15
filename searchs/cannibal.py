#!/usr/bin/python3

from queue import Queue

def main():
    initial = cannibal_state([3,3,0,0,1])
    goal = cannibal_state([0,0,3,3,-1])

    result = BL(initial, goal, boat)
    
    print("caminho")
    for s in result.path:
        print(s)
    
    print("resultado")
    print(result.state)

def BL(init, goal, actions):
    old_states= [] 
    fifo = Queue()
    fifo.put(init)

    while fifo.empty() == False:
        state = fifo.get()
        if state == goal:
            return state
        else:
            old_states.append(state)
            new_states = actions(state)
            for s in [ss for ss in new_states if ss not in old_states]:
                fifo.put(s)
    return None

class cannibal_state:
    def __init__(self, state):
        self.state = state
        self.path = []

    def __eq__(self, other):
        return (self.state == other.state)

def boat(state):
    new_states = []
    for i in range(0,2):
        for j in range(1,3):
            s = list(state.state)
            s[i] = s[i] - j*s[4]
            s[i+2] = s[i+2] + j*s[4]
            s[4] = -1*s[4]
            if valid(s):
                cs = cannibal_state(s)
                cs.path = state.path + [state.state]
                new_states.append(cs)
    
    s = list(state.state)
    s[0] = s[0] -1*s[4]
    s[1] = s[1] -1*s[4]
    s[2] = s[2] +1*s[4]
    s[3] = s[3] +1*s[4]
    s[4] = -1*s[4]
    if valid(s):
        cs = cannibal_state(s)
        cs.path = state.path + [state.state]
        new_states.append(cs)

    return new_states

def valid(state):
    for i in state[0:4]:
        if i <0:
            return False
        elif i >3:
            return False
    
    if state[0]>state[1] and state[1]!=0:
        return False
    elif  state[2]>state[3] and state[3]!=0:
        return False

    return True

if __name__ == "__main__":
    main()
