#define REG_PC  (REG_CFP->pc)
#define GET_PC_COUNT()     (REG_PC - GET_ISEQ()->iseq_encoded)
