//Operator overloading
#include <iostream>
using namespace std;

class Matrix {
private:
	int** values;
	int row, column;
public:
	Matrix(int _row, int _column) : row(_row), column(_column)
	{
		values = new int*[row];
		for (int i = 0; i < row; i++) {
			values[i] = new int[column];
		}
	}

	Matrix(const Matrix& copyMatrix) : row(copyMatrix.row), column(copyMatrix.column)
	{
		values = new int*[row];
		for (int i = 0; i < row; i++) {
			values[i] = new int[column];
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				values[i][j] = copyMatrix.values[i][j];
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < getRow(); i++) {
			delete[] values[i];
		}
		delete[] values;
	}

	int getRow() { return row; }
	int getCol() { return column; }
	void setRow(int _row) { row = _row; }
	void setCol(int _col) { column = _col; }

	bool isEquivalentSize(const Matrix& A, const Matrix& B) {
		return A.row == B.row && A.column == B.column;
	}

	Matrix operator+(const Matrix& m) {
		if (!isEquivalentSize(*this, m)) {
			cout << "operator+ Error" << endl;
			return *this;
		}

		Matrix tmp(*this);
		for (int i = 0; i < tmp.getRow(); i++) {
			for (int j = 0; j < tmp.getCol(); j++) {
				tmp.values[i][j] += m.values[i][j];
			}
		}
		return tmp;
	}

	Matrix& operator=(const Matrix& m) {
		if (!isEquivalentSize(*this, m)) {
			cout << "operator= Error" << endl;
			return *this;
		}

		this->setRow(m.row);
		this->setCol(m.column);
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->column; j++) {
				this->values[i][j] = m.values[i][j];
			}
		}
		return *this;
	}

	friend Matrix operator*(Matrix m, const int num);
	friend istream& operator>>(istream& is, Matrix& matrix);
	friend ostream& operator<<(ostream& os, const Matrix& matrix);
};

Matrix operator*(Matrix m, const int num) {
	for (int i = 0; i < m.getRow(); i++) {
		for (int j = 0; j < m.getCol(); j++) {
			m.values[i][j] *= num;
		}
	}
	return m;
}

istream& operator>>(istream& is, Matrix& matrix) {
	for (int i = 0; i < matrix.getRow(); i++) {
		for (int j = 0; j < matrix.getCol(); j++) {
			is >> matrix.values[i][j];
		}
	}
	return is;
}

ostream& operator<<(ostream& os, const Matrix& matrix) {
	for (int i = 0; i < matrix.row; i++) {
		for (int j = 0; j < matrix.column; j++) {
			os << matrix.values[i][j] << '\t';
		}
		os << endl;
	}
	return os;
}


int main() {
	Matrix m1(2, 2), m2(2, 2);
	cin >> m1;
	cin >> m2;

	Matrix m3(m1 + m2);
	Matrix m4(2, 2);

	m4 = m3 * 10;

	cout << m3 << endl << m4 << endl;

	/*
	cout << m1 << endl << m2 << endl;
	cout << m3 << endl << m4 << endl;
	*/
	return 0;
}
