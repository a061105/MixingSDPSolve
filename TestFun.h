#include "Function.h"

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
