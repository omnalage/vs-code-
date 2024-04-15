import re

def validate_credit_card(card_number):
    pattern = r'^\d{4}-\d{4}-\d{4}-\d{4}$'
    if re.match(pattern, card_number):
        return True
    else:
        return False

def validate_pan(pan):
    pattern = r'^[A-Z]{5}\d{4}[A-Z]$'
    if re.match(pattern, pan.upper()):
        return True
    else:
        return False

def validate_password(password):
    pattern = r'^[a-zA-Z][a-zA-Z]{3,4}[@$#!_%.]{1}\d{2,3}$'
    if re.match(pattern, password):
        return True
    else:
        return False


credit_card_number = '1234-5678-9876-4324'
pan = 'ABCTY1234D'
password = 'a1@345'

print(f'Is {credit_card_number} a valid credit card number? - {validate_credit_card(credit_card_number)}')
print(f'Is {pan} a valid PAN number? - {validate_pan(pan)}')
print(f'Is {password} a valid password? - {validate_password(password)}')

credit_card_number = input("Enter a credit card number:")
pan = input("Enter pan card number:")
password = input("Enter password:")

print(f'Is {credit_card_number} a valid credit card number? - {validate_credit_card(credit_card_number)}')
print(f'Is {pan} a valid PAN number? - {validate_pan(pan)}')
print(f'Is {password} a valid password? - {validate_password(password)}')