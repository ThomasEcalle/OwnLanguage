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
	struct variable *next;
};

typedef struct variable variable;
 
typedef variable* variablesList;

variablesList list = NULL;

variable* getVariableByName(char *vName);
void addVariable(char *newName, double newValue);

int printDepth = 0;
int funcDepth = 0;

double evalExpr(Node *node) {
	switch ( node->type ) 
	{
		case NTEMPTY:  return 0.0;
		case NTNUM: return node->val;
		case NTVAR:
		if (getVariableByName(node->var) != NULL){
			return getVariableByName(node->var)->val;
		}
		printf("Error, %s has not been initialized !" , node->var);
		exit(1);
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
		default: 
			printf("Error in evalExpr ... Wrong node type: %s\n", node2String(node));
			exit(1);
	};
}


void evalInst(Node* node) {
	double val;
	switch ( node->type ) {
	case NTEMPTY: return;
	case NTINSTLIST:
		evalInst(node->children[0]);
		evalInst(node->children[1]);
		return;
	case NTAFF:
		addVariable(node->children[0]->var, evalExpr(node->children[1]));
		return;
	case NTVAR:
	case NTNUM:
	case NTPLUS:
	case NTMIN:
	case NTMULT:
	case NTDIV:
	case NTPOW:
		printf("%f\n", evalExpr(node));
		return;
	 
	default:
		printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
		exit (1);
	};
}


/*
	This funtion enable us to find a variable's value with it's name
*/
variable* getVariableByName(char *vName)
{
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
void addVariable(char *newName, double newValue)
{
	variable *tmp = getVariableByName(newName);
	if (tmp != NULL)
	{
		tmp->val = newValue;
		return;
	}
	
	tmp = malloc(sizeof(variable));
	
	tmp->name = newName;
	tmp->val = newValue;
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