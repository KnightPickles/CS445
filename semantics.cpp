// semantics.cpp
// Zachary Yama
// Contains functions for semantic analyais of a c- syntax tree. 

#include <iostream>
#include <vector>
#include <algorithm>
#include "semantics.h"

using namespace std;

// Make a list for sprintf to sort errors based on lineno
struct err {
    int lineno;
    char* errmsg;
};

vector<err> errorBuffer; 
char buffer[256]; // Used to store the string on each sprintf call
int numerrors = 0, numwarnings = 0;
bool enterScope = true;
bool foundReturn = false;
bool foundMain = false;
bool inLoop = false;
int loopDepth = 1;
TreeNode* currentFunction = NULL;
DeclType functionReturnType;
SymbolTable symbolTable;

bool compare(const err& f, const err& s) {
    return f.lineno < s.lineno;
}

void printErrors() {
    for(int i = 0; i < errorBuffer.size(); i++) {
        printf("%s", errorBuffer[i].errmsg);
    }
}

// Attach the IO Library to the front of our ready-made syntax tree.
// This is a conceptual representation of a linker, without any of the 
// actual useful features. 
void IOLibrary(TreeNode *&t) {
    // Let's be lazy and build a bunch of arrays that represet the name, return type,
    // and params of the IO prototypes. 
    std::string IOID[] = {"input", "output", "inputb", "outputb", "inputc", "outputc", "outnl"};
    DeclType IORET[] = {Int, Void, Bool, Void, Char, Void, Void};
    DeclType IOPARAM[] = {Void, Int, Void, Bool, Void, Char, Void};
    TreeNode* nodes[7];

    // Build 7 nodes with respect to each index of the IOID, IORET, and IOPARAM arrays
    // and insert them into our "nodes[]" array. 
    for(int i = 0; i < 7; i++) {
        // Build base node 
        TreeNode* newNode = newDeclNode(FuncK);
        newNode->lineno = -1;
        newNode->attr.name = strdup(IOID[i].c_str());
        newNode->declType = IORET[i]; // Add return type

        // Add param node to child[0] if necessary
        // Use the Void attribute of declType as if it were NULL, and set params
        // to NULL accordingly.
        if(IOPARAM[i] != Void) {
            TreeNode* paramNode = newDeclNode(ParamK);
            paramNode->lineno = -1;
            paramNode->attr.name = strdup("*dummy*");
            paramNode->declType = IOPARAM[i];
            newNode->child[0] = paramNode;
        } else {
            newNode->child[0] = NULL;
        }

        // Add child[1]
        newNode->child[1] = NULL;
        // Record the node
        nodes[i] = newNode;
    }

    // Run through the "nodes[]" array and attach each node via sibling pointers. 
    for(int i = 0; i < 7 - 1; i++) {
        nodes[i]->sibling = nodes[i + 1];
    }
    nodes[6]->sibling = t; // Attach the IO prototyes by setting the last node's sibling to our old t

    // Use pass-by-reference to redirect the original syntax tree head pointer to the new head of our
    t = nodes[0];
}

void semantics(TreeNode *t, int& errors, int& warnings) {
    scopeAndType(t, numerrors, numwarnings);
    
    // Was main declared?
    TreeNode* main = (TreeNode*)symbolTable.lookup("main");
    if(main == NULL) {
        printError(36, 0, 0, NULL, NULL, NULL, 0);
    }
    //std::sort(errorBuffer.begin(), errorBuffer.end(), compare);
    printErrors();
    errors = numerrors; 
    warnings = numwarnings;
}

// Semantic analysis of a syntax tree. 
void scopeAndType(TreeNode *t, int& numerrors, int& numwarnings) {
    // Break up each node kind for simplicity sake. 
    // Process any children and handle any errors. 
    if(t == NULL) return;
    switch(t->nodekind) {
        case DeclK: processDecl(t, numerrors, numwarnings); break;
        case StmtK: processStmt(t, numerrors, numwarnings); break;
        case ExprK: processExpr(t, numerrors, numwarnings); break;
    }
    // How the recursion happens
    if(t->sibling != NULL) scopeAndType(t->sibling, numerrors, numwarnings);
}

