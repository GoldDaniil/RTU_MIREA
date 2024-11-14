from collections import defaultdict, deque


def check_states_input(prompt, valid_states=None):
    while True:
        user_input = input(prompt).strip().split()

        if not user_input:
            print("введи хотя бы одно состояние:")
            continue

        if all(item.isdigit() for item in user_input):
            user_set = set(user_input)
            if valid_states and not user_set <= valid_states:
                print("ошибка - состояния не из допустимого набора")
                continue
            return user_set
        else:
            print("введи только числовые значения")


def get_input(prompt):
    return input(prompt).strip().split()


def check_input_alphabet(prompt):
    while True:
        user_input = input(prompt).strip().split()

        if len(user_input) < 2:
            print("введи хотя бы два символа алфавита:")
            continue

        if all(item.isalpha() and len(item) == 1 for item in user_input):
            return set(user_input)
        else:
            print("введи только односимвольные буквы:")


def get_transitions_input(prompt, states, alphabet):
    transitions = defaultdict(lambda: defaultdict(set))
    print(prompt)

    while True:
        user_input = input().strip()

        if user_input.lower() == 'домой':
            break

        user_input = user_input.replace(' ', '')
        if user_input.count(',') != 2 or not user_input.startswith('(') or not user_input.endswith(')'):
            print("ошибка: формат ввода :(состояние, символ, следующее состояние)")
            continue

        user_input = user_input[1:-1]
        state_from, symbol, state_to = user_input.split(',')

        if state_from not in states or state_to not in states or symbol not in alphabet:
            print("ошибка: состояние или символ не из допустимого набора")
            continue

        transitions[state_from][symbol].add(state_to)
    return transitions


def epsilon_closure(state_set, transitions):
    stack = list(state_set)
    closure = set(state_set)
    while stack:
        state = stack.pop()
        if '' in transitions[state]:
            for next_state in transitions[state]['']:
                if next_state not in closure:
                    closure.add(next_state)
                    stack.append(next_state)
    return closure


def move(state_set, symbol, transitions):
    next_states = set()
    for state in state_set:
        if symbol in transitions[state]:
            next_states.update(transitions[state][symbol])
    return epsilon_closure(next_states, transitions)


def nfa_to_dfa(states, alphabet, transitions, initial_states, final_states):
    dfa_states = {}
    dfa_transitions = {}
    dfa_final_states = set()

    start_closure = frozenset(epsilon_closure(initial_states, transitions))
    dfa_states[start_closure] = ''.join(sorted(start_closure))
    unmarked_states = deque([start_closure])

    while unmarked_states:
        current = unmarked_states.popleft()
        current_name = dfa_states[current]
        dfa_transitions[current_name] = {}

        for symbol in sorted(alphabet):
            next_state = frozenset(move(current, symbol, transitions))
            if not next_state:
                continue

            if next_state not in dfa_states:
                state_name = ''.join(sorted(next_state))
                dfa_states[next_state] = state_name
                unmarked_states.append(next_state)

            dfa_transitions[current_name][symbol] = dfa_states[next_state]
            if next_state & final_states:
                dfa_final_states.add(dfa_states[next_state])

    return dfa_states, dfa_transitions, dfa_states[start_closure], dfa_final_states


def display_dfa(dfa_states, alphabet, dfa_transitions, initial_state, final_states):
    print("\nDFA:")
    print("Set of states:", ', '.join(dfa_states.values()))
    print("Input alphabet:", ', '.join(sorted(alphabet)))
    print("State-transitions function:")

    for state in dfa_states.values():
        if state in dfa_transitions:
            for symbol in sorted(alphabet):
                if symbol in dfa_transitions[state]:
                    print(f"D({state}, {symbol}) = {dfa_transitions[state][symbol]}")

    print("Initial state:", initial_state)
    print("Final states:", ', '.join(sorted(final_states, key=lambda x: (len(x), x))))

def main():
    print("введи набор состояний:")
    states = check_states_input("")

    alphabet = check_input_alphabet("введи алфавит:")

    transitions = get_transitions_input(
        "введи переход в формате:(состояние, символ, следующее состояние)\nДля окончания ввода введи 'домой':",
        states,
        alphabet
    )

    print("введи набор начальных состояний:")
    initial_states = check_states_input("")

    print("введи набор конечных состояний:")
    final_states = check_states_input("")

    dfa_states, dfa_transitions, dfa_initial_state, dfa_final_states = nfa_to_dfa(
        states,
        alphabet,
        transitions,
        initial_states,
        final_states
    )

    display_dfa(
        dfa_states,
        alphabet,
        dfa_transitions,
        dfa_initial_state,
        dfa_final_states
    )


if __name__ == "__main__":
    main()
