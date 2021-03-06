#include "arm.h"

int32 arm_inst_saddsubx(cpu_state_t *st, uint32 inst)
{
	loginst("saddsubx", inst);

	if (!cond_ok())
		return EXEC_SUCCESS;
	//sbo
	if (inst_b4(8) != 0xf)
		return EXEC_UNPREDICTABLE;

	//必要值
	uint32 rn = inst_b4(16);
	uint32 rd = inst_b4(12);
	uint32 rm = inst_b4(0);

	uint8 ge = 0b0000;
	int32 sum;
	uint32 result = 0x00000000;

	int16 rn0 = bitm(regv(rn), 0, 15);
	int16 rn16 = bitm(regv(rn), 16, 31);

	int16 rm0 = bitm(regv(rm), 0, 15);
	int16 rm16 = bitm(regv(rm), 16, 31);

	sum = rn16 + rm0;
	result |= (sum & 0x0000ffff) << 16;
	if (sum >= 0)
		ge |= 0b1100;

	sum = rn0 - rm16;
	result |= (sum & 0x0000ffff);
	if (sum >= 0)
		ge |= 0b0011;

	regv(rd) = result;
	st->cpsr.ge = ge;

	return EXEC_SUCCESS;
}
