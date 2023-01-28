#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include "de.h"
#include "x_ptrace.h"

bool streq(const char *s1, const char *s2) {
  return !strcmp(s1, s2);
}

void single_step(pid_t pid) {
  int status;

  x_ptrace_run_single_step(pid);
  waitpid(pid, &status, 0);

  if (WIFEXITED(status)) {
    printf("WEXITSTATUS(status) :  %d\n", WEXITSTATUS(status));
    exit(0);
  }
  // TODO :
  if (WSTOPSIG(status) != SIGTRAP && WSTOPSIG(status) != SIGWINCH) {
    printf("WSTOPSIG(status)    : %d\n", WSTOPSIG(status));
    exit(0);
  }
}

long set_brk_point(pid_t pid, void *addr) {
  long original_inst = x_ptrace_get_data_from_addr(pid, addr);
  long trap_inst = (original_inst & ~0xff) | 0xCC;
  x_ptrace_set_data_to_addr(pid, addr, trap_inst);
  return original_inst;
}

void restore_ori_inst(pid_t pid, void *addr, long ori_inst) {
  struct user_regs_struct regs;

  x_ptrace_set_data_to_addr(pid, addr, ori_inst);
  x_ptrace_get_register_info(pid, &regs);
  regs.rip -= 1;
  x_ptrace_set_register_info(pid, &regs);
  x_ptrace_run_single_step(pid);
  wait(NULL);
}

void go_to_main(pid_t pid) {
  char *main_addr_line = readline("input main addr");
  void *main_addr = (void *)strtol(main_addr_line, NULL, 16);
  free(main_addr_line);

  printf("main addr %p\n", main_addr);
  printf(DE_CMD_OUTPUT_END "\n");
  fflush(stdout);

  long original_inst = set_brk_point(pid, main_addr);
  x_ptrace_cont_process(pid);
  wait(NULL);
  restore_ori_inst(pid, main_addr, original_inst);
}

void print_mem(pid_t pid, void *addr, size_t n) {
  size_t cnt = n / WORD_SIZE;

  for (size_t i = 0; i < cnt; i++) {
    long data = x_ptrace_get_data_from_addr(pid, addr);
    printf("%p | 0x%lx\n", addr, data);
    addr += WORD_SIZE;
  }
}

void print_stack(pid_t pid) {
  long rsp = get_rsp(pid);
  size_t print_stack_size = 64;

  printf("rsp : %lx\n", rsp);
  printf("--- print stack ---\n");
  print_mem(pid, (void *)rsp, print_stack_size);
  printf("\n");
}

void tracer(pid_t pid) {
  wait(NULL);

  go_to_main(pid);

  char *line;
  char *ex_cmd = NULL;
  char *prev_cmd = NULL;
  while (1) {
    line = readline("readline > ");
    if (line == NULL) {
      break;
    }
    if (streq(line, "") && prev_cmd != NULL) {
      ex_cmd = prev_cmd;
    } else {
      ex_cmd = line;
    }

    if (streq(ex_cmd, DE_CMD_SINGLE_STEP)) {
      prev_cmd = DE_CMD_SINGLE_STEP;
      single_step(pid);
      print_regs(pid);
      print_regs_to_json_file(pid);
      print_stack(pid);
    } else {
      prev_cmd = DE_CMD_INVALID;
      printf("Invalid command\n");
    }
    free(line);

    printf(DE_CMD_OUTPUT_END "\n");
    fflush(stdout);
  }
}

// 子プロセス
void tracee(char *target_process) {
  // 親プロセスにtraceされるという関係を明示
  ptrace(PTRACE_TRACEME, 0, 0, 0);
  execl(target_process, target_process, NULL);
  printf("Error : execl\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error : invalid Invalid argument\n");
    return 1;
  }

  char *target_process = argv[1];

  pid_t pid = fork();
  if (pid < 0) {
    printf("Error : fork fail\n");
    return 1;
  }
  if (pid > 0) {
    tracer(pid);
  } else {
    tracee(target_process);
  }
  return 0;
}
