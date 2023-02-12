#ifndef DE_H
#define DE_H

#include <sys/types.h>

// TODO : sizeof(long)でいいか確認する。
#define WORD_SIZE sizeof(long)

#define DE_CMD_OUTPUT_END "---DE_CMD_OUTPUT_END---"
#define DE_CMD_INVALID NULL
#define DE_CMD_SINGLE_STEP "s"

#define REGS_JSON_FILE "json/de_output/regs.json"
#define STACK_JSON_FILE "json/de_output/stack.json"

void print_regs(pid_t pid);
void print_regs_to_json_file(pid_t pid);
// rip
void set_rip(pid_t pid, unsigned long long rip);
unsigned long long get_rip(pid_t pid);
// rsp
unsigned long long get_rsp(pid_t pid);

void print_mem(pid_t pid, void *addr, size_t n);
void print_stack(pid_t pid);
void print_stack_to_json_file(pid_t pid);

#endif  // DE_H
