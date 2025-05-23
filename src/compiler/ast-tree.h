#pragma once

#include "compiler/parser.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

typedef enum AstTreeToken {
  AST_TREE_TOKEN_FUNCTION,
  AST_TREE_TOKEN_BUILTIN,

  AST_TREE_TOKEN_KEYWORD_PUTC,
  AST_TREE_TOKEN_KEYWORD_RETURN,
  AST_TREE_TOKEN_KEYWORD_IF,
  AST_TREE_TOKEN_KEYWORD_WHILE,
  AST_TREE_TOKEN_KEYWORD_COMPTIME,
  AST_TREE_TOKEN_KEYWORD_STRUCT,

  AST_TREE_TOKEN_TYPE_FUNCTION,
  AST_TREE_TOKEN_TYPE_ARRAY,
  AST_TREE_TOKEN_TYPE_TYPE,
  AST_TREE_TOKEN_STATIC_VARS_BEGIN = AST_TREE_TOKEN_TYPE_TYPE,
  AST_TREE_TOKEN_TYPE_VOID,
  AST_TREE_TOKEN_TYPE_I8,
  AST_TREE_TOKEN_TYPE_U8,
  AST_TREE_TOKEN_TYPE_I16,
  AST_TREE_TOKEN_TYPE_U16,
  AST_TREE_TOKEN_TYPE_I32,
  AST_TREE_TOKEN_TYPE_U32,
  AST_TREE_TOKEN_TYPE_I64,
  AST_TREE_TOKEN_TYPE_U64,
#ifdef FLOAT_16_SUPPORT
  AST_TREE_TOKEN_TYPE_F16,
#endif
  AST_TREE_TOKEN_TYPE_F32,
  AST_TREE_TOKEN_TYPE_F64,
  AST_TREE_TOKEN_TYPE_F128,
  AST_TREE_TOKEN_TYPE_CODE,
  AST_TREE_TOKEN_TYPE_BOOL,
  AST_TREE_TOKEN_VALUE_VOID,
  AST_TREE_TOKEN_STATIC_VARS_END = AST_TREE_TOKEN_VALUE_VOID,

  AST_TREE_TOKEN_FUNCTION_CALL,
  AST_TREE_TOKEN_VARIABLE,
  AST_TREE_TOKEN_VARIABLE_DEFINE,
  AST_TREE_TOKEN_VALUE_NULL,
  AST_TREE_TOKEN_VALUE_UNDEFINED,
  AST_TREE_TOKEN_VALUE_INT,
  AST_TREE_TOKEN_VALUE_FLOAT,
  AST_TREE_TOKEN_VALUE_BOOL,
  AST_TREE_TOKEN_VALUE_OBJECT,

  AST_TREE_TOKEN_OPERATOR_ASSIGN,
  AST_TREE_TOKEN_OPERATOR_PLUS,
  AST_TREE_TOKEN_OPERATOR_MINUS,
  AST_TREE_TOKEN_OPERATOR_SUM,
  AST_TREE_TOKEN_OPERATOR_SUB,
  AST_TREE_TOKEN_OPERATOR_MULTIPLY,
  AST_TREE_TOKEN_OPERATOR_DIVIDE,
  AST_TREE_TOKEN_OPERATOR_MODULO,
  AST_TREE_TOKEN_OPERATOR_EQUAL,
  AST_TREE_TOKEN_OPERATOR_NOT_EQUAL,
  AST_TREE_TOKEN_OPERATOR_GREATER,
  AST_TREE_TOKEN_OPERATOR_SMALLER,
  AST_TREE_TOKEN_OPERATOR_GREATER_OR_EQUAL,
  AST_TREE_TOKEN_OPERATOR_SMALLER_OR_EQUAL,
  AST_TREE_TOKEN_OPERATOR_POINTER,
  AST_TREE_TOKEN_OPERATOR_ADDRESS,
  AST_TREE_TOKEN_OPERATOR_DEREFERENCE,
  AST_TREE_TOKEN_OPERATOR_ACCESS,
  AST_TREE_TOKEN_OPERATOR_LOGICAL_NOT,
  AST_TREE_TOKEN_OPERATOR_LOGICAL_AND,
  AST_TREE_TOKEN_OPERATOR_LOGICAL_OR,
  AST_TREE_TOKEN_OPERATOR_ARRAY_ACCESS,

  AST_TREE_TOKEN_SCOPE,

  AST_TREE_TOKEN_NONE,
} AstTreeToken;

