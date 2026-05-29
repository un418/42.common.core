# 42.common.core

My 42 common core projects, all in one repo.

| Project | Description |
|---|---|
| [`libft`](libft/) | C library that re-implements standard functions + list utils |
| [`ft_printf`](ft_printf/) | My own version of `printf` |
| [`get_next_line`](get_next_line/) | Read one line from a file descriptor |
| [`_docs`](_docs/) | My learning notes (Obsidian vault) |

## Why a monorepo?

At 42 each project is turned in on its own repo. Keeping them together here is
a choice I made on purpose, for three reasons:

1. **Get better at Git.** Working with many projects in one repo pushes me
   further than the usual `add / commit / push`: `git subtree`, history
   rewrite, commit conventions, etc.
2. **All my code in one place.** One clone, one history, and my notes
   (`_docs/`) live next to the code.
3. **Follow my work day by day.** The single commit history shows my progress
   live, project after project. It also lets someone from outside see what I
   am working on day to day.

### Turn in to 42

Each project is pushed to its own Vogsphere repo with `git subtree`
(see [`_docs/05_Others/Git Mono Repo.md`](_docs/05_Others/Git%20Mono%20Repo.md)).

### Known limit

For group projects I use a separate repo. A solo monorepo with no real tooling
gets painful when you are more than one.
