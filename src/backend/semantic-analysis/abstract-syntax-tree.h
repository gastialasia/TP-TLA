#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

typedef struct Program Program;
typedef struct VmUnion VmUnion;
typedef struct VmType VmType;
typedef struct Resources Resources;
typedef struct Resource Resource;
typedef struct Component Component;
typedef struct Expression Expression;
typedef struct BiosType BiosType;
typedef struct NetExp NetExp;
typedef struct SoResource SoResource;
typedef struct Variable Variable;
typedef struct Operator Operator;
typedef struct NetType NetType;
typedef struct Unit Unit;

//ProgramNode
struct Program{
	VmUnion * vmUnion;
};

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/

//Multiple type means there is more than one VM defined in a single file
typedef enum {
	SINGLEVM,
	MULTIPLEVMS
} VmUnionType;

//Struct for non-terminals
struct VmUnion{
	VmUnionType vmUnionType;
	VmUnion * vmUnion;
	VmType * vmType;
};

struct VmType{
	//Es el nombre de la variable de la estructura que contiene la configuracion de la VM
	//No confundir con el nombre que se asigna a la Maquina virtual
	Resources * resources;
};

typedef enum{
	SINGLERESOURCES,
	MULTIPLERESOURCES
}	ResourcesType;

struct Resources{
	ResourcesType resourcesType;
	Resource * resource;
	Resources * resources;
};

typedef enum{
	COMPONENTCONFIG,
	BIOSCONFIG,
	NETCONFIG,
	NAMESTRING,
	SOCONFIG
}	ResourceType;

struct Resource{
	ResourceType * resourceType;
	Component * component;
	Expression * expression;
	BiosType * biosType;
	NetExp * netExp;
	SoResource * soResource;
};

typedef enum{
	CORESNUMBER,
	RAMNUMBER,
	DISKNUMBER
} ComponentType;

struct Component{
	ComponentType componentType;
};

typedef enum{
	WITHOUTOPERATOR,
	WITHOPERATOR
} ExpressionType;

struct Expression{
	ExpressionType expressionType;
	Variable * variable1;
	Variable * variable2;
	Operator * operator;
};

typedef enum{
	UEFISYSTEM,
	LEGACYSYSTEM
} BiosTypeType;

struct BiosType{
	BiosTypeType biosTypeType;
};

struct NetExp{
	NetType * netType;
};

typedef enum{
	SONAME,
	ISOPATH
} SoResourceType;

struct SoResource{
	SoResourceType soResourceType;
};

typedef enum{
	NUMBER,
	REFERENCE,
	UNITNUMBER
} VariableType;

struct Variable{
	VariableType variableType;
	Component * component;
	Unit * unit;
};

typedef enum{
	ADDITION,
	MULTIPLICATION,
	SUBSTRACTION
} OperatorType;

struct Operator{
	OperatorType operatorType;
};

typedef enum{
	NATCONFIG,
	BRIDGECONFIG,
	MACVTAPCONFIG
} NetTypeType;

struct NetType{
	NetTypeType netTypeType;
};

typedef enum{
	TERAB,
	GIGAB,
	MEGAB,
	KILOB
} UnitType;

struct Unit{
	UnitType unitType;
};

#endif
