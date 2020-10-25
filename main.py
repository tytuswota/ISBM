import requests
import codecs
from geopy.geocoders import Nominatim
from datetime import datetime

#get gps data
def get_gps(self):
    geolocator = Nominatim(user_agent="openstreetmap")
    location = geolocator.geocode("Wijnhaven 107 Rotterdam")
    latitude = location.latitude
    longitude = location.longitude
    data_gps = 1
    return data_gps, latitude, longitude

#gps data to one string
def get_string(data_gps, latitude, longitude):
    now = datetime.now()
    dt_string = now.strftime("%Y-%m-%d %H:%M:%S")
    string_value = str(data_gps) + ";" + str(latitude) + ";" + str(longitude) + ";" + dt_string
    return string_value

#format string to ascii
def get_ascii(string_value):
    ascii_value = ' '.join(list(map(str,map(ord,string_value))))
    return ascii_value

#format string to binary
def get_binary(string_value):
    binary_value = ' '.join(format(ord(x), 'b') for x in string_value)
    return binary_value

#format string to hex
def get_hex(string_value):
    string_to_bytes = bytes(string_value, 'utf-8')
    hex_value = codecs.encode(string_to_bytes, "hex")
    hex_server = hex_value.decode()
    return hex_server

def get_url(binary_value):
    url = 'http://145.24.222.137/index.php?incoming_message='+ binary_value
    x = requests.get(url)
    print(x.text)
    return x

data_type, latitude, longitude = get_gps(self="")

data_string = get_string(data_type, latitude, longitude)
#print(data_string)

binary_data = get_binary(data_string)
#print(binary_data)

url = get_url(binary_data)
#print(url)