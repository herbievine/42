from give_bmi import give_bmi, apply_limit


def main():
    """Run the subject's tests for give_bmi and apply_limit."""
    try:
        height = [2.71, 1.15]
        weight = [165.3, 38.4]

        bmi = give_bmi(height, weight)
        print(bmi, type(bmi))
        print(apply_limit(bmi, 26))
    except AssertionError as error:
        print(f"AssertionError: {error}")


if __name__ == "__main__":
    main()
