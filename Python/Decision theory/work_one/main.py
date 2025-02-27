import csv
import pandas as pd
from tabulate import tabulate

def print_table(data, headers):#ouput таблицы
    df = pd.DataFrame(data)
    print(tabulate(df, headers=headers, tablefmt='pretty', showindex=False))

def dominates(a, b):#a > b ?
    strictly_better = False

    for key in a:
        try:
            a_val = float(a[key])
            b_val = float(b[key])
        except ValueError:
            continue#if знач != привести к числу

        if key.endswith('(+)'):
            if a_val < b_val:
                return False
            elif a_val > b_val:
                strictly_better = True

        elif key.endswith('(-)'):
            if a_val > b_val:
                return False
            elif a_val < b_val:
                strictly_better = True

    return strictly_better

def create_pareto_set(data):#оптимал мнво парето из набора альтернатив
    pareto_set = []

    for candidate in data:
        if not any(dominates(other, candidate) for other in data if other != candidate):
            pareto_set.append(candidate)

    return pareto_set

def bounds_optimization(data, bounds):#фильтрация данных по верхним нижним границам
    #bounds — список словарей - ключ — критерий - значение — порог
    winners = []

    for item in data:
        valid = True

        for b in bounds:
            key, threshold = list(b.items())[0]

            try:
                value = float(item[key])
            except ValueError:
                valid = False
                break

            if key.endswith('(+)') and value < threshold:
                valid = False
                break

            elif key.endswith('(-)') and value > threshold:
                valid = False
                break

        if valid:
            winners.append(item)

    return winners

def suboptimization(data, bounds, main_criteria): #субоптимизация - сначал филтрация - выбор альтентаив - для крит с суф '-' - мин знач, '+' - макс
    filtered_data = bounds_optimization(data, bounds)

    if not filtered_data:
        return []

    try:
        values = [float(item[main_criteria]) for item in filtered_data]
    except ValueError:
        return []

    if main_criteria.endswith('(-)'):
        optimal_value = min(values)
    elif main_criteria.endswith('(+)'):
        optimal_value = max(values)
    else:
        return filtered_data

    return [item for item in filtered_data if float(item[main_criteria]) == optimal_value]


def lex_optimization(data, priority):#лексическ оптимимизация - порядок приоритетов
    #кортеж критиеров в порядке важности - priority

    def sorting_key(item):
        key_values = []

        for crit in priority:
            try:
                val = float(item[crit])
            except ValueError:
                val = 0

            key_values.append(val if crit.endswith('(+)') else -val)#для положительноых критериев - чем выще тем лучше
            #чем ниже тем лучше
        return tuple(key_values)

    sorted_data = sorted(data, key=sorting_key, reverse=True)
    return sorted_data[:1] if sorted_data else []

if __name__ == "__main__":
    with open('tpr_1_1.csv', encoding='utf-8') as file:
        data = list(csv.DictReader(file))

    headers = ["№", "варианты решений", "стоимость подписки (руб/мес) (-)", "рейтинг приложения (+)",
               "скорость соединения (mbps) (+)", "задержка соединения (мс) (-)"]

    print("исходная таблица с альтернативами и критериями:".center(201))
    print_table(data, headers)

    pareto_set = create_pareto_set(data)
    print("оптимальное множество Парето:".center(201))
    print_table(pareto_set, headers)

    bounds = [{"скорость соединения (mbps) (+)": 85}, {"стоимость подписки (руб/мес) (-)": 90}] # Исправлено
    filtered_data = bounds_optimization(pareto_set, bounds)
    print("метод указания верхних/нижних границ:".center(201))
    print_table(filtered_data, headers)

    bounds_subopt = [{"рейтинг приложения (+)": 4.7}, {"задержка соединения (мс) (-)": 50}]#субоптимизация
    main_criteria = "скорость соединения (mbps) (+)" # Исправлено
    subopt_result = suboptimization(pareto_set, bounds_subopt, main_criteria)
    print("cубоптимизация:".center(201))
    print_table(subopt_result, headers)

    priority = ("стоимость подписки (руб/мес) (-)", "скорость соединения (mbps) (+)", # Исправлено
                "задержка соединения (мс) (-)", "рейтинг приложения (+)")
    lex_result = lex_optimization(pareto_set, priority)
    print("лексикографическая оптимизация:".center(201))
    print_table(lex_result, headers)
