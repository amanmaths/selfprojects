#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::invalid_argument;
using std::vector;

// Function to add entries of 2 vectors
vector<int> operator+(vector<int> &a, vector<int> &b)
{
    unsigned la = a.size(), lb = b.size();
    // Check if dimensions are same
    if (la != lb)
    {
        // Throw error if dimensions are not same
        throw invalid_argument("Vector dimensions are different");
    }
    vector<int> r(la);
    for (unsigned i = 0; i < la; i++)
    {
        r[i] = a[i] + b[i];
    }
    return r;
}

// Function to subtract 2 vectors
vector<int> operator-(vector<int> &a, vector<int> &b)
{
    unsigned la = a.size(), lb = b.size();
    // Check if dimensions are same
    if (la != lb)
    {
        // Throw error if dimensions are not same
        throw invalid_argument("Vector dimensions are different");
    }
    vector<int> r(la);
    for (unsigned i = 0; i < la; i++)
    {
        r[i] = a[i] - b[i];
    }
    return r;
}

// Function to negate a vector elementwise
vector<int> operator-(vector<int> &a)
{
    unsigned la = a.size();
    vector<int> t(la, 0);
    return t - a;
}

// Vector-vector dot product
int operator*(vector<int> &a, vector<int> &b)
{
    unsigned la = a.size(), lb = b.size();
    // Check if dimensions are same
    if (la != lb)
    {
        // Throw error if dimensions are not same
        throw invalid_argument("Vector dimensions are different");
    }
    int r = 0;
    for (unsigned i = 0; i < la; i++)
    {
        r += a[i] * b[i];
    }
    return r;
}

// class to define a complete matrix
class matrix
{
    // Some useful properties for checking compatibility
    unsigned row, col;       // number of rows and cols
    vector<vector<int>> mat; // The actual matrix

public:
    // Constructor if all elements are to be the same
    matrix(unsigned n, unsigned m, int k = 0)
    {
        row = n, col = m;
        vector<int> t(m, k);
        mat.resize(n, t);
    }

    // Constructor if matrix is directly given from the inputs
    matrix()
    {
        cout << "Input number of rows and columns\n";
        cin >> row >> col;
        cout << "Input the entries row wise:\n";
        for (unsigned i = 0; i < row; i++)
        {
            vector<int> v(col);
            for (unsigned j = 0; j < col; j++)
            {
                cin >> v[j];
            }
            mat.push_back(v);
        }
    }

    // Method to retrieve the dimensions of the matrix
    vector<unsigned> getdim()
    {
        return {row, col};
    }

    // Method to retrieve the actual entries of the matrix
    vector<vector<int>> getmat()
    {
        return mat;
    }

    // Method to print the entries of the matrix
    void print()
    {
        for (unsigned i = 0; i < row; i++)
        {
            for (unsigned j = 0; j < col; j++)
            {
                cout << mat[i][j] << "\t";
            }
            cout << "\n";
        }
        // Also print the size at the bottom
        cout << "Dimension : (" << row << " , " << col << ")\n";
    }

    // Method to set matrix entries given a 2d vector/matay
    void setmat(vector<vector<int>> mat1)
    {
        unsigned r1 = mat1.size(), c1 = mat1[0].size();
        if (row != r1 || col != c1)
        {
            // Throw error if dimension is tried to changed
            throw invalid_argument("Cannot change matrix dimension");
        }
        mat = mat1;
    }

    // Method to transpose matrix and return the transposed matrix
    matrix T()
    {
        matrix r(col, row); // matrix of proper dimension
        vector<vector<int>> t = r.getmat();
        for (unsigned i = 0; i < col; i++)
        {
            for (unsigned j = 0; j < row; j++)
            {
                t[i][j] = mat[j][i];
            }
        }
        r.setmat(t);
        return r;
    }
};

// Function to add entries of 2 matrices
matrix operator+(matrix &a, matrix &b)
{
    vector<unsigned> da = a.getdim(), db = b.getdim(); // get the dimensions of each matrix
    // Check if the dimensions are same
    if (da[0] != db[0] || da[1] != db[1])
    {
        // Throw error if dimensions are not same
        throw invalid_argument("Matrix dimensions must be same");
    }
    matrix z(da[0], da[1]); // define matrix of proper dimension
    vector<vector<int>> mat1 = a.getmat(), mat2 = b.getmat(), mat = z.getmat();
    for (unsigned i = 0; i < da[0]; i++)
    {
        mat[i] = mat1[i] + mat2[i];
    }
    z.setmat(mat);
    return z;
}

// Function to subtract entries of 2 matrices
matrix operator-(matrix &a, matrix &b)
{
    vector<unsigned> da = a.getdim(), db = b.getdim(); // get the dimensions of each matrix
    // Check if the dimensions are same
    if (da[0] != db[0] || da[1] != db[1])
    {
        // Throw error if dimensions are not same
        throw invalid_argument("Matrix dimensions must be same");
    }
    matrix z(da[0], da[1]); // define matrix of proper dimension
    vector<vector<int>> mat1 = a.getmat(), mat2 = b.getmat(), mat = z.getmat();
    for (unsigned i = 0; i < da[0]; i++)
    {
        mat[i] = mat1[i] - mat2[i];
    }
    z.setmat(mat);
    return z;
}

// Function to change sign of each entry of matrix
matrix operator-(matrix &a)
{
    vector<unsigned> da = a.getdim(); // get the dimension of matrix
    matrix t(da[0], da[1]);           // define zero matrix of proper dimension
    return t - a;                     // return zero matrix - matrix
}

// Function to implement matrix multiplication
matrix operator*(matrix &a, matrix &b)
{
    vector<unsigned> da = a.getdim(), db = b.getdim(); // get the dimensions of each matrix
    // Check if the dimensions are compatibile
    if (da[1] != db[0])
    {
        // Throw error if dimensions are not compatibile
        throw invalid_argument("Matrix dimensions must be compatibile");
    }
    matrix z(da[0], db[1]); // define matrix of proper dimension
    matrix c = b.T(); // Transpose the second matrix for computation purpose
    vector<vector<int>> mat1 = a.getmat(), mat2 = c.getmat(), mat = z.getmat();
    for (unsigned i = 0; i < da[0]; i++)
    {
        for (unsigned j = 0; j < db[1]; j++)
        {
            mat[i][j] = mat1[i] * mat2[j];
        }
    }
    z.setmat(mat);
    return z;
}

int main()
{
    matrix a, b = matrix(), c = a + b, d = a - b, e = a * b;
    cout << "----Matrix Addition----\n";
    c.print();
    cout << "----Matrix Subtraction----\n";
    d.print();
    cout << "----Matrix Multiplication----\n";
    e.print();
    return 0;
}