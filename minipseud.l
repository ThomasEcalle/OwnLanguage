%option noyywrap
%{

#include "minipseud.h"
#include <stdlib.h>
#include "minipseudtree.h"

%}

empty    [ \t]+

num   [0-9]
int    {num}+
exp  [eE][+-]?{int}
if_statement "if"
while_statement "while"
for_statement "for"
var   [a-z]+
real      {int}("."{int})?{exp}?



%%

{empty}  { /* Nothing */ }

 

"("   return(OP_PAR);
")"   return(CL_PAR);

"{"   return(OP_BRACKET);
"}"   return(CL_BRACKET);



{if_statement} {
	yylval.node = createNode(NTIF);
    return(IF);
}
{while_statement} {
	yylval.node = createNode(NTWHILE);
    return(WHILE);
}
{for_statement} {
	yylval.node = createNode(NTFOR);
    return(FOR);
}

{var}    {
    yylval.node = createNode(NTVAR);
    yylval.node->var = (char*)_strdup(yytext);
    return(VAR);
    }
	
{real}    {
    yylval.node = createNode(NTNUM);
    yylval.node->val = atof(yytext);
    return(NUM);
    }

"+"   { yylval.node = createNode(NTPLUS); return(PLUS); }
"-"   { yylval.node = createNode(NTMIN); return(MIN); }
"*"   { yylval.node = createNode(NTMULT); return(MULT); }
"/"   { yylval.node = createNode(NTDIV); return(DIV); }
"^"   { yylval.node = createNode(NTPOW); return(POW); }
"=="  { yylval.node = createNode(NTDOUBLEEQUAL); return(DOUBLEEQUAL); }
"!="  { yylval.node = createNode(NTDIFFERENT); return(DIFFERENT); }
"<="  { yylval.node = createNode(NTINFOREQUAL); return(INFOREQUAL); }
"<"  { yylval.node = createNode(NTINF); return(INF); }
">="  { yylval.node = createNode(NTSUPOREQUAL); return(SUPOREQUAL); }
">="  { yylval.node = createNode(NTSUP); return(SUP); }
"="  { yylval.node = createNode(NTAFF); return(AFF); }



 
 

";"    { return(COLON); }

"\n"   { return(EOL); }
