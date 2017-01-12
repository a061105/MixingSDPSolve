#include "MaxCutSolve.h"
#include "IQPSolve.h"

class TestFun : public ExtensibleFunction{
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
	
	virtual void Xtv(Vector& v, Vector& Xtv){
		Xtv.resize(_K);
		for(int k=0;k<_K;k++)
			Xtv[k] = 0.0;
		for(int i=0;i<_N;i++)
			for(int k=0;k<_K;k++)
				Xtv[k] += v[i]*_X[i][k];
	}

	virtual void setValues(int i, Vector::iterator xi_begin, Vector::iterator xi_end){
		_X[i] = Vector(xi_begin, xi_end);
	}
	
	virtual void setAllValues(double v){
		for(int i=0;i<_X.size();i++)
			for(int j=0;j<_X[i].size();j++)
				_X[i][j] = v;
	}
	
	virtual void setValue(int i, int k, double vik){
		_X[i][k] = vik;
	}
	
	virtual void sum_by_row(Vector::iterator s_begin, Vector::iterator s_end){
		
		assert((s_begin+_N)==s_end);
		
		for(int i=0;i<_N;i++){
			double sum = 0.0;
			for(int j=0;j<_N;j++)
				sum += _C[i][j];
			
			*(s_begin+i) = sum;
		}
	}


	virtual void grad(int i, Vector& g){
		
		g.resize(_K);
		for(int k=0;k<_K;k++)
			g[k] = 0.0;
		
		for(int j=0;j<_N;j++){
			
			if( j==i ) continue;
			
			for(int k=0;k<_K;k++){
				g[k] += _C[i][j]*_X[j][k];
			}
		}
	}
	virtual double funVal(){
		double obj = 0.0;
		for(int i=0;i<_N;i++){
			for(int j=0;j<_N;j++){
				double sum = 0.0;
				for(int k=0;k<_K;k++)
					sum += _X[i][k]*_X[j][k];

				obj += sum*_C[i][j];
			}
		}
				
		return obj;
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
	
	int K = 3;
	ExtensibleFunction* fun = new TestFun(N, K, C);
	
	IQPSolve* solve = new IQPSolve();
	Vector x;
	solve->solve(fun, x);
}
