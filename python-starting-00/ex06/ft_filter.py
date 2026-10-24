"""
ft_filter - Recode of built-in filter function using list comprehensions
"""


def ft_filter(function, iterable):
    """
    Filter items of iterable for which function returns truthy.
    If function is None, return items that are truthy.
    """
    if function is None:
        return [item for item in iterable if item]
    return [item for item in iterable if function(item)]
