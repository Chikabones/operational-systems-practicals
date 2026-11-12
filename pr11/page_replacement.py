def fifo(pages, frames):
    mem = []
    faults = 0
    for p in pages:
        if p not in mem:
            faults += 1
            if len(mem) == frames:
                mem.pop(0)
            mem.append(p)
    return faults

def lru(pages, frames):
    mem = []
    faults = 0
    for p in pages:
        if p not in mem:
            faults += 1
            if len(mem) == frames:
                mem.pop(0)
            mem.append(p)
        else:
            mem.remove(p)
            mem.append(p)
    return faults

def optimal(pages, frames):
    mem = []
    faults = 0
    for i, p in enumerate(pages):
        if p not in mem:
            faults += 1
            if len(mem) == frames:
                farthest = -1
                victim = mem[0]
                for m in mem:
                    if m not in pages[i+1:]:
                        victim = m
                        break
                    idx = pages[i+1:].index(m)
                    if idx > farthest:
                        farthest = idx
                        victim = m
                mem.remove(victim)
            mem.append(p)
    return faults

def clock(pages, frames):
    mem = []
    ref = {}
    ptr = 0
    faults = 0
    for p in pages:
        if p in mem:
            ref[p] = 1
        else:
            faults += 1
            if len(mem) < frames:
                mem.append(p)
                ref[p] = 1
            else:
                while True:
                    curr = mem[ptr]
                    if ref[curr] == 0:
                        del ref[curr]
                        mem[ptr] = p
                        ref[p] = 1
                        ptr = (ptr + 1) % frames
                        break
                    else:
                        ref[curr] = 0
                        ptr = (ptr + 1) % frames
    return faults

ref_str = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1]
print("FIFO (3):", fifo(ref_str, 3))
print("LRU (3):", lru(ref_str, 3))
print("Optimal (3):", optimal(ref_str, 3))
print("Clock (3):", clock(ref_str, 3))

belady_str = [1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5]
print("Belady FIFO 3 frames:", fifo(belady_str, 3))
print("Belady FIFO 4 frames:", fifo(belady_str, 4))