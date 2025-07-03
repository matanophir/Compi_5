#include "genvisitor.hpp"
#include <iostream>

using namespace std;

GenVisitor::GenVisitor() {
    buffer.emit(R"(declare i32 @printf(i8*, ...)
declare void @exit(i32)
@.int_specifier = constant [4 x i8] c"%d\0A\00"
@.str_specifier = constant [4 x i8] c"%s\0A\00"

define void @printi(i32) {
    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0
    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)
    ret void
}

define void @print(i8*) {
    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0
    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)
    ret void
}

)");
}

GenVisitor::~GenVisitor() {
    cout << buffer ;
}

// Expression nodes
void GenVisitor::visit(ast::Num &node) {
    // TODO: Implement code generation for numeric literals
}

void GenVisitor::visit(ast::NumB &node) {
    // TODO: Implement code generation for byte numeric literals
}

void GenVisitor::visit(ast::String &node) {
    // TODO: Implement code generation for string literals
}

void GenVisitor::visit(ast::Bool &node) {
    // TODO: Implement code generation for boolean literals
}

void GenVisitor::visit(ast::ID &node) {
    // TODO: Implement code generation for identifiers
}

void GenVisitor::visit(ast::BinOp &node) {
    // TODO: Implement code generation for binary operations
}

void GenVisitor::visit(ast::RelOp &node) {
    // TODO: Implement code generation for relational operations
}

void GenVisitor::visit(ast::Not &node) {
    // TODO: Implement code generation for logical NOT
}

void GenVisitor::visit(ast::And &node) {
    // TODO: Implement code generation for logical AND
}

void GenVisitor::visit(ast::Or &node) {
    // TODO: Implement code generation for logical OR
}

void GenVisitor::visit(ast::Cast &node) {
    // TODO: Implement code generation for type casting
}

void GenVisitor::visit(ast::Call &node) {
    // TODO: Implement code generation for function calls
}

void GenVisitor::visit(ast::ExpList &node) {
    // TODO: Implement code generation for expression lists
}

// Type nodes
void GenVisitor::visit(ast::ArrayType &node) {
    // TODO: Implement code generation for array type declarations
}

void GenVisitor::visit(ast::PrimitiveType &node) {
    // TODO: Implement code generation for primitive type declarations
}

// Array operations
void GenVisitor::visit(ast::ArrayDereference &node) {
    // TODO: Implement code generation for array element access
}

void GenVisitor::visit(ast::ArrayAssign &node) {
    // TODO: Implement code generation for array element assignment
}

// Statement nodes
void GenVisitor::visit(ast::Statements &node) {
    // TODO: Implement code generation for statement sequences
}

void GenVisitor::visit(ast::Block &node) {
    // TODO: Implement code generation for block statements
}

void GenVisitor::visit(ast::Break &node) {
    // TODO: Implement code generation for break statements
}

void GenVisitor::visit(ast::Continue &node) {
    // TODO: Implement code generation for continue statements
}

void GenVisitor::visit(ast::Return &node) {
    // TODO: Implement code generation for return statements
}

void GenVisitor::visit(ast::If &node) {
    // TODO: Implement code generation for if statements
}

void GenVisitor::visit(ast::While &node) {
    // TODO: Implement code generation for while loops
}

void GenVisitor::visit(ast::VarDecl &node) {
    // TODO: Implement code generation for variable declarations
}

void GenVisitor::visit(ast::Assign &node) {
    // TODO: Implement code generation for assignments
}

// Function-related nodes
void GenVisitor::visit(ast::Formal &node) {
    buffer << output::toLl(node.type->computedType) ;
}

void GenVisitor::visit(ast::Formals &node) {
    for (auto& formal : node.formals) {
        formal->accept(*this);
        if (&formal != &node.formals.back()) {
            buffer << ", ";
        }
    }
}

void GenVisitor::visit(ast::FuncDecl &node) {
    string funcName = node.id->value;
    string returnType = output::toString(node.return_type->computedType);

    buffer << "define " << returnType << " @" << funcName << "(";

    node.formals->accept(*this);

    buffer << ") {\n";

    buffer.indent();

    node.body->accept(*this);

    buffer.unindent();
    buffer << "}\n";
    
}

void GenVisitor::visit(ast::Funcs &node) {
    
    for (auto &func : node.funcs) {
        func->accept(*this);
    }
}
