#!/usr/bin/env python3

# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --


"""
Generate PGCB commands from mlxreg parameter file.

This script reads a text file containing mlxreg parameters (one per line) and
processes them with mlxreg --gen_cmd_buffer to extract buffer data.

Three modes are supported:
1. bin-mode (default): Creates binary files containing the generated buffers
2. hex-mode: Creates text files with hex data in readable format
3. script-mode: Creates a shell script with PGCB commands

Usage:
    python3 generate_pgcb_commands.py <input_file> [options]

Example input file format:
    --get --reg_name SOME_REG --indexes "param1=0x1,param2=0x2"
    --set "field=0x123" --reg_name OTHER_REG --indexes "idx=0x5"
"""

import sys
import subprocess
import re
import os
import argparse
import struct
import shutil
import shlex
import tools_version


class BufferGenerator:
    """
    A class to handle generation of PGCB commands or binary files from mlxreg output.
    """

    # Compiled regex pattern for parsing Word[XX]: 0xYYYYYYYY format
    WORD_PATTERN = re.compile(r'Word\[(\d+)\]:\s*(0x[0-9a-fA-F]+)')

    def __init__(self, input_file, device_type="gpu", mode="bin", output_prefix="buffer", output_path="out.sh", mlxreg_path="mlxreg"):
        """
        Initialize the BufferGenerator with configuration parameters.

        Args:
            input_file: Path to input text file
            device_type: Device type for --gen_cmd_buffer (gpu, hca, switch, retimer)
            mode: Output mode ("bin" for binary files, "script" for shell script)
            output_prefix: Prefix for binary files (bin mode only)
            output_path: Output path - directory for bin mode, file path for script mode
            mlxreg_path: Path to mlxreg executable
        """
        self.input_file = input_file
        self.device_type = device_type
        self.mode = mode
        self.output_prefix = output_prefix
        self.output_path = output_path
        self.mlxreg_path = mlxreg_path

    def parse_raw_buffer_output(self, output):
        """
        Parse the raw buffer output from mlxreg --gen_cmd_buffer.

        Expected format:
        Raw Buffer Data:
        ===================================
        Word[00]: 0x12345678
        Word[01]: 0x9abcdef0
        ...
        ===================================

        Returns:
            List of tuples (word_index, hex_value)
        """
        buffer_data = []

        for line in output.split('\n'):
            match = self.WORD_PATTERN.search(line)
            if match:
                word_index = int(match.group(1))
                hex_value = match.group(2)
                buffer_data.append((word_index, hex_value))

        return buffer_data

    def run_mlxreg(self, params):
        """
        Run mlxreg with --gen_cmd_buffer and return the output.

        Args:
            params: Parameter string for mlxreg

        Returns:
            Output string from mlxreg command
        """
        # Build the complete mlxreg command (offline operation, no -d device needed)
        cmd_str = f"{self.mlxreg_path} {params} --gen_cmd_buffer {self.device_type}"
        cmd_list = shlex.split(cmd_str)

        try:
            result = subprocess.run(cmd_list, capture_output=True, text=True, timeout=30)
            if result.returncode != 0:
                print(f"Error running mlxreg command: {cmd_str}")
                print(f"stderr: {result.stderr}")
                return ""
            return result.stdout
        except subprocess.TimeoutExpired:
            print(f"Timeout running mlxreg command: {cmd_str}")
            return ""
        except Exception as e:
            print(f"Exception running mlxreg command: {cmd_str}")
            print(f"Error: {e}")
            return ""

    def write_binary_file(self, filename, buffer_data):
        """
        Write buffer data to a binary file.

        Args:
            filename: Output binary file path
            buffer_data: List of tuples (word_index, hex_value)
        """
        try:
            with open(filename, 'wb') as f:
                # Sort by word index to ensure correct order
                sorted_data = sorted(buffer_data, key=lambda x: x[0])
                for word_index, hex_value in sorted_data:
                    # Convert hex string to 32-bit integer and write as big-endian
                    value = int(hex_value, 16)
                    f.write(struct.pack('>I', value))
            return True
        except Exception as e:
            print(f"Error writing binary file {filename}: {e}")
            return False

    def write_text_file(self, filename, buffer_data):
        """
        Write buffer data to a text file in hex format.

        Args:
            filename: Output text file path
            buffer_data: List of tuples (word_index, hex_value)
        """
        try:
            with open(filename, 'w') as f:
                for word_index, hex_value in buffer_data:
                    f.write(f"DWORD[{word_index:02d}]: {hex_value}\n")
            return True
        except Exception as e:
            print(f"Error writing text file {filename}: {e}")
            return False

    def process_file_mode(self, cfg_buf_index, buffer_data):
        """
        Process parsed buffer data in bin or hex mode - create one file.

        Args:
            cfg_buf_index: Index of the current buffer
            buffer_data: Parsed buffer data (list of tuples)

        Returns:
            str or None: Output filename if successful, None if failed
        """

        # Ensure output directory exists
        if not os.path.exists(self.output_path):
            try:
                os.makedirs(self.output_path, exist_ok=True)
            except Exception as e:
                print(f"Error creating output directory {self.output_path}: {e}")
                return None

        # Generate filename with appropriate extension based on mode
        if self.mode == "bin":
            extension = "bin"
            write_func = self.write_binary_file
        elif self.mode == "hex":
            extension = "txt"
            write_func = self.write_text_file
        else:
            print(f"Error: Unsupported file mode '{self.mode}'")
            return None

        output_filename = os.path.join(self.output_path, f"{self.output_prefix}_{cfg_buf_index:03d}.{extension}")

        if write_func(output_filename, buffer_data):
            print(f"Created {self.mode} file: {output_filename}")
            return output_filename
        else:
            print(f"Failed to create {self.mode} file: {output_filename}")
            return None

    def process_script_mode(self, cfg_buf_index, buffer_data, params):
        """
        Process parsed buffer data in script mode - generate one PGCB command.

        Args:
            cfg_buf_index: Index of the current buffer
            buffer_data: Parsed buffer data (list of tuples)
            params: Original parameters used for this line

        Returns:
            list: List of command lines for this buffer
        """

        # Generate single PGCB command with all DWORDs for this INDEX
        command_lines = []
        command_lines.append(f"# Commands for cfg_buf_num={cfg_buf_index} (from: {params})")

        # Combine all DWORDs into a single --set parameter
        buf_assignments = []
        for dword_index, hex_value in buffer_data:
            buf_assignments.append(f"buf[{dword_index}]={hex_value}")

        # Create single command with all buffer assignments
        set_param = ",".join(buf_assignments)
        # Use $DEVICE variable that will be provided as script argument
        pgcb_cmd = f'mlxreg -d $DEVICE --reg_name PGCB --indexes "cfg_buf_num={cfg_buf_index}" --set "{set_param}"'
        command_lines.append(pgcb_cmd)
        command_lines.append("")  # Empty line for readability

        return command_lines

    def generate_script_file(self, pgcb_commands):
        """
        Generate shell script file from PGCB commands.

        Args:
            pgcb_commands: List of command lines

        Returns:
            bool: True if successful, False otherwise
        """
        # Build complete script content
        script_lines = []
        script_lines.append("#!/bin/bash")
        script_lines.append("# Generated PGCB commands")
        script_lines.append(f"# Device Type: {self.device_type}")
        script_lines.append("")
        script_lines.append("# Check if device argument was provided")
        script_lines.append("if [ $# -ne 1 ]; then")
        script_lines.append("    echo \"Usage: $0 <device>\"")
        script_lines.append("    echo \"Example: $0 /dev/mst/mt4125_pciconf0\"")
        script_lines.append("    exit 1")
        script_lines.append("fi")
        script_lines.append("")
        script_lines.append("# Set device variable from command line argument")
        script_lines.append("DEVICE=\"$1\"")
        script_lines.append("")
        script_lines.append("echo \"Running PGCB commands on device: $DEVICE\"")
        script_lines.append("")
        script_lines.extend(pgcb_commands)

        # Write shell script file
        try:
            with open(self.output_path, 'w') as f:
                f.write('\n'.join(script_lines))

            # Make output file executable
            os.chmod(self.output_path, 0o755)

            print(f"Generated {len(script_lines)} lines in '{self.output_path}'")
            return True

        except Exception as e:
            print(f"Error writing output file: {e}")
            return False

    def run(self):
        """
        Generate output from input file in specified mode.

        Returns:
            bool: True if successful, False otherwise
        """
        # Read input file
        try:
            with open(self.input_file, 'r') as f:
                input_lines = [line.strip() for line in f if line.strip()]
        except Exception as e:
            print(f"Error reading input file: {e}")
            return False

        if not input_lines:
            print("Error: Input file is empty")
            return False

        # Initialize mode-specific collections
        files_created = []
        pgcb_commands = []

        # Single loop to process each input line
        for cfg_buf_index, params in enumerate(input_lines):
            print(f"Processing line {cfg_buf_index + 1}: {params}")

            # Run mlxreg with --gen_cmd_buffer (offline operation)
            mlxreg_output = self.run_mlxreg(params)

            if not mlxreg_output:
                print(f"Warning: No output from mlxreg for line {cfg_buf_index + 1}")
                if self.mode == "script":
                    pgcb_commands.append(f"# Error processing: {params}")
                    pgcb_commands.append("")
                continue

            # Parse the raw buffer output
            buffer_data = self.parse_raw_buffer_output(mlxreg_output)

            if not buffer_data:
                print(f"Warning: No buffer data found for line {cfg_buf_index + 1}")
                if self.mode == "script":
                    pgcb_commands.append(f"# No buffer data: {params}")
                    pgcb_commands.append("")
                continue

            # Process this single result based on mode
            if self.mode in ["bin", "hex"]:
                output_filename = self.process_file_mode(cfg_buf_index, buffer_data)
                if output_filename:
                    files_created.append(output_filename)

            elif self.mode == "script":
                command_lines = self.process_script_mode(cfg_buf_index, buffer_data, params)
                if command_lines:
                    pgcb_commands.extend(command_lines)

            else:
                print(f"Error: Unknown mode '{self.mode}'")
                return False

        # Handle final output based on mode
        if self.mode in ["bin", "hex"]:
            if files_created:
                file_type = "binary" if self.mode == "bin" else "hex text"
                print(f"Successfully created {len(files_created)} {file_type} files:")
                for filename in files_created:
                    print(f"  {filename}")
                return True
            else:
                file_type = "binary" if self.mode == "bin" else "hex text"
                print(f"No {file_type} files were created")
                return False

        elif self.mode == "script":
            return self.generate_script_file(pgcb_commands)


