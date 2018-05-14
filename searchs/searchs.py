#!/usr/bin/python3.5
from queue import Queue

def main():
    init_state = [5, 4, 0, 6, 1, 8, 7, 3, 2]
    goal_state = [5, 0, 4, 6, 1, 8, 7, 3, 2]
    #goal_state = [1, 2, 3, 8, 0, 4, 7, 6, 5]
    depth_search(init_state, goal_state)

def depth_search(init, goal):
    queue = Queue()
    queue.put(init)
    counter = 0
    while not queue.empty():
        state = queue.get()
        if state == goal:
            print("Found Solution")
            break
        else:
            new_states = expand(state)
            for s in new_states:
                queue.put(s)
        counter +=1
        print(counter)
    print("No solution found!!!!!!")

def expand(state):
    index = state.index(0)
    new_states = []
    if index == 0:
        new_states.append(move(state, index, 1))
        new_states.append(move(state, index, 3))
    elif index == 1:
        new_states.append(move(state, index, 0))
        new_states.append(move(state, index, 2))
        new_states.append(move(state, index, 4))
    elif index == 2:
        new_states.append(move(state, index, 1))
        new_states.append(move(state, index, 5))
    elif index == 3:
        new_states.append(move(state, index, 0))
        new_states.append(move(state, index, 4))
        new_states.append(move(state, index, 6))
    elif index == 4:
        new_states.append(move(state, index, 1))
        new_states.append(move(state, index, 3))
        new_states.append(move(state, index, 5))
        new_states.append(move(state, index, 7))
    elif index == 5:
        new_states.append(move(state, index, 2))
        new_states.append(move(state, index, 4))
        new_states.append(move(state, index, 8))
    elif index == 6:
        new_states.append(move(state, index, 3))
        new_states.append(move(state, index, 7))
    elif index == 7:
        new_states.append(move(state, index, 4))
        new_states.append(move(state, index, 6))
        new_states.append(move(state, index, 8))
    elif index == 8:
        new_states.append(move(state, index, 5))
        new_states.append(move(state, index, 7))
    return new_states

def move(state, index, j):
    s = state
    s[index], s[j] = s[j], s[index]
    return s
    

if __name__ == "__main__":
    main()
