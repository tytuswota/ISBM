import sched, time
import requests
import codecs
from geopy.geocoders import Nominatim

#gps data to one string
def gps_to_sting(data_type, lat, long):
    string_value = str(data_type) + ";" + str(lat) + ";" + str(long)
    return string_value

#format string to ascii
def string_to_ascii(gps_string):
    ascii_value = ' '.join(list(map(str,map(ord,gps_string))))
    return ascii_value

#format string to binary
def string_to_binary(gps_string):
    binary_value = ' '.join(format(ord(x), 'b') for x in gps_string)
    return binary_value

#format string to hex
def string_to_hex(gps_string):
    string_to_bytes = bytes(gps_string, 'utf-8')
    hex_value = codecs.encode(string_to_bytes, "hex")
    hex_server = hex_value.decode()
    return hex_server

#binary string to server url
def url_data(binary_value):
    url = 'http://145.24.222.137/iridium_sim/index.php?incoming_message='+ binary_value
    x = requests.get(url)
    return x

#set scheduler time
s = sched.scheduler(time.time, time.sleep)

#get gps data
geolocator = Nominatim(user_agent="openstreetmap")
location = geolocator.geocode("Ankara")
latitude = location.latitude
longitude = location.longitude
data_gps = "1"

#functies
gps_string = gps_to_sting(data_gps, latitude, longitude)
ascii_value = string_to_ascii(gps_string)
binary_value = string_to_binary(gps_string)
hex_value = string_to_hex(gps_string)

# print(string_to_ascii(gps_string))
# print(string_to_binary(gps_string))
# print(string_to_hex(gps_string))

def do_something(sc): 
    url_data(binary_value)
    print(url_data(binary_value))
    s.enter(60, 1, do_something, (sc,))

s.enter(60, 1, do_something, (s,))
s.run()