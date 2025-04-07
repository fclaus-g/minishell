# 🐚 Minishell

Welcome to **Minishell**, a simplified Unix shell implemented in C as part of the 42 school curriculum.

This project aims to replicate key features of a real shell, including command execution, redirections, pipes, environment variable handling, and more — all built from scratch with a deep understanding of system calls and process management.

---

## ✨ Features

- 🖥️ Interactive prompt  
- ⚙️ Execution of binaries from `PATH`  
- 🔧 Built-in commands:  
  - `echo`  
  - `cd`  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`  
- 💬 Environment variable expansion (`$VAR`)  
- 📤 Redirections (`>`, `>>`, `<`)  
- 🔗 Pipes (`|`)  
- ✋ Signal handling (`Ctrl+C`, `Ctrl+D`)  
- 🧹 Error management and memory leak protection  

---

## 🛠️ Requirements

- 🐧 Linux or macOS  
- 🧱 `gcc` compiler  
- 📦 GNU Make  

---

## 🔧 Build Instructions

```bash
git clone https://github.com/fclaus-g/minishell.git
cd minishell
make
```

---

## ▶️ Running the Shell

```bash
./minishell
```

Once launched, you can type commands just like in a real shell:

```bash
$ echo Hello, world!
Hello, world!
$ ls -la | grep minishell
```

---

## 🤝 Team & Acknowledgments

This project was developed as a team effort with [pgomez-r](https://github.com/pgomez-r) 🤝.  
His **invaluable help**, dedication, and deep technical insight made this shell come to life.  
I am truly grateful for his collaboration and support throughout the entire project.

---

## 📁 Project Structure

```
.
├── Makefile
├── minishell.c
├── include/
│   └── minishell.h
├── src/
│   ├── builtins/
│   ├── execution/
│   ├── parsing/
│   └── utils/
└── libft/
```

---

## 📚 References

- 📘 Bash manual: https://www.gnu.org/software/bash/manual/  
- 📗 Advanced Linux Programming  
- 📄 42 Network subject guidelines  

---
