def validate_ingredients(ingredients: str) -> str:
    from alchemy.grimoire import light_spell_allowed_ingredients
    ing_list = ingredients.lower().replace("and", ", ").split(",")
    allowed = light_spell_allowed_ingredients()
    if any(ing.strip() in allowed for ing in ing_list):
        return f"{ingredients} - VALID"
    return f"{ingredients} - INVALID"


if __name__ == "__main__":
    # py -m alchemy.grimoire.light_validator
    print(validate_ingredients("Earth, wind and fire"))
    print(validate_ingredients("Earthquake, wind and firefly"))
