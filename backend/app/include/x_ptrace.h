#ifndef X_PTRACE_H
#define X_PTRACE_H

#include <sys/types.h>

// PTRACE_CONT
void x_ptrace_cont_process(pid_t pid);

// PTRACE_SINGLESTEP
void x_ptrace_run_single_step(pid_t pid);

// PTRACE_PEEKTEXT
long x_ptrace_get_data_from_addr(pid_t pid, void *addr);

// PTRACE_POKETEXT
void x_ptrace_set_data_to_addr(pid_t pid, void *addr, long data);

// PTRACE_GETREGS
void x_ptrace_get_register_info(pid_t pid, struct user_regs_struct *regs);

// PTRACE_SETREGS
void x_ptrace_set_register_info(pid_t pid, struct user_regs_struct *regs);

#endif  // X_PTRACE_H
