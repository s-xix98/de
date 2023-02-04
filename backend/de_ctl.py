import sys
import pexpect
import subprocess

DE_CMD_OUTPUT_END = "---DE_CMD_OUTPUT_END---"

OBJDUMP_SECTION_STR = "Disassembly of section "


def make() -> bool:
    proc = subprocess.run("make", shell=True, cwd="app")


def get_objdump_output(path) -> str:
    proc = subprocess.run(f"objdump -DS -M intel {path}", shell=True, stdout=subprocess.PIPE)
    return proc.stdout.decode()


def parse_objdump_output(objdump_output: str):
    func_dic = {}

    section = ""
    func_name = ""
    dump_target_info = ""
    for line in objdump_output.splitlines():
        if line == "":
            continue
        if dump_target_info == "":
            dump_target_info = line
        elif line.startswith(OBJDUMP_SECTION_STR):
            # Disassembly of section .text: -> "text"
            section = line[len(OBJDUMP_SECTION_STR) - 1 : -1]
        elif line[0].isdigit():
            # 0000000000401106 <main>: -> func_addr "0000000000401106", "func_name" main
            splited_line = line.split()
            func_addr = int(splited_line[0], 16)
            func_name = splited_line[1][1:-2]
            func_dic[func_name] = {"section": section, "func_addr": func_addr, "code": []}
        else:
            func_dic[func_name]["code"].append(line)
    return func_dic


def get_func_addr(func_dic, target_func_name) -> int:
    target_func_dic = func_dic.get(target_func_name)
    if target_func_dic == None:
        return None
    return target_func_dic["func_addr"]


def get_main_addr(func_dic) -> int:
    return get_func_addr(func_dic, "main")


def show_asm_code(rip, objdump_output, output_range=5):
    objdump_output_splited = objdump_output.splitlines()

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

    objdump_output = get_objdump_output(target_path)
    func_dic = parse_objdump_output(objdump_output)

    connection = pexpect.spawn(f"./app/de {target_path}", encoding="utf-8")

    main_addr = get_main_addr(func_dic)
    if main_addr == None:
        print("Error : main addr not found")
        sys.exit(1)

    connection.sendline(str(hex(main_addr)[2:]))
    connection.expect(DE_CMD_OUTPUT_END)
    de_output = connection.before
    print(de_output)

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

        show_asm_code(rip, objdump_output)


def main():
    make()
    interactive()


if __name__ == "__main__":
    main()
