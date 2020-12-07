#include "operator.h"

#include "complexnumber.h"

Operator::Operator(Operator::Type t_) : m_type{t_} { }

Operator::Operator(char c_) : Operator(charToType(c_)) { }

Operator::Operator(const std::string& s_) : Operator(stringToType(s_)) { }

void Operator::ChangeType(char t) {
    this->m_type = charToType(t);
}

ComplexNumber Operator::Calculate(Stack<ComplexNumber> stack) const {
    ComplexNumber number;
    auto s = stack.reversed();
    if (m_type == Type::ABS) {
        return stack.top().abs();
    }
    if (m_type == Type::IMAGINARY) {
        return stack.top().imaginary();
    }
    if (m_type == Type::REAL) {
        return stack.top().real();
    }
    if (m_type == Type::MULTIPLY || m_type == Type::DIVIDE) {
        number = {1,0};
    }

        while (!s.empty()) {
            if (m_type == Type::PLUS) {
                number = number + s.pop();
            } else if (m_type== Type::MINUS) {
                number = number - s.pop();
            } else if (m_type== Type::MULTIPLY) {
                number = number * s.pop();
            } else if (m_type== Type::DIVIDE) {
                number = number / s.pop();
            }
        }
    return number;
}

void Operator::evaluate(Stack<ComplexNumber>& operands_) const {
    ComplexNumber arg1, arg2;
    switch (m_type) {
    case Type::PLUS:
        arg2 = operands_.pop();
        arg1 = operands_.pop();
        operands_.push(arg1 + arg2);
        break;
    case Type::MINUS:
        arg2 = operands_.pop();
        arg1 = operands_.pop();
        operands_.push(arg1 - arg2);
        break;
    case Type::MULTIPLY:
        arg2 = operands_.pop();
        arg1 = operands_.pop();
        operands_.push(arg1 * arg2);
        break;
    case Type::DIVIDE:
        arg2 = operands_.pop();
        arg1 = operands_.pop();
        operands_.push(arg1 / arg2);
        break;
    case Type::REAL:
        arg1 = operands_.pop();
        operands_.push(arg1.real());
        break;
    case Type::IMAGINARY:
        arg1 = operands_.pop();
        operands_.push(ComplexNumber(0.0, arg1.imaginary()));
        break;
    case Type::ABS:
        arg1 = operands_.pop();
        operands_.push(arg1.abs());
        break;
    default:
        break;
    }
}

Operator::Type Operator::charToType(char c_) {
    switch (c_) {
    case '+':
        return Type::PLUS;
    case '-':
        return Type::MINUS;
    case '*':
        return Type::MULTIPLY;
    case '/':
        return Type::DIVIDE;
    case 'R':
        return Type::REAL;
    case 'I':
        return Type::IMAGINARY;
    case 'A':
        return Type::ABS;
    default:
        return Type::NONE;
    }
}

Operator::Type Operator::stringToType(const std::string& s_) {
    if (s_.size() > 0) {
        return charToType(s_[0]);
    }
    return Type::NONE;
}
