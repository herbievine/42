import matplotlib.pyplot as plt

from load_image import ft_load
from pimp_image import ft_invert, ft_red, ft_green, ft_blue, ft_grey


def main():
    """Load landscape.jpg and display it with each color filter applied."""
    try:
        array = ft_load("landscape.jpg")
        if array is None:
            return

        plt.imshow(array)
        plt.title("Original")
        plt.axis("off")
        plt.show()

        ft_invert(array)
        ft_red(array)
        ft_green(array)
        ft_blue(array)
        ft_grey(array)

        print(ft_invert.__doc__)
    except AssertionError as error:
        print(f"AssertionError: {error}")


if __name__ == "__main__":
    main()
