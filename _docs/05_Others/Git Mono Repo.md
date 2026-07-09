## Push project from Monorepo to 42 Vogosphere

```bash
git remote add voglibft git@vogsphere.42lisboa.com:vogsphere/intra-uuid-blablabla-adaferna
git subtree push --prefix=libft voglibft master

git remote add vogP00 git@vogsphere.42lisboa.com:vogsphere/intra-uuid-blablabla-adaferna
git subtree push --prefix=python_module/P00 vogP00 master 

git remote add vogP01 git@vogsphere.42lisboa.com:vogsphere/intra-uuid-79acfaef-a0ae-4a25-8d05-c8d9fde2a1a3-7498368-adaferna
git subtree push --prefix=python_module/P01 vogP01 master 


```