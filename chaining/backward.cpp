#include <iostream>
#include <list>
#include <vector>

std::vector< std::string> state = {"sapatoE", "sapatoD", "calça", "camisa", "chapeu"};
std::vector< std::string> goal = {"limpaE", "limpaD", "cueca"};

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
    for (size_t i = 0; i < effects.size(); i++) {
      for (size_t j = 0; j < effects[i].size(); j++) {
        aux2 = false;
        for(size_t w =0; w<state.size(); ++w){
          if(effects[i][j]==state[w]){
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
        for (size_t z = 0; z < pre_cond[i].size(); z++) {
          state.push_back(pre_cond[i][z]);
        }
        for (size_t q = 0; q < effects[i].size(); q++) {
          for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
            if(effects[i][q]==*it){
              state.erase(it);
            }
          }
        }
        break;
      }

    }

    std::cout<<"Estado Final ";
    for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
      std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    int a=0;
    std::cin>>a;
  }
}

// #include <iostream>
// #include <list>
//
// std::list< std::pair<std::string, std::string> > actions;
// std::list< std::string> state = {"sapatoE", "sapatoD"};
// int main(){
//   actions.push_back(std::make_pair("limpaE", "meiaE"));
//   actions.push_back(std::make_pair("limpaD", "meiaD"));
//   actions.push_back(std::make_pair("meiaE", "sapatoE"));
//   actions.push_back(std::make_pair("meiaD", "sapatoD"));
//
//   while(!state.empty()){
//     std::string current = state.front();
//     std::cout<<"Efeito "<<current<<std::endl;
//     bool match =false;
//
//     for(std::list< std::pair<std::string, std::string> >::iterator it=actions.begin(); it!=actions.end(); ++it){
//       if(current.compare(it->second) == 0){
//         state.pop_front();
//         state.push_back(it->first);
//         match = true;
//         std::cout<<"Pre-condição "<<it->first<<std::endl;
//       }
//     }
//     if(match ==false){
//       state.pop_front();
//     }
//   }
// }
