#include "arm.h"

int32 arm_inst_uqadd16(cpu_state_t *st, uint32 inst)
{
	loginst("uqadd16", inst);

	if (!cond_ok())
		return EXEC_SUCCESS;

	//sbo
	if (inst_b4(8) != 0xf)
		return EXEC_UNPREDICTABLE;

	uint32 rn = inst_b4(16);
	uint32 rd = inst_b4(12);
	uint32 rm = inst_b4(0);

	bool issat;
	uint32 res0 = unsigned_sat(bitm(regv(rn), 0, 15) + bitm(regv(rm), 0, 15), 16, &issat);
	uint32 res16 = unsigned_sat(bitm(regv(rn), 16, 31) + bitm(regv(rm), 16, 31), 16, &issat);

	regv(rd) = res0 | (res16 << 16);

	return EXEC_SUCCESS;
}
