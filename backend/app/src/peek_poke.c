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

  FILE *fp = fopen(STACK_JSON_FILE, "w+");
  if (fp == NULL) {
    fprintf(stderr, "Error : print_stack_to_json_file fopen\n");
    exit(1);
  }

  fprintf(fp, "[\n");
  for (size_t i = 0; i < cnt; i++) {
    bool is_last = i == cnt - 1;
    long data = x_ptrace_get_data_from_addr(pid, addr);
    fprintf(fp, "  { \"addr\": \"%p\", \"val\": \"%lx\" }", addr, data);
    fprintf(fp, "%s", is_last ? "\n" : ",\n");
    addr += WORD_SIZE;
  }
  fprintf(fp, "]\n");

  fclose(fp);
}
