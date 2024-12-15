import sys
import subprocess
import argparse

def read_input(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    return lines

def main() -> int:
    parser = argparse.ArgumentParser(usage='%(prog)s [-h] [-v] input_file program [args...]')
    parser.add_argument('input_file', type=str, help='Input file containing graph description')
    parser.add_argument('program', nargs=argparse.REMAINDER, help='Program to run')
    parser.add_argument('-v', action='store_true', help='Print all activity between two programs')

    args = parser.parse_args()
    if not args.program:
        parser.error('Must specify program to run')

    input_file = args.input_file
    program_path = args.program
    verbose = args.v

    lines = read_input(input_file)
    n = int(lines[0].strip())
    graph = [line.strip() for line in lines[1:]]

    # Start the program
    process = subprocess.Popen(
        program_path,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    # Send initial information to the program
    if verbose:
        print(f"> {n}")
        print(f"> {graph[0]}")
    process.stdin.write(f"{n}\n")
    process.stdin.write(f"{graph[0]}\n")
    process.stdin.flush()

    current_node = 0  # 1-based index, 0 means 1
    operations = 0

    try:
        while True:
            # Read the program's output
            move = process.stdout.readline().strip()
            if verbose:
                print(f"< {move}")

            if move == "yes" or move == "no":
                print("Participant program stopped with output", move, "at vertex", current_node + 1)
                return 0

            if operations >= 2 * n:
                if verbose:
                    print(f"> FAIL")
                process.stdin.write("FAIL\n")
                process.stdin.flush()
                process.terminate()
                return 1

            move_int = int(move)
            if move_int >= 1 and move_int <= n:
                if graph[current_node][move_int - 1] == '1':
                    current_node = move_int - 1
                    if verbose:
                        print(f"> {graph[current_node]}")
                    process.stdin.write(f"{graph[current_node]}\n")
                    process.stdin.flush()
                    operations += 1
                else:
                    if verbose:
                        print(f"> FAIL")
                    print('ERROR: invalid move', move, 'at vertex', current_node + 1)
                    process.stdin.write("FAIL\n")
                    process.stdin.flush()
                    process.terminate()
                    return 1
            else:
                if verbose:
                    print(f"> FAIL")
                print('ERROR: invalid move', move, 'at vertex', current_node + 1)
                process.stdin.write("FAIL\n")
                process.stdin.flush()
                process.terminate()
                return 1
    except BrokenPipeError:
        print('ERROR: error when communicating with program - exited prematurely?')
        return 2
    except Exception as e:
        print('ERROR:', e)
        return 3

if __name__ == "__main__":
    sys.exit(main())