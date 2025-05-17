# Recursive-Descent Grammar Parser

This repository implements a top‑down parser for grammars that performs recursive backtracking through grammar nodes.
It evaluates each node sequentially and employs explicit state checkpointing to revert on match failure.


The worst‑case time complexity is currently exponential O(R^n) for R rules over an input of length n due to the combinatorial exploration of grammar nodes and the lack of memoization.

See the [todo file](./todo) for roadmap.

# Usage 

Run `make` to test

With these rules:
```C
    gdef(&y, digit,  alt( term("0"), term("1"), term("2"), term("3"), term("4"), 
                          term("5"), term("6"), term("7"), term("8"),  term("9")));    

    gdef(&y, number, seq(digit, alt(digit, number)));
    gdef(&y, expr,   seq(number, term("+"), number));
```

The evaluation result for "23+52" is:

```text
---------
AST Dump:
- expr 
  - number 
    - digit 
      - term (2)
    - digit 
      - term (3)
  - term (+)
  - number 
    - digit 
      - term (5)
    - digit 
      - term (2)
```

# Deps
**any C99 compiler with:**
- malloc, free
- printf, fprintf
- strdup, strcmp, strncmp, strlen
- exit