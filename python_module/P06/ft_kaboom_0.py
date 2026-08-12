from alchemy.grimoire import light_spell_record

if __name__ == "__main__":
    print("=== Kaboom 0 ===")
    print("Using grimoire module directly")
    print(
        "Testing record light spell: "
        f"Spell recorded: "
        f"{light_spell_record('Fantasy', 'Earth, wind and fire')}"
    )
