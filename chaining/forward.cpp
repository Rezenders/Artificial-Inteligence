#include <iostream>
#include <vector>
#include <queue>

class Estado{
public:
  Estado(std::vector< std::string> s, std::string a){
    state =s;
    actions.push_back(a);
  }
  Estado(std::vector< std::string> s){
    state = s;
  }
  Estado(Estado estado, std::vector< std::string> s, std::string a){
    state =s;
    actions = estado.actions;
    actions.push_back(a);
  }
  std::vector< std::string> state;
  std::vector< std::string> actions;
};

std::queue< Estado > state_queue;
std::vector<std::vector< std::string> > expanded;
std::vector< std::string> initial_state = {"limpaE", "limpaD", "cueca"};
// std::vector< std::string> goal = {"limpaE", "limpaD", "cueca"};
std::vector< std::string> goal = {"sapatoE", "sapatoD", "calça", "camisa", "chapeu"};

int main(){
  std::vector<std::string> actions = {            "calcaMeiaE",        "calcaMeiaD",        "vesteCalça" ,      "calçaSapatoE",     "calçaSapatoD",      "vesteCamisa",                   "colocaChapeu"};
  std::vector< std::vector< std::string> > pre_cond = {{"limpaE"},          {"limpaD"},          {"cueca"} ,        {"meiaE", "calça"},  {"meiaD", "calça"},  {"sapatoE", "sapatoD", "calça"}, {"camisa"}};
  std::vector< std::vector< std::string> > effects = {{"meiaE", "limpaE"},  {"meiaD","limpaD"},  {"calça","cueca"}, {"sapatoE","meiaE"}, {"sapatoD","meiaD"}, {"camisa"},                      {"chapeu"}};
  std::vector< std::vector< std::string> > op =      {{"pos", "neg"},       {"pos","neg"},       {"pos","neg"},     {"pos","neg"},       {"pos","neg"},       {"pos"},                          {"pos"}};

  state_queue.push(Estado(initial_state));

  while(!state_queue.empty()) {
    Estado estado_class = state_queue.front();
    std::vector< std::string > state = estado_class.state;
    state_queue.pop();

    //Verifica se estado já foi expandido
    bool in_expanded = false;
    for (std::vector<std::vector< std::string> >::iterator it_exp=expanded.begin(); it_exp!=expanded.end(); ++it_exp) {
      in_expanded |= (state==*it_exp);
    }

    if(!in_expanded){
      expanded.push_back(state);

      // //printa estado
      // std::cout<<"Estado ";
      // for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
      //   std::cout<<*it<<" ";
      // }
      // std::cout<<std::endl;

      //Verifica se estado objetivo
      bool aux = false;
      for(std::vector< std::string>::iterator it=goal.begin(); it!=goal.end(); ++it){
        aux = false;
        for(std::vector< std::string>::iterator it2=state.begin(); it2!=state.end(); ++it2){
          if(*it==*it2){
            aux = true;
            break;
          }
        }
        if(!aux){
          break;
        }
      }
      if(aux){
        std::cout<<"Actions "<<std::endl;
        for (size_t as = 0; as < estado_class.actions.size(); as++) {
          std::cout<<estado_class.actions[as]<<std::endl;
        }
        break;
      }

      //Loop em todos as pre condições
      bool aux2 = false;
      for (size_t i = 0; i < pre_cond.size(); ++i) {
        //verifica se o estado atende essa pre condição
        for (size_t j = 0; j < pre_cond[i].size(); ++j) {
          aux2 = false;
          for(size_t w =0; w<state.size(); ++w){
            if(pre_cond[i][j]==state[w]){
              aux2 = true;
              break;
            }
          }
          if(!aux2){
            break;
          }
        }

        //se pre condição satisfez aplica a ação
        if(aux2){
          // std::cout<<actions[i]<<std::endl;
          std::vector< std::string> state_aux = state;

            for (size_t z = 0; z < effects[i].size(); z++) {
              //adiciona efeito se o mesmo for positivo e não estiver no estado
              if(op[i][z]=="pos"){
                bool effect_in_state=false;
                for (size_t u = 0; u < state.size(); u++) {
                  if(effects[i][z]==state[u]){
                    effect_in_state=true;
                    break;
                  }
                }
                if(!effect_in_state){
                  state_aux.push_back(effects[i][z]);
                }
              }else if(op[i][z]=="neg"){ //remove efeito se o msm for negativo e estiver no estado e
                for(std::vector< std::string>::iterator it=state_aux.begin(); it!=state_aux.end(); ++it){
                  if(effects[i][z]==*it){
                    state_aux.erase(it);
                  }
                }
              }
            }
          //adiciona estado gerado na fila (busca em largura)
          state_queue.push(Estado(estado_class, state_aux, actions[i]));
        }
      }
    }
  }
}
