def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:

    msg: dict[str, str] = {
        "packets": f"{quantity} packets available",
        "grams": f"{quantity} grams total",
        "area": f"covers {quantity} square meters"
    }

    if unit not in msg:
        print("Unknown unit type")
    else:
        print(f"{seed_type.capitalize()} seeds: {msg[unit]}")
