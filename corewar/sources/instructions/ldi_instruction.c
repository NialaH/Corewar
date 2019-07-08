/*
** EPITECH PROJECT, 2018
** name
** File description:
** ldi instruction
*/

#include "corewar.h"

static int ldi_error(prog_t **prog, int i, int *values)
{
    if (prog[i]->instruction->params[0] == 'r') {
        if (!(values[0] >= 1 && values[0] <= 16)) {
            prog[i]->carry_flag = 1;
            return (-1);
        }
        values[0] = prog[i]->registre[values[0]];
    }
    if (prog[i]->instruction->params[1] == 'r') {
        if (!(values[1] >= 1 && values[1] <= 16)) {
            prog[i]->carry_flag = 1;
            return (-1);
        }
        values[1] = prog[i]->registre[values[1]];
    }
    return (0);
}

static void launch_ldi(int *memory, prog_t **prog, int i, int *values)
{
    int sum = 0;

    sum += get_mem_special_value(memory, ((prog[i]->pc + values[0]) % IDX_MOD)
    % MEM_SIZE, IND_SIZE);
    sum += values[1];
    if (!(values[2] >= 1 && values[2] <= 16)) {
        prog[i]->carry_flag = 1;
        return;
    }
    sum = (sum < 0) ? MEM_SIZE + sum : sum;
    prog[i]->registre[values[2]] = get_memvalue(memory, sum % MEM_SIZE);
    free(values);
}

void ldi_instruction(int *memory, prog_t **prog, int i)
{
    int *values;
    int size = 0;

    values = get_params_value(prog[i]->instruction->inst,
    prog[i]->instruction->params);
    for (; values[size] != -1; size++);
    if (size != 3) {
        free(values);
        prog[i]->carry_flag = 1;
        return;
    }
    if (ldi_error(prog, i, values) == -1) {
        free(values);
        prog[i]->carry_flag = 1;
        return;
    }
    launch_ldi(memory, prog, i, values);
}
