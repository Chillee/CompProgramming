import re

T = int(input())
for _ in range(T):
    N = int(input())
    for idx in range(N):
        mapping = {}
        for _ in range(10):
            t = input()
            match = re.search(r'(.*)={(.*)}', t)
            if match != None:
                mapping[match.groups()[0]] = match.groups()[1]
        mapping['author'] = mapping['author'].split(',')
        mapping['author'] = [i.split() for i in mapping['author']]
        mapping['author'] = [
            f'{i[0][:2]}. {i[1][0]}' for i in mapping['author']]
        mapping['author'] = ', '.join(mapping['author'])
        print(f"{mapping['author']}. {mapping['title']}. {mapping['journal']}. {mapping['year']};{mapping['volume']}({mapping['number']}):{mapping['pages']}.")
