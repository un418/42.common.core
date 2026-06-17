# ft_printf — va_list bug: full explanation

> Concept: passing a `va_list` by value vs. by pointer  
> Context: bug caught during review before submission (2026-05-29)

---

## The problem in one line

Passing a `va_list` by value to a function and then calling `va_arg` inside it is **undefined behavior** in C. It manifests differently depending on the architecture.

---

## How `va_list` is defined per architecture

### On x86-64 Linux (glibc)

```c
typedef struct {
    unsigned int gp_offset;
    unsigned int fp_offset;
    void *overflow_arg_area;
    void *reg_save_area;
} __va_list_tag;

typedef __va_list_tag va_list[1];  // ← ARRAY of one element
```

**Consequence**: in C, an array passed as a function argument **decays into a pointer** to its first element. It is not a copy — both functions share the same memory object.

```
Caller            Callee
  args ──────────► [struct __va_list_tag in memory]
                        va_arg advances this object
                        → caller sees the advancement ✓ (by accident)
```

### On arm64 macOS (and ARM in general)

```c
typedef struct __va_list {
    void *__stack;
    void *__gr_top;
    void *__vr_top;
    int   __gr_offs;
    int   __vr_offs;
} va_list;  // ← plain STRUCT
```

**Consequence**: a struct passed by value is **fully copied**. The callee receives its own independent copy.

```
Caller            Callee
  args ─ copy ───► [copy of args in the stack frame]
  (unchanged)          va_arg advances the copy
                        copy destroyed on return
                        → caller sees nothing ✗
```

---

## The observed behavior

```
// Format string with 3 distinct arguments
ft_printf("%d %d %d\n", 1, 2, 3)

// On arm64, each call to ft_dprintf_switch receives a FRESH copy
// of args, always pointing at the 1st argument:
→ 1st %d : va_arg(copy) → 1, copy destroyed, original args unchanged
→ 2nd %d : va_arg(copy) → 1, copy destroyed, original args unchanged
→ 3rd %d : va_arg(copy) → 1, copy destroyed, original args unchanged
→ Output: "1 1 1"   (expected: "1 2 3")
```

---

## Why this is undefined behavior even on x86-64

The C standard (C99 §7.15, C11 §7.16) states:

> *"If access to the varying arguments is desired, the called function shall declare an object having type `va_list`"*

More precisely, `va_arg` may only be called on a `va_list` initialized locally via `va_start` or `va_copy`. Using a `va_list` passed by value after `va_arg` was called in another function → **undefined behavior**.

On x86-64, the "correct" behavior is only a side-effect of the `typedef ... [1]` implementation — it is not guaranteed.

---

## The fix — standard pattern

The only portable way to pass a `va_list` to a sub-function is via a **pointer**:

```c
// Signature
static ssize_t ft_dprintf_switch(int fd, va_list *args, const char *str);

// Call site
ret = ft_dprintf_switch(fd, &args, str);

// Inside the function
va_arg(*args, int)   // dereference → advances the original
```

```
Caller            Callee
  args ─ &args ──► va_list *args   (pointer to the original)
                       va_arg(*args,…) advances the original ✓
```

This is exactly what libc does internally in `vprintf` → `printf`.

---

## Alternative: va_copy

`va_copy` allows **intentionally duplicating** the state of a `va_list`:

```c
va_list copy;
va_copy(copy, args);       // legal and portable copy
// use copy...
va_end(copy);              // mandatory
```

Useful when you need to read arguments twice (e.g. compute length before writing). Not needed for this project.

---

## Summary

| Architecture | `va_list` is | Pass by value | Result |
|---|---|---|---|
| x86-64 Linux | `typedef struct {...} [1]` (array) | shares the object (disguised pointer) | works **by accident** |
| arm64 macOS/Linux | `typedef struct {...}` (struct) | independent copy | **bug**: always reads the 1st arg |
| C standard guarantee | — | undefined behavior | unpredictable |

**Rule**: always pass a `va_list` to a sub-function **by pointer** (`va_list *`).
