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
	
	z = MixMaxCutSparse( );

	(find max_{z} < S , zz'> )


Usage of MixMaxCutComposite (in matlab):
	
	z = MixMaxCutComposite(S, b, L, sdp_rank, iter)

	(find max_{z} < S + b*LL' , zz'> )
