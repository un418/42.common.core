# Ubuntu version used at 42
FROM ubuntu:22.04

# Prevent blocking prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

RUN yes | unminimize
# Install dev packages
RUN apt-get update && apt-get install -y \
build-essential \
libbsd-dev \
clang \
gdb \
git \
valgrind \
man-db \
manpages \
manpages-dev \
vim \
zsh \
python3-setuptools \
pipx \
curl \
tzdata \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/*
# To be able to use man command
# cc alias to clang compiler
RUN ln -sf /usr/bin/clang /usr/bin/cc
# norminette installation
RUN pipx install norminette && pipx ensurepath
# Install oh my zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
# Install & Deploy my customs dotfiles
RUN cd ~ && git clone https://github.com/un418/.dotfiles.git && cd .dotfiles && ./deploy_dotfiles.sh

CMD ["/bin/zsh"]

# docker build -t 42dev:0.1 .
# docker builder prune -f
