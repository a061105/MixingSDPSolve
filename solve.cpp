#include "MaxCutSolve.h"
#include "IQPSolve.h"
#include "LowRankFunc.h"

int main(){
	
	Matrix A;
	int N, D;
	readMat( "A.txt", N, D, A );
	
	int K = 3;
	ExtensibleFunction* fun = new LowRankFunc(N, D, K, A);
	
	IQPSolve* solve = new IQPSolve();
	Vector x;
	solve->solve(fun, x);

	for(int i=0;i<N;i++)
		cerr << x[i] << " ";
	cerr << endl;
}
