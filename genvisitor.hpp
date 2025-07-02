#ifndef GENVISITOR_HPP
#define GENVISITOR_HPP

#include "visitor.hpp"
#include "nodes.hpp"
#include "output.hpp"

class GenVisitor : public Visitor {
public:
    GenVisitor();
    virtual ~GenVisitor();

    // Expression nodes
    virtual void visit(ast::Num &node) override;
    virtual void visit(ast::NumB &node) override;
    virtual void visit(ast::String &node) override;
    virtual void visit(ast::Bool &node) override;
    virtual void visit(ast::ID &node) override;
    virtual void visit(ast::BinOp &node) override;
    virtual void visit(ast::RelOp &node) override;
    virtual void visit(ast::Not &node) override;
    virtual void visit(ast::And &node) override;
    virtual void visit(ast::Or &node) override;
    virtual void visit(ast::Cast &node) override;
    virtual void visit(ast::Call &node) override;
    virtual void visit(ast::ExpList &node) override;

    // Type nodes
    virtual void visit(ast::ArrayType &node) override;
    virtual void visit(ast::PrimitiveType &node) override;

    // Array operations
    virtual void visit(ast::ArrayDereference &node) override;
    virtual void visit(ast::ArrayAssign &node) override;

    // Statement nodes
    virtual void visit(ast::Statements &node) override;
    virtual void visit(ast::Break &node) override;
    virtual void visit(ast::Continue &node) override;
    virtual void visit(ast::Return &node) override;
    virtual void visit(ast::If &node) override;
    virtual void visit(ast::While &node) override;
    virtual void visit(ast::VarDecl &node) override;
    virtual void visit(ast::Assign &node) override;

    // Function-related nodes
    virtual void visit(ast::Formal &node) override;
    virtual void visit(ast::Formals &node) override;
    virtual void visit(ast::FuncDecl &node) override;
    virtual void visit(ast::Funcs &node) override;

private:
    // Add any private member variables needed for code generation
    output::CodeBuffer buffer;
};

#endif // GENVISITOR_HPP