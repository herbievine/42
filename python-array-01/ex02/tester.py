from load_image import ft_load

# enable full print in console:
# np.set_printoptions(threshold=np.inf)


def main():
    """Load landscape.jpg and print its shape and pixel content."""
    print(ft_load("landscape.jpg"))


if __name__ == "__main__":
    main()
