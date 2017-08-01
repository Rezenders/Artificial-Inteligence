#include <iostream>
#include <list>
#include <vector>

std::vector< std::string> state = {"limpaE", "limpaD", "cueca"};
std::vector< std::string> goal = {"sapatoE", "sapatoD", "calça", "camisa", "chapeu"};

int main(){
  std::vector<std::string> actions = {            "calcaMeiaE",        "calcaMeiaD",        "vesteCalça" ,      "calçaSapatoE",     "calçaSapatoD",      "vesteCamisa",                   "colocaChapeu"};
  std::vector< std::vector< std::string> > pre_cond = {{"limpaE"},          {"limpaD"},          {"cueca"} ,        {"meiaE", "calça"},  {"meiaD", "calça"},  {"sapatoE", "sapatoD", "calça"}, {"sapatoE", "sapatoD", "calça", "camisa"}};
  std::vector< std::vector< std::string> > effects = {{"meiaE", "limpaE"},  {"meiaD","limpaD"},  {"calça","cueca"}, {"sapatoE","meiaE"}, {"sapatoD","meiaD"}, {"camisa"},                      {"chapeu"}};
  std::vector< std::vector< std::string> > op =      {{"pos", "neg"},       {"pos","neg"},       {"pos","neg"},     {"pos","neg"},       {"pos","neg"},       {"pos"},                          {"pos"}};

  while(true) {
    bool aux = false;
    for(std::vector< std::string>::iterator it=state.begin(); it!=state.end(); ++it){
      aux = false;
      for(std::vector< std::string>::iterator it2=goal.begin(); it2!=goal.end(); ++it2){
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
      break;
    }

    bool aux2 = false;
    for (size_t i = 0; i < pre_cond.size(); i++) {
      for (size_t j = 0; j < pre_cond[i].size(); j++) {
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
      if(aux2){//achou uma ação
        std::cout<<actions[i]<<std::endl;
        for (size_t z = 0; z < effects[i].size(); z++) {

          if(op[i][z]=="pos"){
            // std::cout<<"inseriu "<<std::endl;
            state.push_back(effects[i][z]);
          }else if(op[i][z]=="neg"){
            // std::cout<<"deletar "<<std::endl;
            for(std::vector< std::string>::iterator it=state.begin(); it!=state.end(); ++it){
              if(effects[i][z]==*it){
                state.erase(it);
              }
            }
          }

        }
      }

    }

    std::cout<<"Estado Final ";
    for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
      std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
  }
}