void processDecl(TreeNode* t, int& numerrors, int& numwarnings) {
    //Find re-declarations. Varkind is special as per its initialization. 
    TreeNode* initializer; 
    if(t->kind.decl != VarK && !symbolTable.insert(t->attr.name,t)) {
        initializer = (TreeNode*)symbolTable.lookup(t->attr.name);
        printError(0, t->lineno, initializer->lineno, t->attr.name, NULL, NULL, 0);
    }

    switch(t->kind.decl) {
        case ParamK:
            for(int i = 0; i < 3; i++) { 
                scopeAndType(t->child[i], numerrors, numwarnings); 
                // Tree print stuff?
                //initializer = (TreeNode*)symbolTable.lookup(t->attr.name);
                //t->declType = initializer->declType;
                //t->isArray = initializer->isArray;
            }
            initializer = NULL; // just being safe
            break;
        case VarK:
            for(int i = 0; i < 3; i++) { scopeAndType(t->child[i], numerrors, numwarnings); }
            // If we have an initializer
            if(t->child[0] != NULL) {
                // If we have an ID of some kind, lookup its declaration. 
                if(t->child[0]->nodekind == ExprK && (t->kind.expr == IdK && t->child[0]->kind.expr == CallK)) {
                    initializer = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name);
                } else initializer = t->child[0];
              
                // Must be initialized with "constant"
                if(initializer->nodekind == ExprK && (initializer->kind.expr == IdK || initializer->kind.expr == CallK)) {
                    printError(34, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                } else { // Was a constant but...
                    // Types do not match /35
                    // One side was an array, but wasn't supposed to be
                    if(initializer->isArray && t->isArray) {
                        if(t->declType != Char) { 
                            printError(31, t->lineno, 0, t->attr.name, getTypeStr(t->declType), NULL, 0);
                        }
                    } else if(initializer->isArray && !t->isArray) {
                        printError(33, t->lineno, 0, t->attr.name, getTypeStr(t->declType), NULL, 0);
                        // Specific case of Undefined:CharArray
                        if(initializer->declType == Char) {
                            if(initializer->declType != t->declType) printError(35, t->lineno, 0, t->attr.name, getTypeStr(t->declType), getTypeStr(initializer->declType), 0); 
                        }
                    } else if(!initializer->isArray && t->isArray) {
                        printError(32, t->lineno, 0, t->attr.name, getTypeStr(initializer->declType), NULL, 0);
                    } else {
                        if(initializer->declType != t->declType) printError(35, t->lineno, 0, t->attr.name, getTypeStr(t->declType), getTypeStr(initializer->declType), 0);
                    }
                }
            }
            
            if(!symbolTable.insert(t->attr.name,t)) {
                TreeNode* exists = (TreeNode*)symbolTable.lookup(t->attr.name);
                printError(0, t->lineno, exists->lineno, t->attr.name, NULL, NULL, 0);
            }
            break;
        case FuncK:
            currentFunction = t;
            // Establish a scope that applies to both the function params and the contents of the compound. 
            symbolTable.enter(t->attr.name);
            // Avoid a second enter() call while recognizing the upcoming compound open-brace.
            enterScope = false;
            functionReturnType = t->declType;

            // Process the function's param and statement nodes. 
            for(int i = 0; i < 3; i++) {
                if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
            }

            // Handle return errors
            if(foundReturn) {
                foundReturn = false;
            } else {
                if(t->declType != Void && t->lineno >= 0) {
                    printError(15, t->lineno, 0, getTypeStr(t->declType), t->attr.name, NULL, 0);
                }
            }
            symbolTable.leave();
            currentFunction = NULL;
            break;
    }
}

