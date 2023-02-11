import json

import socketio
from aiohttp import web

from de_ctl import DE

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


g_de_proc = None


@sio.event
async def init(sid):
    print("init")
    global g_de_proc
    g_de_proc = DE("./app/target")
    g_de_proc.de_start()


@sio.event
async def single_step(sid):
    print("single_step")
    global g_de_proc
    if g_de_proc == None:
        return
    g_de_proc.de_one_cmd("s")


@sio.event
async def get_regs(sid):
    print("get_regs", sid)
    with open("json/de_output/regs.json") as f:
        regs_json = json.load(f)
    await sio.emit("get_regs", regs_json)


@sio.event
async def get_code(sid):
    print("get_code", sid)
    with open("json/de_output/code.json") as f:
        code_json = json.load(f)
    await sio.emit("get_code", code_json)


@sio.event
async def get_mem(sid):
    print("get_mem", sid)
    with open("json/de_output/stack.json") as f:
        stack_json = json.load(f)
    await sio.emit("get_mem", stack_json)


@sio.event
def disconnect(sid):
    print("disconnect ", sid)


app.router.add_static("/static", "static")
app.router.add_get("/", index)

if __name__ == "__main__":
    web.run_app(app, port=8000)
