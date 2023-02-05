import { RegType } from '../features/regs/types/RegType';
import { ShowRegs } from '../features/regs/components/ShowRegs';
import { io } from 'socket.io-client';

const socket = io('http://localhost:8000');

export const RegsArea = () => {
  socket.on('connect', () => {
    console.log('socket connect', socket.connect());
  });

  let regsArr: Array<RegType> = [
    { name: 'RAX', val: 0 },
    { name: 'RBX', val: 1 },
  ];

  const clickAct = () => {
    const res = socket.emit('get_regs');
    console.log('');
    console.log('CLICK ACT', res);
    console.log('');
  };

  socket.on('get_regs', (res) => {
    console.log('SOCKET.ON GET_REGS', res);
  });

  return (
    <div>
      <button onClick={clickAct}>button</button>
      <ShowRegs regs={regsArr} />
    </div>
  );
};
