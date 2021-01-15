


class Allocation:
    def __init__(self, str):
        raw = str.split('=')[1].split(',')
        raw_address = raw[3].split('[')
        self.module = raw[0]
        self.line = raw[1]
        self.function = raw[2]
        self.address = raw_address[0]
        self.size = (raw_address[1])[:-2]
