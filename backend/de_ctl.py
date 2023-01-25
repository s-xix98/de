import sys
import pexpect
import subprocess

DE_END_CMD = "---DE_END_CMD---"


def make() -> bool:
    proc = subprocess.run("make", shell=True, cwd="app")


def interactive():
    connection = pexpect.spawn("./app/de ./app/target", encoding="utf-8")
    while True:
        s = input()
        print("de_ctl input : ", s)
        print()
        connection.sendline(s)
        connection.expect(DE_END_CMD)
        print(connection.before)


def main():
    make()
    interactive()


if __name__ == "__main__":
    main()
