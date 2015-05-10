#include "predictor.h"
#define GPT_CTR_MAX 3
#define GPT_CTR_INIT 2
#define CRR_CTR_INIT 65535
#define CRR_CTR_MAX 131071
#define HIST_LEN 17
#define PC_AND 8191
#define CRR_AND 131071

PREDICTOR::PREDICTOR(void) {
	historyLength = HIST_LEN;
	numGptEntries = (1<<HIST_LEN);
	numCrrEtries  = (1<<PC_LSB_TO_COMPARE);
	gpt = new UINT32[numGptEntries];
	crr = new UINT32[1<<PC_LSB_TO_COMPARE];
	UINT32 ii;

	for(ii=0; ii< numGptEntries; ii++){
		gpt[ii]=GPT_CTR_INIT;
	}

	for(ii=0; ii< numCrrEtries; ii++){
		crr[ii]=CRR_CTR_INIT;
	}
}

bool PREDICTOR::GetPrediction(UINT32 PC) {
	UINT32 gptIndex	= crr[PC&PC_AND] & CRR_AND; // Index last 13 bits of PC 
	UINT32 gptCounter = gpt[gptIndex];
	
	if(gptCounter > GPT_CTR_MAX/2){
		return TAKEN;
	}else{
		return NOT_TAKEN;
	}
}

void PREDICTOR::UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget) {
	UINT32 gptIndex	= crr[PC&PC_AND] & CRR_AND;
	UINT32 gptCounter = gpt[gptIndex];
	// update the GPT
	if(resolveDir == TAKEN){
		gpt[gptIndex] = SatIncrement(gptCounter, GPT_CTR_MAX);
	}else{
		gpt[gptIndex] = SatDecrement(gptCounter);
	}

	// update the CRR
	crr[PC&PC_AND] = (gptIndex << 1);
	if(resolveDir == TAKEN){
		crr[PC&PC_AND]++;
	}
}
void PREDICTOR::TrackOtherInst(UINT32 PC, OpType opType, UINT32 branchTarget) {
	return;
}