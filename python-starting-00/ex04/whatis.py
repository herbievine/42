import sys


def main(argv):
    """
    Check if a number is even or odd.
    """
    try:
        assert len(argv) <= 2, "more than one argument is provided"
        if len(argv) > 1:
            is_negative = argv[1][0] == "-"
            is_int = (is_negative and argv[1][1:].isnumeric() or
                      argv[1].isnumeric())
            assert is_int, "argument is not an integer"
            print("I'm Even." if int(argv[1]) % 2 == 0 else "I'm Odd.")

    except AssertionError as msg:
        print(f'AssertionError: {msg}')
        exit(1)


if __name__ == "__main__":
    main(sys.argv)
