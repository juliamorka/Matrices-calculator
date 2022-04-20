#pragma once
#include <iostream>
using namespace std;
#define VERROR             0x00
#define INDEX_OUT_OF_RANGE 0x01
#define ALLOCATION_ERROR   0x02
#define INCOMPATIBLE_SIZES 0x04
typedef unsigned short int USSHORT;
class VectException
{
public:
	VectException(USSHORT errCode);
	const char* getReason();
private:
	USSHORT m_ErrCode;
};
class Vector
{
public: 
	//construction, destruction
	Vector(int nDim = 2, int nElem = 0); //vector will be initialized by nElem value
	Vector(const Vector& v);
	virtual ~Vector();
	inline int getDim() const;
	inline operator int* () const; //casts vector to an integer array
	//operators
public:
	//unary minus
	friend const Vector operator - (const Vector& v);
	//assignment
	Vector& operator = (const Vector& v); //v1=v2
	//addition
	friend const Vector operator + (const Vector& v1, const Vector& v2); //v1+v2
	friend const Vector operator + (const Vector& v1, int x); //v1 + 3 -> adds 3 to every vector element
	friend const Vector operator + (int x, const Vector& v1); //3 + v1
	Vector& operator += (const Vector& v);
	Vector& operator += (int x);
	//substraction
	friend const Vector operator - (const Vector& v1, const Vector& v2); //v1-v2
	friend const Vector operator - (const Vector& v1, int x); //v1 - 3 
	friend const Vector operator - (int x, const Vector& v1); //3 - v1
	Vector& operator -= (const Vector& v);
	Vector& operator -= (int x);
	//multiplication
	friend const Vector operator * (const Vector& v1, int x); //
	friend const Vector operator * (int x, const Vector& v1); //
	Vector& operator *= (int x);
	//scalar multiplication
	friend const int operator * (const Vector& v1, const Vector& v2);
	//comparision
	friend bool operator == (const Vector& v1, const Vector& v2);
	friend bool operator != (const Vector& v1, const Vector& v2);
	//indexation
	inline int& operator[] (int); //v[1] = 2;
	inline const int& operator[] (int) const; // int x = v[3];
	//input/output
	friend istream& operator >> (istream& in, Vector& v);
	friend ostream& operator << (ostream& out, const Vector& v);
private:
	int* m_pCoord; 
	int m_nDim; 
private:
	inline void createVect(int nDim);
	inline void copyVec(const Vector& v);
};
inline VectException::VectException(USSHORT errCode)
{
	m_ErrCode = errCode;
}
inline const char* VectException::getReason()
{
	switch (m_ErrCode)
	{
	case VERROR: return "Vector error!";
	case INDEX_OUT_OF_RANGE: return "Index out of range!";
	case ALLOCATION_ERROR: return "Allocation error!";
	default: return "Incompatible sizes!";
	}
}
//inline functions
inline int Vector::getDim() const
{
	return m_nDim;
}
inline Vector::operator int* () const
{
	return m_pCoord;
}
inline void Vector::createVect(int nDim)
{
	if (nDim < 2) nDim = 2;
	m_nDim = nDim;
	m_pCoord = new (nothrow) int[nDim];
	if (!m_pCoord) throw VectException(ALLOCATION_ERROR);
}
//indexation
inline int& Vector::operator[] (int ix) //v[1] = 2;
{
	if (ix >= 0 && ix < getDim())
		return m_pCoord[ix];
	throw VectException(INDEX_OUT_OF_RANGE);
}
inline const int& Vector::operator[] (int ix) const // int x = v[3];
{
	if (ix >= 0 && ix < getDim())
		return m_pCoord[ix];
	throw VectException(INDEX_OUT_OF_RANGE);
}
inline void Vector::copyVec(const Vector& v)
{
	memcpy(m_pCoord, (int*)v, v.getDim() * sizeof(int));
}