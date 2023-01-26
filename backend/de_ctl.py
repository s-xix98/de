import sys
import pexpect
import subprocess

DE_CMD_OUTPUT_END = "---DE_CMD_OUTPUT_END---"


def make() -> bool:
    proc = subprocess.run("make", shell=True, cwd="app")


def get_objdump_output(path) -> str:
    proc = subprocess.run(f"objdump -DS -M intel {path}", shell=True, stdout=subprocess.PIPE)
    return proc.stdout.decode()


def show_asm_code(rip, objdump_output_splited, output_range=5):
    idx = 0
    for line in objdump_output_splited:
        # TODO : "  " objdump の 出力に依存している ちゃんとパースして消す
        if "  " + str(hex(rip))[2:] in line:
            start = max(0, idx - output_range)
            end = min(len(objdump_output_splited), idx + output_range + 1)
            for i in range(start, end):
                if i == idx:
                    print(f"==> {objdump_output_splited[i]}")
                else:
                    print(f"    {objdump_output_splited[i]}")
            return
        idx += 1


def get_rip(s) -> int:
    for line in s.splitlines():
        if "RIP" in line:
            rip = int(line.split()[2], 16)
            return rip
    return None


def interactive():
    target_path = "./app/target"
    objdump_output_splited = get_objdump_output(target_path).splitlines()
    connection = pexpect.spawn(f"./app/de {target_path}", encoding="utf-8")
    while True:
        connection.sendline(input())
        connection.expect(DE_CMD_OUTPUT_END)
        de_output = connection.before

        print(de_output)

        rip = get_rip(de_output)
        if rip == None:
            continue

        print("RIP :", hex(rip))
        print()

        show_asm_code(rip, objdump_output_splited)


def main():
    make()
    interactive()


if __name__ == "__main__":
    main()
