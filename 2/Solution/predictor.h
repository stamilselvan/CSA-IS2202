#ifndef _PREDICTOR_H_
#define _PREDICTOR_H_
#define PC_LSB_TO_COMPARE 13
#include "utils.h"
#include "tracer.h"

class PREDICTOR{
	private:
		UINT32 *crr; 	// correlation register table
		UINT32 *gpt; 	// Global pattern table
		UINT32 historyLength;	// history length
		UINT32 numGptEntries;	// entries in gpt	
		UINT32 numCrrEtries;	// No.of crr entries
	
	public:
		PREDICTOR(void);
		bool GetPrediction(UINT32 PC);
		void UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget);
		void TrackOtherInst(UINT32 PC, OpType opType, UINT32 branchTarget);
};

#endif