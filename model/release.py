class Release:
    def __init__(self, str):
        raw_address = str.split('=')[1].split(',')[3].split('[')[0]
        self.address = raw_address[0]
        self.size = (raw_address[1])[:-2]