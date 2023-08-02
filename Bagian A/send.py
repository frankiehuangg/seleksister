import hmac
import time
import struct
import base64
import hashlib
import requests


def generate_totp(T0, X, algorithm, shared_secret):
    current_time = int(time.time())
    time_steps = (current_time - T0) // X
    time_steps_bytes = struct.pack('>Q', time_steps)

    hash_algorithm = getattr(hashlib, algorithm.lower())
    hmac_digest = hmac.new(shared_secret.encode(), time_steps_bytes, hash_algorithm).digest()
    offset = hmac_digest[-1] & 0x0F
    binary_code = struct.unpack('>I', hmac_digest[offset:offset+4])[0] & 0x7FFFFFFF
    totp = str(binary_code % 10**8).zfill(8)

    return totp

def main():
    print(f"Generated data:\n{str(data)}\nLength: {len(str(data))}\n")

    userid = "13521092"
    password = generate_totp(T0, X, algorithm, shared_secret)

    auth = userid.encode() + b':' + password.encode()
    auth = base64.b64encode(auth)

    header = {
        "Content-Type"  : "application/json",
        "Authorization" : f"Basic {auth.decode()}",
        "Content-Length": str(len(str(data)))
    }

    print(f"Generated header:\n{str(header)}\n")

    print(f"""Connecting with the following credentials
    userid    : {userid}
    password  : {password}""")

    url = "http://recruit.sister20.tech/submit/a"

    response = requests.post(url, headers=header, json=data)

    if (response.status_code == 201):
        print("Request suceeded!")
        print(response.content)
    else:
        print("Request failed!")
        print(response.status_code)
        print(response.content)

data = {
    "fullName"  : "Frankie Huang",
    "link"      : "https://drive.google.com/drive/folders/1-8uJlGT06OJt7hhXfqhwp2p2alV4Kvpg?usp=sharing",
    "message"   : "trw ngerjain soal sister https://www.youtube.com/shorts/LHZIc3B4kfE"
}

T0 = 0
X = 30
algorithm = 'SHA256'
shared_secret = "seleksister2313521092"

password = generate_totp(T0, X, algorithm, shared_secret)
print(f"Starting password: {password}")

new_key = False
while (not new_key):
    if (password != generate_totp(T0, X, algorithm, shared_secret)):
        password = generate_totp(T0, X, algorithm, shared_secret)
        print(f"Different password ({password}) has been generated, sending data...")
        break
    password = generate_totp(T0, X, algorithm, shared_secret)
    print(f"Next password: {password}")
    time.sleep(1)

main()
