#!/usr/bin/env python3

import sys


def parse_arg(arg: str) -> tuple[str, str]:
    parsed_arg = tuple(arg.split(":"))
    if len(parsed_arg) != 2:
        raise ValueError(f"Error - invalid parameter '{arg}'")
    return parsed_arg


def check_no_duplicate(item: str, inventory: dict[str, int]) -> None:
    if item in inventory:
        raise ValueError(f"Redundant item '{item}' - discarding")


def parse_qty(item: str, raw_qty: str) -> int:
    err_prefix = f"Quantity error for '{item}'"
    try:
        qty = int(raw_qty)
    except ValueError as e:
        raise ValueError(f"{err_prefix}: {e}")
    if qty < 0:
        raise ValueError(f"{err_prefix}: quantity can't be negative")
    return qty


def print_analytics(inventory: dict[str, int]) -> None:
    item_count = len(inventory)
    total_qty = sum(inventory.values())
    print(f"Total quantity of the {item_count} items: {total_qty}")
    first_key = list(inventory)[0]
    most_abundant = first_key
    least_abundant = first_key
    for item, qty in inventory.items():
        if total_qty == 0:
            percentage = 0.0
        else:
            percentage = qty / total_qty * 100
        print(f"Item {item} represents {percentage:.1f}%")
        if qty > inventory[most_abundant]:
            most_abundant = item
        if qty < inventory[least_abundant]:
            least_abundant = item
    print(f"Item most abundant: {most_abundant} "
          f"with quantity {inventory[most_abundant]}")
    print(f"Item least abundant: {least_abundant} "
          f"with quantity {inventory[least_abundant]}")


def main() -> None:
    print("=== Inventory System Analysis ===")

    args = sys.argv[1:]
    inventory: dict[str, int] = {}

    for arg in args:
        try:
            item, raw_qty = parse_arg(arg)
            check_no_duplicate(item, inventory)
            inventory[item] = parse_qty(item, raw_qty)
        except ValueError as e:
            print(e)
    if len(inventory) == 0:
        print("The inventory is empty.")
    else:
        print(f"Got inventory: {inventory}")
        print(f"Item list: {list(inventory.keys())}")
        print_analytics(inventory)
    inventory.update(magic_item=1)
    print(f"Updated inventory: {inventory}")


if __name__ == "__main__":
    main()
