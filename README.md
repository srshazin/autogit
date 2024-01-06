# AUTOGIT

A command line app for automating `git add .` , `git commit -m` and `git push`.

## Building from Source

- **Install meson**

  For example:

  ```bash
  apt install meson # for ubuntu or debian based distro
  ```

  it can also be installed using pip by running `pip install meson`.

  Please refer to [Meson Build](https://github.com/mesonbuild/meson) repo for other installations.

- **Install Ninja**
  for example
  ```bash
  apt install ninja # for ubuntu or debian based distro
  ```
  ```bash
  yum install ninja # for redhat or fedora based distro
  ```
  Please refer to [Ninja Build](https://github.com/ninja-build/ninja) repo for other installations.
- **Clone This Repository**
  ```bash
  git clone https://github.com/dev5h/autogit.git && cd autogit
  ```
- **Run Build Commands**
  `bash
meson build
cd build
ninja install
`
  And that should complete the installation . You might need `sudo` to install it depends on your system.

## How it works?

Basically as the name suggests **autogit** automate basic repetitive git tasks. It handles your git add, commit and push tasks in three ways

1. Set `autogit -i 100` meaning it will commit and will not make any push to remote repo.

2. Set the `autogit -i 20 -p 60` this way the commit interval is smaller than the push interval thus after 20 every 20 seconds it will do `git add .` and than generate a suitable commit message and make the commit. And in every 60 seconds it will make a git push meaning it will do the `git add .` and commit generation again than push the changes to remote repository.

3. If you set `autogit -i 60 -p 20` meaning your git push interval is smaller than commit interval than autogit will not disable auto commit and only push . This is true if commit interval and push interval is equal.
