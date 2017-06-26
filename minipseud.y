%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minipseudtree.h"
#include "minipseudeval.h"

extern int  yyparse();
extern FILE *yyin;


Node root;
 

%}

%union {
	struct Node *node;
}


%token   <node> NUM VAR STRING PRINT
%token   <node> PLUS MIN MULT DIV POW AFF IF ELSE DOUBLEEQUAL WHILE DIFFERENT INF SUP INFOREQUAL SUPOREQUAL FOR FUNCTION COMA
%token   OP_PAR CL_PAR OP_BRACKET CL_BRACKET COLON
%token   EOL


%type   <node> Instlist
%type   <node> Inst
%type   <node> Expr
%type   <node> BoolExpr
%type   <node> FUNC
%type   <node> ARGS
  

%left OR
%left AND
%left EQ NEQ
%left GT LT GET LET
%left PLUS  MIN
%left MULT  DIV
%left NEG NOT
%right  POW

%start Input
%%

Input:
      {/* Nothing ... */ }
  | Line Input { /* Nothing ... */ }


Line:
    EOL {  }
  | Instlist EOL { exec($1);    }
  ; 

Instlist:
    Inst { $$ = nodeChildren(createNode(NTINSTLIST), $1, createNode(NTEMPTY)); } 
  | Instlist Inst { $$ = nodeChildren(createNode(NTINSTLIST), $1, $2); }
  ;

Inst:
    Expr COLON { $$ = $1; } 
	| VAR AFF Expr COLON {$$ =  nodeChildren($2, $1, $3);}
	| FUNC {$$=$1;}
	| IF OP_PAR BoolExpr CL_PAR OP_BRACKET Instlist CL_BRACKET
						{ 
							Node* ifNode =  nodeChildren($1,$3,$6);
							Node* elseNode = createNode(NTEMPTY);
							
							$$ = nodeChildren( createNode(NTIFELSE), ifNode, elseNode );
						}
	| IF OP_PAR BoolExpr CL_PAR OP_BRACKET Instlist CL_BRACKET ELSE OP_BRACKET Instlist CL_BRACKET
						{ 
							Node* ifNode =  nodeChildren($1,$3,$6);
							Node* elseNode = nodeChildren($8, $10, createNode(NTEMPTY));
							
							$$ = nodeChildren( createNode(NTIFELSE), ifNode, elseNode );
						}
	
	| WHILE OP_PAR BoolExpr CL_PAR OP_BRACKET Instlist CL_BRACKET
						{ 
							$$ = nodeChildren($1,$3,$6);
						}
	| FOR OP_PAR VAR AFF Expr COLON BoolExpr COLON Instlist CL_PAR OP_BRACKET Instlist CL_BRACKET
						{ 
							$$ = nodeChildren($1,nodeChildren($4,$3,$5),nodeChildren(createNode(NTIF), $7, nodeChildren(createNode(NTINSTLIST), $12, $9)));
						}
  ;

ARGS:
	{ $$ = nodeChildren(createNode(NTVAR), createNode(NTEMPTY), createNode(NTEMPTY)); }
	| VAR { $$ = nodeChildren(createNode(NTVAR), $1, createNode(NTEMPTY)); } 
	| NUM { $$ = nodeChildren(createNode(NTNUM), $1, createNode(NTEMPTY)); } 
	| VAR COMA ARGS { $$ = nodeChildren(createNode(NTARGS), $2, $1); }
	| NUM COMA ARGS { $$ = nodeChildren(createNode(NTARGS), $2, $1); }
FUNC:
	FUNCTION VAR OP_PAR ARGS CL_PAR OP_BRACKET Instlist CL_BRACKET
	{
		$$=nodeChildren(createNode(NTFUNC),nodeChildren(createNode(NTEMPTY),$2,$4),$7);
	}
	
	
BoolExpr:

	Expr DOUBLEEQUAL Expr { $$ = nodeChildren($2,$1,$3); }
	| Expr DIFFERENT Expr { $$ = nodeChildren($2,$1,$3); }
	| Expr INF Expr { $$ = nodeChildren($2,$1,$3); }
	| Expr INFOREQUAL Expr { $$ = nodeChildren($2,$1,$3); }
	| Expr SUP Expr { $$ = nodeChildren($2,$1,$3); }
	| Expr SUPOREQUAL Expr { $$ = nodeChildren($2,$1,$3); }

	;
Expr:
  NUM			{ $$ = $1; }
  | VAR { $$ = $1; }
  | STRING { $$ = $1; }
  | VAR OP_PAR ARGS CL_PAR { $$ = nodeChildren(createNode(NTFUNC2), $1, $3);  }
  | Expr PLUS Expr   { $$ = nodeChildren($2, $1, $3); }
  | Expr MIN Expr      { $$ = nodeChildren($2, $1, $3); }
  | Expr MULT Expr     { $$ = nodeChildren($2, $1, $3); }
  | Expr DIV Expr      { $$ = nodeChildren($2, $1, $3); }
  | MIN Expr %prec NEG { $$ = nodeChildren($1, createNode(NTEMPTY), $2); }
  | Expr POW Expr      { $$ = nodeChildren($2, $1, $3); }
  | OP_PAR Expr CL_PAR { $$ = $2; }
  | BoolExpr {$$ = $1}
  | PRINT OP_PAR Expr CL_PAR { $$ = $3; }
  ;


%%

 
 

int exec(Node *node) {
   //printGraph(node);
	eval(node);
}

 

int yyerror(char *s) {
  printf("%s\n", s);
}

 

int main(int arc, char **argv) {
   if ((arc == 3) && (strcmp(argv[1], "-f") == 0)) {
    
    FILE *fp=fopen(argv[2],"r");
    if(!fp) {
      printf("Impossible d'ouvrir le fichier à executer.\n");
      exit(0);
    }      
    yyin=fp;
    yyparse();
		  
    fclose(fp);
  }  
  exit(0);
}
