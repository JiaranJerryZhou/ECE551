#include <string.h>

#include <iostream>
#include <sstream>

class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
  long num;

 public:
  NumExpression(long num) : num(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
  virtual long evaluate() const { return num; }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OpExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  virtual ~PlusExpression() {}
};
class MinusExpression : public OpExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }

  virtual ~MinusExpression() {}
};
class TimesExpression : public OpExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }

  virtual ~TimesExpression() {}
};
class DivExpression : public OpExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }

  virtual ~DivExpression() {}
};
