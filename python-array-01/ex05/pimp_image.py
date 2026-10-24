import numpy as np
import matplotlib.pyplot as plt


def _check(array) -> bool:
    """Return True if array is a 3-channel uint8 image, else print why.

    Shape alone is not enough. A zero-sized array reaches plt.imshow and
    raises ValueError; a bool array makes the '-' in ft_green raise
    TypeError; a float or int64 array is silently clipped by imshow and
    displays the wrong picture. All of these must be reported here with
    a clear message rather than escaping from the filters.
    """
    try:
        assert isinstance(array, np.ndarray), \
            "array must be a numpy ndarray"
        assert array.ndim == 3, "array must be 3-dimensional (H, W, C)"
        assert array.shape[2] == 3, "array must have exactly 3 channels"
        assert array.dtype == np.uint8, "array must have dtype uint8"
        assert array.size > 0, "array must not be empty"
    except AssertionError as error:
        print(f"Error: {error}")
        return False
    return True


def _show(array: np.ndarray, title: str) -> None:
    """Display an image array with matplotlib under the given title."""
    plt.imshow(array)
    plt.title(title)
    plt.axis("off")
    plt.show()


def ft_invert(array) -> np.ndarray:
    """Inverts the color of the image received."""
    if _check(array):
        result = 255 - array
        _show(result, "Invert")
        return result
    return None


def ft_red(array) -> np.ndarray:
    """Keeps only the red channel of the image received."""
    if _check(array):
        result = array * np.array([1, 0, 0], dtype=np.uint8)
        _show(result, "Red")
        return result
    return None


def ft_green(array) -> np.ndarray:
    """Keeps only the green channel of the image received."""
    if _check(array):
        result = array.copy()
        result[:, :, 0] = result[:, :, 0] - result[:, :, 0]
        result[:, :, 2] = result[:, :, 2] - result[:, :, 2]
        _show(result, "Green")
        return result
    return None


def ft_blue(array) -> np.ndarray:
    """Keeps only the blue channel of the image received."""
    if _check(array):
        result = array.copy()
        result[:, :, 0] = 0
        result[:, :, 1] = 0
        _show(result, "Blue")
        return result
    return None


def ft_grey(array) -> np.ndarray:
    """Converts the image received to greyscale."""
    if _check(array):
        result = array.copy()
        # Only "=" and "/" are allowed here, and averaging the channels
        # needs "+" (sum() and mean() are "+" in disguise), so the green
        # channel is copied over the other two: it carries most of the
        # perceived luminance (about 59% in the Rec. 601 weights).
        result[:, :, 0] = result[:, :, 1]
        result[:, :, 2] = result[:, :, 1]
        _show(result, "Grey")
        return result
    return None
