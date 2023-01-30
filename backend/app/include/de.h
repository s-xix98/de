#ifndef DE_H
#define DE_H

#include <sys/types.h>

// TODO : sizeof(long)でいいか確認する。
#define WORD_SIZE sizeof(long)

#define DE_CMD_OUTPUT_END "---DE_CMD_OUTPUT_END---"
#define DE_CMD_INVALID NULL
#define DE_CMD_SINGLE_STEP "s"

#define REGS_JSON_FILE "de_output_json/regs.json"
#define STACK_JSON_FILE "de_output_json/stack.json"

void print_regs(pid_t pid);
void print_regs_to_json_file(pid_t pid);
unsigned long long get_rsp(pid_t pid);
unsigned long long get_rbp(pid_t pid);
unsigned long long get_rip(pid_t pid);

void print_mem(pid_t pid, void *addr, size_t n);
void print_stack(pid_t pid);
void print_stack_to_json_file(pid_t pid);

void print_bt(pid_t pid);

#endif  // DE_H
