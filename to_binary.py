import argparse
import re
from typing import List

import argparse_constants

allowed_heads : List[re.Pattern] = [re.compile(r"""
    Hello everybody.
    I'm practised 2.5 years, and my name is .*\.
    I like singing, dancing, rapping, and playing basketball.
    Music.
    """.strip(' \n\t')),
    re.compile(r"""J.N.T.M. by .*""".strip(' \n\t'))
]

syntax_dic = {
    "":""
}

parser = argparse.ArgumentParser(description="Compiler from RapLan to binary code "
                                "which running in a virtual machine.")
parser.add_argument("--run", action=argparse_constants.ARGPARSE_STORE_TRUE,
                    default=False, help="Auto run the program.")
parser.add_argument("--assembly", action=argparse_constants.ARGPARSE_STORE_TRUE,
                    default=False, help="Compile function to NASM assembly, "
                    "not VM construction. You need assemble it by yourself.")
parser.add_argument("--output", "-o", action=argparse_constants.ARGPARSE_STORE, required=True,
                    help="Output file, required.")
parser.add_argument("input", action=argparse_constants.ARGPARSE_STORE, required=True,
                    help="Input file, required.")
args=parser.parse_args()

with open(args.input, "r", encoding="utf-8") as f:
    rap = f.readline()

# Check the head
matched = -1
for index,i in enumerate(allowed_heads):
    if i.match("\n".join(
        rap[:4+1]
    )):
        matched=index
        break
    pass
else:
    print("\x1b[31m%s:1: ERROR: What's your name?\x1b[0m" % args.input)

for i in range():
    pass
