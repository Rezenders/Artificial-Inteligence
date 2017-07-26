#include <iostream>
#include <list>

std::list< std::pair<std::string, std::string> > actions;
std::list< std::string> state = {"sapatoE", "sapatoD"};
int main(){
  actions.push_back(std::make_pair("limpaE", "meiaE"));
  actions.push_back(std::make_pair("limpaD", "meiaD"));
  actions.push_back(std::make_pair("meiaE", "sapatoE"));
  actions.push_back(std::make_pair("meiaD", "sapatoD"));

  while(!state.empty()){
    std::string current = state.front();
    std::cout<<"Efeito "<<current<<std::endl;
    bool match =false;

    for(std::list< std::pair<std::string, std::string> >::iterator it=actions.begin(); it!=actions.end(); ++it){
      if(current.compare(it->second) == 0){
        state.pop_front();
        state.push_back(it->first);
        match = true;
        std::cout<<"Pre-condição "<<it->first<<std::endl;
      }
    }
    if(match ==false){
      state.pop_front();
    }
  }
}
