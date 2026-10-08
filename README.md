# Algo problems collection (C++)

## Commands

| command | what it does |
|---|---|
| `./run` / `./run list` | progress by category (`-s core` / `-s interview`, `-c graph`, `-d hard`) |
| `./run show 12` | print the statement |
| `./run web 12` | open the problem's source page in the browser |
| `./run check 12` | build + test #12 (no argument: last edited solution; `--fast`, `-t 10`) |
| `./run check 1-20`, `-c trees`, `-s interview`, `--all` | check many in parallel (`-v` for details) |
| `./run watch 12` | re-run on every save |
| `./run next` / `./run random [-s interview] [-d medium]` | pick an unsolved problem |
| `./run reset 12`, `-c trees`, `--all` | restore blank stubs, keeping yours as `solution.cpp.bak` (`-y` skips the prompt) |
| `./run selftest` | test the reference solutions |
| `./run clean` | delete `build/` |

## License

MIT, see `LICENSE`. Unofficial, not affiliated with LeetCode or NeetCode. Problems link to their
LeetCode source; the lists are based on the NeetCode 150 (see `meta/THIRD_PARTY_NOTICES.md`) and
LeetCode's Top Interview 150.
