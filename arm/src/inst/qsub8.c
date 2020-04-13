#include "arm.h"

int32 arm_inst_qsub8(cpu_state_t *st, uint32 inst)
{
	loginst("qsub8", inst);

	if (!cond_ok())
		return EXEC_SUCCESS;

	//sbo
	if (inst_b4(8) != 0xf)
		return EXEC_UNPREDICTABLE;

	uint32 rn = inst_b4(16);
	uint32 rd = inst_b4(12);
	uint32 rm = inst_b4(0);
	bool issat;

	//pc
	if (rn == r_pc || rd == r_pc || rd == r_pc)
		return EXEC_UNPREDICTABLE;

	//低位结果
	int64 resLL = bitm(regvl(rn), 0, 7) - bitm(regvl(rm), 0, 7);
	uint32 LL = signed_sat(resLL, int_min(8), int_max(8), &issat);
	int64 resLH = bitm(regvl(rn), 8, 15) - bitm(regvl(rm), 8, 15);
	uint32 LH = signed_sat(resLH, int_min(8), int_max(8), &issat);
	//高位结果
	int64 resHL = bitm(regvl(rn), 16, 23) - bitm(regvl(rm), 16, 23);
	uint32 HL = signed_sat(resHL, int_min(8), int_max(8), &issat);
	int64 resHH = bitm(regvl(rn), 24, 31) - bitm(regvl(rm), 24, 31);
	uint32 HH = signed_sat(resHH, int_min(8), int_max(8), &issat);

	//结果综合
	regvs(rd, (HH << 24) | (HL << 16) | (LH << 8) | LL);

	return EXEC_SUCCESS;
}
