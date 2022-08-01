//
// Created by sayan on 06.06.2022.
//

#include "function.h"
#include "parser.h"
#include <sstream>
#include <cmath>


SinFunction::SinFunction(std::unique_ptr<Function> &&f)
	: UnaryFunction(std::move(f))
{
}

double SinFunction::f(double x)
{
	return sin(f1->f(x));
}

CosFunction::CosFunction(std::unique_ptr<Function> &&f)
	: UnaryFunction(std::move(f))
{
}

double CosFunction::f(double x)
{
	return cos(f1->f(x));
}

SumFunction::SumFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2)
	: BinaryFunction(std::move(f1), std::move(f2))
{
}

double SumFunction::f(double x)
{
	return f1->f(x) + f2->f(x);
}

MultiplyFunction::MultiplyFunction(std::unique_ptr<Function>&& f1, std::unique_ptr<Function> &&f2)
	: BinaryFunction(std::move(f1), std::move(f2))
{
}

double MultiplyFunction::f(double x)
{
	return f1->f(x) * f2->f(x);
}

ConstFunction::ConstFunction(double a)
	: a(a)
{
}

double ConstFunction::f(double x)
{
	return a;
}

double LinearFunction::f(double x)
{
	return x;
}

UnaryFunction::UnaryFunction(std::unique_ptr<Function> &&f1)
{
	this->f1 = std::move(f1);
}


BinaryFunction::BinaryFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2) : UnaryFunction(std::move(f1))
{
	this->f2 = std::move(f2);
}

std::unique_ptr<Function> Function::parse(std::string const &functionText)
{
	std::istringstream stream{functionText};
	parser p(stream);
	return p.parse();
}

InverseFunction::InverseFunction(std::unique_ptr<Function> &&f)
	: UnaryFunction(std::move(f))
{
}

double InverseFunction::f(double x)
{
	return -f1->f(x);
}

MinusFunction::MinusFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2)
	: BinaryFunction(std::move(f1), std::move(f2))
{
}

double MinusFunction::f(double x)
{
	return f1->f(x) - f2->f(x);
}

DivideFunction::DivideFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2)
	: BinaryFunction(std::move(f1), std::move(f2))
{

}

double DivideFunction::f(double x)
{
	return f1->f(x) / f2->f(x);
}
