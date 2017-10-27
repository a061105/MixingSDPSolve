# MixingSDPSolve

To Compile: (in matlab)
	
	mex MixMaxCutDense.cpp 
	mex MixMaxCut.cpp
	mex MixMaxCutSparse.cpp
	mex MixMaxCutComposite.cpp


Usage of MixMaxCutDense (in matlab):

	z = MixMaxCutDense( C, sdp_rank, iter );
	
	(find max_{z} tr(z'Cz))



Usage of MixMaxCut (in matlab):

	z = MixMaxCut( A, sdp_rank, iter );

	(find max_{z} tr(z'AA'z)))



Usage of MixMaxCutSparse (in matlab):
	
	Usage:function z = MixMaxCutSparse(C_sparse, sdp_rank, iter)
	(find max_{z} < C_sparse , zz'> )


Usage of MixMaxCutComposite (in matlab):
	
	z = MixMaxCutComposite(C_sparse, b, L, sdp_rank, iter)

	(find max_{z} < C_sparse + b*LL' , zz'> )
