#include "arm.h"

int32 arm_inst_qsub(cpu_state_t *st, uint32 inst)
{
	loginst("qsub", inst);

	if (!cond_ok())
		return EXEC_SUCCESS;

	//sbz
	if (inst_b4(8) != 0)
		return EXEC_UNPREDICTABLE;

	uint32 rn = inst_b4(16);
	uint32 rd = inst_b4(12);
	uint32 rm = inst_b4(0);

	//pc
	if (rn == r_pc || rd == r_pc || rm == r_pc)
		return EXEC_UNPREDICTABLE;

	bool issat;

	int64 _res = regvl(rm) - regvl(rn);
	uint32 res = signed_sat(_res, int_min(32), int_max(32), &issat);
	regvs(rd, res);

	if (issat)
	{
		st->cpsr.q = true;
	}

	return EXEC_SUCCESS;
}
