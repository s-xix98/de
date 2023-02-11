#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/user.h>

#include "de.h"
#include "x_ptrace.h"

void print_regs(pid_t pid) {
  struct user_regs_struct regs;

  x_ptrace_get_register_info(pid, &regs);

  printf("--- print_registers ---\n");
  printf("RAX : 0x%llx\n", regs.rax);
  printf("RBX : 0x%llx\n", regs.rbx);
  printf("RCX : 0x%llx\n", regs.rcx);
  printf("RDX : 0x%llx\n", regs.rdx);
  printf("RSI : 0x%llx\n", regs.rsi);
  printf("RDI : 0x%llx\n", regs.rdi);
  printf("RBP : 0x%llx\n", regs.rbp);
  printf("RSP : 0x%llx\n", regs.rsp);
  printf("RIP : 0x%llx\n", regs.rip);
  printf("R8  : 0x%llx\n", regs.r8);
  printf("R9  : 0x%llx\n", regs.r9);
  printf("R10 : 0x%llx\n", regs.r10);
  printf("R11 : 0x%llx\n", regs.r11);
  printf("R12 : 0x%llx\n", regs.r12);
  printf("R13 : 0x%llx\n", regs.r13);
  printf("R14 : 0x%llx\n", regs.r14);
  printf("R15 : 0x%llx\n", regs.r15);
  printf("--- --- ---\n");
  printf("\n");
}

void print_regs_to_json_file(pid_t pid) {
  FILE *fp;
  struct user_regs_struct regs;

  fp = fopen(REGS_JSON_FILE, "w+");
  if (fp == NULL) {
    fprintf(stderr, "Error : print_regs_to_json_file fopen\n");
    exit(1);
  }

  x_ptrace_get_register_info(pid, &regs);

  fprintf(fp, "[\n");
  fprintf(fp, "  {\"name\" : \"RAX\", \"val\" : \"0x%llx\"},\n", regs.rax);
  fprintf(fp, "  {\"name\" : \"RBX\", \"val\" : \"0x%llx\"},\n", regs.rbx);
  fprintf(fp, "  {\"name\" : \"RCX\", \"val\" : \"0x%llx\"},\n", regs.rcx);
  fprintf(fp, "  {\"name\" : \"RDX\", \"val\" : \"0x%llx\"},\n", regs.rdx);
  fprintf(fp, "  {\"name\" : \"RSI\", \"val\" : \"0x%llx\"},\n", regs.rsi);
  fprintf(fp, "  {\"name\" : \"RDI\", \"val\" : \"0x%llx\"},\n", regs.rdi);
  fprintf(fp, "  {\"name\" : \"RBP\", \"val\" : \"0x%llx\"},\n", regs.rbp);
  fprintf(fp, "  {\"name\" : \"RSP\", \"val\" : \"0x%llx\"},\n", regs.rsp);
  fprintf(fp, "  {\"name\" : \"RIP\", \"val\" : \"0x%llx\"},\n", regs.rip);
  fprintf(fp, "  {\"name\" : \"R8 \", \"val\" : \"0x%llx\"},\n", regs.r8);
  fprintf(fp, "  {\"name\" : \"R9 \", \"val\" : \"0x%llx\"},\n", regs.r9);
  fprintf(fp, "  {\"name\" : \"R10\", \"val\" : \"0x%llx\"},\n", regs.r10);
  fprintf(fp, "  {\"name\" : \"R11\", \"val\" : \"0x%llx\"},\n", regs.r11);
  fprintf(fp, "  {\"name\" : \"R12\", \"val\" : \"0x%llx\"},\n", regs.r12);
  fprintf(fp, "  {\"name\" : \"R13\", \"val\" : \"0x%llx\"},\n", regs.r13);
  fprintf(fp, "  {\"name\" : \"R14\", \"val\" : \"0x%llx\"},\n", regs.r14);
  fprintf(fp, "  {\"name\" : \"R15\", \"val\" : \"0x%llx\"}\n", regs.r15);
  fprintf(fp, "]\n");

  fclose(fp);
}

unsigned long long get_rsp(pid_t pid) {
  struct user_regs_struct regs;

  x_ptrace_get_register_info(pid, &regs);

  return regs.rsp;
}
