print('세 정수의 최댓값을 구합니다')
a = float(input('정수 a의 값을 입력하세요.: '))
b = float(input('정수 b의 값을 입력하세요.: '))
c = float(input('정수 c의 값을 입력하세요.: '))
maximum = a
if b> maximum: maximum = b
if c> maximum: maximum = c
if 100> maximum*10 > 9: maximum = int(maximum)

print(f'최댓값은 {maximum}입니다.')          