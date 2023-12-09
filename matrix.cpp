#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;

int row1, col1, row2, col2;
vector<vector<int>> firstmatrix, secondmatrix;

int readInput()
{
    // open file
    ifstream inputFile("Input.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open the file." << endl;
        return 0;
    }
    cout << "File opened successfully!" << endl;

    // read no of rows and columns of first matrix
    inputFile >> row1 >> col1;
    //cout << col1;
    //cout << std::endl;

    // reading first matrix
    firstmatrix.resize(row1, vector<int>(col1));
    for(int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            inputFile >> firstmatrix[i][j];
        }
    }

    // read no of rows and columns of second matrix
    inputFile >> row2 >> col2;
    //cout << row2 ;
    //cout << std::endl;

    // reading second matrix
    secondmatrix.resize(row2, vector<int>(col2));
    for(int i = 0; i < row2; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            inputFile >> secondmatrix[i][j];
        }
    }

    if ( col1 != row2)
    {
        cout << "No";
        return -1;
    }

    // close the file
    inputFile.close();


    return 0;
}

void print()
{

    // printing two matrices
    for(int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            cout << firstmatrix[i][j] << " ";
        }
        cout << std::endl;
    }

    cout << "----------\n" ;

    for(int i = 0; i < row2; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            cout << secondmatrix[i][j] << " ";
        }
        cout << std::endl;
    }

    cout << "----------\n" ;
}

vector<vector<int>> matrixMultiplyByElement()
{
    vector<vector<int>> resultmatrix;
    resultmatrix.resize(row1, vector<int>(col2));

    // initializing an array of threads (thread for each element of output matrix)
    vector<thread> threads(row1 * col2);
    int t = 0;

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            resultmatrix[i][j] = 0;
            // creation and addition of new thread at index t in the threads array
            // passing lambda function as arguments to the thread constructor
            // specifies how variables outside the lambda function should be captured
            // & indicates that all variables used in the lambda should be captured by reference
            threads[t] = thread{[&]()
            {
                // body of lambda function (thread logic)
                for(int k = 0; k < firstmatrix[0].size(); k++)
                    resultmatrix[i][j] += firstmatrix[i][k] * secondmatrix[k][j];
            }};
            // to ensure that the main thread waits for each created thread to finish its work before moving on
            threads[t].join();
            // to move on to next thread in the array
            t++;
        }
    }
    return resultmatrix;
}

vector<vector<int>> matrixMultiplyByRow()
{
    vector<vector<int>> resultmatrix;
    resultmatrix.resize(row1, vector<int>(col2));

    // initializing an array of threads (thread for each element of output matrix)
    vector<thread> threads (row1);

    int t = 0;

    for (int i = 0; i < row1; i++)
    {
        threads[t] = thread{[&]()
        {
            for (int j = 0; j < col2; j++)
            {
                resultmatrix[i][j] = 0;
                for (int k = 0; k < col1; k++)
                {
                    resultmatrix[i][j] += firstmatrix[i][k] * secondmatrix[k][j];
                }
            }
        }};
        threads[t].join();
        t++;
    }
    return resultmatrix;
}

int main()
{
    int y = readInput();
    if (y == -1)
    {
        return 0;
    }

    vector<vector<int>> byElement,byRow;

    auto start = chrono::steady_clock::now();
    byElement = matrixMultiplyByElement();
    auto end = chrono::steady_clock::now();
    auto byElementTime = end - start;

    start = chrono::steady_clock::now();
    byRow = matrixMultiplyByRow();
    end = chrono::steady_clock::now();
    auto byRowTime = end - start;

    cout << "By Row\n";

    for(int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            cout << byRow[i][j] << " ";
        }
        cout << std::endl;
    }
    auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(byRowTime);
    std::cout << "Time taken: " << seconds.count() << " seconds" << std::endl;

    cout << "By Element\n" ;
     for(int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            cout << byElement[i][j] << " ";
        }
        cout << std::endl;
    }
    seconds = std::chrono::duration_cast<std::chrono::duration<double>>(byElementTime);
    std::cout << "Time taken: " << seconds.count() << " seconds" << std::endl;


    return 0;
}
