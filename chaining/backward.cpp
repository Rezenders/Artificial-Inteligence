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
std::vector< std::string> initial_state = {"sapatoE", "sapatoD", "calça", "camisa", "chapeu"};
std::vector< std::string> goal = {"limpaE", "limpaD", "cueca"};
// std::vector< std::string> goal = {"limpaE", "limpaD", "cueca"};

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

      //printa estado
      std::cout<<"Estado ";
      for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
        std::cout<<*it<<" ";
      }
      std::cout<<std::endl;

      //Verifica se estado objetivo
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
        std::cout<<"Actions "<<std::endl;
        for (size_t as = 0; as < estado_class.actions.size(); as++) {
          std::cout<<estado_class.actions[as]<<std::endl;
        }
        break;
      }

      //Loop em todos os efeitos
      bool aux2 = false;
      for (size_t i = 0; i < effects.size(); ++i) {
        //verifica se o estado atende esse efeito
        for (size_t j = 0; j < effects[i].size(); ++j) {
          aux2 = false;
          for(size_t w =0; w<state.size(); ++w){
            if((effects[i][j]==state[w]) && (op[i][j]=="pos")){
              aux2 = true;
              break;
            }else if(op[i][j]=="neg"){
              aux2 = true;
            }
          }
          if(!aux2){
            break;
          }
        }

        //se efeito satisfez aplica a ação
        if(aux2){
          std::cout<<actions[i]<<std::endl;
          std::vector< std::string> state_aux = state;

            for (size_t z = 0; z < pre_cond[i].size(); z++) {
              //adiciona pre_cond se o mesmo for positivo e não estiver no estado
              bool pre_cond_in_state=false;
                for (size_t u = 0; u < state.size(); u++) {
                  if(pre_cond[i][z]==state[u]){
                    pre_cond_in_state=true;
                    break;
                  }
                }
                if(!pre_cond_in_state){
                  state_aux.push_back(pre_cond[i][z]);
                }

                for (size_t q = 0; q < effects[i].size(); q++) {
                  if(op[i][q]=="neg"){
                    // state_aux.push_back(effects[i][q]);
                  } else if(op[i][q]=="pos"){
                    for(std::vector<std::string>::iterator it=state_aux.begin(); it!=state_aux.end(); ++it){
                      if(effects[i][q]==*it){
                        std::cout<<"OOOIOIOI"<<std::endl;
                        state_aux.erase(it);
                        it=state_aux.begin();
                      }
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


// #include <iostream>
// #include <list>
// #include <vector>
//
// std::vector< std::string> state = {"sapatoE", "sapatoD", "calça", "camisa", "chapeu"};
// std::vector< std::string> goal = {"limpaE", "limpaD", "cueca"};
//
// int main(){
//   std::vector<std::string> actions = {            "calcaMeiaE",        "calcaMeiaD",        "vesteCalça" ,      "calçaSapatoE",     "calçaSapatoD",      "vesteCamisa",                   "colocaChapeu"};
//   std::vector< std::vector< std::string> > pre_cond = {{"limpaE"},          {"limpaD"},          {"cueca"} ,        {"meiaE", "calça"},  {"meiaD", "calça"},  {"sapatoE", "sapatoD", "calça"}, {"sapatoE", "sapatoD", "calça", "camisa"}};
//   std::vector< std::vector< std::string> > effects = {{"meiaE", "limpaE"},  {"meiaD","limpaD"},  {"calça","cueca"}, {"sapatoE","meiaE"}, {"sapatoD","meiaD"}, {"camisa"},                      {"chapeu"}};
//   std::vector< std::vector< std::string> > op =      {{"pos", "neg"},       {"pos","neg"},       {"pos","neg"},     {"pos","neg"},       {"pos","neg"},       {"pos"},                          {"pos"}};
//
//   while(true) {
//     bool aux = false;
//     for(std::vector< std::string>::iterator it=state.begin(); it!=state.end(); ++it){
//       aux = false;
//       for(std::vector< std::string>::iterator it2=goal.begin(); it2!=goal.end(); ++it2){
//         if(*it==*it2){
//           aux = true;
//           break;
//         }
//       }
//       if(!aux){
//         break;
//       }
//     }
//     if(aux){
//       break;
//     }
//
//     bool aux2 = false;
//     for (size_t i = 0; i < effects.size(); i++) {
//       for (size_t j = 0; j < effects[i].size(); j++) {
//         aux2 = false;
//         for(size_t w =0; w<state.size(); ++w){
//           if(effects[i][j]==state[w]){
//             aux2 = true;
//             break;
//           }
//         }
//         if(!aux2){
//           break;
//         }
//       }
//       if(aux2){//achou uma ação
//         std::cout<<actions[i]<<std::endl;
//         for (size_t z = 0; z < pre_cond[i].size(); z++) {
//           state.push_back(pre_cond[i][z]);
//         }
//         for (size_t q = 0; q < effects[i].size(); q++) {
//           for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
//             if(effects[i][q]==*it){
//               state.erase(it);
//             }
//           }
//         }
//         break;
//       }
//
//     }
//
//     std::cout<<"Estado Final ";
//     for(std::vector<std::string>::iterator it=state.begin(); it!=state.end(); ++it){
//       std::cout<<*it<<" ";
//     }
//     std::cout<<std::endl;
//     int a=0;
//     std::cin>>a;
//   }
// }
//
// // #include <iostream>
// // #include <list>
// //
// // std::list< std::pair<std::string, std::string> > actions;
// // std::list< std::string> state = {"sapatoE", "sapatoD"};
// // int main(){
// //   actions.push_back(std::make_pair("limpaE", "meiaE"));
// //   actions.push_back(std::make_pair("limpaD", "meiaD"));
// //   actions.push_back(std::make_pair("meiaE", "sapatoE"));
// //   actions.push_back(std::make_pair("meiaD", "sapatoD"));
// //
// //   while(!state.empty()){
// //     std::string current = state.front();
// //     std::cout<<"Efeito "<<current<<std::endl;
// //     bool match =false;
// //
// //     for(std::list< std::pair<std::string, std::string> >::iterator it=actions.begin(); it!=actions.end(); ++it){
// //       if(current.compare(it->second) == 0){
// //         state.pop_front();
// //         state.push_back(it->first);
// //         match = true;
// //         std::cout<<"Pre-condição "<<it->first<<std::endl;
// //       }
// //     }
// //     if(match ==false){
// //       state.pop_front();
// //     }
// //   }
// // }
