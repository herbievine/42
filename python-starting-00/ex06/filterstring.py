import sys
from ft_filter import ft_filter


def main(argv):
    """
    Filter words from a string by length.
    """
    try:
        assert len(argv) == 3, "the arguments are bad"

        s = argv[1]
        assert s is not None and isinstance(s, str), "the arguments are bad"

        try:
            n = int(argv[2])
        except ValueError:
            assert False, "the arguments are bad"

        words = s.split()
        result = ft_filter(lambda w: len(w) > n, words)
        print(result)

    except AssertionError as msg:
        print(f'AssertionError: {msg}')
        exit(1)


if __name__ == "__main__":
    main(sys.argv)
