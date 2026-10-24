import numpy as np


def _shape_2d(array: np.ndarray) -> tuple:
    """Return the shape of array as a 2-tuple.

    numpy gives an empty array the shape (0,), so an empty family would
    otherwise print a 1-tuple; this normalises it to (0, 0).
    """
    if array.ndim == 2:
        return array.shape
    return (array.shape[0], 0)


def slice_me(family: list, start: int, end: int) -> list:
    """Print the shape of a 2D list and return its rows sliced [start:end].

    family must be a list of lists of equal length; start and end are
    row indices (negative values allowed, as with regular slicing).
    On invalid input, prints a clear error message and returns None.
    """
    try:
        assert isinstance(family, list), "family must be a list"
        for row in family:
            assert isinstance(row, list), \
                "each row of family must be a list"
        for row in family:
            assert len(row) == len(family[0]), \
                "all rows of family must have the same size"
        for index in (start, end):
            assert isinstance(index, int) and not isinstance(index, bool), \
                "start and end must be integers"
        # Chapter IV only requires rows that are lists of the same size,
        # so element types are left free. numpy is used for the shape
        # and to reject nested elements (it raises ValueError on those),
        # but the rows themselves are sliced from the original list so
        # the values come back exactly as given: converting through
        # numpy would turn [[1, 2.5]] into [[1.0, 2.5]].
        try:
            array = np.array(family)
        except ValueError:
            raise AssertionError("family must be a rectangular 2D array")
        assert not family or array.ndim == 2, "family must be a 2D array"
        print(f"My shape is : {_shape_2d(array)}")
        print(f"My new shape is : {_shape_2d(array[start:end])}")
        return family[start:end]
    except AssertionError as error:
        print(f"Error: {error}")
        return None
