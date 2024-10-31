Bin_num = ['1', '0', 'B', 'b']
Oct_num = ['0', '1', '2', '3', '4', '5', '6', '7', 'O', 'o']
Dec_num = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'd']
Hex_num = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f', 'H', 'h']
real_num = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'e', 'E']
keywords = ["program", "var", "begin", "end", "integer", "real", "boolean",
            "if", "then", "else", "for", "to", "do", "while", "read", "write",
            "as", "plus", "min", "or", "mult", "div", "and", "NE", "EQ", "LT",
            "LE", "GT", "GE"]

class States:
    H = "H"
    ID = "ID"
    NM = "NM"
    ASGN = "ASGN"
    DLM = "DLM"
    COMM = "COMM"
    ERR = "ERR"

class Toknames:
    KWORD = "KWORD"
    IDENT = "IDENT"
    NUM = "NUM"
    OPER = "OPER"
    DELIM = "DELIM"

class token:
    def __init__(self, token_name, token_value):
        self.token_name = token_name
        self.token_value = token_value

class LexemeTable:
    def __init__(self, tok=None):
        self.tok = tok
        self.next = None

lt = None
lt_head = None

def is_kword(id):
    return id in keywords

def add_token(tok):
    global lt, lt_head
    new_entry = LexemeTable(tok)
    if lt is None:
        lt = new_entry
        lt_head = new_entry
    else:
        lt.next = new_entry
        lt = new_entry

def lexer(filename):
    try:
        with open(filename, "r") as fd:
            CS = States.H
            c = fd.read(1)
            while c:
                if CS == States.H:
                    while c in [' ', '\t', '\n']:
                        c = fd.read(1)
                    if c.isalpha() or c == '_':
                        CS = States.ID
                    elif c.isdigit() or c == '.':
                        CS = States.NM
                    elif c == ':':
                        CS = States.ASGN
                    elif c == '{':
                        CS = States.COMM
                        c = fd.read(1)
                    elif c in [',', ';', '(', ')', '"']:
                        tok = token(Toknames.DELIM, c)
                        add_token(tok)
                        c = fd.read(1)
                    else:
                        CS = States.DLM
                elif CS == States.ASGN:
                    colon = c
                    c = fd.read(1)
                    if c == '=':
                        tok = token(Toknames.OPER, ":=")
                        add_token(tok)
                        c = fd.read(1)
                        CS = States.H
                    else:
                        tok = token(Toknames.OPER, ":")
                        add_token(tok)
                        CS = States.H
                elif CS == States.DLM:
                    if c in ['+', '-', '*', '/', '!', '=', '<', '>', '&', '|', '~']:
                        buf = c
                        c = fd.read(1)
                        if buf == '=' and c == '=':
                            buf += c
                            tok = token(Toknames.OPER, buf)
                            add_token(tok)
                            c = fd.read(1)
                        else:
                            tok = token(Toknames.OPER, buf)
                            add_token(tok)
                        CS = States.H
                    else:
                        print(f"\nunknown character: {c}")
                        c = fd.read(1)
                        CS = States.ERR
                elif CS == States.COMM:
                    while c:
                        if c == '}':
                            c = fd.read(1)
                            CS = States.H
                            break
                        c = fd.read(1)
                elif CS == States.ERR:
                    CS = States.H
                elif CS == States.ID:
                    buf = c
                    c = fd.read(1)
                    while c.isalnum() or c == '_':
                        buf += c
                        c = fd.read(1)
                    if is_kword(buf):
                        tok = token(Toknames.KWORD, buf)
                    else:
                        tok = token(Toknames.IDENT, buf)
                    add_token(tok)
                    CS = States.H
                elif CS == States.NM:
                    buf = ''
                    while c.isdigit() or c in ['B', 'b', 'O', 'o', 'D', 'd', 'H', 'h', '.']:
                        buf += c
                        c = fd.read(1)
                    tok = token(Toknames.NUM, buf)
                    add_token(tok)
                    CS = States.H

    except FileNotFoundError:
        print(f"\ncannot open file {filename}.\n")
        return -1

def print_tokens(lt_head):
    current = lt_head
    while current:
        print(f"token name: {current.tok.token_name}, token value: {current.tok.token_value}")
        current = current.next

def main():
    filename = "text.txt"
    result = lexer(filename)
    if result == -1:
        print("lexical analysis failed")
    else:
        print("\nlexical analysis successful")
        print_tokens(lt_head)

if __name__ == "__main__":
    main()
