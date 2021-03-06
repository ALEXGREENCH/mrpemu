#include "arm.h"

int32 arm_inst_ldm_2(cpu_state_t *st, uint32 inst)
{
	loginst("ldm2", inst);

	if (!cond_ok())
		return EXEC_SUCCESS;

	//rn不能是pc
	ldm_rn_pc_check();

	//TODO 内存权限检测

	//计算地址
	uint32 start_address, end_address;
	addr_mode_4(st, inst, &start_address, &end_address);

	//拷贝
	uint32 address = start_address;
	for (uint32 i = 0; i <= 14; i++)
	{
		if (has_reg_m4(i))
		{
			st->registers[i] = mem_ld32(st->mem, address);
			address += 4;
		}
	}

	return EXEC_SUCCESS;
}
