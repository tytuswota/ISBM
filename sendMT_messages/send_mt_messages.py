import requests

data = list(input('Voer data in\n'))
hexString = ''

for i in data:
    hexString += hex(ord(i))

hexString = hexString.replace("0x", "")

url = "https://rockblock.rock7.com/rockblock/MT"

querystring = { "imei":"300434064434370",
                "data": hexString,
                "username":"microtranshro@gmail.com",
                "password":"1234Erin"}

response = requests.request("POST", url, params=querystring)

print(response.text)
