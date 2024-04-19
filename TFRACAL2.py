#ÅºrÃ³dÅo1: https://www.algorytm.edu.pl/algorytmy-maturalne/onp
#ÅºrÃ³dÅo2: korzystaÅem z prezentacji z przedmiotu Algorytmy i Struktury Danych
from fractions import Fraction
 
def collect_data():
    data = []
    try:
        while True:
            line = input()
            data.append(line)
    except EOFError:
        pass
    return data
 
 
def process_data(data):
    cases = []
    case = []
    for _,token in enumerate(data):
        if "case" in token:
            cases.append(case)
            case = []
        else:
            case.append(token)
    cases.append(case)
    cases = cases[1:] #removing first empty case
    return cases
 
def calculate(a,b,token):
    if token == '+':
        return b+a
    elif token == '*':
        return b*a
    elif token == '/':
        return b/a
 
def calculate_onp(variables, onp):
    stack = []
    onp_splited = onp.split("_")[1:] #skipping first empty element
    onp_parsed = []
    for token in onp_splited:
        if token.isalpha():
            onp_parsed.append(token)
        else:
            var = ""
            operators = []
            for c in token:
                if c.isalpha():
                    var += c
                else:
                    operators.append(c)
            onp_parsed.append(var)
            for op in operators:
                onp_parsed.append(op)
 
    for token in onp_parsed:
        if token.isalpha():
            stack.append(variables[token])
        else:
            a = stack.pop()
            b = stack.pop()
            b = calculate(a,b,token)
            stack.append(b)
    return stack.pop()
def solve_case(case):
    variables = {}
    for token in reversed(case):
        variable,value = token.split('=')
        try:
            val = Fraction(value)
            variables[variable] = val
        except ValueError:
            val = calculate_onp(variables,value)
            variables[variable] = val
    return variables
 
raw_data = collect_data()
cases = process_data(raw_data)
for index,case in enumerate(cases,start=1):
    print("case " + str(index) + " Y")
    computed_variables = solve_case(case)
    for _,(key,val) in enumerate(sorted(computed_variables.items())):
        print(key, val.numerator,val.denominator)
