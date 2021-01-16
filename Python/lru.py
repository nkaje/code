class LRU:
    def __init__(self, size):
        self.size = size
        self.array = {}
        self.list = []

    def put(self, key, value):
        if key in self.array.keys():
            self.array[key] = value
            self.list.remove(key)
            self.list.insert(0, key)
            return

        if (len(self.array) == self.size):
            #eviction logic
            key_to_remove = self.list[-1]
            self.list.remove(key_to_remove)
            self.array.pop(key_to_remove)
            self.array[key] = value
            self.list.insert(0, key)
        else:
            self.array[key] = value
            self.list.insert(0, key)

    def get(self, key):
        if key in self.array.keys():
            return self.array[key]

    def display(self):
        print(self.array)

lru = LRU(3)

lru.put(1, 10)
lru.put(2, 30)
lru.put(3, 50)
print(lru.get(1))
print(lru.get(2))
print(lru.get(3))

lru.display()
print("adding %s" % 40)
lru.put(4, 40)
lru.display()
