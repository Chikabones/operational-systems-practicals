"
class MLFQ:
    def __init__(self):
        # 3 уровня очередей с возрастающим квантом
        self.queues = [[], [], []]
        self.quanta = [2, 4, 8]

    def add_process(self, process):
        self.queues[0].append(process)

    def simulate_step(self):
        for level in range(len(self.queues)):
            if self.queues[level]:
                p = self.queues[level].pop(0)
                q = self.quanta[level]
                print(f'Executing process {p.pid} at queue level {level} for quantum {q}')
                # Симуляция выполнения...
                break

if __name__ == '__main__':
    print('Multilevel Feedback Queue (MLFQ) Simulation initialized.')
"