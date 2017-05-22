# -*- coding: utf-8 -*-

class SpaceSplitter(object):
    def split(self, text):
        # split text with space

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

        return result

class BinaryLengthExtractor(object):
    def extract(self, key, value):
        return [("length_{0}".format(key), float(len(value)))]

# TODO write unit test
assert SpaceSplitter().split(" hello  jubatus !") == [ (1, 5), (8, 7), (16, 1) ]
assert BinaryLengthExtractor().extract("data", "test") == [ ("length_data", 4) ]
