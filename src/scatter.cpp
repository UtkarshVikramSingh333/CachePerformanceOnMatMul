#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() 
{

}

void parsec_roi_end() 
{
	
}

struct Result {
	vector< vector<int> > A;
};

Result read(string filename) {
	vector< vector<int> > A;
	Result ab;
	string line;
	ifstream infile;
	infile.open (filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		A.resize(A.size() + 1);
		int a, j = 0;
		while (iss >> a) {
			A[i].push_back(a);
			j++;
		}
		i++;
	}
	infile.close();
	ab.A = A;
	return ab;
}

vector<vector<int>> scatterMatrix(vector<vector<int>> targetMatrix) {
    int matrixSize = targetMatrix.size(); // Dimension of the square matrix
    const int totalEntries = 1000;       // Number of entries to scatter

    vector<int> indexList(totalEntries), valueList(totalEntries);

   
    srand(static_cast<unsigned int>(time(0)));

    
    for (int i = 0; i < totalEntries; ++i) {
        indexList[i] = rand() % (matrixSize * matrixSize);
        valueList[i] = rand();
    }

    
    for (int i = 0; i < totalEntries; ++i) {
        int row = indexList[i] / matrixSize;
        int col = indexList[i] % matrixSize;
        targetMatrix[row][col] = valueList[i];
    }

    return targetMatrix;
}

void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

int main (int argc, char* argv[]) {
	srand(time(0));
	string filename;
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}
	Result result = read (filename);
    parsec_roi_begin();
	vector< vector<int> > C = scatterMatrix(result.A);
    parsec_roi_end();
	//printMatrix(C);
	return 0;
}
