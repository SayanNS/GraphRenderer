//
// Created by sayan on 06.06.2022.
//

#ifndef GRAPH_FUNCTION_H
#define GRAPH_FUNCTION_H

#include <string>
#include <memory>


class Function
{
public:
	static std::unique_ptr<Function> parse(std::string const &function);

	virtual double f(double x) = 0;

	virtual ~Function() = default;
};

class UnaryFunction : public Function
{
public:
	explicit UnaryFunction(std::unique_ptr<Function> &&f1);

protected:
	std::unique_ptr<Function> f1;
};

class BinaryFunction : public UnaryFunction
{
public:
	BinaryFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2);

protected:
	std::unique_ptr<Function> f2;
};

class InverseFunction : public UnaryFunction
{
public:
	explicit InverseFunction(std::unique_ptr<Function> &&f);

	double f(double x) override;
};

class SinFunction : public UnaryFunction
{
public:
	explicit SinFunction(std::unique_ptr<Function> &&f);

	double f(double x) override;
};

class CosFunction : public UnaryFunction
{
public:
	explicit CosFunction(std::unique_ptr<Function> &&f);

	double f(double x) override;
};

class SumFunction : public BinaryFunction
{
public:
	SumFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2);

	double f(double x) override;
};

class MinusFunction : public BinaryFunction
{
public:
	MinusFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2);

	double f(double x) override;
};

class MultiplyFunction : public BinaryFunction
{
public:
	MultiplyFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2);

	double f(double x) override;
};

class DivideFunction : public BinaryFunction
{
public:
	DivideFunction(std::unique_ptr<Function> &&f1, std::unique_ptr<Function> &&f2);

	double f(double x) override;
};

class LinearFunction : public Function
{
public:
	double f(double x) override;
};


class ConstFunction : public Function
{
public:
	explicit ConstFunction(double a);

	double f(double x) override;

private:
	double a;
};

#endif //GRAPH_FUNCTION_H
