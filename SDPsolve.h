#include <iostream>
#include "util.h"

using namespace std;

/** A Max-Cut SDP function of the form:
 *
 *  tr(X'CX)
 *
 *  where X:N*K and C is N*N.
 */
class Function{

	public:
	
	/* Get the dimension of the problem.
	 */
	virtual void getDim(int& N, int& K) = 0;
	/* Set the values of X_{i,:}.
	 */
	virtual void setValues(int i, Vector& xi) = 0;
	
	/** Given an index i, get current gradient [CX]_{i,:}.
	 */
	virtual void grad(int i, Vector& g) = 0;
	
	/* Compute the current function value tr(X'CX).
	 */ 
	virtual double funVal() = 0;
};

/** A solver that finds
 *  
 *  	X* = argmax_{X}  tr(X'*C*X)
 *
 *  given an objective function.
 */
class SDPSolve{
	
	public:
	virtual void solve(Function* f, Matrix& X) = 0;
};

class MixSDPSolve: public SDPSolve{
	public:
	
	virtual void solve(Function* f, Matrix& X){
		
		int N, K;
		f->getDim(N, K);
		
		//random initialize
		X.resize(N);
		for(int i=0;i<N;i++){
			
			X[i].resize(K);
			randn(X[i]);
			
			f->setValues(i, X[i]);
		}
		
		//main loop
		vector<int> indexes;
		indexes.resize(N);
		for(int i=0;i<N;i++)
			indexes[i] = i;
		
		Vector g;
		g.resize(K);
		
		int max_iter = 5;
		int iter=0;
		while(iter<max_iter){
			cerr << iter << endl;
			random_shuffle(indexes.begin(), indexes.end());
			for(int r=0;r<N;r++){
				
				int i = indexes[r];
				
				f->grad(i, g);
				normalize(g, X[i]);
				
				f->setValues(i, X[i]);
				if( iter % 1 == 0 )
					cerr << "iter=" << iter << ", obj=" <<  f->funVal()  << endl;
			}

			iter++;
		}
	}
};
