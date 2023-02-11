import { useState, useEffect } from 'react';

import { io } from 'socket.io-client';

import { RegType } from './features/regs/types/RegType';
import { MemoryType } from './features/memory/types/MemoryType';

import { RegsArea } from './components/RegsArea';
import { CodeArea } from './components/CodeArea';
import { MemoryArea } from './components/MemoryArea';

import './App.css';

const socket = io('http://localhost:8000');

function App() {
  const [regsArr, setRegsArr] = useState<RegType[]>([]);
  const [codeArr, setCodeArr] = useState<string[]>([]);
  const [memArr, setMemArr] = useState<MemoryType[]>([]);

  socket.on('connect', () => {
    console.log('socket connect', socket.connect());
  });

  useEffect(() => {
    socket.on('get_regs', (res) => {
      setRegsArr(res);
    });
  }, []);

  useEffect(() => {
    socket.on('get_code', (res) => {
      setCodeArr(res);
    });
  }, []);

  useEffect(() => {
    socket.on('get_mem', (res) => {
      setMemArr(res);
      console.log(res);
    });
  });

  const initAct = () => {
    let res;
    res = socket.emit('init');
    res = socket.emit('get_regs');
    res = socket.emit('get_code');
    res = socket.emit('get_mem');
  };

  const singleStepAct = () => {
    let res;
    res = socket.emit('single_step');
    res = socket.emit('get_regs');
    res = socket.emit('get_code');
    res = socket.emit('get_mem');
  };

  return (
    <div>
      <h1>DE</h1>
      <hr />
      <button onClick={initAct}>INIT</button>
      <button onClick={singleStepAct}>S</button>
      <div className="box">
        <div className="one">
          <RegsArea regsArr={regsArr} />
        </div>
        <div className="two">
          <CodeArea codeArr={codeArr} />
        </div>
        <div className="three">
          <MemoryArea memArr={memArr} />
        </div>
      </div>
    </div>
  );
}

export default App;
