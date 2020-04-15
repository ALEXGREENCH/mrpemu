#include "arm.h"

int32 arm_inst_uadd16(cpu_state_t *st, uint32 inst)
{
	loginst("uadd16", inst);

	if (!cond_ok())
		return EXEC_SUCCESS;

	//sbo
	if (inst_b4(8) != 0xf)
		return EXEC_UNPREDICTABLE;

	uint32 rn = inst_b4(16);
	uint32 rd = inst_b4(12);
	uint32 rm = inst_b4(0);

	uint32 ge;

	uint32 res0 = bitm(regv(rn), 0, 15) + bitm(regv(rm), 0, 15);
	if (carry16(res0))
		ge |= 0b0011;
	uint32 res16 = bitm(regv(rn), 16, 31) + bitm(regv(rm), 16, 31);
	if (carry16(res16))
		ge |= 0b1100;

	regv(rd) = res0 | (res16 << 16);

	return EXEC_SUCCESS;
}
