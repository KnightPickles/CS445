// semantics.cpp
// Zachary Yama
// Contains functions for semantic analyais of a c- syntax tree. 

#include "semantics.h"

bool enterScope = true;
bool foundReturn = false;
bool foundMain = false;
TreeNode* currentFunction = NULL;
DeclType functionReturnType;
SymbolTable symbolTable;



// Attach the IO Library to the front of our ready-made syntax tree.
// This is a conceptual representation of a linker, without any of the 
// actual useful features. 
void IOLibrary(TreeNode *&t) {
    // Let's be lazy and build a bunch of arrays that represet the name, return type,
    // and params of the IO prototypes. 
    std::string IOID[] = {"output", "outputb", "outputc", "input", "inputb", "inputc", "outnl"};
    DeclType IORET[] = {Void, Void, Void, Int, Bool, Char, Void};
    DeclType IOPARAM[] = {Int, Bool, Char, Void, Void, Void, Void};
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
    nodes[6]->sibling = t; // Attach the IO prototyes by setting the last node's sibling to our old tree's head.
    
    // Use pass-by-reference to redirect the original syntax tree head pointer to the new head of our "linked" tree. 
    t = nodes[0];
}

void semantics(TreeNode* t, int& numerrors, int& numwarnings) {
    scopeAndType(t, numerrors, numwarnings);
    // Was main declared?
    TreeNode* main = (TreeNode*)symbolTable.lookup("main");
    if(main == NULL) {
        numerrors++;
        printError(36, 0, 0, NULL, NULL, NULL, 0);
    }
}

// Semantic analysis of a syntax tree. 
void scopeAndType(TreeNode* t, int& numerrors, int& numwarnings) {
    // Break up each node kind for simplicity sake. 
    // Process any children and handle any errors. 
    switch(t->nodekind) {
        case DeclK: processDecl(t, numerrors, numwarnings); break;
        case StmtK: processStmt(t, numerrors, numwarnings); break;
        case ExprK: processExpr(t, numerrors, numwarnings); break;
    }
    // Process the next sibling
    if(t->sibling != NULL) scopeAndType(t->sibling, numerrors, numwarnings);
}

