
from flask import Flask, request

app = Flask(__name__)

@app.route('/saludo', methods=['GET'])
def saludo():
    nombre = request.args.get('nombre', 'Mundo')
    return f"¡Hola, {nombre}!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

