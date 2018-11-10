#include "ade32.h"

typedef struct {
	int	prefix_len;
	int	name_len;
	int	operand1_len;
	int	operand2_len;
	int	operand3_len;
	char	*prefix;
	char	*name;
	char	*operand1;
	char	*operand2;
	char	*operand3;
} instr_name;

int instr_decode (struct ade32_struct *diza, instr_name *name, unsigned long ip);

