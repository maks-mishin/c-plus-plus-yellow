#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

/*
	@brief - Class for representation of matrix
*/
class Matrix
{
public:
	/*
		@brief - Default constructor
	*/
	Matrix()
	{
		rows = 0;
		cols = 0;
	}
	/*
		@brief - Constructor with params
	*/
	Matrix(int num_rows, int num_cols)
	{
		Reset(num_rows, num_cols);
	}

	~Matrix() {}

	int GetNumRows() const
	{
		return rows;
	}

	int GetNumColumns() const
	{
		return cols;
	}

	/*
		@return - item of matrix with params (row, column)
	*/
	int At(int row, int col) const
	{
		return matrix.at(row).at(col);
	}

	/*
		@return - address of item of matrix with params (row, column)
	*/
	int& At(int row, int col)
	{
		return matrix.at(row).at(col);
	}

	/*
		@brief - change of size of matrix and reset it values to 0
	*/
	void Reset(int new_rows, int new_cols)
	{
		try
		{
			if (new_cols < 0 || new_rows < 0)
			{
				throw std::out_of_range("Number of rows or cols mustn't be negative.");
			}
			if (new_cols == 0 || new_rows == 0)
			{
				rows = 0;
				cols = 0;
			}

			rows = new_rows;
			cols = new_cols;

			matrix.assign(new_rows, std::vector<int>(new_cols));
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	friend std::ostream& operator << (std::ostream& stream, const Matrix& m);
	friend std::istream& operator >> (std::istream& stream, const Matrix& m);
private:
	int rows;
	int cols;
	std::vector<std::vector<int>> matrix;
};

std::ostream& operator<<(std::ostream& stream, const Matrix& m)
{
	stream << m.GetNumRows() << " " << m.GetNumColumns() << std::endl;

	for (int i = 0; i < m.GetNumRows(); i++)
	{
		for (int j = 0; j < m.GetNumColumns(); j++)
		{
			stream << m.At(i, j) << " ";
		}
		stream << std::endl;
	}
	return stream;
}

std::istream& operator >> (std::istream& stream, Matrix& m)
{
	int cols = 0, rows = 0;
	stream >> rows >> cols;

	m.Reset(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			stream >> m.At(i, j);
		}
	}
	return stream;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	try
	{
		if (lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows())
		{
			throw std::invalid_argument("The dimensions of the matrices must be the same.");
		}

		Matrix temp(lhs.GetNumRows(), lhs.GetNumColumns());

		for (int row = 0; row < lhs.GetNumRows(); row++)
		{
			for (int col = 0; col < lhs.GetNumColumns(); col++)
			{
				temp.At(row, col) = lhs.At(row, col) + rhs.At(row, col);
			}
		}
		return temp;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
	{
		return false;
	}

	for (int row = 0; row < lhs.GetNumRows(); ++row)
	{
		for (int column = 0; column < lhs.GetNumColumns(); ++column)
		{
			if (rhs.At(row, column) != rhs.At(row, column))
			{
				return false;
			}
		}
	}
	return true;
}