def validate_input_path(input_path):
    """
    Validate the input file path.

    Args:
        input_path: Input file path to validate

    Returns:
        bool: True if valid, False otherwise

    Raises:
        SystemExit: If validation fails with descriptive error message
    """
    if not os.path.exists(input_path):
        print(f"Error: Input file '{input_path}' not found")
        sys.exit(1)

    if not os.path.isfile(input_path):
        print(f"Error: Input path '{input_path}' is not a file")
        sys.exit(1)

    if not os.access(input_path, os.R_OK):
        print(f"Error: No read permission to file '{input_path}'")
        sys.exit(1)

    return True


def validate_mlxreg_path(mlxreg_path):
    """
    Validate the mlxreg executable path.

    Args:
        mlxreg_path: Path to mlxreg executable to validate

    Returns:
        bool: True if valid, False otherwise

    Raises:
        SystemExit: If validation fails with descriptive error message
    """
    # Check if it's an absolute path or just a command name
    if os.path.sep in mlxreg_path:
        # It's a path, check if it exists
        if not os.path.exists(mlxreg_path):
            print(f"Error: Mlxreg executable '{mlxreg_path}' not found")
            sys.exit(1)

        if not os.path.isfile(mlxreg_path):
            print(f"Error: Mlxreg path '{mlxreg_path}' is not a file")
            sys.exit(1)

        if not os.access(mlxreg_path, os.X_OK):
            print(f"Error: Mlxreg executable '{mlxreg_path}' is not executable")
            sys.exit(1)
    else:
        # It's a command name, check if it's in PATH
        if not shutil.which(mlxreg_path):
            print(f"Error: Command '{mlxreg_path}' not found in PATH")
            sys.exit(1)

    return True


