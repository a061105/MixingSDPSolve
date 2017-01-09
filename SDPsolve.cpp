#include "SDPsolve.h"

class TestFun : public Function{
	public:
	TestFun(int N, int K, Matrix& C){
		
		_N = N;
		_K = K;
		_X.resize(N);
		_C = C;
	}

	virtual void getDim(int& N, int& K){
		N = _N;
		K = _K;
	}
	virtual void setValues(int i, Vector& xi){
		_X[i] = xi;
	}
	virtual void grad(int i, Vector& g){
		
		g.resize(_K,0.0);
		for(int j=0;j<_N;j++){
			for(int k=0;k<_K;k++){
				g[k] += _C[i][j]*_X[j][k];
			}
		}
	}
	virtual double funVal(){
		double sum = 0.0;
		for(int i=0;i<_N;i++)
			for(int j=0;j<_N;j++)
				for(int k=0;k<_K;k++)
					sum += _C[i][j]*_X[i][k]*_X[j][k];
				
		return sum;
	}

	private:
	Matrix _X;
	Matrix _C;
	int _N;
	int _K;
};

int main(){
	
	Matrix C;
	int N;
	readMat( "C.txt", N, C );
	int K = 2;
	Function* fun = new TestFun(N, K, C);
	
	SDPSolve* solve = new MixSDPSolve();
	Matrix X;
	solve->solve(fun, X);
}
