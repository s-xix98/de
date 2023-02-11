import { useState } from 'react';
import { RegType } from '../types/RegType';

const ShowReg = ({
  reg,
  radix,
  radixPrefix,
}: {
  reg: RegType;
  radix: number;
  radixPrefix: string;
}) => {
  return (
    <p>
      {reg.name} : {radixPrefix} {reg.val.toString(radix)}
    </p>
  );
};

export const ShowRegs = ({ regs }: { regs: Array<RegType> }) => {
  const [radix, setRadix] = useState(10);
  const [radixPrefix, setRadixPrefix] = useState('');

  const changeRadix = () => {
    const prevRadix = radix;

    if (radix == 10) {
      setRadix(16);
      setRadixPrefix('0x');
    } else if (radix == 16) {
      setRadix(2);
      setRadixPrefix('0b');
    } else {
      setRadix(10);
      setRadixPrefix('');
    }

    console.log('changeRadix', prevRadix, '->', radix);
  };

  return (
    <div>
      {regs.length != 0 && <button onClick={changeRadix}>Change Radix</button>}
      {regs.length != 0 && <p>Radix {radix}</p>}
      {regs.map((reg, idx) => (
        <ShowReg
          reg={reg}
          radix={radix}
          radixPrefix={radixPrefix}
          key={idx}
        ></ShowReg>
      ))}
    </div>
  );
};
