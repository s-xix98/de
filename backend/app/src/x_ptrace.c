#include <errno.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <unistd.h>

// long ptrace(enum ptrace_request request, pid_t pid, void *addr, void *data);

// PTRACE_CONT
// プロセスを再開させる
void x_ptrace_cont_process(pid_t pid) {
  long ret = ptrace(PTRACE_CONT, pid, NULL, NULL);
  if (ret == -1) {
    exit(1);
  }
}

// PTRACE_SINGLESTEP
// 1命令のみ実行
void x_ptrace_run_single_step(pid_t pid) {
  long ret = ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
  if (ret == -1) {
    exit(1);
  }
}

// PTRACE_PEEKTEXT
// アドレスからワードを読み出す
long x_ptrace_get_data_from_addr(pid_t pid, void *addr) {
  errno = 0;
  long data = ptrace(PTRACE_PEEKTEXT, pid, addr, NULL);
  if (data == -1 && errno != 0) {
    exit(1);
  }
  return data;
}

// PTRACE_POKETEXT
// アドレスにデータセット
// TODO : long ok ?
void x_ptrace_set_data_to_addr(pid_t pid, void *addr, long data) {
  long ret = ptrace(PTRACE_POKETEXT, pid, addr, data);
  if (ret == -1) {
    exit(1);
  }
}

// PTRACE_GETREGS
// レジスタ情報の取得
void x_ptrace_get_register_info(pid_t pid, struct user_regs_struct *regs) {
  long ret = ptrace(PTRACE_GETREGS, pid, NULL, regs);
  if (ret == -1) {
    exit(1);
  }
}

// PTRACE_SETREGS
// レジスタに値をセット
void x_ptrace_set_register_info(pid_t pid, struct user_regs_struct *regs) {
  long ret = ptrace(PTRACE_SETREGS, pid, NULL, regs);
  if (ret == -1) {
    exit(1);
  }
}
