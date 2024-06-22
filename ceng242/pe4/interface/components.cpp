#include "components.hpp"

/* operator<< overloads */
std::ostream& operator<<(std::ostream& os, Alphabet& a){
    std::set<char> symbols = a.get_symbols();
    for (char elem : symbols) {
        os << elem << " ";
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const Rule& r){
    std::string initial_state = r.initial_state;
    std::string final_state = r.final_state;
    char symbol = r.symbol;
    os << initial_state << " " << symbol << " " << final_state;
    return os;
}
std::ostream& operator<<(std::ostream& os, TransitionTable& t){
    std::vector<Rule> rules = t.rules;
    for(int i = 0; i < rules.size(); i++){
        os << rules[i] << std::endl; 
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const ComputationBranch& c){
    for(int i = 0; i < c.config_history.size(); i++){
        if(c.config_history[i].second != ""){
            if(i != c.config_history.size()-1){
                os << "(" << c.config_history[i].first << ", " << c.config_history[i].second << " :- ";
            } else {
                os << "(" << c.config_history[i].first << ", " << c.config_history[i].second;
            }
        } else {
            os << "(" << c.config_history[i].first << ", e";
        }
        
    }
    return os;
}


/* Alphabet */
bool Alphabet::is_valid(const std::string& input) const{
    int notValidSymbol = 0;
    for(int i = 0; i < input.length(); i++){
        if(symbols.count(input[i]) == 0){
            notValidSymbol++;
        }
    }
    if(notValidSymbol == 0){
        return true;
    } else {
        return false;
    }
}

const std::set<char> Alphabet::get_symbols() const { 
    std::set<char> a;
    a = symbols;
    return a; 
}

Alphabet& Alphabet::operator+=(const Alphabet& other){
    for(char symbol : other.get_symbols()){
        symbols.insert(symbol);
    }
    return *this;
}


/* Rule */
Rule::Rule(const std::string& init_s, char symbol, const std::string& final_s){
    this->initial_state = init_s;
    this->symbol = symbol;
    this->final_state = final_s;
}

const std::string Rule::get_final_state() const {
    return final_state;
}

void Rule::update_state_name(const std::string& old_name, const std::string& new_name){
    if(initial_state == old_name){
        initial_state = new_name;
    }
    if(final_state == old_name){
        final_state = new_name;
    }
}

bool Rule::applies_to(const std::string& c, char s) const{
    if(initial_state == c && symbol == s){
        return true;
    } else {
        return false;
    }
}


/* TransitionTable */
void TransitionTable::add_rule(const std::string& initial_state, char symbol, const std::string& final_state){
    Rule newRule = Rule(initial_state, symbol, final_state);
    rules.push_back(newRule);
}

void TransitionTable::update_state_name(const std::string& old_name, const std::string& new_name){
    for(int i = 0; i < rules.size(); i++){
        rules[i].update_state_name(old_name, new_name);
    }
}

const std::set<std::string> TransitionTable::operator()(const std::string& curr_state, char symbol) const{
    std::set<std::string> next_states;
    for(int i = 0; i < rules.size(); i++){
        if(rules[i].applies_to(curr_state,symbol)){
            next_states.insert(rules[i].get_final_state());
        }
    }
    return next_states;
}

TransitionTable& TransitionTable::operator+=(const TransitionTable& other){
    std::vector<Rule> otherRules = other.rules;
    for(int i = 0; i < otherRules.size(); i++){
        rules.push_back(otherRules[i]);
    }
    return *this;
}

/* ComputationBranch */
void ComputationBranch::push_config(const std::string& state, const std::string& input){
    std::pair<std::string, std::string> newConfig(state, input);
    config_history.push_back(newConfig);
}

const std::pair<std::string,std::string> ComputationBranch::get_last_config() const{
    return config_history[config_history.size()-1];
}

