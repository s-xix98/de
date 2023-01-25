import sys
import pexpect
import subprocess

DE_CMD_OUTPUT_END = "---DE_CMD_OUTPUT_END---"


def make() -> bool:
    proc = subprocess.run("make", shell=True, cwd="app")


def interactive():
    connection = pexpect.spawn("./app/de ./app/target", encoding="utf-8")
    while True:
        s = input()
        print("de_ctl input : ", s)
        print()
        connection.sendline(s)
        connection.expect(DE_CMD_OUTPUT_END)
        print(connection.before)


def main():
    make()
    interactive()


if __name__ == "__main__":
    main()