def validate_output_path(output_path, mode):
    """
    Validate the output path based on the mode.

    Args:
        output_path: Output path to validate
        mode: Output mode ("bin" or "script")

    Returns:
        bool: True if valid, False otherwise

    Raises:
        SystemExit: If validation fails with descriptive error message
    """
    if mode in ["bin", "hex"]:
        # For bin/hex mode, output should be a directory with write permissions
        if os.path.exists(output_path):
            if not os.path.isdir(output_path):
                print(f"Error: Output path '{output_path}' exists but is not a directory (bin/hex mode requires a directory)")
                sys.exit(1)
            if not os.access(output_path, os.W_OK):
                print(f"Error: No write permission to directory '{output_path}'")
                sys.exit(1)
        else:
            # Directory doesn't exist, check if we can create it
            parent_dir = os.path.dirname(os.path.abspath(output_path))
            if not os.path.exists(parent_dir):
                print(f"Error: Parent directory '{parent_dir}' does not exist")
                sys.exit(1)
            if not os.access(parent_dir, os.W_OK):
                print(f"Error: No write permission to parent directory '{parent_dir}'")
                sys.exit(1)

    elif mode == "script":
        # For script mode, output should be a file we can write to
        if os.path.exists(output_path):
            if os.path.isdir(output_path):
                print(f"Error: Output path '{output_path}' is a directory (script mode requires a file path)")
                sys.exit(1)
            if not os.access(output_path, os.W_OK):
                print(f"Error: No write permission to file '{output_path}'")
                sys.exit(1)
        else:
            # File doesn't exist, check if we can create it
            parent_dir = os.path.dirname(os.path.abspath(output_path))
            if not os.path.exists(parent_dir):
                print(f"Error: Parent directory '{parent_dir}' does not exist")
                sys.exit(1)
            if not os.access(parent_dir, os.W_OK):
                print(f"Error: No write permission to parent directory '{parent_dir}'")
                sys.exit(1)

            # Try to create and immediately remove a test file to verify we can write
            try:
                with open(output_path, 'w') as test_file:
                    pass
                os.remove(output_path)
            except (OSError, IOError) as e:
                print(f"Error: Cannot create file '{output_path}': {e}")
                sys.exit(1)

    return True


