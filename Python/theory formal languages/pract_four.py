from collections import defaultdict

def check_states_input(prompt, valid_states=None):
    while True:
        user_input = input(prompt).strip().split()

        if not user_input:
            print("введи хотя бы одно состояние:")
            continue

        if all(item.isdigit() for item in user_input):#все элементы - числа
            user_set = set(user_input)
            if valid_states and not user_set <= valid_states:#если допустимый набор - все введеннные состояния принадлежат набору
                print("ошибка - Н")
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
            print("введи хотя бы два символа(алфавит)")
            continue

        if all(item.isalpha() and len(item) == 1 for item in user_input):
            return set(user_input)
        else:
            print("только односимвольные буквы")

from collections import defaultdict

def check_states_input(prompt, valid_states=None):
    while True:
        user_input = input(prompt).strip().split()

        if not user_input:
            print("введи хотя бы одно состояние")
            continue

        if all(item.isdigit() for item in user_input):
            user_set = set(user_input)
            if valid_states and not user_set <= valid_states:
                print("ошибка - состояния не из допустимого набора")
                continue
            return user_set
        else:
            print("введи только числовые значения")

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

        user_input = user_input[1:-1]#убираем 0-ую и посл скобку
        state_from, symbol, state_to = user_input.split(',')

        if state_from not in states or state_to not in states or symbol not in alphabet:
            print("ошибка:состояние или символ не из допустимого набора")
            continue

        transitions[state_from][symbol].add(state_to)
    return transitions

def read_nfa(states, alphabet, transitions, initial_states, final_states):#нка параметры
    transition_input = get_input("")
    for entry in transition_input:
        state, symbol, next_state = entry.strip("()").split(',')
        transitions[state][symbol].add(next_state)

def epsilon_closure(state_set, transitions):#находим E-замыкание (closure) для множества состояний state_set
    stack = list(state_set)
    closure = set(state_set)
    while stack:#пока стек не пуст - ивзлекаем состояние state
        state = stack.pop()
        if '' in transitions[state]:  # Проверяем ε-переходы
            for next_state in transitions[state]['']:
                if next_state not in closure:
                    closure.add(next_state)
                    stack.append(next_state)
    return closure

def move(state_set, symbol, transitions):#функция переходов
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
    dfa_states[start_closure] = 'S0'
    unmarked_states = [start_closure]
    state_count = 0

    while unmarked_states:
        current = unmarked_states.pop()
        dfa_transitions[dfa_states[current]] = {}
        for symbol in alphabet:
            next_state = frozenset(move(current, symbol, transitions))
            if next_state not in dfa_states:
                state_count += 1
                state_name = f'S{state_count}'
                dfa_states[next_state] = state_name
                unmarked_states.append(next_state)
            dfa_transitions[dfa_states[current]][symbol] = dfa_states[next_state]
            if next_state & final_states:
                dfa_final_states.add(dfa_states[next_state])

    return dfa_states, dfa_transitions, dfa_states[start_closure], dfa_final_states

def display_dfa(dfa_states, alphabet, dfa_transitions, initial_state, final_states):
    print("\nDFA:")
    print("set of states:", ', '.join(dfa_states.values()))
    print("input alphabet:", ', '.join(alphabet))
    print("state-transitions function:")
    for state in dfa_transitions:
        for symbol in alphabet:
            if symbol in dfa_transitions[state]:
                print(f"D({state}, {symbol}) = {dfa_transitions[state][symbol]}")
    print("initial state:", initial_state)
    print("final states:", ', '.join(final_states))

def main():
    print("введи набор состояний:")
    states = check_states_input("")

    alphabet = check_input_alphabet("введи алфавит:")

    transitions = get_transitions_input("введи переход в формате:(состояние, символ, следующее состояние)", states, alphabet)

    print("введи набор начальных состояний:")
    initial_states = check_states_input("")

    print("введи набор конечныз состояний:")
    final_states = check_states_input("")

    dfa_states, dfa_transitions, dfa_initial_state, dfa_final_states = nfa_to_dfa(
        states,
        alphabet,
        transitions,
        initial_states,
        final_states
    )#преобразуем НКА в ДКА

    display_dfa(
        dfa_states,
        alphabet,
        dfa_transitions,
        dfa_initial_state,
        dfa_final_states
    )#выводим ДКА

if __name__ == "__main__":
    main()
