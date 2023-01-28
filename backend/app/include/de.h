#ifndef DE_H
#define DE_H

#include <sys/types.h>

#define REGS_JSON_FILE "de_output_json/regs.json"

void print_regs(pid_t pid);
void print_regs_to_json_file(pid_t pid);
long get_rsp(pid_t pid);

#endif  // DE_H