extern const char *AST_TREE_TOKEN_STRINGS[];

typedef struct AstTree {
  AstTreeToken token;
  void *metadata;
  struct AstTree *type;
  char *str_begin;
  char *str_end;
} AstTree;

extern AstTree AST_TREE_TYPE_TYPE;
extern AstTree AST_TREE_VOID_TYPE;
extern AstTree AST_TREE_BOOL_TYPE;
extern AstTree AST_TREE_I8_TYPE;
extern AstTree AST_TREE_U8_TYPE;
extern AstTree AST_TREE_I16_TYPE;
extern AstTree AST_TREE_U16_TYPE;
extern AstTree AST_TREE_I32_TYPE;
extern AstTree AST_TREE_U32_TYPE;
extern AstTree AST_TREE_I64_TYPE;
extern AstTree AST_TREE_U64_TYPE;
#ifdef FLOAT_16_SUPPORT
extern AstTree AST_TREE_F16_TYPE;
#endif
extern AstTree AST_TREE_F32_TYPE;
extern AstTree AST_TREE_F64_TYPE;
extern AstTree AST_TREE_F128_TYPE;
extern AstTree AST_TREE_CODE_TYPE;
extern AstTree AST_TREE_VOID_VALUE;

typedef struct AstTreeVariable {
  char *name_begin;
  char *name_end;
  AstTree *type;
  AstTree *value;
  AstTree *initValue;
  bool isConst;
} AstTreeVariable;

typedef struct AstTreeVariables {
  AstTreeVariable **data;
  size_t size;
} AstTreeVariables;

typedef struct AstTrees {
  AstTree **data;
  size_t size;
} AstTrees;

typedef struct AstTreeRoot {
  char *filePath;
  AstTreeVariables variables;
  AstTrees trees;
  struct AstTreeRoot **imports;
  size_t imports_size;
} AstTreeRoot;

typedef struct AstTreeRoots {
  AstTreeRoot **data;
  size_t size;
} AstTreeRoots;

extern AstTreeRoots AST_TREE_ROOTS_ERROR;

typedef struct AstTreeScope {
  AstTreeVariables variables;
  AstTree **expressions;
  size_t expressions_size;
} AstTreeScope;

typedef struct AstTreeFunction {
  AstTreeVariables arguments;
  AstTreeScope scope;
  AstTree *returnType;
} AstTreeFunction;

typedef struct AstTreeTypeFunctionArgument {
  char *str_begin;
  char *str_end;
  char *name_begin;
  char *name_end;
  AstTree *type;
} AstTreeTypeFunctionArgument;

typedef struct AstTreeTypeFunction {
  AstTreeTypeFunctionArgument *arguments;
  size_t arguments_size;
  AstTree *returnType;
} AstTreeTypeFunction;

typedef struct AstTreeFunctionCallParam {
  char *nameBegin;
  char *nameEnd;
  AstTree *value;
} AstTreeFunctionCallParam;

typedef struct AstTreeFunctionCall {
  AstTree *function;
  AstTreeFunctionCallParam *parameters;
  size_t parameters_size;
} AstTreeFunctionCall;

typedef u64 AstTreeInt;

typedef f128 AstTreeFloat;

typedef bool AstTreeBool;

typedef struct AstTreeObject {
  AstTreeVariables variables;
} AstTreeObject;

typedef AstTree AstTreeSingleChild;

typedef struct AstTreeInfix {
  AstTree *left;
  AstTree *right;
} AstTreeInfix;

