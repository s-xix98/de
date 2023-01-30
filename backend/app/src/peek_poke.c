#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "de.h"
#include "x_ptrace.h"

void print_mem(pid_t pid, void *addr, size_t n) {
  size_t cnt = n / WORD_SIZE;

  for (size_t i = 0; i < cnt; i++) {
    long data = x_ptrace_get_data_from_addr(pid, addr);
    printf("%p | 0x%lx\n", addr, data);
    addr += WORD_SIZE;
  }
}

void print_stack(pid_t pid) {
  unsigned long long rsp = get_rsp(pid);
  size_t print_stack_size = 64;

  printf("rsp : %llx\n", rsp);
  printf("--- print stack ---\n");
  print_mem(pid, (void *)rsp, print_stack_size);
  printf("\n");
}

void print_stack_to_json_file(pid_t pid) {
  unsigned long long rsp = get_rsp(pid);
  void *addr = (void *)rsp;
  size_t print_stack_size = 64;
  size_t cnt = print_stack_size / WORD_SIZE;

  FILE *output_file = fopen(STACK_JSON_FILE, "w+");
  if (output_file == NULL) {
    fprintf(stderr, "Error : print_stack_to_json_file fopen\n");
    exit(1);
  }

  fprintf(output_file, "{\n");
  fprintf(output_file, "  \"stack\": [\n");
  for (size_t i = 0; i < cnt; i++) {
    bool is_last = i == cnt - 1;
    long data = x_ptrace_get_data_from_addr(pid, addr);
    fprintf(output_file, "    { \"%p\": \"%lx\" }", addr, data);
    fprintf(output_file, "%s", is_last ? "\n" : ",\n");
    addr += WORD_SIZE;
  }
  fprintf(output_file, "  ]\n");
  fprintf(output_file, "}\n");

  fclose(output_file);
}

void print_bt(pid_t pid) {
  unsigned long long rbp = get_rbp(pid);

  printf("--- print bt ---\n");
  printf("0x%llx\n", get_rip(pid));
  while (1) {
    // TODO : 終了条件調べる, 多分こいつは argc
    if (rbp == 0x1) {
      break;
    }
    long retaddr = x_ptrace_get_data_from_addr(pid, (void *)rbp + WORD_SIZE);
    rbp = x_ptrace_get_data_from_addr(pid, (void *)rbp);
    printf("0x%llx\n", (unsigned long long)retaddr);
  }
  printf("\n");
}
