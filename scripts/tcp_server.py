#!/usr/bin/env python3

import json
import socket
import signal
import sys

HOST = "0.0.0.0"
PORT = 8080

# Глобальная ссылка на сокет сервера, чтобы обработчик сигнала мог до него дотянуться
server_socket = None


def shutdown_server(sig, frame):
    """Гарантированное закрытие при Ctrl+C"""
    if server_socket:
        print("\nShutting down server...")
        try:
            server_socket.shutdown(socket.SHUT_RDWR)
        except OSError:
            pass  # Сокет уже закрыт или не связан
        server_socket.close()
    sys.exit(0)


def main():
    global server_socket
    
    # Ловим Ctrl+C (SIGINT) для чистого выхода
    signal.signal(signal.SIGINT, shutdown_server)

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # SO_REUSEADDR позволяет переиспользовать порт СРАЗУ ПОСЛЕ остановки,
    # но не поможет, если старый процесс всё еще висит в памяти.
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))
    server_socket.listen()

    print(f"Listening on {HOST}:{PORT}")
    print("\033[32mPress Ctrl+C to stop gracefully.\033[0m")
    print("\033[31mWARNING: Ctrl+Z will pause process but keep port busy until timeout.\033[0m\n")

    while True:
        try:
            client, addr = server_socket.accept() # Блокирующий вызов
            print(f"\nClient connected: {addr}")
            
            # Обработка клиента вынесена в функцию для гарантированного close
            handle_client(client)

        except KeyboardInterrupt:
            # На случай если SIGINT пришел прямо в момент accept()
            break
        except Exception as e:
            print(f"Server error: {e}")

    shutdown_server(None, None)


def handle_client(client_socket):
    try:
        while True:
            data = client_socket.recv(4096)
            if not data:
                break  # Клиент закрыл соединение штатно

            try:
                message = json.loads(data.decode())
                print(json.dumps(message, indent=4))
            except json.JSONDecodeError:
                print(f"[RAW] {data.decode().strip()}")

    except ConnectionResetError:
        # Клиент упал (например, kill -9 агента). recv выкинет исключение.
        print("Connection forcibly closed by peer.")
    finally:
        # Этот блок выполнится ВСЕГДА
        print("Closing client socket")
        client_socket.close()

if __name__ == "__main__":
    main()