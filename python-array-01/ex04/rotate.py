import numpy as np
import matplotlib.pyplot as plt
from load_image import ft_load


def ft_transpose(square: np.ndarray) -> np.ndarray:
    """Transpose a (N, N, 1) single-channel square into a (N, N) array.

    The transposition is done by hand: every value found at ``[y][x]``
    is written at ``[x][y]`` and the trailing channel axis is dropped.
    No library transpose helper is used.
    """
    height, width = square.shape[0], square.shape[1]
    rows = []
    for x in range(width):
        row = []
        for y in range(height):
            row.append(square[y][x][0])
        rows.append(row)
    return np.array(rows, dtype=square.dtype)


def display(image: np.ndarray) -> None:
    """Display a 2D grayscale image with the scale on both axes."""
    plt.imshow(image, cmap="gray")
    plt.title("Transposed square")
    plt.show()


def main() -> None:
    """Load animal.jpeg, cut a square, transpose it by hand, display it."""
    try:
        image = ft_load("animal.jpeg")
        if image is None:
            print("Error: could not load the image, nothing to rotate")
            return
        square = image[200:600, 450:850, 0:1]
        if square.shape != (400, 400, 1):
            print(
                f"Error: expected a (400, 400, 1) square, "
                f"got {square.shape}"
            )
            return
        print(f"The shape of image is: {square.shape}")
        print(square)
        transposed = ft_transpose(square)
        print(f"New shape after Transpose: {transposed.shape}")
        print(transposed)
        display(transposed)
    except (ValueError, TypeError, IndexError) as error:
        print(f"Error: {error}")


if __name__ == "__main__":
    main()
