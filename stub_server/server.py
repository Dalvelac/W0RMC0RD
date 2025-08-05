from flask import Flask, request, jsonify

app = Flask(__name__)

@app.post('/login')
def login():
    data = request.get_json() or {}
    token = data.get('token', '')
    if token:
        return jsonify({'status': 'ok'}), 200
    return jsonify({'status': 'error'}), 400

@app.get('/friends')
def friends():
    token = request.args.get('token', '')
    return jsonify({'friends': ['friend1', 'friend2']})

@app.post('/dm')
def dm():
    data = request.get_json() or {}
    return jsonify({'status': 'sent', 'to': data.get('to')}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

