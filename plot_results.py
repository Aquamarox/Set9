import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv")

array_types = [
    "random",
    "reversed",
    "almost_sorted"
]

for array_type in array_types:

    subset = data[
        data["array_type"] == array_type
        ]

    plt.figure(figsize=(10, 6))

    for algorithm in subset["algorithm"].unique():

        algo_data = subset[
            subset["algorithm"] == algorithm
            ]

        plt.plot(
            algo_data["size"],
            algo_data["time_us"],
            marker='o',
            label=algorithm
        )

    plt.title(
        f"Execution Time ({array_type})"
    )

    plt.xlabel("Array Size")
    plt.ylabel("Time (microseconds)")
    plt.legend()
    plt.grid()

    plt.savefig(
        f"time_{array_type}.png"
    )

    plt.close()

for array_type in array_types:

    subset = data[
        data["array_type"] == array_type
        ]

    plt.figure(figsize=(10, 6))

    for algorithm in subset["algorithm"].unique():

        algo_data = subset[
            subset["algorithm"] == algorithm
            ]

        plt.plot(
            algo_data["size"],
            algo_data["char_comparisons"],
            marker='o',
            label=algorithm
        )

    plt.title(
        f"Character Comparisons ({array_type})"
    )

    plt.xlabel("Array Size")
    plt.ylabel("Character Comparisons")
    plt.legend()
    plt.grid()

    plt.savefig(
        f"comparisons_{array_type}.png"
    )

    plt.close()