void processStmt(TreeNode* t, int& numerrors, int& numwarnings) {
    bool c0err, c1err, c2err;
    c0err = c1err = c2err = false;
    // Track whether we're in a loop so we can throw break errors
    // This is done here because we're about to scopeAndType the children, but need the marker beforehand.
    if(t->kind.stmt == WhileK || t->kind.stmt == ForK) { 
        if(!inLoop) loopDepth = symbolTable.depth();
        inLoop = true;
    }
    if(t->kind.stmt != CompK) {
        for(int i = 0; i < 3; i++) { 
            scopeAndType(t->child[i], numerrors, numwarnings);
            // Do not throw errors if an ID was not declared. 
            if(t->child[i] != NULL && t->child[i]->declType == Void) {
                // Ignore Voids that apply to function calls
                if(!(t->child[i]->nodekind == ExprK && t->child[i]->kind.expr == CallK)) {
                    if(i == 0) c0err = true;
                    if(i == 1) c1err = true;
                    if(i == 2) c2err = true;
                }
            }
        }
    }
    TreeNode* c0 = t->child[0];
    TreeNode* c1 = t->child[1];
    TreeNode* c2 = t->child[2];

    switch(t->kind.stmt) {
        case IfK:
            if(c0->declType != Bool && !c0err) printError(10, t->lineno, 0, t->attr.name, getTypeStr(c0->declType), NULL, 0);
            if(c0->isArray) printError(9, t->lineno, 0, t->attr.name, NULL, NULL, 0);
            break;
        case WhileK:
            if(c0->declType != Bool && !c0err) printError(10, t->lineno, 0, t->attr.name, getTypeStr(c0->declType), NULL, 0);
            if(c0->isArray) printError(9, t->lineno, 0, t->attr.name, NULL, NULL, 0);
            if(loopDepth == symbolTable.depth()) inLoop = false; // Tracking breaks via recursion
            break;
        case ForK:
            // Requires LH of 'in' to be nonarray type
            if(c0->isArray && !c0err) printError(30, t->lineno, 0, NULL, NULL, NULL, 0);
            // If RH of 'in' isn't an array, it must be an int
            if(!c1->isArray) {
                if(c1->declType != Int && !c1err) printError(29, t->lineno, 0, getTypeStr(c1->declType), NULL, NULL, 0);
                // Requires LH of 'in' to be int
                if(c0->declType != Int && !c0err) printError(28, t->lineno, 0, getTypeStr(c0->declType), NULL, NULL, 0);
            } else {
                // Requires same types
                if(c0->declType != c1->declType && (!c0err || !c1err)) printError(27, t->lineno, 0, getTypeStr(c0->declType), getTypeStr(c1->declType), NULL, 0); 
            }
            if(loopDepth == symbolTable.depth()) inLoop = false; // Tracking breaks via recursion
            break;
        case ReturnK:
            if(t->child[0] != NULL) {
                if(t->child[0]->isArray) printError(11, t->lineno, 0, NULL, NULL, NULL, 0);
                if(currentFunction == NULL) break; // Because segfaults
                if(currentFunction->declType != Void && t->child[0]->declType != Void && currentFunction->declType != t->child[0]->declType) printError(13, t->lineno, currentFunction->lineno, currentFunction->attr.name, getTypeStr(currentFunction->declType), getTypeStr(t->child[0]->declType), 0);
            }
            foundReturn = true; // Throws error 15 in FuncK
            // Expecing no return type but got x
            if(currentFunction->declType == Void && t->child[0] != NULL) printError(12, t->lineno, currentFunction->lineno, currentFunction->attr.name, NULL, NULL, 0);
            // Expecting return type but not returning anything
            if(currentFunction->declType != Void && t->child[0] == NULL) printError(14, t->lineno, currentFunction->lineno, currentFunction->attr.name, getTypeStr(currentFunction->declType), NULL, 0);
            break;
        case BreakK:
            if(!inLoop) { printError(16, t->lineno, 0, NULL, NULL, NULL, 0); }
            break;
        case CompK:
            // Enter a new scope. If this compound is the beginning of a funciton defenition, 
            // ignore this compound statement entirely as it's scope has already been handled. 
            bool retainScope = enterScope;
            if(retainScope) {
                symbolTable.enter("compound");
            } else {
                // If enterScope was false, hold onto it's original false setting in
                // "retainScope" to avoid calling ".leave()" twice. 
                enterScope = true;
            }
            for(int i = 0; i < 3; i++) scopeAndType(t->child[i], numerrors, numwarnings);
            // Check if we were a lone compound, and leave the scope if we were. 
            if(retainScope) symbolTable.leave();
            break;
    }
}
    
