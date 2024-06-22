#include "nfa.hpp"

// private:
bool NFA::has_state(const std::string& state) const{
    if(all_states.count(state) > 0){
        return true;
    } else {
        return false;  
    }
}

bool NFA::is_final_state(const std::string& state) const{
    if(final_states.count(state) == 0){
        return false;
    } else {
        return true;
    }
}

// public:
bool NFA::is_DFA() const{
    bool isDFA = true;
    const std::set<char> alphabetSymbols = alphabet.get_symbols();
    if(alphabetSymbols.find('e')!=alphabetSymbols.end()){
        isDFA = false;
    }
    for(auto state : all_states){
        for(auto symbol : alphabetSymbols){
            if(transitions(state, symbol).size() > 1 || transitions(state, symbol).size() == 0){
                isDFA = false;
            }
        }
    }
    return isDFA;
}

void NFA::update_state_name(const std::string& old_name, const std::string& new_name){
    if(starting_state == old_name){
        starting_state = new_name;
    }
    
    auto find1 = all_states.find(old_name);
    if (find1 != all_states.end()) {
        all_states.erase(old_name);
        all_states.insert(new_name);
    }
    
    auto find2 = final_states.find(old_name);
    if (find2 != final_states.end()) {
        final_states.erase(old_name);
        final_states.insert(new_name);
    }
    
    transitions.update_state_name(old_name, new_name);
}

bool NFA::process(std::string input){
    if(!alphabet.is_valid(input)){
        std::cout << "Invalid string" << std::endl;
        return false;
    }
    
    std::queue<ComputationBranch> processQueue;
    processQueue.push(ComputationBranch(starting_state, input));
    ComputationBranch processConfig;
    
    while(!processQueue.empty()){
        processConfig = processQueue.front();
        processQueue.pop();
        
        if(is_final_state(processConfig.get_last_config().first) && processConfig.get_last_config().second == ""){
            std::cout << processConfig << std::endl;
            std::cout << "Accept" << std::endl;
            return true;
        }
        
        std::set<std::string> newStates1 = transitions(processConfig.get_last_config().first, 'e');
        std::set<std::string> newStates2 = transitions(processConfig.get_last_config().first, processConfig.get_last_config().second[0]);
        
        for(auto state : newStates1){
            ComputationBranch newBranch = processConfig;
            newBranch.push_config(state, processConfig.get_last_config().second);
            processQueue.push(newBranch);
        }
        
        for(auto state : newStates2){
            ComputationBranch newBranch = processConfig;
            newBranch.push_config(state, processConfig.get_last_config().second.substr(1));
            processQueue.push(newBranch);
        }
    }
    std::cout << processConfig << std::endl;
    std::cout << "Reject" << std::endl;
    return false;
}
    
NFA NFA::operator!() const{
    NFA result = *this;
    if (result.is_DFA()) {
        std::set<std::string> difference;
        for (const auto& elem : result.all_states) {
            if (result.final_states.find(elem) == result.final_states.end()) {
                difference.insert(elem);
            }
        }
        result.final_states = difference;
    } else {
        std::cout << "Not a DFA" << std::endl;
    }
    return result;
}

NFA NFA::operator+(const NFA& other) const{
    NFA result = *this;
    NFA otherCopy = other;
    result.alphabet += other.alphabet;
    
    int i = 0;
    for(auto otherState : other.all_states){
        std::string new_state = otherState;
        while(other.has_state(new_state) && has_state(new_state)){
            new_state = "q" + new_state;
        }
        int j = 0;
        for(auto otherState2 : other.all_states){
            if(otherState2 == new_state && i != j){
                new_state = "q" + new_state;
            }
            j++;
        }
        otherCopy.update_state_name(otherState, new_state);
        i++;
    }

    
    std::string newStart = "s";
    
    for(auto state : all_states){
        if(state == newStart){
            newStart = "s" + newStart;
        }
    }
    
    for(auto state : otherCopy.all_states){
        if(state == newStart){
            newStart = "s" + newStart;
        }
    }
    
    for(auto state : otherCopy.all_states){
        result.all_states.insert(state);
    }
    
    for(auto state : otherCopy.final_states){
        result.final_states.insert(state);
    }
    
    result.transitions += otherCopy.transitions;
    result.transitions.add_rule(newStart, 'e', result.starting_state);
    result.transitions.add_rule(newStart, 'e', otherCopy.starting_state);
    
    result.all_states.insert(newStart);
    result.starting_state = newStart;
    
    return result;
}