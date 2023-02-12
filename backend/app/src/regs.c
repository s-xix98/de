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

void print_regs_to_json_file(pid_t pid) {
  FILE *output_file;
  struct user_regs_struct regs;

  output_file = fopen(REGS_JSON_FILE, "w+");
  if (output_file == NULL) {
    fprintf(stderr, "Error : print_regs_to_json_file fopen\n");
    exit(1);
  }

  x_ptrace_get_register_info(pid, &regs);

  fprintf(output_file, "{\n");
#ifndef IS_ARM
  fprintf(output_file, "  \"RAX\": \"0x%llx\",\n", regs.rax);
  fprintf(output_file, "  \"RBX\": \"0x%llx\",\n", regs.rbx);
  fprintf(output_file, "  \"RCX\": \"0x%llx\",\n", regs.rcx);
  fprintf(output_file, "  \"RDX\": \"0x%llx\",\n", regs.rdx);
  fprintf(output_file, "  \"RSI\": \"0x%llx\",\n", regs.rsi);
  fprintf(output_file, "  \"RDI\": \"0x%llx\",\n", regs.rdi);
  fprintf(output_file, "  \"RBP\": \"0x%llx\",\n", regs.rbp);
  fprintf(output_file, "  \"RSP\": \"0x%llx\",\n", regs.rsp);
  fprintf(output_file, "  \"RIP\": \"0x%llx\",\n", regs.rip);
  fprintf(output_file, "  \"R8\": \"0x%llx\",\n", regs.r8);
  fprintf(output_file, "  \"R9\": \"0x%llx\",\n", regs.r9);
  fprintf(output_file, "  \"R10\": \"0x%llx\",\n", regs.r10);
  fprintf(output_file, "  \"R11\": \"0x%llx\",\n", regs.r11);
  fprintf(output_file, "  \"R12\": \"0x%llx\",\n", regs.r12);
  fprintf(output_file, "  \"R13\": \"0x%llx\",\n", regs.r13);
  fprintf(output_file, "  \"R14\": \"0x%llx\",\n", regs.r14);
  fprintf(output_file, "  \"R15\": \"0x%llx\"\n", regs.r15);
#else
  fprintf(output_file, "  \"RSP\": \"0x%llx\",\n", regs.sp);
  fprintf(output_file, "  \"RIP\": \"0x%llx\",\n", regs.pc);
  int regs_count = 31;
  for (int i = 0; i < regs_count; i++) {
    fprintf(output_file, "  \"REGS[%d]\": \"0x%llx\",\n", i, regs.regs[i]);
  }
#endif
  fprintf(output_file, "}\n");

  fclose(output_file);
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