void processExpr(TreeNode* t, int& numerrors, int& numwarnings) {
    bool isLStr, isRStr, isBinary, isLHSArray, isRHSArray, isLHSIndexed, isRHSIndexed, throwError;
    isLStr = isRStr = isBinary = isLHSArray = isRHSArray = isLHSIndexed = isRHSIndexed = throwError = false;

    DeclType LHS, RHS, retType, expectedLHS, expectedRHS;
    LHS = RHS = retType = expectedLHS = expectedRHS = retType = Undefined;

    bool rerr, lerr, singleSidedErrors;
    rerr = lerr = singleSidedErrors = false;
    TreeNode* found = NULL;
    TreeNode* lhNode = NULL;
    TreeNode* rhNode = NULL;
    // NOTE: The DeclType enum's Error attribute is used to prevent cascading errors.
    // The Exclusive attribute is used to trigger error checking for cases that require
    // both the LHS and RHS to be of one type.

    switch(t->kind.expr) {
        case AssignK:
        case OpK:
            for(int i = 0; i < 3; i++) { scopeAndType(t->child[i], numerrors, numwarnings); }
            if(t->child[0] != NULL) {
                lhNode = t->child[0];
                LHS = lhNode->declType;
                isLHSArray = lhNode->isArray;
                if(lhNode->child[0] != NULL) {
                    isLHSArray = false; // Because an indexed array is no longer an array
                    isLHSIndexed = true; // Redundancy needed for indexing nonarrays
                }
                if(lhNode->nodekind == ExprK) { // Note: is always ExprK: this is just a safety check against segfaults
                    if(lhNode->kind.expr == CallK) isLHSArray = false;
                    if(lhNode->kind.expr == ConstK) isLStr = true;
                }
            }
            
            if(t->child[1] != NULL) {
                rhNode = t->child[1];
                RHS = rhNode->declType;
                isRHSArray = rhNode->isArray;
                if(rhNode->child[0] != NULL) {
                    isRHSArray = false;
                    isRHSIndexed = true;
                }
                if(rhNode->nodekind == ExprK) {
                    if(rhNode->kind.expr == CallK) isRHSArray = false;
                    if(rhNode->kind.expr == ConstK) isRStr= true;
                }
                isBinary = true;
            }
            
            // Find what kind of types we're expecting based on the op name.
            exprTypes(t->attr.name, isBinary, singleSidedErrors, expectedLHS, expectedRHS, retType);

            // If Void, there was an undeclared ID so force certain errors to work correctly
            // Note: don't mistake void for a void function call
            if(LHS == Void && !(lhNode->nodekind == ExprK && lhNode->kind.expr == CallK)) lerr = true;
            if(RHS == Void && !(rhNode->nodekind == ExprK && rhNode->kind.expr == CallK)) rerr = true;

            // Process LHS and RHS nodes for errors
            if(!isBinary && !lerr) { // Unary statement
                // Unary requires op of type x but was given y
                if(LHS != expectedLHS && expectedLHS != Undefined) printError(8, t->lineno, 0, t->attr.name, getTypeStr(expectedLHS), getTypeStr(LHS), 0);

                // Array errors: Does not work w/arr, only works w/arr 
                if(isLHSArray) {
                    if(strcmp(t->attr.name, "*") != 0) printError(6, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                } else if(strcmp(t->attr.name, "*") == 0) printError(7, t->lineno, 0, t->attr.name, NULL, NULL, 0);
            } else { // Binary statement
                // Expected undefined types to be the same 
                if(!singleSidedErrors) {
                    if(LHS != RHS && !lerr && !rerr) printError(2, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0); 
                }
                // Give specifics if the expected types are not undefined. 
                if(!(expectedLHS == Undefined || expectedRHS == Undefined)) { // Expected LHS of type x & RHS of type y to be the same 
                    // Handle our mutant type intchar for things like >= 
                    if(expectedLHS == IntChar || expectedRHS == IntChar) {
                        if(LHS == Bool && !lerr) printError(38, t->lineno, 0, t->attr.name, getTypeStr(LHS), NULL, 0);
                        if(RHS == Bool && !rerr) printError(37, t->lineno, 0, t->attr.name, getTypeStr(RHS), NULL, 0);
                    } else {
                        if(LHS != expectedLHS && !lerr) printError(3, t->lineno, 0, t->attr.name, getTypeStr(expectedLHS), getTypeStr(LHS), 0);
                        if(RHS != expectedRHS && !rerr) printError(4, t->lineno, 0, t->attr.name, getTypeStr(expectedRHS), getTypeStr(RHS), 0);
                    }
                }
                // Array errors
                if(isLHSArray || isRHSArray) { 
                    // Does not work with arrays
                    if(expectedLHS != Undefined) {
                        printError(6, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                    } else { // Works with arrays but...
                        // Requires both sides to be an array
                        if((isLHSArray && !isRHSArray) || (!isLHSArray && isRHSArray)) printError(5, t->lineno, 0, t->attr.name, NULL, NULL, 0); 
                    }
                }
            }
            
            // Prevent cascading errors
            if(retType != Undefined) {
                t->declType = retType;
            } else t->declType = LHS;
            break;
        case ConstK:
            for(int i = 0; i < 3; i++) { scopeAndType(t->child[i], numerrors, numwarnings); }
            break;
        case IdK:
            found = (TreeNode*)symbolTable.lookup(t->attr.name);
            // If not found, undeclared error
            if(found == NULL) {
                printError(1, t->lineno, 0, t->attr.name, NULL, NULL, 0);
            } else {
                // Print tree stuff
                t->declType = found->declType;
                t->isArray = found->isArray;

                // Can't use a function as a simple expression. 
                if(found->kind.decl == FuncK) { printError(18, t->lineno, 0, t->attr.name, NULL, NULL, 0); break; }

                // Array indexing errors
                if(t->child[0] != NULL) {
                    scopeAndType(t->child[0], numerrors, numwarnings);
                    if(t->child[0]->declType == Void && !(t->child[0]->nodekind == ExprK && t->child[0]->kind.expr == CallK)) break; // It was an undefined error
                    if(!t->isArray) { 
                        printError(21, t->lineno, 0, t->attr.name, NULL, NULL, 0); 
                    } else {
                        if(t->child[0]->declType != Int) printError(20, t->lineno, 0, t->attr.name, getTypeStr(t->child[0]->declType), NULL, 0);
                        if(t->child[0]->isArray && t->child[0]->child[0] == NULL) printError(19, t->lineno, 0, t->child[0]->attr.name, NULL, NULL, 0);
                    }
                }
            }
            break;
        case CallK:
            for(int i = 0; i < 3; i++) scopeAndType(t->child[i], numerrors, numwarnings);
            found = (TreeNode*)symbolTable.lookup(t->attr.name);
            // If not found, undeclared error
            if(found == NULL) {
                printError(1, t->lineno, 0, t->attr.name, NULL, NULL, 0);
            } else {
                // Print tree stuff
                t->declType = found->declType;

                // t is a simple variable and cannot be used as a call
                if(found->kind.decl != FuncK) printError(17, t->lineno, 0, t->attr.name, NULL, NULL, 0);

                TreeNode* callParams = t->child[0];
                TreeNode* declParams = found->child[0];
                bool dArray = false;
                bool cArray = false;
                int index = 1;
                // What if there are more call params than necessary?
                while(declParams != NULL && callParams != NULL) {
                    if(callParams->kind.expr == IdK && callParams->declType == Void) {
                        callParams = callParams->sibling;
                        declParams = declParams->sibling;
                        cArray = dArray = false;
                        index++;
                        continue;
                    }
                    if(declParams->isArray) {
                        dArray = true;
                        if(declParams->child[0] != NULL) dArray = false;
                    }
                    if(callParams->isArray) {
                        cArray = true;
                        if(callParams->child[0] != NULL) cArray = false;
                    }
                    if(declParams->declType != callParams->declType) printError(22, t->lineno, found->lineno, getTypeStr(declParams->declType), t->attr.name, getTypeStr(callParams->declType), index); 
                    if(dArray && !cArray) printError(23, t->lineno, found->lineno, t->attr.name, NULL, NULL, index);
                    if(!dArray && cArray) printError(24, t->lineno, found->lineno, t->attr.name, NULL, NULL, index);
                    callParams = callParams->sibling;
                    declParams = declParams->sibling;
                    index++;
                    dArray = cArray = false;
                }
                if(callParams == NULL && declParams != NULL) printError(25, t->lineno, found->lineno, t->attr.name, NULL, NULL, 0);
                if(callParams != NULL && declParams == NULL) printError(26, t->lineno, found->lineno, t->attr.name, NULL, NULL, 0);
            }

            break;
    }
}

// Based on an OpK's name, determine the set of expected variables associated with that operator
void exprTypes(const char* s, bool isBinary, bool &singleSidedErrors, DeclType &lhs, DeclType &rhs, DeclType &rt) {
    // 0-8: basic arithmatic; 9-12 inequalities; 13,14: comparisons; 15: assignment; 16,17: And/Or
    std::string binaryList[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", ">=", "<=", "==", "!=", "=", "&", "|"};
    // 0: Not; 2: Address; 3: Ternary; 3-5: Integer modifiers
    std::string unaryList[6] = {"!", "*", "?", "-", "--", "++"};
    std::string op(s);
    singleSidedErrors = false; // There are some weird errors that only do error 3 and 4, but others that do 2, 3 and 4. 

    if(!isBinary) {
        for(int i = 0; i < 6; i++) {
            if(op == unaryList[i]) {
                if(i == 0) { lhs = rhs = rt = Bool; }
                if(i == 1) { lhs = rhs = Undefined; rt = Int; } // Works with arrays
                if(i >= 2) { lhs = rhs = rt = Int; }
            }         
        }
    } else {
        for(int i = 0; i < 18; i++) {
            if(op == binaryList[i]) {
                if(i >= 0 && i <= 8) { lhs = rhs = rt = Int; singleSidedErrors = true; }
                if(i >= 9 && i <= 12)  { lhs = rhs = IntChar; rt = Bool; } // Doesnt work with arrays
                if(i >= 13 && i <= 14) { lhs = rhs = Undefined; rt = Bool; }
                if(i == 15) { lhs = rhs = rt = Undefined; }
                if(i >= 16) { lhs = rhs = rt = Bool; singleSidedErrors = true; }
            } 
        }
    }
}

// Translates the DeclType enum into its string counterparts. 
char* getTypeStr(DeclType type) {
    switch(type) {
    case Int: return strdup("int");
    case Char: return strdup("char");
    case Bool: return strdup("bool");
    case Void: return strdup("void");
    case Undefined: return strdup("undef");
    case IntChar: return strdup("intchar");
    default: return strdup("[ERROR MUTANT TYPE]");
    }
}

// Use function pointers to print the symbol table a little more easily.
// Used for debugging.
void pointerPrintNode(void* data) {
    printf("%s ", ((TreeNode*)(data))->attr.name);
}
void printTable() {
    symbolTable.print(pointerPrintNode);
}

void printError(int code, int lineno, int explineno, char* s1, char* s2, char* s3, double d1) {
    if(code == 15) {
        numwarnings++;
    } else numerrors++;
    switch(code) {
        // DECLARATIONS
        case 0: sprintf(buffer, "ERROR(%d): Symbol '%s' is already defined at line %d.\n", lineno, s1, explineno); break;
        case 1: sprintf(buffer, "ERROR(%d): Symbol '%s' is not defined.\n", lineno, s1); break;

        // EXPRESSIONS
        case 2: sprintf(buffer, "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is %s.\n", lineno, s1, s2, s3); break;
        case 3: sprintf(buffer, "ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", lineno, s1, s2, s3); break;
        case 4: sprintf(buffer, "ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", lineno, s1, s2, s3); break;
        case 5: sprintf(buffer, "ERROR(%d): '%s' requires that if one operand is an array so must the other operand.\n", lineno, s1); break;
        case 6: sprintf(buffer, "ERROR(%d): The operation '%s' does not work with arrays.\n", lineno, s1); break;
        case 7: sprintf(buffer, "ERROR(%d): The operation '%s' only works with arrays.\n", lineno, s1); break;
        case 8: sprintf(buffer, "ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", lineno, s1, s2, s3); break;

        // TEST CONDITIONS
        case 9: sprintf(buffer, "ERROR(%d): Cannot use array as test condition in %s statement.\n", lineno, s1); break;
        case 10: sprintf(buffer, "ERROR(%d): Expecting Boolean test condition in %s statement but got type %s.\n", lineno, s1, s2); break;

        // RETURN
        case 11: sprintf(buffer, "ERROR(%d): Cannot return an array.\n", lineno); break;
        case 12: sprintf(buffer, "ERROR(%d): Function '%s' at line %d is expecting no return value, but return has return value.\n", lineno, s1, explineno); break;
        case 13: sprintf(buffer, "ERROR(%d): Function '%s' at line %d is expecting to return type %s but got %s.\n", lineno, s1, explineno, s2, s3); break;
        case 14: sprintf(buffer, "ERROR(%d): Function '%s' at line %d is expecting to return type %s but return has no return value.\n", lineno, s1, explineno, s2); break;
        case 15: sprintf(buffer, "WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", lineno, s1, s2); break;

        // BREAK
        case 16: sprintf(buffer, "ERROR(%d): Cannot have a break statement outside of loop.\n", lineno); break;

        // FUNCTION INVOCATION
        case 17: sprintf(buffer, "ERROR(%d): '%s' is a simple variable and cannot be called.\n", lineno, s1); break;
        case 18: sprintf(buffer, "ERROR(%d): Cannot use function '%s' as a simple variable.\n", lineno, s1); break;

        // ARRAY INDEXING
        case 19: sprintf(buffer, "ERROR(%d): Array index is the unindexed array '%s'.\n", lineno, s1); break;
        case 20: sprintf(buffer, "ERROR(%d): Array '%s' should be indexed by type int but got %s.\n", lineno, s1, s2); break;
        case 21: sprintf(buffer, "ERROR(%d): Cannot index nonarray '%s'.\n", lineno, s1); break;

        // PARAM LIST
        case 22: sprintf(buffer, "ERROR(%d): Expecting type %s in parameter %i of call to '%s' defined on line %d but got %s.\n", lineno, s1, (int)d1, s2, explineno, s3); break;
        case 23: sprintf(buffer, "ERROR(%d): Expecting array in parameter %i of call to '%s' defined on line %d.\n", lineno, (int)d1, s1, explineno); break;
        case 24: sprintf(buffer, "ERROR(%d): Not expecting array in parameter %i of call to '%s' defined on line %d.\n", lineno, (int)d1, s1, explineno); break;
        case 25: sprintf(buffer, "ERROR(%d): Too few parameters passed for function '%s' defined on line %d.\n", lineno, s1, explineno); break;
        case 26: sprintf(buffer, "ERROR(%d): Too many parameters passed for function '%s' defined on line %d.\n", lineno, s1, explineno); break;

        // FOREACH
        case 27: sprintf(buffer, "ERROR(%d): Foreach requires operands of 'in' be the same type but lhs is type %s and rhs array is type %s.\n", lineno, s1, s2); break;
        case 28: sprintf(buffer, "ERROR(%d): If not an array, foreach requires lhs of 'in' be of type int but it is type %s.\n", lineno, s1); break;
        case 29: sprintf(buffer, "ERROR(%d): If not an array, foreach requires rhs of 'in' be of type int but it is type %s.\n", lineno, s1); break;
        case 30: sprintf(buffer, "ERROR(%d): In foreach statement the variable to the left of 'in' must not be an array.\n", lineno); break;

        // INITIALIZERS
        case 31: sprintf(buffer, "ERROR(%d): Array '%s' must be of type char to be initialized, but is of type %s.\n", lineno, s1, s2); break;
        case 32: sprintf(buffer, "ERROR(%d): Initializer for array variable '%s' must be a string, but is of nonarray type %s.\n", lineno, s1, s2); break;
        case 33: sprintf(buffer, "ERROR(%d): Initializer for nonarray variable '%s' of type %s cannot be initialized with an array.\n", lineno, s1, s2); break;
        case 34: sprintf(buffer, "ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", lineno, s1); break;
        case 35: sprintf(buffer, "ERROR(%d): Variable '%s' is of type %s but is being initialized with an expression of type %s.\n", lineno, s1, s2, s3); break;

        // MISC
        case 36: sprintf(buffer, "ERROR(LINKER): Procedure main is not defined.\n"); break;
        case 37: sprintf(buffer, "ERROR(%d): '%s' requires operands of type char or int but rhs is of type %s.\n", lineno, s1, s2); break;
        case 38: sprintf(buffer, "ERROR(%d): '%s' requires operands of type char or int but lhs is of type %s.\n", lineno, s1, s2); break;
    }
    // Add the error message to our vector of errors. 
    err e; 
    e.lineno = lineno;
    e.errmsg = strdup(buffer);
    errorBuffer.push_back(e);
    // Sort every time to preserve order of same # lineno's. They are printed backwards otherwise.
    //std::sort(errorBuffer.begin(), errorBuffer.end(), compare); 
}


