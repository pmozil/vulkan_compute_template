#!/usr/bin/env python3

import argparse
import subprocess
import csv

from tqdm import tqdm


def run_code_iteration(
        exe_path: str,
        filepath: str,
        method: int = 1,
) -> tuple:
    result = subprocess.check_output([exe_path, str(method), filepath])
    return result.decode("utf-8").strip().split("\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-c", "--config_file_prefix", default="config_files/func"
    )
    parser.add_argument(
        "--exe_path", type=str, default="build/integrate_parallel"
    )
    parser.add_argument("-m", "--methods", type=int, default=3)
    parser.add_argument("--iterations", type=int, default=1)
    parser.add_argument("-o", "--output", default="results.csv")

    args = parser.parse_args()

    results_of_calculation = [[] for _ in range(args.methods)]

    print(f"Running {args.iterations} iterations")
    for _ in tqdm(range(args.iterations)):
        for i in range(1, args.methods + 1):
            res = run_code_iteration(
                exe_path=args.exe_path,
                filepath=f"{args.config_file_prefix}{i}.cfg",
                method=i,
            )
            results_of_calculation[i - 1].append(res)
    for result in results_of_calculation:
        result_of_integration = str(
            sum(float(i[0]) for i in result) / args.iterations
        )
        absolute_error = str(
            sum(float(i[1]) for i in result) / args.iterations
        )
        relative_error = str(
            sum(float(i[2]) for i in result) / args.iterations
        )
        minimal_time = str(min(float(i[3]) for i in result))
        average_time = str(sum(float(i[3]) for i in result) / args.iterations)
        sum_of_times = 0
        for k in [float(i[3]) for i in result]:
            sum_of_times += (k - float(average_time)) ** 2
        standard_deviation = str(sum_of_times / args.iterations)
        print(
            "\n".join(
                [
                    result_of_integration,
                    absolute_error,
                    relative_error,
                    minimal_time,
                    average_time,
                    standard_deviation,
                ]
            )
        )
        print("\n")

    with open(args.output, "w") as out:
        writer = csv.writer(out)

        times = [[str(i[3]) for i in row] for row in results_of_calculation]
        times_t = [[times[i][j] for i in range(len(results_of_calculation))] for j in range(len(results_of_calculation[0]))]
        writer.writerow(["First function", "Second function", "Third function", "Fourth function"])
        for row in times_t:
            writer.writerow(row)
