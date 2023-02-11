import sys
import pexpect
import subprocess

DE_CMD_OUTPUT_END = "---DE_CMD_OUTPUT_END---"

OBJDUMP_SECTION_STR = "Disassembly of section "


class DE:
    def __init__(self, target_path):
        self.target_path = target_path
        self.objdump_output = get_objdump_output(target_path)
        self.func_dic, self.addr_dic = parse_objdump_output(self.objdump_output)
        print_func_lst(self.func_dic)
        self.connection = None

    def de_start(self):
        print("--- START ---")
        self.connection = pexpect.spawn(f"./app/de {self.target_path}", encoding="utf-8")
        main_addr = get_main_addr(self.func_dic)
        if main_addr == None:
            print("Error : main addr not found")
            sys.exit(1)
        self.connection.sendline(str(hex(main_addr)[2:]))
        self.connection.expect(DE_CMD_OUTPUT_END)
        de_output = self.connection.before
        print(de_output)

    def de_one_cmd(self, s):
        self.connection.sendline(s)
        self.connection.expect(DE_CMD_OUTPUT_END)
        de_output = self.connection.before

        print(de_output)

        rip = get_rip(de_output)
        if rip == None:
            print("Error : rip not found")
            return
        print("RIP :", hex(rip))
        print()

        exec_func_name = get_func_name_by_rip(self.addr_dic, rip)
        if exec_func_name == None:
            return
        show_asm_func_code(self.func_dic, rip, exec_func_name)


def make() -> bool:
    proc = subprocess.run("make", shell=True, cwd="app")
    return proc.returncode == 0


def get_objdump_output(path) -> str:
    proc = subprocess.run(f"objdump -DS -M intel --insn-width=10 {path}", shell=True, stdout=subprocess.PIPE)
    return proc.stdout.decode()


def parse_objdump_output(objdump_output: str):
    func_dic = {}
    addr_dic = {}

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
            # TODO : .debug_str の時など 邪魔なので弾いた方がいいかも
            splited_line = line.split(":", maxsplit=1)
            if len(splited_line) != 2:
                continue
            addr_dic[int(splited_line[0], 16)] = func_name
    return func_dic, addr_dic


def get_func_name_by_rip(addr_dic, rip):
    func_name = addr_dic.get(rip)
    if func_name == None:
        print("Error : func name not found", hex(rip))
        return None
    return func_name


def get_func_addr(func_dic, target_func_name) -> int:
    target_func_dic = func_dic.get(target_func_name)
    if target_func_dic == None:
        return None
    return target_func_dic["func_addr"]


def print_func_lst(func_dic: dict) -> None:
    print("--- PRINT_FUNC_LST ---")
    for key in func_dic.keys():
        print(f"{key[:30]:<30} : 0x{func_dic[key]['func_addr']:x}")
    print()


def get_main_addr(func_dic) -> int:
    return get_func_addr(func_dic, "main")


def show_asm_func_code(func_dic, rip, func_name):
    target_func_dic = func_dic[func_name]
    print(f"{func_name} RIP {hex(rip)}")
    print()
    for line in target_func_dic["code"]:
        if "  " + str(hex(rip))[2:] in line.split(":")[0]:
            print(f"==> {line}")
        else:
            print(f"    {line}")


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
    de_proc = DE("./app/target")
    de_proc.de_start()

    while True:
        s = input()
        de_proc.de_one_cmd(s)


def main():
    if make() == False:
        print("Error : make fail")
        sys.exit(1)
    interactive()


if __name__ == "__main__":
    main()
