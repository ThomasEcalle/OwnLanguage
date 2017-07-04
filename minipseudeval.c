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
void printVarList();

int printDepth = 0;
int funcDepth = 0;

double evalExpr(Node *node) {
	// printf("EVALEXPR\n");
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
			variable* func =  getVariableByName(node->children[0]->var);
			Node *funcArgs = func->funcNode->children[0]->children[1];
			
			int numberOfArgs = 0;
			if (funcArgs->type != NTEMPTY)
			{
				while (funcArgs && funcArgs->var && funcArgs->type != NTEMPTY)
				{
					numberOfArgs++;
					funcArgs = funcArgs->children[1];
				}
				
			}
			Node *execArgs = node->children[1];
			int numberOfArgsEx = 0;
			if (execArgs->type != NTEMPTY)
			{
				while (execArgs && execArgs->var && execArgs->type != NTEMPTY)
				{
					numberOfArgsEx++;
					execArgs = execArgs->children[1];
				}
				
			}
			if (numberOfArgsEx != numberOfArgs)
			{
				printf("Error parsing function %s, expected %d arguments, recieved %d\n",node->children[0]->var,numberOfArgs,numberOfArgsEx);
				exit(1);
			}
			if (numberOfArgsEx > 0)
			{
				execArgs = node->children[1];
				funcArgs = func->funcNode->children[0]->children[1];
				while (execArgs && execArgs->var && execArgs->type != NTEMPTY)
				{
					addVariable(funcArgs->children[0]->var, execArgs->children[0]->val,NULL);
					execArgs = execArgs->children[1];
					funcArgs = funcArgs->children[1];
				}
			}
			
			
			evalInst(func->funcNode->children[1]);
			if (numberOfArgsEx > 0)
			{
				funcArgs = func->funcNode->children[0]->children[1];
				while (funcArgs && funcArgs->var && funcArgs->type != NTEMPTY)
				{
					//deleteVariableByName(funcArgs->children[0]->var);
					funcArgs = funcArgs->children[1];
				}
			}
			return;
		}
		else
		{
			printf("Error, %s has not been initialized2 !" , node->children[0]->var);
			exit(1);
		}
		case NTPLUS: 
				return evalExpr(node->children[0])
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
		case NTPRINTLIST:
			printVarList();
			return 0.0;
		default: 
			printf("Error in evalExpr ... Wrong node type: %s\n", node2String(node));
			exit(1);
	};
}


void evalInst(Node* node) {
	// printf("EVALINST\n");
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
		
	case NTCONCAT:
		evalInst(node->children[0]);
		evalInst(node->children[1]);
		//printf("\n%s%s" , removeQuotes((node->children[0])->var), removeQuotes((node->children[1])->var));
		return;
	case NTPRINTLIST:
			printVarList();
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
	char* result = malloc( sizeof(char) * ( strlen(mString) - 2 ) );
	int counter = 0;
	for (i; i < strlen(mString); i++)
	{
		if (mString[i] == '\\' && mString[i+1] == 'n')
		{
			result[counter] = '\n';
			counter++;
			i += 2;
		}
		if (mString[i] != '"')
		{
			result[counter] = mString[i];
			counter++;
		}
	}
	
	result[counter] = '\0';
	
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
void printVarList()
{
	int empty = 0;
	variable *tmp = list;
	
	while(tmp != NULL)
	{
		if (tmp->funcNode==NULL)
		{
			if (empty == 0)
			{
				empty = 1;
				printf("\nList of all declared variables:\n");
			}
			printf("Name: %s\tValue: %f\n", tmp->name,tmp->val);
		}
		
		tmp = tmp->next;
	}
	if (empty == 0)
		printf("Variables list is empty:\n");
	return;
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