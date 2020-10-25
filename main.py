import requests
import codecs
from geopy.geocoders import Nominatim

#get gps data
geolocator = Nominatim(user_agent="openstreetmap")
location = geolocator.geocode("Spijkenisse")
latitude = location.latitude
longitude = location.longitude
data_gps = "1"

#gps data to one string
string_value = str(data_gps) + ";" + str(latitude) + ";" + str(longitude)
#print(string_value)

#format string to ascii
ascii_value = ' '.join(list(map(str,map(ord,string_value))))
#print(ascii_value)

#format string to binary
binary_value = ' '.join(format(ord(x), 'b') for x in string_value)
print(binary_value)

#format string to hex
# string_to_bytes = bytes(string_value, 'utf-8')
# hex_value = codecs.encode(string_to_bytes, "hex")
# hex_server = hex_value.decode()
# print(hex_server)

url = 'http://145.24.222.137/index.php?incoming_message='+ binary_value
x = requests.get(url)

#print the response text (the content of the requested file):
#print(x.text)