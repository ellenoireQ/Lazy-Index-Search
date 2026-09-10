# Lazy Index Search

> Based on this commit https://github.com/ellenoireQ/Lazy-Index-Search/commit/222c9d852ada9a4428e20a7014b4ea3475f7c7c9
## Benchmark 1 — `fs_ops.h`

**Environment:**
> Github Codespace, 4 vCPU

**Commands:**
```
time find / -name fs_ops.h 2>/dev/null

time build/lis --find fs_ops.h --path / --enable-multithread 1
time build/lis --find fs_ops.h --path / --enable-multithread 2
time build/lis --find fs_ops.h --path / --enable-multithread 4
time build/lis --find fs_ops.h --path / --enable-multithread 8
```

| Test   | Real    | User   | Sys    |
|--------|---------|--------|--------|
| find   | 11.107s | 0.389s | 1.372s |
| LIS 1T | 3.709s  | 0.564s | 2.805s |
| LIS 2T | 2.274s  | 0.617s | 2.205s |
| LIS 4T | 1.634s  | 0.715s | 2.433s |
| LIS 8T | 1.695s  | 0.761s | 2.448s |

---

## Benchmark 2 — `stdio.h`

**Commands:**
```
time find / -name stdio.h 2>/dev/null

time build/lis --find stdio.h --path / --enable-multithread 1
time build/lis --find stdio.h --path / --enable-multithread 2
time build/lis --find stdio.h --path / --enable-multithread 4
time build/lis --find stdio.h --path / --enable-multithread 8
```

| Test   | Real   | User   | Sys    |
|--------|--------|--------|--------|
| find   | 1.160s | 0.316s | 0.842s |
| LIS 1T | 2.758s | 0.612s | 2.140s |
| LIS 2T | 2.243s | 0.623s | 2.161s |
| LIS 4T | 1.697s | 0.781s | 2.360s |
| LIS 8T | 1.756s | 0.753s | 2.535s |

---

## Benchmark 3 — `crtbegin.o`

**Commands:**
```
time find / -name crtbegin.o 2>/dev/null

time build/lis --find crtbegin.o --path / --enable-multithread 1
time build/lis --find crtbegin.o --path / --enable-multithread 2
time build/lis --find crtbegin.o --path / --enable-multithread 4
time build/lis --find crtbegin.o --path / --enable-multithread 8
```

| Test   | Real   | User   | Sys    |
|--------|--------|--------|--------|
| find   | 1.169s | 0.342s | 0.826s |
| LIS 1T | 2.740s | 0.587s | 2.147s |
| LIS 2T | 2.263s | 0.629s | 2.182s |
| LIS 4T | 1.640s | 0.763s | 2.359s |
| LIS 8T | 1.556s | 0.746s | 2.403s |