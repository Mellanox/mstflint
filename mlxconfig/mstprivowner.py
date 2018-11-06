from __future__ import print_function

import argparse
import os
import subprocess
import sys
import tempfile

import tools_version

PROG = 'mlxprivowner'
TOOL_VERSION = "1.0.0"

CMD_HELP = """\
restrict:  Set host 1 (ARM) privileged, host 0 (x86_64) restricted.
privilege: Set host 1 (ARM) privileged, host 0 (x86_64) privileged
           (back to default).
"""

DESCRIPTION = """\
restrict or privilege owner
Note: New configurations takes effect immediately.
Note: a restricted host is not allowed to be port_owner, to own the tracer
      and to read physical port counters.

"""


def _log(level, msg, *args, **kw):
    if args:
        msg = msg % args
    print(level, msg, end=kw.get('end', '\n'))


def info(msg, *args, **kw):
    _log("-I-", msg, *args, **kw)


def error(msg, *args, **kw):
    _log("-E-", msg, *args, **kw)


class PrivilegeMgr(object):
    CMD_LINE = "mlxconfig -d %s -f %s --yes set_raw"
    TITLE = "MLNX_RAW_TLV_FILE\n"
    RESTRICT_BYTES = "0x03000204 0x07000083 0x00000000 0x1000000f"
    PRIVILEGE_BYTES = "0x03000204 0x07000083 0x00000000 0x00000000"

    def __init__(self, device, privilege):
        self._privilege = privilege
        self._device = device
        self._file_p = tempfile.NamedTemporaryFile(
            suffix='.raw', prefix="nvconfig_setting_")
        self._file_name = self._file_p.name

    def prepare(self):
        info("preparing configuration file...", end='')
        self._file_p.write(self.TITLE)
        if self._privilege:
            self._file_p.write(self.PRIVILEGE_BYTES)
        else:
            self._file_p.write(self.RESTRICT_BYTES)
        self._file_p.flush()
        print("Done!")

    @staticmethod
    def _exec_cmd(cmd):
        p = subprocess.Popen(cmd,
                             stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE,
                             universal_newlines=True,
                             shell=True)
        stdout, stderr = p.communicate()
        exit_code = p.wait()

        return (exit_code, stdout, stderr)

    def configure(self):
        info("configuring device...", end='')
        cmd = self.CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)

        if exit_code != 0:
            print("Failed")
            print(stdout + stderr)
        else:
            print("Done!")
        return exit_code

    def cleanup(self):
        self._file_p.close()
        if os.path.isfile(self._file_name):
            os.remove(self._file_name)


def parse_args():
    parser = argparse.ArgumentParser(
        prog=PROG, description=DESCRIPTION,
        formatter_class=argparse.RawTextHelpFormatter,
        version=tools_version.GetVersionString(PROG, TOOL_VERSION))
    # options arguments
    options_group = parser.add_argument_group('Options')
    options_group.add_argument(
        '--device',
        '-d',
        required=True,
        help='Device to work with.')

    # command arguments
    command_group = parser.add_argument_group('Commands')
    command_group.add_argument(
        'command',
        nargs=1,
        choices=["r", "restrict", "p", "privilege"],
        help=CMD_HELP)
    args = parser.parse_args()
    return args


def main():
    args = parse_args()

    device = args.device

    command = args.command[0]
    if command in ("p", "privilege"):
        privilege = True
    elif command in ("r", "restrict"):
        privilege = False
    retcode = 0
    mgr = PrivilegeMgr(device, privilege)
    try:
        mgr.prepare()
        retcode = mgr.configure()

    except Exception as exc:
        error("got an error: %s", str(exc))
        retcode = 1
    except(KeyboardInterrupt, SystemExit):
        print("\nInterrupted!\nExiting")
        retcode = 1
    finally:
        mgr.cleanup()
    return retcode


if __name__ == "__main__":
    sys.exit(main())