def main():
    tool_name = os.path.basename(__file__).split('.')[0]
    parser = argparse.ArgumentParser(
        prog=tool_name,
        description="Generate PGCB commands from mlxreg parameter file",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Generate binary files (default mode)
  python3 generate_pgcb_commands.py --input input.txt

  # Generate hex text files
  python3 generate_pgcb_commands.py --input input.txt --mode hex

  # Generate binary files with custom prefix and output directory
  python3 generate_pgcb_commands.py --input input.txt --output-prefix my_buffer --output ./output_dir

  # Generate shell script
  python3 generate_pgcb_commands.py --input input.txt --mode script --output commands.sh

  # Use different device type
  python3 generate_pgcb_commands.py --input input.txt --device-type hca

  # Use custom mlxreg path
  python3 generate_pgcb_commands.py --input input.txt --mlxreg-path /path/to/mlxreg

Input file format (one command per line):
  --get --reg_name SOME_REG --indexes "param1=0x1,param2=0x2"
  --set "field=0x123" --reg_name OTHER_REG --indexes "idx=0x5"
        """
    )

    parser.add_argument(
        '--input', '-i',
        required=True,
        help='Text file with mlxreg parameters (one per line)'
    )

    parser.add_argument(
        '--device-type', '-d',
        type=str.lower,
        choices=['gpu', 'hca', 'switch', 'retimer'],
        metavar="{'GPU', 'HCA', 'Switch', 'Retimer'}",
        default='GPU',
        help='Device type for --gen_cmd_buffer (default: gpu)'
    )

    parser.add_argument(
        '--mode', '-m',
        choices=['bin', 'hex', 'script'],
        default='hex',
        help='Output mode: "bin" creates binary files, "hex" creates text files with hex data, "script" creates shell script (default: bin)'
    )

    parser.add_argument(
        '--output-prefix', '-p',
        default='prm_buffer',
        help='Prefix for output files (bin/hex mode only, default: prm_buffer)'
    )

    parser.add_argument(
        '--output', '-o',
        default=None,
        help='Output path: file path for script mode (default: out.sh), directory path for bin/hex mode (default: current directory)'
    )

    parser.add_argument(
        '--mlxreg-path',
        default='mstreg',
        help='Path to mlxreg executable (default: mlxreg)'
    )

    parser.add_argument(
        '--version', '-v',
        help='Print tool version',
        action="version",
        version=tools_version.GetVersionString(tool_name, None)
    )

    args = parser.parse_args()

    # Validate input file
    validate_input_path(args.input)

    # Validate mlxreg executable path
    validate_mlxreg_path(args.mlxreg_path)

    # Handle default values for output based on mode
    if args.output is None:
        if args.mode == "script":
            output_path = "out.sh"
        else:  # bin/hex mode
            output_path = "."
    else:
        output_path = args.output

    # Validate output path based on mode
    validate_output_path(output_path, args.mode)

    print(f"Input file: {args.input}")
    print(f"Device type: {args.device_type}")
    print(f"Mode: {args.mode}")
    print(f"Mlxreg path: {shutil.which(args.mlxreg_path)}")
    if args.mode in ["bin", "hex"]:
        print(f"Output prefix: {args.output_prefix}")
        print(f"Output directory: {output_path}")
    else:
        print(f"Output file: {output_path}")
    print("")

    buffer_generator = BufferGenerator(
        input_file=args.input,
        device_type=args.device_type,
        mode=args.mode,
        output_prefix=args.output_prefix,
        output_path=output_path,
        mlxreg_path=args.mlxreg_path
    )
    success = buffer_generator.run()

    if success:
        if args.mode == "bin":
            print(f"Successfully generated binary PRM commands files in directory: {output_path}")
        elif args.mode == "hex":
            print(f"Successfully generated hex text PRM commands files in directory: {output_path}")
        else:
            print(f"Successfully generated PRM commands shell script: {output_path}")
        sys.exit(0)
    else:
        print("Operation failed")
        sys.exit(1)


if __name__ == "__main__":
    main()
