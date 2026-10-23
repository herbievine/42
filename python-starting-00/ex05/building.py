import sys


def count_characters(text):
    """
    Count different character types in a string.
    Returns total, uppercase, lowercase, punctuation, digits, and spaces.
    """
    punct_chars = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
    upper = sum(1 for c in text if c.isupper())
    lower = sum(1 for c in text if c.islower())
    punctuation = sum(1 for c in text if c in punct_chars)
    digits = sum(1 for c in text if c.isdigit())
    spaces = sum(1 for c in text if c.isspace())

    total = upper + lower + punctuation + digits + spaces

    return total, upper, lower, punctuation, digits, spaces


def main(argv):
    """
    Count character types in a string.
    """
    try:
        assert len(argv) <= 2, "more than one argument is provided"

        if len(argv) == 1:
            text = input("What is the text to count?\n")
        else:
            text = argv[1]

        total, upper, lower, punct, digits, spaces = count_characters(text)

        print(f"The text contains {total} characters:")
        print(f"{upper} upper letter{'s' if upper != 1 else ''}")
        print(f"{lower} lower letter{'s' if lower != 1 else ''}")
        print(f"{punct} punctuation mark{'s' if punct != 1 else ''}")
        print(f"{spaces} space{'s' if spaces != 1 else ''}")
        print(f"{digits} digit{'s' if digits != 1 else ''}")

    except AssertionError as msg:
        print(f'AssertionError: {msg}')
        exit(1)


if __name__ == "__main__":
    main(sys.argv)
