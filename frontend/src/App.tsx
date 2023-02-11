import { useState, useEffect } from 'react';

import { io } from 'socket.io-client';

import { RegType } from './features/regs/types/RegType';

import { RegsArea } from './components/RegsArea';
import { CodeArea } from './components/CodeArea';
import { MemoryArea } from './components/MemoryArea';

import './App.css';

const socket = io('http://localhost:8000');

function App() {
  const [regsArr, setRegsArr] = useState<RegType[]>([]);

  socket.on('connect', () => {
    console.log('socket connect', socket.connect());
  });

  useEffect(() => {
    socket.on('get_regs', (res) => {
      setRegsArr(res);
    });
  }, []);

  const clickAct = () => {
    const res = socket.emit('get_regs');
    console.log('CLICK ACT', res);
  };

  return (
    <div>
      <h1>DE</h1>
      <hr />
      <button onClick={clickAct}>Get Info</button>
      <div className="box">
        <div className="one">
          <RegsArea regsArr={regsArr} />
        </div>
        <div className="two">
          <CodeArea />
        </div>
        <div className="three">
          <MemoryArea />
        </div>
      </div>
    </div>
  );
}

export default App;
