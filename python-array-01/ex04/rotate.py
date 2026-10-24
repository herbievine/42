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


def check_transpose(square: np.ndarray, transposed: np.ndarray) -> None:
    """Raise ValueError if ``transposed`` is not the transpose of ``square``.

    Checks the shape and a few sampled coordinates so the result is
    proven correct rather than merely correctly shaped.
    """
    expected = (square.shape[1], square.shape[0])
    if transposed.shape != expected:
        raise ValueError(
            f"transpose shape is {transposed.shape}, expected {expected}"
        )
    # Derived from the real shape, never hard-coded: the subject invites
    # a different crop, and fixed coordinates would raise IndexError
    # instead of reporting a mismatch. Off-diagonal pairs included, since
    # a point on the diagonal is unchanged by a transpose and proves
    # nothing.
    last_x, last_y = transposed.shape[0] - 1, transposed.shape[1] - 1
    samples = [
        (0, 0), (0, last_y), (last_x, 0), (last_x, last_y),
        (last_x // 3, last_y // 2), (last_x // 7, last_y // 11),
    ]
    for x, y in samples:
        if transposed[x][y] != square[y][x][0]:
            raise ValueError(f"transpose mismatch at ({x}, {y})")


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
        check_transpose(square, transposed)
        print(f"New shape after Transpose: {transposed.shape}")
        print(transposed)
        display(transposed)
    except (ValueError, TypeError, IndexError) as error:
        print(f"Error: {error}")


if __name__ == "__main__":
    main()
