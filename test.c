#include "Grammar.h"
#include "GrammarNodes/Alt.h"
#include "GrammarNodes/Opt.h"
#include "GrammarNodes/Rep.h"
#include "GrammarNodes/Seq.h"
#include "GrammarNodes/Rule.h"
#include "GrammarNodes/Term.h"

#include "Ctx.h"

int main()
{
    Grammar y = {.rules_count = 0, .terms_count = 0};


    term_prop(&y, 0, "=", ASSO_RIGHT);
    term_prop(&y, 1, "+", ASSO_LEFT);

    
    gdef(&y, digit,  alt( term("0"), term("1"), term("2"), term("3"), term("4"), 
                          term("5"), term("6"), term("7"), term("8"),  term("9")));    

    gdef(&y, number, seq(digit, alt(digit, number)));
    gdef(&y, expr,   seq(number, term("+"), number));

    Ctx ctx = {
        .y = y,
        .ast = NULL,
        .last_rule = "",
        .source = "23+52"
    };

    cmatch(&ctx);

    printf("---------\n");
    Ast_dump(ctx.ast);
}