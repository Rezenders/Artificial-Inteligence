from queue import Queue

vertice = {"A":5, "C":10, "G":20, "L": 13, "O": 40, "P": 10, "F": 50, "B": 5, "M": 13, "N": 13} 
arestas = [("A","B"),("A","C"),("B","P"),("B","G"),("C","O"),("C","F"),("G","N"),("G","L"),("G","O"),("F","M")]
beta = 70

class Estado:
    def __init__(self, s, ligados, custo):
        self.current_state = s
        self.ligados = ligados
        self.custo = custo
    
    def __str__(self):
        return "(atual: %s, ligados: %s, custo: %i)"%(self.current_state,self.ligados,self.custo)
    
    def __repr__(self):
        return "(atual: %s, ligados: %s, custo: %i)"%(self.current_state,self.ligados,self.custo)


def religar(estado):
    
    new_states = []
    for l in estado.ligados:
        for a in arestas:
            if a[0] == l and a[1] not in estado.ligados:
                state = Estado(a[1], estado.ligados + [a[1]], estado.custo + vertice[a[1]])
                if state.custo <= beta:
                    new_states.append(state)
            elif a[1] == l and a[0] not in estado.ligados:
                state = Estado(a[0], estado.ligados + [a[0]], estado.custo + vertice[a[0]])
                if state.custo <= beta:
                    new_states.append(state)
    
    return new_states

def main():

    v = "A"
    estado_inicial = Estado(v, [v], vertice[v])
    
    fifo = Queue()
    fifo.put(estado_inicial)
    
    while(fifo.empty() == False):
        estado_atual = fifo.get() 
        print(estado_atual)
        novos_estados = religar(estado_atual)
        for s in novos_estados:
            fifo.put(s)

    


if __name__ == '__main__':
    main()