void processDecl(TreeNode* t, int& numerrors, int& numwarnings) {
    //Find re-declarations. Varkind is special as per its initialization. 
    if(t->kind.decl != VarK && !symbolTable.insert(t->attr.name,t)) {
        TreeNode* exists = (TreeNode*)symbolTable.lookup(t->attr.name);
        numerrors++;
        printError(0, t->lineno, exists->lineno, t->attr.name, NULL, NULL, 0);
    } 

    TreeNode* lookup = NULL;

    //If we are declaring a function:
    switch(t->kind.decl) {
        case ParamK:
            // Nothing special; process children and siblings. 
            for(int i = 0; i < 3; i++) {
                if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
            }
            break;
        case VarK:

            // Check for undefined errors if a var kind is being initialized by "int x:y;"
            // and especially "int x:x;". x should not be mistakenly added to the symbol
            // table, and the initializer x sucessfully applied. 
            if(t->child[0] != NULL) {
                // Do NOT insert our current 'x' yet as per "type x:(some-expr)" to prevent any
                // occurance of 'x' in "(some-expr)" mistakenly being used to initialze "type x.." 
                scopeAndType(t->child[0], numerrors, numwarnings);
                // Wrong expression initialization error
                if(t->child[0]->nodekind == ExprK && (t->child[0]->kind.expr == IdK || t->child[0]->kind.expr == CallK)) {
                    lookup = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name);
                } else lookup = t->child[0];
                
                if(t->isArray) {
                    if(t->declType != lookup->declType && (t->declType != Char && lookup->declType != CStr)) {
                        numerrors++;
                        printError(35, t->lineno, 0, t->attr.name, getTypeStr(t->declType), getTypeStr(lookup->declType), 0);
                    }
                    else if(t->declType != Char && lookup->declType == CStr) {
                        numerrors++;
                        printError(31, t->lineno, 0, t->attr.name, getTypeStr(t->declType), NULL, 0);
                    }
                    else if(t->declType == Char && lookup->declType != CStr) {
                        numerrors++;
                        printError(32, t->lineno, 0, t->attr.name, getTypeStr(lookup->declType), NULL, 0);
                    }
                } else {
                    if(t->declType != lookup->declType) {
                        numerrors++;
                        printError(35, t->lineno, 0, t->attr.name, getTypeStr(t->declType), getTypeStr(lookup->declType), 0);
                    }
                    else if(lookup->isArray) {
                        numerrors++;
                        printError(33, t->lineno, 0, t->attr.name, getTypeStr(t->declType), NULL, 0);
                    }
                    else if((lookup->nodekind == ExprK && lookup->kind.expr != ConstK) || lookup->nodekind != ExprK) {
                        numerrors++;
                        printError(34, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                    }
                }
            }

                          //  numerrors++;
                          //  printError(35, t->lineno, 0, t->attr.name, getTypeStr(t->declType), getTypeStr(t->child[0]->declType), 0);
            // The child has been processed for redeclarations correctly. We can add the
            // original declaration now. 
            if(!symbolTable.insert(t->attr.name,t)) {
                TreeNode* exists = (TreeNode*)symbolTable.lookup(t->attr.name);
                numerrors++;
                printError(0, t->lineno, exists->lineno, t->attr.name, NULL, NULL, 0);
            } 
            break;
        case FuncK:    
            currentFunction = t; 

            // Establish a scope that applies to both the function params and the contents
            // of the compound. 
            symbolTable.enter(t->attr.name);
            // Avoid a second enter() call while recognizing the upcoming compound open-brace.
            enterScope = false; 
            functionReturnType = t->declType;
        
            // Process the function's param and statement nodes. 
            for(int i = 0; i < 3; i++) {
                if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
            }
        
            if(foundReturn) {
                foundReturn = false;
            } else {
                if(t->declType != Void && t->lineno >= 0) {
                    numwarnings++;
                    printError(15, t->lineno, 0, getTypeStr(t->declType), t->attr.name, NULL, 0);
                }
            }
            symbolTable.leave();
            currentFunction = NULL;
            break;    
    }
}

