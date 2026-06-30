def ft_count_harvest_recursive():
    day: int = int(input("Days until harvest: "))

    def print_recurse(day: int):
        if day > 1:
            print_recurse(day - 1)
        if day > 0:
            print("Day ", day)

    print_recurse(day)
