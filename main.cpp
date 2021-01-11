#include <iostream>

class Matrix
{
public:
	Matrix(int rows = 0, int cols = 0, const char* desc = nullptr)
	{
		if (rows > 0 && cols > 0)
		{
			arr = new float* [rows];
			for (int i = 0; i < rows; i++)
			{
				arr[i] = new float[cols];
				for (int j = 0; j < cols; j++)
				{
					arr[i][j] = 0;
				}
			}
		
			this->rows = rows;
			this->cols = cols;
		}
		else
		{
			this->arr = nullptr;
			this->rows = 0;
			this->cols = 0;
		}

		if (desc)
		{
			this->desc = new std::string(desc);
		}
		else
		{
			this->desc = nullptr;
		}
	}

	Matrix(const Matrix& m)
	{
		//std::cout << "Copy Constructor!" << "\n";
		copy(m);
	}

	~Matrix()
	{
		//std::cout << "Destructor!" << "\n";
		clear();
	}

	Matrix& operator=(Matrix& m)
	{
		//std::cout << "Assignment!" << "\n";
		copy(m);
		return (*this);
	}

	float* operator[](int index) const
	{
		return arr[index];
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	friend std::istream& operator>>(std::istream& in, const Matrix& m);

private:
	float** arr;
	int rows, cols;
	std::string* desc;

	void copy(const Matrix& m)
	{
		clear();

		rows = m.rows;
		cols = m.cols;

		arr = new float* [rows];
		for (int i = 0; i < rows; i++)
		{
			arr[i] = new float[cols];
			for (int j = 0; j < cols; j++)
			{
				arr[i][j] = m[i][j];
			}
		}

		if (m.desc)
		{
			desc = new std::string(*(m.desc));
		}
		
	}
	void clear()
	{
		if(arr)
		{
			for (int i = 0; i < rows; i++)
			{
				delete arr[i];
			}
			delete arr;
		}

		this->rows = 0;
		this->cols = 0;

		if (desc) delete desc;
	}
};


std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
	out << "Matrix " << m.rows << " X " << m.cols;
	if (m.desc) out << " (Description: " << *(m.desc) << ")";
	out << ":\n";

	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			out << m.arr[i][j] << "\t";
		}
		out << "\n";
	}
	return out;
}

std::istream& operator>>(std::istream& in, const Matrix& m)
{
	std::cout << "Enter matrix " << m.rows << " x " << m.cols << ":\n";
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			in >> m.arr[i][j];
		}
	}
	return in;
}

int main()
{
	//Default constructor
	Matrix m0(0,0, "matrix 0");
	std::cout << m0 << "\n";

	//Dimension constructor + Input data from keyboard
	Matrix m(2, 3);
	std::cin >> m;

	//Copy constructor
	Matrix m2 = m;
	std::cout << "\n" << m2 << "\n\n";

	//m = m0;
	//std::cout << "\n" << m << "\n\n";

	//Description constructor + operator[]
	Matrix m3(2, 2, "Matrix 3");
	m3[0][1] = 50;
	m3[1][0] = 100;
	std::cout << "m3[1][0]: " << m3[1][0] << "\n\n";

	//operator=
	m2 = m3;
	std::cout << m2 << "\n";

	return 0;
}