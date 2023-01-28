#ifndef DE_H
#define DE_H

#include <sys/types.h>

// TODO : sizeof(long)でいいか確認する。
#define WORD_SIZE sizeof(long)

#define DE_CMD_OUTPUT_END "---DE_CMD_OUTPUT_END---"
#define DE_CMD_INVALID NULL
#define DE_CMD_SINGLE_STEP "s"

#define REGS_JSON_FILE "de_output_json/regs.json"

void print_regs(pid_t pid);
void print_regs_to_json_file(pid_t pid);
long get_rsp(pid_t pid);

#endif  // DE_H
