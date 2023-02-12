#include <elf.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/user.h>
#include <unistd.h>

#include "error.h"

// long ptrace(enum ptrace_request request, pid_t pid, void *addr, void *data);

// PTRACE_CONT
// プロセスを再開させる
void x_ptrace_cont_process(pid_t pid) {
  long ret = ptrace(PTRACE_CONT, pid, NULL, NULL);
  if (ret == -1) {
    err_exit(__func__);
  }
}

// PTRACE_SINGLESTEP
// 1命令のみ実行
void x_ptrace_run_single_step(pid_t pid) {
  long ret = ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
  if (ret == -1) {
    err_exit(__func__);
  }
}

// PTRACE_PEEKTEXT
// アドレスからワードを読み出す
long x_ptrace_get_data_from_addr(pid_t pid, void *addr) {
  errno = 0;
  long data = ptrace(PTRACE_PEEKTEXT, pid, addr, NULL);
  if (data == -1 && errno != 0) {
    err_exit(__func__);
  }
  return data;
}

// PTRACE_POKETEXT
// アドレスにデータセット
// TODO : long ok ?
void x_ptrace_set_data_to_addr(pid_t pid, void *addr, long data) {
  long ret = ptrace(PTRACE_POKETEXT, pid, addr, data);
  if (ret == -1) {
    err_exit(__func__);
  }
}

// PTRACE_GETREGS
// レジスタ情報の取得
#ifdef PTRACE_GETREGS
void x_ptrace_get_register_info(pid_t pid, struct user_regs_struct *regs) {
  long ret = ptrace(PTRACE_GETREGS, pid, NULL, regs);
  if (ret == -1) {
    err_exit(__func__);
  }
}
#else
void x_ptrace_get_register_info(pid_t pid, struct user_regs_struct *regs) {
  struct iovec iov;
  iov.iov_len = sizeof(struct user_regs_struct);
  iov.iov_base = regs;
  long ret = ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &iov);
  if (ret == -1) {
    err_exit(__func__);
  }
}
#endif

// PTRACE_SETREGS
// レジスタに値をセット
#ifdef PTRACE_SETREGS
void x_ptrace_set_register_info(pid_t pid, struct user_regs_struct *regs) {
  long ret = ptrace(PTRACE_SETREGS, pid, NULL, regs);
  if (ret == -1) {
    err_exit(__func__);
  }
}
#else
void x_ptrace_set_register_info(pid_t pid, struct user_regs_struct *regs) {
  struct iovec iov;
  iov.iov_len = sizeof(struct user_regs_struct);
  iov.iov_base = regs;
  long ret = ptrace(PTRACE_SETREGSET, pid, NT_PRSTATUS, &iov);
  if (ret == -1) {
    err_exit(__func__);
  }
}
#endif
