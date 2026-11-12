def fcfs(head, reqs):
    total = 0
    curr = head
    for r in reqs:
        total += abs(curr - r)
        curr = r
    return total

def sstf(head, reqs):
    pending = reqs.copy()
    total = 0
    curr = head
    while pending:
        closest = min(pending, key=lambda x: abs(x - curr))
        total += abs(curr - closest)
        curr = closest
        pending.remove(closest)
    return total

def scan(head, reqs, max_cyl=199):
    left = sorted([r for r in reqs if r < head], reverse=True)
    right = sorted([r for r in reqs if r >= head])
    total = 0
    curr = head
    for r in right:
        total += abs(curr - r)
        curr = r
    if left:
        total += abs(curr - max_cyl)
        curr = max_cyl
        for r in left:
            total += abs(curr - r)
            curr = r
    return total

def look(head, reqs):
    left = sorted([r for r in reqs if r < head], reverse=True)
    right = sorted([r for r in reqs if r >= head])
    total = 0
    curr = head
    for r in right:
        total += abs(curr - r)
        curr = r
    for r in left:
        total += abs(curr - r)
        curr = r
    return total

def c_look(head, reqs):
    left = sorted([r for r in reqs if r < head])
    right = sorted([r for r in reqs if r >= head])
    total = 0
    curr = head
    for r in right:
        total += abs(curr - r)
        curr = r
    for r in left:
        total += abs(curr - r)
        curr = r
    return total

queue = [98, 183, 37, 122, 14, 124, 65, 67]
start = 53
print("FCFS:", fcfs(start, queue))
print("SSTF:", sstf(start, queue))
print("SCAN:", scan(start, queue))
print("LOOK:", look(start, queue))
print("C-LOOK:", c_look(start, queue))