#include "Vector.h"
int mult(int*, int*, int nDim);
Vector::Vector(int nDim, int nElem)
{
	try
	{
		createVect(nDim); 
		m_nDim = nDim;
		for (int i = 0; i < nDim; i++)
		{
			m_pCoord[i] = nElem;
		}
	}
	catch (VectException e)
	{
		cerr << e.getReason() << endl;
	}
}
Vector::Vector(const Vector& v)
{
	m_nDim = 0;
	m_pCoord = NULL;
	*this = v;
}
Vector::~Vector()
{
	delete[] m_pCoord;
}
istream& operator >> (istream& in, Vector& v)
{
	for (int i = 0; i < v.getDim(); i++)
		in >> v.m_pCoord[i];
	return in;
}
ostream& operator << (ostream& out, const Vector& v)
{
	out << "[";
	for (int i = 0; i < v.getDim(); i++)
		out << v.m_pCoord[i] << ((i < v.getDim() - 1) ? "," : "");
	out << ']';
	return out;
}
//unary minus
const Vector operator - (const Vector& v)
{
	Vector res(v);
	for (int i = 0; i < v.getDim(); i++)
	//res[i] = -res[i];
	res.m_pCoord[i] = -res.m_pCoord[i];
	return res;

}
//assignment
Vector& Vector::operator = (const Vector& v) //v1=v2
{
	if (getDim() != v.getDim())
	{
		delete [] m_pCoord;
		m_pCoord = NULL;
		try
		{
			createVect(v.getDim());
		}
		catch (VectException e)
		{
			cerr << e.getReason() << endl;
			return *this;
		}
	}
	copyVec(v);
	return *this;
}
//addition
const Vector operator + (const Vector& v1, const Vector& v2)//v1+v2
{
	Vector res(v1);
	return res += v2;
}
const Vector operator + (const Vector& v, int x) //v1 + 3 
{
	Vector res(v);
	return res += x;
}
const Vector operator + (int x, const Vector& v) //3 + v1
{
	return v + x;
}
Vector& Vector::operator += (const Vector& v)
{
	if (getDim() != v.getDim()) throw VectException(INCOMPATIBLE_SIZES);
	for (int i = 0; i < getDim(); i++)
		m_pCoord[i] += v.m_pCoord[i];
	return *this;
}
Vector& Vector::operator += (int x)
{
	for (int i = 0; i < getDim(); i++)
		m_pCoord[i] += x;
	return *this;
}
//substraction
const Vector operator - (const Vector& v1, const Vector& v2) //v1-v2
{
	return v1 + (-v2);
}
const Vector operator - (const Vector& v, int x) //v1 - 3 
{
	return v + (-x);
}
const Vector operator - (int x, const Vector& v) //3 - v1
{
	return -v + x;
}
Vector& Vector::operator -= (const Vector& v)
{
	return *this += -v;
}
Vector& Vector::operator -= (int x)
{
	return *this += -x;
}
//multiplication
const Vector operator * (const Vector& v, int x)//
{
	Vector res(v);
	return res *= x;
}
const Vector operator * (int x, const Vector& v)//
{
	return v * x;
}
Vector& Vector::operator *= (int x)
{
	for (int i = 0; i < getDim(); i++)
		m_pCoord[i] *= x;
	return *this;
}
//scalar multiplication
const int operator * (const Vector& v1, const Vector& v2)
{
	if (v1.getDim() != v2.getDim()) throw VectException(INCOMPATIBLE_SIZES);
	return mult((int*)v1, (int*)v2, v1.getDim());
}
bool operator == (const Vector& v1, const Vector& v2)
{
	if (v1.getDim() != v2.getDim()) return false;
	for (int i = 0; i < v1.getDim(); i++)
		if (v1[i] != v2[i]) return false;
	return true;
}
bool operator != (const Vector& v1, const Vector& v2)
{
	return !(v1 == v2);
}
int mult(int* p, int* v, int nDim)
{
	int res = 0;
	for (int i = 0; i < nDim; i++)
	{
		res += *p++ * *v++;
	}
	return res;
}