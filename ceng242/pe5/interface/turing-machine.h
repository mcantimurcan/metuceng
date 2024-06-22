#pragma once
#include "turing-machine_utils.h"

template <typename A, typename B> struct is_same { static constexpr auto value = false; };
template <typename A> struct is_same<A, A>{ static constexpr auto value = true; };

template <bool C, typename = void> struct EnableIf;
template <typename Type> struct EnableIf<true, Type>{ using type = Type; };

template <typename Config, typename Transitions, typename = void>
struct TransitionFunction
{
    using TransitionIsEmpty = Rule<typename Config::state, typename Config::input_tape, QReject, typename Config::input_tape, STOP>;
    
    template <typename Transition>
    struct FilterFunction {
        static constexpr bool value = is_same<typename Transition::old_state, typename Config::state>::value &&
                                      is_same<typename Transition::input, typename Config::input_tape::template at<Config::position>>::value;
    };
    
    using RuleSet = typename Filter<FilterFunction,List<>,Transitions>::type;
    
    using FinalRule = typename Conditional<Size<RuleSet>::value == 0,
        TransitionIsEmpty,
        typename RuleSet::template at<0>>::type;
    
    using NewInput = typename Replace<typename FinalRule::output, Config::position, typename Config::input_tape>::type;
    
    using AddBlankLeft = typename Conditional<(Config::position == 0 && FinalRule::direction == -1),
        typename Prepend<Input<-1>, NewInput>::type, NewInput>::type;
        
    using AddBlankRight = typename Conditional<(Config::position == Size<AddBlankLeft>::value - 1 && FinalRule::direction == 1),
        typename Append<Input<-1>, AddBlankLeft>::type, AddBlankLeft>::type;
    
    using NextConfig = Configuration<AddBlankRight, typename FinalRule::new_state, Config::position + FinalRule::direction>;
    using NextTransition = TransitionFunction<NextConfig, Transitions>;
    
    using end_input = typename NextTransition::end_input;
    using end_config = typename NextTransition::end_config;
    using end_state = typename NextTransition::end_state;
    static constexpr auto end_position = NextTransition::end_position;
};

template <typename InputTape, typename State, int Position, typename Transitions>
struct TransitionFunction<Configuration<InputTape, State, Position>, Transitions,
                          typename EnableIf<is_same<State, QAccept>::value ||
                                            is_same<State, QReject>::value>::type>
{
    // @TODO: Implement this
    using end_config = Configuration<InputTape, State, Position>;
    using end_input = InputTape;
    using end_state = State;
    static constexpr auto end_position = Position;

};