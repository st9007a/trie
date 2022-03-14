import random

if __name__ == '__main__':
    chars = r"abcdefghijklenopqrstuvwxyzABCDEFGHIJKLENOPQRSTUVWXYZ+-*\.?=!~_;:[]{}(),@#$%^&`"

    n_prefix = random.randint(150, 300)
    n_query = 1000000

    with open('prefix.txt', 'w+') as f:
        for _ in range(n_prefix):
            length = random.randint(5, 20)
            prefix = ''.join(random.choices(chars, k=length))
            f.write(prefix + '\n')

    with open('query.txt', 'w+') as f:
        for _ in range(n_query):
            length = random.randint(1, 300)
            query = ''.join(random.choices(chars, k=length))
            f.write(query + '\n')
