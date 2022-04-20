#pragma once
#include "Vector.h"
class Matrix
{
private:
	int nRow;    
	Vector* vTab; 
	void createMatr(int n, int m, int nElem);
	void copyMatr(const Matrix& m);

public:
	Matrix(int n = 2, int m = 2, int nElem = 0); 
	Matrix(const Matrix& m); 
	virtual ~Matrix(); 

public:
	inline int getRowNo() const; 
	inline int getColNo() const; 

	friend istream& operator >> (istream& in, Matrix& m);
	friend ostream& operator << (ostream& out, const Matrix& m);

	inline Vector& operator[] (int); //v[1] = Vector(3,1);
	inline const Vector& operator[] (int) const; // Vector x = v[3];

	inline operator Vector* () const;
	
	friend bool operator == (const Matrix& m1, const Matrix& m2);
	friend bool operator != (const Matrix& m1, const Matrix& m2);
	
	Matrix& operator = (const Matrix& m);
	
	friend const Matrix operator * (const Matrix& m1, const Matrix& m2);
	
	friend const Vector operator * (const Matrix& m, const Vector& v);
};
inline int Matrix::getRowNo() const
{
	return nRow;
}
inline int Matrix::getColNo() const
{
	if (!vTab) return 0;
	return vTab[0].getDim(); 
}

inline Vector& Matrix::operator[] (int ix) 
{
	if (ix >= 0 && ix < getRowNo())
		return vTab[ix];
	throw VectException(INDEX_OUT_OF_RANGE);
}
inline const Vector& Matrix::operator[] (int ix) const 
{
	if (ix >= 0 && ix < getRowNo())
		return vTab[ix];
	throw VectException(INDEX_OUT_OF_RANGE);
}

inline Matrix::operator Vector* () const
{
	return vTab;
}
inline void Matrix::createMatr(int n, int m, int nElem)
{
	nRow = (n < 2) ? 2 : n;
	vTab = new (nothrow) Vector[nRow];
	if (!vTab) throw VectException(ALLOCATION_ERROR);
	for (int i = 0; i < nRow; i++)
	{
		vTab[i] = Vector(m, nElem);
	}
}
inline void Matrix::copyMatr(const Matrix& m)
{
	for (int i = 0; i < m.getRowNo(); i++) {
		memcpy(vTab[i], m.vTab[i], m.getColNo() * sizeof(int));
	} 
}