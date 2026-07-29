# Python docs offline — `pydoc`, `help()`, `dir()`

> Le manuel Python en ligne de commande. Il lit les **docstrings** des modules et
> objets réellement installés — donc la doc correspond *exactement* à la version de
> l'interpréteur, sans réseau. Trois outils, trois usages : `pydoc`/`help()` pour
> *comprendre*, `dir()` pour *inventorier*.

---

## `pydoc` — le manuel (façon `man`)

Descriptions + signatures. C'est la doc lisible.

```bash
# La doc complète du type list : toutes les méthodes, signatures et docstrings
python3 -m pydoc list

# Une seule méthode
python3 -m pydoc list.append

# Dans un pager
python3 -m pydoc list | less

# Un module entier
python3 -m pydoc os
python3 -m pydoc os.path.join
```

Bonus — serveur web local avec toute la doc navigable :

```bash
python3 -m pydoc -p 8080        # puis http://localhost:8080
python3 -m pydoc -b             # ouvre direct le navigateur
```

> Note : `pydoc list` marche aussi sans `-m` si le script `pydoc` est dans le PATH,
> mais `python3 -m pydoc` est la forme fiable (utilise le bon interpréteur).

---

## `help()` — le même manuel, en interactif

Dans un `python3` (REPL), `help()` est l'équivalent exact de `pydoc` :

```python
>>> help(list)          # doc complète du type
>>> help(list.append)   # une méthode
>>> help(str)
>>> help()              # mode interactif, tape "list" puis Entrée, "q" pour sortir
```

Même contenu que `pydoc` (les deux lisent les docstrings) — l'un depuis le shell,
l'autre depuis le REPL.

---

## `dir()` — l'inventaire brut des noms

Pas de description : juste **la liste des attributs/méthodes**. Idéal pour "quelles
méthodes existent, vite".

```python
>>> dir(list)                                   # tout, dunder inclus
['__add__', ..., 'append', 'clear', 'copy', 'count', 'extend', 'index',
 'insert', 'pop', 'remove', 'reverse', 'sort']

>>> [m for m in dir(list) if not m.startswith('_')]   # que le "public"
['append', 'clear', 'copy', 'count', 'extend', 'index', 'insert',
 'pop', 'remove', 'reverse', 'sort']
```

En one-liner depuis le shell :

```bash
python3 -c "print([m for m in dir(list) if not m.startswith('_')])"
```

---

## Lequel choisir

| Besoin                                   | Outil                     |
| ---------------------------------------- | ------------------------- |
| Comprendre ce que fait une méthode       | `pydoc` / `help()`        |
| Voir la signature / les arguments        | `pydoc` / `help()`        |
| Lister vite les méthodes disponibles     | `dir()`                   |
| Naviguer toute la stdlib au calme        | `pydoc -b` (serveur web)  |

**Défense en une ligne :**
> `pydoc`/`help()` lisent les docstrings de la version installée : la doc est locale
> et toujours à jour. `dir()` ne donne que les *noms*, sans description — pour
> l'inventaire, pas la compréhension.

---

See also: [dev_env.md](dev_env.md) (setup interpréteur / outils),
[python_keywords.md](../02_syntax_flow/python_keywords.md).
