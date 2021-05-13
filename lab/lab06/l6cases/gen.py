from random import randint, choice, random
import string
import subprocess
import sys
import os

def random_string(n=50, include_space=False):
    if include_space:
        return "".join(choice(string.ascii_uppercase + string.ascii_lowercase + string.digits + "     ") for _ in range(n))
    return "".join(choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range(n))

def g_TypeNode():
    return[choice(["IntNode", "BoolNode", "VoidNode"]), 0]

def g_IdNode():
    n = randint(1, 10)
    return["IdNode", 0, random_string(n)]

def g_IntLitNode():
    n = randint(-10, 10)
    return["IntLitNode", 0, n]

def g_ExpNode():
    node = choice([["TrueNode", 0], ["FalseNode", 0], g_IntLitNode, g_IdNode, ["AssignNode", 2]])
    if type(node) != list:
        node = node()
    return node

def g_ProgramNode():
    n = randint(1, 10)
    tree = [["ProgramNode", 1], ["DeclListNode", n]]
    queue = [["DeclListNode", n]]
    while queue:
        cur_node = queue.pop(0)
        node_type = cur_node[0]
        num_child = cur_node[1]
        child = []
        if node_type == "DeclListNode":
            for _ in range(num_child):
                if random() < 0.2:
                    child.append(["FnDeclNode", 4])
                else:
                    child.append(["VarDeclNode", 2])
        elif node_type == "FnDeclNode":
            n = randint(1, 10)
            child.extend([g_TypeNode(), g_IdNode(), ["FormalsListNode", n], ["FnBodyNode", 2]])
        elif node_type == "FormalsListNode":
            for _ in range(num_child):
                child.append(["FormalDeclNode", 2])
        elif node_type == "FormalDeclNode":
            child.extend([g_TypeNode(), g_IdNode()])
        elif node_type == "FnBodyNode":
            child.extend([["DeclListNode", randint(0, 10)], ["StmtListNode", randint(0, 10)]])
        elif node_type == "VarDeclNode":
            child.append(g_TypeNode())
            child.append(g_IdNode())
        elif node_type == "StmtListNode":
            for _ in range(num_child):
                child.append(choice([["AssignStmtNode", 1], ["PostIncStmtNode", 1], ["PostDecStmtNode", 1]]))
        elif node_type == "AssignStmtNode":
            child.append(["AssignNode", 2])
        elif node_type == "AssignNode":
            child.append(g_ExpNode())
            child.append(g_ExpNode())
        elif node_type == "PostIncStmtNode":
            child.append(g_ExpNode())
        elif node_type == "PostDecStmtNode":
            child.append(g_ExpNode())

        queue.extend(child)
        tree.extend(child)
    return tree

if __name__ == "__main__":
    num_case = 100
    if len(sys.argv) <= 1:
        os.makedirs("out", exist_ok=True)
        for i in range(num_case):
            with open(f"out/{i}", "w") as fout:
                with open(f"in/{i}") as fin:
                    subprocess.run(['./ex1'], stdin=fin, stdout=fout)
            # diff
            p = subprocess.run(['diff', '--ignore-all-space', f"out/{i}", f"ans/{i}"], stdout=subprocess.PIPE)
            if p.stdout:
                print(f"Case {i} failed:")
                print(p.stdout.decode())
            else:
                print(f"Case {i} passed.")
    elif sys.argv[1] == "gen":
        os.makedirs("in", exist_ok=True)
        for i in range(num_case):
            tree = g_ProgramNode()
            while len(tree) > 1000:
                tree = g_ProgramNode()
            with open(f"in/{i}", "w") as f:
                f.write(str(len(tree)) + '\n')
                for node in tree:
                    f.write(' '.join([str(n) for n in node]) + '\n')
    elif sys.argv[1] == "ans":
        os.makedirs("ans", exist_ok=True)
        for i in range(num_case):
            with open(f"ans/{i}", "w") as fout:
                with open(f"in/{i}") as fin:
                    subprocess.run(['./ex1'], stdin=fin, stdout=fout)

