#include "Matrix.h"
Matrix::Matrix(int n, int m, int nElem) 
{
	try 
	{
		createMatr(n,m,nElem);
	}
	catch (VectException e)
	{
		cerr << e.getReason() << endl;
	}
}
Matrix::Matrix(const Matrix& m)  
{
	nRow = 0;
	vTab = NULL;
	*this = m;
}
Matrix::~Matrix() 
{
	delete[] vTab;
}

istream& operator >> (istream& in, Matrix& m)
{
	for (int i = 0; i < m.getRowNo(); i++)
	{
		in >> m.vTab[i];
	}
	return in;
}
ostream& operator << (ostream& out, const Matrix& m)
{
	out << endl << "______" << endl << endl;
	for (int i = 0; i < m.getRowNo(); i++)
	{
		out << m[i] << endl;
	}
	out << "______";
	return out;
}

bool operator == (const Matrix& m1, const Matrix& m2)
{
	if (m1.getRowNo() != m2.getRowNo()) return false;
	if (m1.getColNo() != m2.getColNo()) return false;
	for (int i = 0; i < m1.getRowNo(); i++)
		//if (m1[i] != m2[i]) return false;
	for (int j = 0; j < m1.getColNo(); j++)
		if (m1[i][j] != m2[i][j]) return false;
	return true;
}
bool operator != (const Matrix& m1, const Matrix& m2)
{
	return !(m1 == m2);
}

Matrix& Matrix::operator = (const Matrix& m) ///
{
	if (getRowNo() != m.getRowNo() || getColNo() != m.getColNo())
	{
		delete [] vTab;
		try
		{
			createMatr(m.getRowNo(), m.getColNo(), 0);
		}
		catch(VectException e)
		{
			cerr << e.getReason() << endl;
			return *this;
		}
	}
	copyMatr(m);
	return *this;
}

const Matrix operator * (const Matrix& m1, const Matrix& m2) 
{
	if (m1.getColNo() != m2.getRowNo()) throw VectException(INCOMPATIBLE_SIZES);
	Matrix m(m1.getRowNo(), m2.getColNo(), 0);
	for (int k = 0; k < m1.getRowNo(); k++)
		for (int i = 0; i < m2.getColNo(); i++)
			for (int j = 0; j < m1.getColNo(); j++)
			{
				m.vTab[k][i] += m1.vTab[k][j] * m2.vTab[j][i];
			}
	return m;

}

const Vector operator * (const Matrix& m, const Vector& v)
{
	if (m.getColNo() != v.getDim())
		throw VectException(INCOMPATIBLE_SIZES);
	Vector temp(v.getDim(), 1);
	for (int i = 0; i < v.getDim(); i++) {
		temp[i] = m[i] * v;
	}
	return temp;
}