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
    """Inverts the color of the image received.

    Every channel value is in 0..255, so 255 - value flips it: 0 becomes
    255, 255 becomes 0, 100 becomes 155. numpy applies the subtraction
    to every pixel at once and the result stays uint8 because 255 minus
    a uint8 can never go negative. Only "-" is used.
    """
    if _check(array):
        result = 255 - array
        _show(result, "Invert")
        return result
    return None


def ft_red(array) -> np.ndarray:
    """Keeps only the red channel of the image received.

    Each pixel is [R, G, B]. Multiplying by the mask [1, 0, 0] keeps R
    (x * 1) and zeroes G and B (x * 0). numpy broadcasts the 3-value
    mask across every pixel of the (H, W, 3) array. The mask is uint8 so
    the result keeps the image's dtype. Only "*" is used.
    """
    if _check(array):
        result = array * np.array([1, 0, 0], dtype=np.uint8)
        _show(result, "Red")
        return result
    return None


def ft_green(array) -> np.ndarray:
    """Keeps only the green channel of the image received.

    Only "=" and "-" are allowed, and a literal 0 is not an operator, so
    the red and blue channels are zeroed with x - x, which is 0 for any
    value. Channel 1 (green) is left untouched. The copy keeps the
    caller's array intact, since the assignments are in place.
    """
    if _check(array):
        result = array.copy()
        result[:, :, 0] = result[:, :, 0] - result[:, :, 0]
        result[:, :, 2] = result[:, :, 2] - result[:, :, 2]
        _show(result, "Green")
        return result
    return None


def ft_blue(array) -> np.ndarray:
    """Keeps only the blue channel of the image received.

    Only "=" is allowed, so the red (0) and green (1) channels are set
    to 0 by plain assignment into a copy. Channel 2 (blue) is kept.
    """
    if _check(array):
        result = array.copy()
        result[:, :, 0] = 0
        result[:, :, 1] = 0
        _show(result, "Blue")
        return result
    return None


def ft_grey(array) -> np.ndarray:
    """Converts the image received to greyscale.

    A grey pixel has R == G == B. Only "=" and "/" are allowed, and a
    real average (R + G + B) / 3 needs "+" (sum() and mean() are "+" in
    disguise), so the green channel is copied over red and blue instead.
    Green is the channel closest to perceived brightness (about 59% of
    the luminance weights), so the result looks like a true greyscale.
    """
    if _check(array):
        result = array.copy()
        result[:, :, 0] = result[:, :, 1]
        result[:, :, 2] = result[:, :, 1]
        _show(result, "Grey")
        return result
    return None
