#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <setjmp.h>
#include "minipseudtree.h"

struct variable
{
	char *name;
	double val;
	Node *funcNode;
	struct variable *next;
};

typedef struct variable variable;
 
typedef variable* variablesList;

variablesList list = NULL;

variable* getVariableByName(char *vName);
void addVariable(char *newName, double newValue,Node *funcNode);
char* removeQuotes(char* mString);

int printDepth = 0;
int funcDepth = 0;

double evalExpr(Node *node) {
	// printf("le type de expr %d\n", node->type);
	switch ( node->type ) 
	{
		case NTEMPTY:  return 0.0;
		case NTNUM: return node->val;
		
		case NTVAR:
		if (getVariableByName(node->var) != NULL && getVariableByName(node->var)->funcNode == NULL){
			return getVariableByName(node->var)->val;
		}
		printf("Error, %s has not been initialized !" , node->var);
		exit(1);
		case NTFUNC2:
		if (getVariableByName(node->children[0]->var) != NULL && getVariableByName(node->children[0]->var)->funcNode != NULL){
			// printf("titi\n");
			variable* func =  getVariableByName(node->children[0]->var);
			// printf("tototo\n");
			
			// printf("function name : %s\n", func->name);
			return evalInst(func->funcNode->children[1]);
		}
		else
		{
			printf("Error, %s has not been initialized2 !" , node->children[0]->var);
			exit(1);
		}
		case NTPLUS: return evalExpr(node->children[0])
				+ evalExpr(node->children[1]);
		case NTMIN: return evalExpr(node->children[0])
				- evalExpr(node->children[1]);
		case NTMULT: return evalExpr(node->children[0])
				* evalExpr(node->children[1]);
		case NTDIV: return evalExpr(node->children[0])
				/ evalExpr(node->children[1]);
		case NTPOW: return pow(evalExpr(node->children[0]),
				evalExpr(node->children[1]));
		case NTDOUBLEEQUAL:
			return evalExpr(node->children[0])
				== evalExpr(node->children[1]);
		case NTDIFFERENT:
			return evalExpr(node->children[0])
				!= evalExpr(node->children[1]);
		case NTINF:
			return evalExpr(node->children[0])
				< evalExpr(node->children[1]);
		case NTSUP:
			return evalExpr(node->children[0])
				> evalExpr(node->children[1]);
		case NTSUPOREQUAL:
			return evalExpr(node->children[0])
				>= evalExpr(node->children[1]);
		case NTINFOREQUAL:
			return evalExpr(node->children[0])
				<= evalExpr(node->children[1]);
		default: 
			printf("Error in evalExpr ... Wrong node type: %s\n", node2String(node));
			exit(1);
	};
}


void evalInst(Node* node) {
	// printf("trolo\n");
	double val;
	// printf("le type de Inst %d\n", node->type);
	switch ( node->type ) {
	case NTEMPTY: return;
	case NTINSTLIST:
		evalInst(node->children[0]);
		evalInst(node->children[1]);
		return;
	case NTAFF:
		addVariable(node->children[0]->var, evalExpr(node->children[1]),NULL);
		return;
	case NTFUNC:
		// printf("tututu\n");
		addVariable(node->children[0]->children[0]->var, 42, node);
		// printf("tatatatata\n");
		return;
	case NTFUNC2:
		evalExpr(node);
		return;
	/*case NTIF:
		
		if ( evalExpr(node->children[0]) ){
			evalInst(node->children[1]);
		}
		return;*/
	case NTFOR:
		addVariable(node->children[0]->children[0]->var, evalExpr(node->children[0]->children[1]),NULL);
		for (double i = node->children[0]->children[1]->val; evalExpr(node->children[1]->children[0])
				;evalInst(node->children[1]->children[1]->children[1]))
		{
			evalInst(node->children[1]->children[1]->children[0]);
		}

		return;
	
	case NTELSE:
		evalInst(node->children[0]);
		return;
		
	case NTWHILE:
		while ( evalExpr(node->children[0]) ){
			evalInst(node->children[1]);
		}

		return;
	case NTIFELSE:
		if ( evalExpr((node->children[0])->children[0]) == 1)
		{
			evalInst((node->children[0])->children[1]);
		}
		else
		{
			if ((node->children[1])->type != NTEMPTY)
			{
				evalInst((node->children[1])->children[0]);
			}
		}
		return;
	case NTSTRING:
		
		printf("%s" , removeQuotes(node->var));
		return;
		
	case NTVAR:
	case NTNUM:
	case NTPLUS:
	case NTMIN:
	case NTMULT:
	case NTDIV:
	case NTPOW:
	case NTDIFFERENT:
	case NTDOUBLEEQUAL:
	case NTINF:
	case NTSUP:
	case NTINFOREQUAL:
	case NTSUPOREQUAL:
		printf("%f\n", evalExpr(node));
		return;
	 
	default:
		printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
		exit (1);
	};
}

/*
	Used to remove the String quotes
*/
char* removeQuotes(char* mString)
{
	int i = 0;
	char* result = malloc( sizeof(char) * ( strlen(mString) - 3) );
	int counter = 0;
	for (i; i < strlen(mString); i++)
	{
		if (mString[i] != '\"')
		{
			result[counter] = mString[i];
			counter++;
		}
	}
	
	return result;
}


/*
	This funtion enable us to find a variable's value with it's name
*/
variable* getVariableByName(char *vName)
{
	// printf("tata\n");
	variable *result = NULL;
	variable *tmp = list;
	
	while(tmp != NULL)
	{
		if (strcmp(tmp->name,vName) == 0)
		{
			result = tmp;
			break;
		}
		
		tmp = tmp->next;
	}
	
	return result;
}

/*
	If the variable already exist, we only change it's value
	Else, we create a new variable
*/
void addVariable(char *newName, double newValue,Node *funcNode)
{
	variable *tmp = getVariableByName(newName);
	if (tmp != NULL)
	{
		tmp->val = newValue;
		tmp->funcNode = funcNode;
		return;
	}
	
	tmp = malloc(sizeof(variable));
	
	tmp->name = newName;
	tmp->val = newValue;
	tmp->funcNode = funcNode;
	tmp->next = NULL;
	
	if (list == NULL)
	{
		list = tmp;
	}
	else
	{
		variable* element = list;
        while(element->next != NULL)
        {
            element = element->next;
        }
        element->next = tmp;
	}	
}


void eval(Node *node) {
	 
	evalInst(node);
}