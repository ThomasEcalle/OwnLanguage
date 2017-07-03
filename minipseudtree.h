#ifndef MINIPSEUDTREE
# define MINIPSEUDTREE
    
enum NodeType {
	NTEMPTY = 0,
	NTINSTLIST = 1,
	NTNUM   = 201,
	NTVAR = 222,
	NTPLUS  = 321,
	NTMIN   = 322,
	NTMULT  = 323,
	NTDIV   = 324,
	NTPOW   = 325,
	NTEQ = 326,
	NTAFF = 328,
	NTDOUBLEEQUAL = 329,
	NTIF = 330,
	NTWHILE = 331,
	NTDIFFERENT = 332,
	NTELSE = 333,
	NTIFELSE = 334,
	
	NTINF = 335,
	NTINFOREQUAL = 336,
	NTFOR = 337,
	NTSUP = 338,
	NTSUPOREQUAL = 339,
	NTFUNC = 340,
	NTFUNC2 = 341,
	NTARGS = 342,
	
	NTSTRING = 343,
	NTPRINT = 344,
	NTCONCAT = 345,
	NTPRINTLIST = 346
};
   
typedef struct Node {
	enum NodeType type;
	union { 
		double val;
		char* var;
		struct Node** children;
	} ;
} Node;

Node* createNode(int type);

Node* nodeChildren(Node* father, Node *child1, Node *child2);

const char* node2String(Node *node);

void printGraph(Node *root);

#endif