void processStmt(TreeNode* t, int& numerrors, int& numwarnings) {
    TreeNode* ANode = NULL;
    TreeNode* BNode = NULL;
    TreeNode* CNode = NULL;
    bool throwError = false;

    if(t->child[0] != NULL) {
        if(t->child[0]->nodekind == ExprK && (t->child[0]->kind.expr == IdK || t->child[0]->kind.expr == CallK)) {
            ANode = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name); 
        } else ANode = t->child[0];
    }  
    if(t->child[1] != NULL) {
        if(t->child[1]->nodekind == ExprK && (t->child[1]->kind.expr == IdK || t->child[1]->kind.expr == CallK)) {
            BNode = (TreeNode*)symbolTable.lookup(t->child[1]->attr.name); 
        } else BNode = t->child[1];
    }
    
    if(ANode!=NULL) {
   //     printf("%i, NodeT %s\n", t->lineno, getTypeStr(t->child[0]->declType));
    }
    switch(t->kind.stmt) {
    case IfK:
        for(int i = 0; i < 3; i++) {
            if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
        }
        if(ANode != NULL) {
            if(ANode->declType != Bool) {
                numerrors++;
                printError(10, t->lineno, 0, t->attr.name, getTypeStr(ANode->declType), NULL, 0);
            }
        }
        break;
    case WhileK:
        for(int i = 0; i < 3; i++) {
            if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
        }
        if(ANode != NULL) {
            if(ANode->declType != Bool) {
                numerrors++;
                printError(10, t->lineno, 0, t->attr.name, getTypeStr(ANode->declType), NULL, 0);
            }
        }
        break;
    case ForK:
        
        for(int i = 0; i < 3; i++) {
            if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
        }
        if(ANode != NULL && BNode != NULL) {
            
            if(ANode->isArray && t->child[0]->child[0] == NULL) {
                numerrors++;
                printError(30, t->lineno, 0, NULL, NULL, NULL, 0);
            }
            // Error 29 If RHS is not Array, must be int
            if(BNode->child[0] != NULL) {
                if(BNode->child[0]->nodekind == ExprK && (BNode->child[0]->kind.expr == IdK || BNode->child[0]->kind.expr == CallK)) {
                    CNode = (TreeNode*)symbolTable.lookup(BNode->child[0]->attr.name); 
                } else CNode = BNode->child[0];
            }  
            bool starArray = false;
            if(BNode->nodekind == ExprK && BNode->kind.expr == OpK) {
                if(strcmp(BNode->attr.name, "*") == 0) {
                    if(CNode != NULL) {
                        if(CNode->isArray || (!CNode->isArray && CNode->declType == CStr)) { 
                            starArray = true;
                        }
                    }
                }
            }
            if(!BNode->isArray && !starArray) {
                // If * and has child array
                if(BNode->declType != Int && BNode->declType != CStr) {
                    numerrors++;
                    printError(29, t->lineno, 0, getTypeStr(BNode->declType), NULL, NULL, 0);
                    throwError = true;
                }
            } 

            // Requires both sides of IN be the same
            if(ANode->declType != BNode->declType && !throwError && !starArray) {
                if(!(ANode->declType == Char && BNode->declType == CStr)) {
                    numerrors++;
                    printError(27, t->lineno, 0, getTypeStr(ANode->declType), getTypeStr(BNode->declType), NULL, 0);
                }
            }
        }

        break;
    case ReturnK: 
        if(t->child[0] != NULL) scopeAndType(t->child[0], numerrors, numwarnings);
        foundReturn = true;
        
        if(ANode != NULL) {
            if(ANode->isArray) {
                numerrors++;
                printError(11, t->lineno, 0, NULL, NULL, NULL, 0);
            }
        } else {
            if(currentFunction != NULL) {
                if(currentFunction->declType != Void && t->child[0] == NULL) {
                    numerrors++;
                    printError(14, t->lineno, currentFunction->lineno, currentFunction->attr.name, getTypeStr(currentFunction->declType), NULL, 0);
                }
            }
        }
        break;
    case BreakK:
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

        for(int i = 0; i < 3; i++) {
            if(t->child[i] != NULL) scopeAndType(t->child[i], numerrors, numwarnings);
        }

        // Check if we were a lone compound, and leave the scope if we were. 
        if(retainScope) symbolTable.leave();
        break;
    }
}

