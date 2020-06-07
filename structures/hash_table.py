fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

elements = list(map(int, fin.read().split()))

class Hash_Table:
    def __init__(self):
        self.size = len(elements)
        self.keys = [0] * self.size
        self.info = [False] * self.size

    def hash_func(self, data, plus):
        return (data + plus) % self.size

    def push(self, data):
        value = self.hash_func(data, 0)

        if self.keys[value] == 0:
            self.keys[value] = data
            self.info[value] = True
        else:
            if self.keys[value] == data:
                self.keys[value] = data
            else:
                i = 1
                next_value = self.hash_func(data, i)

                while self.keys[next_value] != 0:
                    i = i + 1
                    next_value = self.hash_func(data, i)

                self.keys[next_value] = data
                self.info[next_value] = True

    def pop(self, data):
        value = self.hash_func(data, 0)

        if self.keys[value] == data:
            self.keys[value] = 0
        else:
            i = 1
            next_value = self.hash_func(data, i)

            while self.keys[next_value] != False and self.keys[next_value] != data:
                i = i + 1
                next_value = self.hash_func(data, i)

            self.keys[next_value] = 0

    def write(self):
        for i in range(len(self.keys)):
            if self.keys[i] != 0:
                fout.write(str(self.keys[i]) + ' ')


table = Hash_Table()

for i in elements:
    if i > 0:
        table.push(i)
    if i < 0:
        table.pop(-i)
    if i == 0:
        break

table.write()
