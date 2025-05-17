#include "Grammar.h"
#include "GrammarNodes/Alt.h"
#include "GrammarNodes/Opt.h"
#include "GrammarNodes/Rep.h"
#include "GrammarNodes/Seq.h"
#include "GrammarNodes/Rule.h"
#include "GrammarNodes/Term.h"

#include "Ctx.h"

#define test2(arr) printf("arr of %zu\n", sizeof(arr) / sizeof(arr[0]))
#define test1(...) test2((GrammarNode*[]) { __VA_ARGS__ })

int main()
{
    Grammar y = {.rules_count = 0, .terms_count = 0};


    term_prop(&y, 0, "=", ASSO_RIGHT);
    term_prop(&y, 1, "+", ASSO_LEFT);

    test1(term("0"));

    
    gdef(&y, digit,  alt(term("0"), 
                        alt(term("1"),
                            alt(term("2"),
                                alt(term("3"),
                                    alt(term("4"),
                                        alt(term("5"),
                                            alt(term("6"),
                                                alt(term("7"),
                                                    alt(term("8"), term("9")

                    ))))))))));    
    gdef(&y, number, seq(rule(digit), alt(rule(digit), rule(number))));

    Ctx ctx = {
        .y = y,
        .ast = NULL,
        .last_rule = "",
        .source = "23"
    };

    cmatch(&ctx);

    printf("---------\n");
    Ast_dump(ctx.ast);
}