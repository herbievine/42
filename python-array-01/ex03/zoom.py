import matplotlib.pyplot as plt
import numpy as np

from load_image import ft_load


def zoom(image: np.ndarray) -> np.ndarray:
    """Crop a 400x400 square around the raccoon's face and keep one channel.

    Slicing with ``0:1`` (instead of ``0``) preserves the trailing axis so
    the result has shape ``(400, 400, 1)``. Raises ``ValueError`` if the
    image is too small for the requested crop.
    """
    zoomed = image[200:600, 450:850, 0:1]
    if zoomed.shape != (400, 400, 1):
        raise ValueError(
            f"image too small to zoom: got {zoomed.shape} "
            f"instead of (400, 400, 1)"
        )
    return zoomed


def display(zoomed: np.ndarray) -> None:
    """Draw the single retained channel with a grey colormap.

    The data is the red channel, not a luminance conversion, so this is
    a grey rendering of one channel rather than a true greyscale image.
    The axis scales are left on, as the subject requires.
    """
    plt.imshow(zoomed[:, :, 0], cmap="gray")
    plt.title("Zoomed image")
    plt.xlabel("X (pixels)")
    plt.ylabel("Y (pixels)")
    plt.show()


def main() -> None:
    """Load animal.jpeg, print its content, then zoom and display it."""
    try:
        image = ft_load("animal.jpeg")
        if image is None:
            print("Error: could not load the image, aborting")
            return
        print(image)
        zoomed = zoom(image)
        print(f"New shape after slicing: {zoomed.shape}")
        print(zoomed)
        display(zoomed)
    except (ValueError, TypeError, IndexError) as error:
        print(f"Error: {error}")


if __name__ == "__main__":
    main()