typedef struct AstTreeReturn {
  AstTree *value;
} AstTreeReturn;

typedef struct AstTreeIf {
  AstTree *condition;
  AstTree *ifBody;
  AstTree *elseBody;
} AstTreeIf;

typedef struct AstTreeWhile {
  AstTree *condition;
  AstTree *body;
} AstTreeWhile;

typedef struct AstTreeHelper {
  AstTreeVariables **variables;
  size_t variables_size;
} AstTreeHelper;

typedef struct AstTreeSetTypesHelper {
  AstTree *lookingType;
  AstTreeVariables dependencies;
  AstTreeVariables variables;
} AstTreeSetTypesHelper;

typedef struct AstTreeStruct {
  size_t id;
  AstTreeVariables variables;
} AstTreeStruct;

typedef struct AstTreeName {
  char *begin;
  char *end;
} AstTreeName;

typedef struct AstTreeAccess {
  AstTree *object;
  struct {
    AstTreeName name;
    size_t index;
  } member;
} AstTreeAccess;

typedef struct AstTreeBracket {
  AstTree *operand;
  AstTrees parameters;
} AstTreeBracket;

typedef enum AstTreeBuiltinToken {
  AST_TREE_BUILTIN_TOKEN_CAST,
  AST_TREE_BUILTIN_TOKEN_TYPE_OF,
  AST_TREE_BUILTIN_TOKEN_IMPORT,
  AST_TREE_BUILTIN_TOKEN__SIZE__,
} AstTreeBuiltinToken;

extern const char *AST_TREE_BUILTIN_TOKEN_STRINGS[];

typedef struct AstTreeBuiltin {
  AstTreeBuiltinToken token;
} AstTreeBuiltin;

#ifdef PRINT_COMPILE_TREE
void astTreePrint(const AstTree *tree, int indent);
void astTreeVariablePrint(const AstTreeVariable *variable, int indent);
void astTreeRootPrint(const AstTreeRoot *root);
#endif

void astTreeDestroy(AstTree tree);
void astTreeVariableDestroy(AstTreeVariable variable);
void astTreeVariableDelete(AstTreeVariable *variable);
void astTreeDelete(AstTree *tree);
bool astTreeShouldDelete(AstTree *tree);
void astTreeRootDelete(AstTreeRoot *root);
void astTreeRootsDestroy(AstTreeRoots roots);

AstTree *newAstTree(AstTreeToken token, void *metadata, AstTree *type,
                    char *str_begin, char *str_end);
AstTree *copyAstTree(AstTree *tree);
AstTree *copyAstTreeBack(AstTree *tree, AstTreeVariables oldVariables[],
                         AstTreeVariables newVariables[],
                         size_t variables_size);
AstTreeVariables copyAstTreeVariables(AstTreeVariables variables,
                                      AstTreeVariables oldVariables[],
                                      AstTreeVariables newVariables[],
                                      size_t variables_size);

AstTreeRoots makeAstTree(const char *filePath);
AstTreeRoot *getAstTreeRoot(char *filePath, AstTreeRoots *roots);
AstTreeRoot *makeAstRoot(ParserNode *parsedRoot, char *filePath);

bool pushVariable(AstTreeHelper *helper, AstTreeVariables *variables,
                  AstTreeVariable *variable);

