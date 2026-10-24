from array2D import slice_me


def main():
    """Run the subject's tests for slice_me, catching any error."""
    try:
        family = [[1.80, 78.4],
                  [2.15, 102.7],
                  [2.10, 98.5],
                  [1.88, 75.2]]

        print(slice_me(family, 0, 2))
        print(slice_me(family, 1, -2))
    except AssertionError as error:
        print(f"AssertionError: {error}")


if __name__ == "__main__":
    main()
