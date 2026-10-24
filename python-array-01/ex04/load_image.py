import os

import numpy as np
from PIL import Image, UnidentifiedImageError


def ft_load(path: str) -> np.ndarray:
    """Load a JPG/JPEG image and return its pixels as an RGB numpy array.

    Prints the shape of the image on success and returns a numpy
    ``ndarray`` of dtype ``uint8`` with shape ``(height, width, 3)``.
    On any error, prints a clear message and returns ``None`` instead
    of raising.
    """
    supported = (".jpg", ".jpeg")
    try:
        if not isinstance(path, str):
            raise TypeError(
                f"path must be a str, not {type(path).__name__}"
            )
        extension = os.path.splitext(path)[1].lower()
        if extension not in supported:
            raise ValueError(
                f"unsupported format '{extension}' for '{path}', "
                f"expected one of {supported}"
            )
        with Image.open(path) as image:
            # np.array (not np.asarray) so the caller gets a writeable copy:
            # asarray wraps Pillow's read-only buffer, and the callers
            # assign into the array in place.
            array = np.array(image.convert("RGB"), dtype=np.uint8)
        print(f"The shape of image is: {array.shape}")
        return array
    except FileNotFoundError:
        print(f"Error: file not found: '{path}'")
    except UnidentifiedImageError:
        print(f"Error: '{path}' is not a valid image file")
    except Image.DecompressionBombError:
        # Not an OSError: Pillow refuses images whose header claims more
        # pixels than Image.MAX_IMAGE_PIXELS, so it would escape otherwise.
        print(f"Error: '{path}' claims too many pixels to be loaded safely")
    except PermissionError:
        print(f"Error: permission denied: '{path}'")
    except IsADirectoryError:
        print(f"Error: '{path}' is a directory, not a file")
    except OSError as error:
        print(f"Error: cannot read '{path}': {error}")
    except (TypeError, ValueError) as error:
        print(f"Error: {error}")
    return None
