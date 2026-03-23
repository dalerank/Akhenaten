# Contributing

When contributing to this repository, please first discuss the change you wish to make via issue,
Discord chat, or any other method with the owner of this repository before opening a pull request.

## Aim of the project

The aim of Akhenaten is to re-create the exact same logic that the original Pharaoh uses, with full savegame
compatibility, but with some small user interface enhancements.

Later on there may be an 'enhanced' edition with new features, but for now any pull requests which change the game logic
or alter the UI in a major way will be declined.

## Code Style & Formatting
We use **clang-format version 20.1.0** to enforce a consistent code style. All C++ files must be formatted according to the rules defined in [.clang-format](.clang-format) in the repository root.

### Pre-commit (recommended)
- Install [pre-commit](https://pre-commit.com/#install) (requires Python).

- In the repository root, run:
```bash
pre-commit install
```

- Now every `git commit` will automatically format changed files. No extra steps needed.

### Manual formatting
- Install **clang-format 20** (see [LLVM downloads](https://releases.llvm.org/download.html))
- Run `git clang-format --style=file --extensions cpp,cc,cxx,h,hpp` to format only changed files.

**Note**: `git clang-format` requires the *git-clang-format* script. It is included in the LLVM package (on Windows, add the `bin` folder to PATH; on Linux, install `git-clang-format` or the *clang-format-20* package).

### CI process
Pull requests are checked for formatting before builds.

If formatting fails, CI will post a comment with the required changes.

Fix locally and push again; the check will re-run.