AstTree *astTreeParse(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseFunction(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseTypeFunction(ParserNode *parserNode,
                                  AstTreeHelper *helper);
AstTree *astTreeParseFunctionCall(ParserNode *parserNode,
                                  AstTreeHelper *helper);
AstTree *astTreeParseIdentifier(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseValue(ParserNode *parserNode, AstTreeToken token,
                           size_t metadata_size, AstTree *type);
AstTree *astTreeParseString(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseKeyword(ParserNode *parserNode, AstTreeToken token);
AstTree *astTreeParsePrintU64(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseReturn(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseBinaryOperator(ParserNode *parserNode,
                                    AstTreeHelper *helper, AstTreeToken token);
AstTree *astTreeParseUnaryOperator(ParserNode *parserNode,
                                   AstTreeHelper *helper, AstTreeToken token);
AstTree *astTreeParseOperateAssignOperator(ParserNode *parserNode,
                                           AstTreeHelper *helper,
                                           AstTreeToken token);
bool astTreeParseConstant(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseVariable(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseIf(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseWhile(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseComptime(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseCurlyBracket(ParserNode *parserNode,
                                  AstTreeHelper *helper);
AstTree *astTreeParseParenthesis(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseStruct(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseAccessOperator(ParserNode *parserNode,
                                    AstTreeHelper *helper, AstTreeToken token);
AstTree *astTreeParseBuiltin(ParserNode *parserNode, AstTreeHelper *helper);
AstTree *astTreeParseBracket(ParserNode *parserNode, AstTreeHelper *helper,
                             AstTreeToken token);

bool isFunction(AstTree *value);
bool isConst(AstTree *tree);
bool isConstByValue(AstTree *tree);
AstTree *makeTypeOf(AstTree *value);
bool typeIsEqual(AstTree *type0, AstTree *type1);
bool typeIsEqualBack(const AstTree *type0, const AstTree *type1);
AstTree *getValue(AstTree *tree);
bool isIntType(AstTree *type);
bool isEqual(AstTree *left, AstTree *right);
bool isEqualVariable(AstTreeVariable *left, AstTreeVariable *right);

void allOfVariablesWithImport(AstTreeVariables *variables, AstTreeRoot *root,
                              AstTreeRoots *checkedRoots);
bool setAllTypesRoot(AstTreeRoot *root);
bool setAllTypes(AstTree *tree, AstTreeSetTypesHelper helper,
                 AstTreeFunction *function, AstTreeFunctionCall *functionCall);
bool setTypesValueBool(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesValueInt(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesValueFloat(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesValueNull(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesValueUndefined(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesValueObject(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesFunction(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesPrintU64(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesReturn(AstTree *tree, AstTreeSetTypesHelper helper,
                    AstTreeFunction *function);
bool setTypesTypeFunction(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesFunctionCall(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesVariable(AstTree *tree, AstTreeSetTypesHelper helper,
                      AstTreeFunctionCall *functionCall);
bool setTypesOperatorAssign(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesOperatorInfix(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesOperatorInfixWithRet(AstTree *tree, AstTree *retType,
                                  AstTreeSetTypesHelper helper);
bool setTypesOperatorInfixWithRetAndLooking(AstTree *tree, AstTree *lookingType,
                                            AstTree *retType,
                                            AstTreeSetTypesHelper helper);
bool setTypesOperatorUnary(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesOperatorUnaryWithRetAndLooking(AstTree *tree, AstTree *lookingType,
                                            AstTree *retType,
                                            AstTreeSetTypesHelper helper);
bool setTypesOperatorPointer(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesOperatorAddress(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesOperatorDereference(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesVariableDefine(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesIf(AstTree *tree, AstTreeSetTypesHelper helper,
                AstTreeFunction *function);
bool setTypesWhile(AstTree *tree, AstTreeSetTypesHelper helper,
                   AstTreeFunction *function);
bool setTypesScope(AstTree *tree, AstTreeSetTypesHelper helper,
                   AstTreeFunction *function);
bool setTypesComptime(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesStruct(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesOperatorAccess(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesBuiltin(AstTree *tree, AstTreeSetTypesHelper helper,
                     AstTreeFunctionCall *functionCall);
bool setTypesTypeArray(AstTree *tree, AstTreeSetTypesHelper helper);
bool setTypesArrayAccess(AstTree *tree, AstTreeSetTypesHelper helper);

bool setTypesAstVariable(AstTreeVariable *variable,
                         AstTreeSetTypesHelper helper);
bool setTypesAstInfix(AstTreeInfix *infix, AstTreeSetTypesHelper helper);

char *u8ArrayToCString(AstTree *tree);

AstTree *makeStringType();