void processExpr(TreeNode* t, int& numerrors, int& numwarnings) {
    bool isUnary, isLHSArray, isRHSArray, throwError;
    isLHSArray = isRHSArray = throwError = false;
    isUnary = true;
    bool onlyArrays = false;
    bool nonBoolean = false;
    bool isLHSIndexed, isRHSIndexed;
    isLHSIndexed = isRHSIndexed = false;

    DeclType LHS, RHS, retType, expectedLHS, expectedRHS, expectedRetType, charArray;
    LHS = RHS = retType = expectedLHS = expectedRHS = expectedRetType = charArray = Exclusive;
    
    TreeNode* found = NULL;
    TreeNode* lhNode = NULL;
    TreeNode* rhNode = NULL;
    // NOTE: The DeclType enum's Error attribute is used to prevent cascading errors.
    // The Exclusive attribute is used to trigger error checking for cases that require
    // both the LHS and RHS to be of one type.

    switch(t->kind.expr) {
        case AssignK:
        case OpK: 
            //printf("%i, opk\n", t->lineno);
            // Check if Unary or Binary operator, process children, and collect their data.
            if(t->child[0] != NULL) {
                scopeAndType(t->child[0], numerrors, numwarnings);
                if(t->child[0]->nodekind == ExprK && (t->child[0]->kind.expr == IdK || t->child[0]->kind.expr == CallK)) {
                    lhNode = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name);
                }
                if(lhNode != NULL) { 
                    LHS = lhNode->declType;
                    isLHSArray = lhNode->isArray; 
                    if(isLHSArray && t->child[0]->child[0] != NULL) {
                        isLHSIndexed = true;
                    } 
                } else {
                    LHS = t->child[0]->declType;
                }
            }
            if(t->child[1] != NULL) { // If != NULL, it's a binary expression
                scopeAndType(t->child[1], numerrors, numwarnings);
                if(t->child[1]->nodekind == ExprK && (t->child[1]->kind.expr == IdK || t->child[1]->kind.expr == CallK)) {
                    rhNode = (TreeNode*)symbolTable.lookup(t->child[1]->attr.name);
                }
                if(rhNode != NULL) { 
                    RHS = rhNode->declType;
                    isRHSArray = rhNode->isArray;
                    if(isRHSArray && t->child[1]->child[0] != NULL) {
                        isRHSIndexed = true;
                    }
                } else {
                    // RHS was a constant something or other
                    RHS = t->child[1]->declType;
                }
                isUnary = false; 
            }
            
            // Grab LHS and RHS information & check for unary statement. 
            exprTypes(t->attr.name, isUnary, onlyArrays, nonBoolean, expectedLHS, expectedRHS, expectedRetType);
            
            // Throw any unary based errors
            if(isUnary && LHS != Error) {
                // Types are not the same
               
                /*if(!onlyArrays && !isLHSArray && LHS != expectedLHS && expectedLHS != Exclusive) {
                    numerrors++;
                    throwError = true;
                    printError(8, t->lineno, 0, t->attr.name, getTypeStr(expectedLHS), getTypeStr(LHS), 0);
                }*/

                if(LHS != expectedLHS) {
                    numerrors++;
                    throwError = true;
                    printError(8, t->lineno, 0, t->attr.name, getTypeStr(expectedLHS), getTypeStr(LHS), 0);
                    
                }

                // Only works with arrays/not with arrays
                if((isLHSArray || LHS == CStr) && !onlyArrays && !isLHSIndexed) {
                    numerrors++;
                    throwError = true;
                    printError(6, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                } else if(!isLHSArray && onlyArrays && t->child[0]->declType != CStr) {
                    numerrors++;
                    throwError = true;
                    printError(7, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                } else if((isLHSArray || LHS == CStr) && onlyArrays && isLHSIndexed) {
                    numerrors++;
                    throwError = true;
                    printError(7, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                } 
            }

            // Throw and binary based errors
            if(!isUnary && LHS != Error && RHS != Error) {
                // Check equal operators requiring equal sides
                // Check arrays
                
                if((isLHSArray || isRHSArray) && expectedLHS != Exclusive && expectedRHS != Exclusive)  {
                    numerrors++;
                    throwError = true;
                    printError(6, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0);
                
                // Check exclusive-based operators
                } else if(expectedLHS == Exclusive && expectedRHS == Exclusive) {
                    // Make sure we are allowed to set a char array to a string const
                    // and that otherwise the LHS == RHS
                    if(RHS != LHS) {
                        if(!(LHS == Char && RHS == CStr) && isLHSArray && !isLHSIndexed) {
                            numerrors++;
                            throwError = true;
                            printError(2, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0);
                        } else if(!(LHS == CStr && RHS == Char) && isRHSArray && !isRHSIndexed) {
                            numerrors++;
                            throwError = true;
                            printError(2, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0);
                        } else if(!isLHSArray && !isRHSArray) {
                            numerrors++;
                            throwError = true;
                            printError(2, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0);
                        }
                    }

                    // Cases where both sides must be arrays; accounts for string constant array
                    if((isLHSArray || LHS == CStr) && (!isRHSArray && RHS != CStr)) {
                        if(!isLHSIndexed) {
                            if(!(LHS == Char && RHS == CStr)) {
                                numerrors++;
                                throwError = true;
                                printError(5, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                            }
                        } else {
                            if(LHS != RHS) {
                                numerrors++;
                                throwError = true;
                                printError(2, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0);
                            }
                        }
                    } else if((!isLHSArray && LHS != CStr) && (isRHSArray || RHS == CStr)) {
                        if(!isRHSIndexed) {
                            if(!(LHS == CStr && RHS == Char)) {
                                numerrors++;
                                throwError = true;
                                printError(5, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                            }
                        } else {
                            if(RHS != LHS) {
                                numerrors++;
                                throwError = true;
                                printError(2, t->lineno, 0, t->attr.name, getTypeStr(LHS), getTypeStr(RHS), 0);
                            }
                        }
                    }

                
                // Check for non-exclusive binary operators
                } else {
                    // Requires of the same type
                    if(expectedLHS == expectedRHS) {
                        if(!nonBoolean) {
                            if(LHS != expectedLHS) {
                                numerrors++;
//                                throwError = true;
                                printError(3, t->lineno, 0, t->attr.name, getTypeStr(expectedLHS), getTypeStr(LHS), 0);
                            }

                            if(RHS != expectedRHS) {
                                numerrors++;
//                                throwError = true;
                                printError(4, t->lineno, 0, t->attr.name, getTypeStr(expectedLHS), getTypeStr(RHS), 0);
                            }
                        } else if(nonBoolean) {
                            if(LHS == Bool) {
                                numerrors++;
//                                throwError = true;
                                printError(38, t->lineno, 0, t->attr.name, getTypeStr(LHS), NULL, 0);
                            } 
                            if(RHS == Bool) {
                                numerrors++;
//                                throwError = true;
                                printError(37, t->lineno, 0, t->attr.name, getTypeStr(RHS), NULL, 0);
                            }
                        }
                    }
                }
            }
            
            // Finish up preventing cascading errors.
            if(throwError) {
                t->declType = Error;
            } else if(LHS == Error || RHS == Error) {
                t->declType = Error;
            } else {
                if(expectedRetType == Exclusive) {
                    t->declType = LHS;
                } else {
                    t->declType = expectedRetType;
                }
            }
            break;
        case ConstK: 
                 
            break;
        case IdK: 
            // Check for symbol
            found = (TreeNode*)symbolTable.lookup(t->attr.name);
            // If not found, undefined error
            if(found == NULL) {
                numerrors++;
                printError(1, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                t->declType = Error; // Avoid cascading errors
            // If found, grab type
            } else if(found != NULL) {
                t->declType = found->declType;
                // Check if being indexed incorrectly
            /*    if(!(t->isArray) && t->child[0] != NULL) {
                    numerrors++;
                    throwError = true;
                    printError(21, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                }*/
            }     

            // If child exists, it's an index
            if(t->child[0] != NULL) {
                scopeAndType(t->child[0], numerrors, numwarnings);
                // If not an array, throw error
                if(found != NULL) {
                    if(!found->isArray) {
                        numerrors++;
                        printError(21, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                    // The index's type must be an integer and not be part of an error
                    } else if(t->child[0]->declType != Error && t->child[0]->declType != Int) {
                        numerrors++;
                        printError(20, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                    }
                }
            }

            break;
        case CallK: 
            found = (TreeNode*)symbolTable.lookup(t->attr.name);
            // If not found, undeclared error
            if(found == NULL) {
                numerrors++;
                printError(1, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                t->declType = Error; // Avoid cascading errors
            // If found, process function call
            } else {
                t->declType = found->declType; // Get our funciton return type
                TreeNode* callParams = t->child[0]; // Track function params
                TreeNode* declParams = found->child[0];
                // Check if the declared paramaters match what was called
                for(int index = 1; callParams != NULL && declParams != NULL; index++) {
                    scopeAndType(callParams, numerrors, numwarnings); // Process call params
                    TreeNode* callParamID = NULL;
                    if(callParams->nodekind == ExprK && (callParams->kind.expr == IdK || callParams->kind.expr == CallK)) {
                        callParamID = (TreeNode*)symbolTable.lookup(callParams->attr.name);
                    } else callParamID = callParams;

                    // Check for correct types
                    if(declParams->declType != Error && callParamID->declType != Error && declParams->declType != callParamID->declType) {
                        numerrors++;
                        printError(22, t->lineno, declParams->lineno, getTypeStr(declParams->declType), found->attr.name, getTypeStr(callParamID->declType), index); 
                    }
                    
                    // Were we expecting an array?
                    if(declParams->isArray && !callParamID->isArray) {
                        numerrors++;
                        printError(23, t->lineno, declParams->lineno, found->attr.name, NULL, NULL, index);
                    }

                    // Check if we're too few or too many params
                    callParams = callParams->sibling;
                    declParams = declParams->sibling;
                    if(callParams == NULL && declParams != NULL) {
                        // Too few params 25
                        numerrors++;
                        printError(25, t->lineno, found->lineno, found->attr.name, NULL, NULL, 0);
                    } else if(callParams != NULL && declParams == NULL) {
                        // Too many params 26
                        numerrors++;
                        printError(26, t->lineno, found->lineno, found->attr.name, NULL, NULL, 0);
                    }
                }
            }
            break;
    }
}

// Translates the DeclType enum into its string counterparts. 
char *getTypeStr(DeclType type) {
    switch(type) {
    case Int: return strdup("int");
    case Char: return strdup("char");
    case CStr: return strdup("char");
    case Bool: return strdup("bool");
    case Void: return strdup("void");
    case Error: return strdup("[TYPE ERROR]");
    case Exclusive: return strdup("[TYPE EXCLUSIVE]");
    }
}

// Based on a given operator name, set appropriate LHS, RHS and return types. 
void exprTypes(const char* s, bool isUn, bool &onlyAr, bool &nonBoolean, DeclType &lhs, DeclType &rhs, DeclType &returnType) { 
    std::string op(s); //Didn't want to write strcmp(..) 15 times.

    if(!isUn) {
        // Add += -= *= /=
        if(op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "+=" || op == "-=" || op == "/=" || op == "*=") {
            lhs = Int;
            rhs = Int;
            returnType = Int;
            // Single sided errors
        } else if(op == ">" || op == "<" || op == ">=" || op == "<=") {
            lhs = Int;
            rhs = Int;
            returnType = Bool;
            nonBoolean = true;
            //double sided errors
        } else if(op == "==" || op == "!=") { 
            lhs = Exclusive;
            rhs = Exclusive;
            returnType = Bool;
            // double sided errors
        } else if(op == "=") {
            lhs = Exclusive;
            rhs = Exclusive;
            returnType = Exclusive;
            // double sided errors
        } else if(op == "&" || op == "|") {
            lhs = Bool;
            rhs = Bool;
            returnType = Bool;
            // single sided errors
        } else {
            lhs = Error;
            rhs = Error;
            returnType = Error;
        }
    } else {
        // Add ++, --
        if(op == "?") {
            lhs = Int;
            rhs = Int;
            returnType = Int;
            onlyAr = false;
            // single sided errors?
        } else if(op == "!") {
            lhs = Bool;
            rhs = Bool;
            returnType = Bool;
            onlyAr = false;
        } else if(op == "*") { 
            lhs = Exclusive;
            rhs = Exclusive;
            returnType = Int; 
            onlyAr = true;
        } else if(op == "++" || op == "--" || op == "-") {
            lhs = Int;
            rhs = Int;
            returnType = Int;
        } else {
            lhs = Error;
            rhs = Error;
            returnType = Error;
        }
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
    switch(code) {
        // DECLARATIONS
        case 0: printf("ERROR(%d): Symbol '%s' is already defined at line %d.\n", lineno, s1, explineno); break;
        case 1: printf("ERROR(%d): Symbol '%s' is not defined.\n", lineno, s1); break;

        // EXPRESSIONS
        case 2: printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is %s.\n", lineno, s1, s2, s3); break;
        case 3: printf("ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", lineno, s1, s2, s3); break;
        case 4: printf("ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", lineno, s1, s2, s3); break;
        case 5: printf("ERROR(%d): '%s' requires that if one operand is an array so must the other operand.\n", lineno, s1); break;
        case 6: printf("ERROR(%d): The operation '%s' does not work with arrays.\n", lineno, s1); break;
        case 7: printf("ERROR(%d): The operation '%s' only works with arrays.\n", lineno, s1); break;
        case 8: printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", lineno, s1, s2, s3); break;

        // TEST CONDITIONS
        case 9: printf("ERROR(%d): Cannot use array as test condition in %s statement.\n", lineno, s1); break;
        case 10: printf("ERROR(%d): Expecting Boolean test condition in %s statement but got type %s.\n", lineno, s1, s2); break;

        // RETURN
        case 11: printf("ERROR(%d): Cannot return an array.\n", lineno); break;
        case 12: printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has return value.\n", lineno, s1, explineno); break;
        case 13: printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but got %s.\n", lineno, s1, lineno, s2, s3); break;
        case 14: printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but return has no return value.\n", lineno, s1, explineno, s2); break;
        case 15: printf("WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", lineno, s1, s2); break;

        // BREAK
        case 16: printf("ERROR(%d): Cannot have a break statement outside of loop.\n", lineno); break;
        
        // FUNCTION INVOCATION
        case 17: printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", lineno, s1); break; 
        case 18: printf("ERROR(%d): Cannot use function '%s' as a simple variable.\n", lineno, s1); break;
        
        // ARRAY INDEXING
        case 19: printf("ERROR(%d): Array index is the unindexed array '%s'.\n", lineno, s1); break;
        case 20: printf("ERROR(%d): Array '%s' should be indexed by type int but got %s.\n", lineno, s1, s2); break;
        case 21: printf("ERROR(%d): Cannot index nonarray '%s'.\n", lineno, s1); break;

        // PARAM LIST
        case 22: printf("ERROR(%d): Expecting type %s in parameter %i of call to '%s' defined on line %d but got %s.\n", lineno, s1, (int)d1, s2, explineno, s3); break;
        case 23: printf("ERROR(%d): Expecting array in parameter %i of call to '%s' defined on line %d.\n", lineno, (int)d1, s1, explineno); break;
        case 24: printf("ERROR(%d): Not expecting array in parameter %i of call to '%s' defined on line %d.\n", lineno, (int)d1, s1, explineno); break;
        case 25: printf("ERROR(%d): Too few parameters passed for function '%s' defined on line %d.\n", lineno, s1, explineno); break;
        case 26: printf("ERROR(%d): Too many parameters passed for function '%s' defined on line %d.\n", lineno, s1, explineno); break;

        // FOREACH
        case 27: printf("ERROR(%d): Foreach requires operands of 'in' be the same type but lhs is type %s and rhs array is type %s.\n", lineno, s1, s2); break;
        case 28: printf("ERROR(%d): If not an array, foreach requires lhs of 'in' be of type int but it is type %s.\n", lineno, s1); break;
        case 29: printf("ERROR(%d): If not an array, foreach requires rhs of 'in' be of type int but it is type %s.\n", lineno, s1); break;
        case 30: printf("ERROR(%d): In foreach statement the variable to the left of 'in' must not be an array.\n", lineno); break;

        // INITIALIZERS
        case 31: printf("ERROR(%d): Array '%s' must be of type char to be initialized, but is of type %s.\n", lineno, s1, s2); break;
        case 32: printf("ERROR(%d): Initializer for array variable '%s' must be a string, but is of nonarray type %s.\n", lineno, s1, s2); break;
        case 33: printf("ERROR(%d): Initializer for nonarray variable '%s' of type %s cannot be initialized with an array.\n", lineno, s1, s2); break;
        case 34: printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", lineno, s1); break;
        case 35: printf("ERROR(%d): Variable '%s' is of type %s but is being initialized with an expression of type %s.\n", lineno, s1, s2, s3); break;

        // MISC
        case 36: printf("ERROR(LINKER): Procedure main is not defined.\n"); break;
        case 37: printf("ERROR(%d): '%s' requires operands of type char or int but rhs is of type %s.\n", lineno, s1, s2); break;
        case 38: printf("ERROR(%d): '%s' requires operands of type char or int but lhs is of type %s.\n", lineno, s1, s2); break;
    }
}
