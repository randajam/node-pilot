#!/usr/bin/env python3

import json
import socket


HOST = "0.0.0.0"
PORT = 8080


def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    server.bind((HOST, PORT))
    server.listen()

    print(f"Listening on {HOST}:{PORT}")

    while True:
        client, addr = server.accept()

        print(f"\nClient connected: {addr}")

        try:
            while True:
                data = client.recv(4096)

                if not data:
                    break

                try:
                    message = json.loads(data.decode())
                    print(json.dumps(message, indent=4))
                except json.JSONDecodeError:
                    print(data.decode())

        finally:
            print("Client disconnected")
            client.close()


if __name__ == "__main__":
    main()