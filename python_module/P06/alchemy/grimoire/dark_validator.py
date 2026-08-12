from .dark_spellbook import dark_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    ing_list = ingredients.lower().replace("and", ", ").split(",")
    allowed = dark_spell_allowed_ingredients()
    if any(ing.strip() in allowed for ing in ing_list):
        return f"{ingredients} - VALID"
    return f"{ingredients} - INVALID"
