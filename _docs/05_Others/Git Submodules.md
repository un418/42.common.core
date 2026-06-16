## Add a project as a submodule

```bash
git submodule add <repo-URL> <folder-name>
git add .gitmodules <folder-name>
git commit -m "<project> - add submodule"
```

---

## Update the submodule

```bash
# 1. Commit inside the project repo
cd <folder-name>
git add .
git commit -m "..."
git push

# 2. Update the pointer in the monorepo
cd ..
git add <folder-name>
git commit -m "<project> - update submodule"
```

---

## Clone the monorepo with submodules

```bash
git clone --recurse-submodules <monorepo-URL>

# If already cloned without:
git submodule update --init --recursive
```

---

## How it works

The parent repo only stores a **SHA** + the URL of the sub-repo.  
The `<folder-name>/` directory is an independent Git repo — its commits belong to it alone.

See also: [[Git Mono Repo]]
