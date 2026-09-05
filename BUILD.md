# Device registry — build & verify

## Build
    make                # compile list_demo (warnings are errors)

## Run
    ./list_demo         # builds a named device list, finds, removes, frees

## Leak gate (the bar)
    make check          # runs under Valgrind; non-zero exit on ANY leak/UAF

A green `make check` means: every `malloc` (struct AND name) has a matching
`free`, no node was used after free, and removing the middle device leaked
nothing. "It ran" is not the bar — "it ran clean under Valgrind" is.

## Reading a failure
- `definitely lost: N bytes in M blocks` — M allocations never freed. The trace
  points at the `malloc`/`dup_str` site. Usually a forgotten `free(d->name)`.
- `Invalid read of size 8` after a free — a use-after-free. Check that you
  unlink before freeing and grab `next` before freeing a node.
