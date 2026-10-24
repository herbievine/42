import math

import numpy as np


def _check_numbers(values: list, name: str) -> None:
    """Assert that values is a list of finite, float-convertible numbers.

    Being an int or a float is not enough: an int of arbitrary precision
    such as 10 ** 400 has no float equivalent and would make numpy raise
    OverflowError, and nan/inf would silently produce nonsense BMIs.
    """
    assert isinstance(values, list), f"{name} must be a list"
    for value in values:
        assert isinstance(value, (int, float)) \
            and not isinstance(value, bool), \
            f"{name} must contain only int or float values"
        try:
            number = float(value)
        except OverflowError:
            raise AssertionError(f"{name} values must fit in a float")
        assert math.isfinite(number), \
            f"{name} values must be finite numbers"


def give_bmi(height: list[int | float],
             weight: list[int | float]) -> list[int | float]:
    """Return the BMI (weight / height ** 2) of each height/weight pair.

    On invalid input, prints a clear error message and returns None
    instead of raising: the subject voids any exercise that lets an
    exception escape, even when called outside the tester.
    """
    try:
        _check_numbers(height, "height")
        _check_numbers(weight, "weight")
        assert len(height) == len(weight), \
            "height and weight must have the same size"
        assert all(h > 0 for h in height), "height values must be positive"
        assert all(w >= 0 for w in weight), \
            "weight values must not be negative"
        # A height small enough to underflow squares to 0.0 and would
        # divide by zero, so guard the square itself rather than only
        # the height.
        assert all(float(h) ** 2 > 0 for h in height), \
            "height values are too small to square"
        height_arr = np.array(height, dtype=float)
        weight_arr = np.array(weight, dtype=float)
        with np.errstate(over="ignore"):
            bmi = (weight_arr / height_arr ** 2).tolist()
        assert all(math.isfinite(value) for value in bmi), \
            "BMI values are too large to fit in a float"
        return bmi
    except AssertionError as error:
        print(f"Error: {error}")
        return None


def apply_limit(bmi: list[int | float], limit: int) -> list[bool]:
    """Return a list of booleans, True where the BMI is above limit.

    On invalid input, prints a clear error message and returns None.
    """
    try:
        _check_numbers(bmi, "bmi")
        assert isinstance(limit, int) and not isinstance(limit, bool), \
            "limit must be an int"
        try:
            float(limit)
        except OverflowError:
            raise AssertionError("limit must fit in a float")
        return (np.array(bmi, dtype=float) > limit).tolist()
    except AssertionError as error:
        print(f"Error: {error}")
        return None
