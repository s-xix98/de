import { Socket } from 'socket.io-client';
import { useEffect, useState } from 'react';

import { RegType } from '../features/regs/types/RegType';
import { ShowRegs } from '../features/regs/components/ShowRegs';

export const RegsArea = ({ socket }: { socket: Socket }) => {
  const [regsArr, setRegsArr] = useState<RegType[]>([]);

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
      <h1>RegsArea</h1>
      <button onClick={clickAct}>Get Regs</button>
      <ShowRegs regs={regsArr} />
    </div>
  );
};
