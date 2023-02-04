import { RegType } from '../features/regs/types/RegType';
import { ShowRegs } from '../features/regs/components/ShowRegs';
import { io } from 'socket.io-client';

export const RegsArea = () => {
  const socket = io('http://localhost:8000');

  socket.on('connect', () => {
    console.log('socket connect', socket.connect());
  });

  const regsArr: Array<RegType> = [
    { name: 'RAX', val: 0 },
    { name: 'RBX', val: 1 },
  ];

  return <ShowRegs regs={regsArr} />;
};
