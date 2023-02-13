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
#ifndef IS_ARM
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
#else
  printf("RSP : 0x%llx\n", regs.sp);
  printf("RIP : 0x%llx\n", regs.pc);
  int regs_count = 31;
  for (int i = 0; i < regs_count; i++) {
    printf("REGS[%d] : 0x%llx\n", i, regs.regs[i]);
  }
#endif
  printf("--- --- ---\n");
  printf("\n");
}

void print_reg_to_fp(FILE *fp, char *reg_name, unsigned long long val,
                     char *sep) {
  fprintf(fp, "  {\"name\" : \"%s\", \"val\" : \"0x%llx\"}", reg_name, val);
  fprintf(fp, "%s\n", sep);
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
#ifndef IS_ARM
  print_reg_to_fp(fp, "RAX", regs.rax, ",");
  print_reg_to_fp(fp, "RBX", regs.rbx, ",");
  print_reg_to_fp(fp, "RCX", regs.rcx, ",");
  print_reg_to_fp(fp, "RDX", regs.rdx, ",");
  print_reg_to_fp(fp, "RSI", regs.rsi, ",");
  print_reg_to_fp(fp, "RDI", regs.rdi, ",");
  print_reg_to_fp(fp, "RBP", regs.rbp, ",");
  print_reg_to_fp(fp, "RSP", regs.rsp, ",");
  print_reg_to_fp(fp, "RIP", regs.rip, ",");
  print_reg_to_fp(fp, "R8 ", regs.r8, ",");
  print_reg_to_fp(fp, "R9 ", regs.r9, ",");
  print_reg_to_fp(fp, "R10", regs.r10, ",");
  print_reg_to_fp(fp, "R11", regs.r11, ",");
  print_reg_to_fp(fp, "R12", regs.r12, ",");
  print_reg_to_fp(fp, "R13", regs.r13, ",");
  print_reg_to_fp(fp, "R14", regs.r14, ",");
  print_reg_to_fp(fp, "R15", regs.r15, "");
#else
  print_reg_to_fp(fp, "RSP", regs.sp, ",");
  print_reg_to_fp(fp, "RIP", regs.pc, ",");
  int regs_count = 31;
  for (int i = 0; i < regs_count; i++) {
    char *sep = i != 30 ? "," : "";
    print_reg_to_fp(fp, "REGS", regs.regs[i], sep);
  }
#endif
  fprintf(fp, "]\n");

  fclose(fp);
}

// rip
// ------------------------------------------------------------------------------------------
void set_rip(pid_t pid, unsigned long long rip) {
  struct user_regs_struct regs;

  x_ptrace_get_register_info(pid, &regs);
#ifndef IS_ARM
  regs.rip = rip;
#else
  regs.pc = rip;
#endif
  x_ptrace_set_register_info(pid, &regs);
}

unsigned long long get_rip(pid_t pid) {
  struct user_regs_struct regs;

  x_ptrace_get_register_info(pid, &regs);

#ifndef IS_ARM
  return regs.rip;
#else
  return regs.pc;
#endif
}

// rsp
// ------------------------------------------------------------------------------------------
unsigned long long get_rsp(pid_t pid) {
  struct user_regs_struct regs;

  x_ptrace_get_register_info(pid, &regs);

#ifndef IS_ARM
  return regs.rsp;
#else
  return regs.sp;
#endif
}
