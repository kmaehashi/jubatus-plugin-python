# -*- coding: utf-8 -*-

print("example module initialized!")

class SpaceSplitter(object):
    def __init__(self):
        print("SpaceSplitter initialized")

    def split(self, text):
        # split text with space
        print("split method called: {0}".format(text))

        result = []
        begin = 0
        length = 0
        for (pos, char) in enumerate(text):
            if char == ' ':
                if 0 < length:
                    result.append((begin, length))
                    length = 0
                begin = pos + 1
            else:
                length += 1
        if length != 0:
            result.append((begin, length))

        print("split result: {0}".format(result))
        return result

class BinaryLengthExtractor(object):
    def __init__(self):
        print("BinaryLengthExtractor initialized")

    def add_feature(self, key, value):
        return [("length_{0}".format(key), float(len(value)))]

# TODO write unit test
assert SpaceSplitter().split(" hello  jubatus !") == [ (1, 5), (8, 7), (16, 1) ]
assert BinaryLengthExtractor().add_feature("data", "test") == [ ("length_data", 4) ]
