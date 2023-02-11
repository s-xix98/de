import json

import socketio
from aiohttp import web

sio = socketio.AsyncServer(cors_allowed_origins="*")
app = web.Application()
sio.attach(app)


async def index(request):
    """Serve the client-side application."""
    with open("index.html") as f:
        return web.Response(text=f.read(), content_type="text/html")


@sio.event
def connect(sid, environ):
    print("connect ", sid)


@sio.event
async def chat_message(sid, data):
    print("message ", data)


@sio.event
async def get_regs(sid):
    print("get_regs", sid)
    with open("json/regs.json") as f:
        regs_json = json.load(f)
    await sio.emit("get_regs", regs_json)


@sio.event
async def get_code(sid):
    print("get_code", sid)
    with open("json/code.json") as f:
        code_json = json.load(f)
    await sio.emit("get_code", code_json)


@sio.event
def disconnect(sid):
    print("disconnect ", sid)


app.router.add_static("/static", "static")
app.router.add_get("/", index)

if __name__ == "__main__":
    web.run_app(app, port=8000)
