import { RegType } from '../types/RegType';

const ShowReg = ({ reg }: { reg: RegType }) => {
  return (
    <p>
      {reg.name} : {reg.val}
    </p>
  );
};

export const ShowRegs = ({ regs }: { regs: Array<RegType> }) => {
  return (
    <div>
      {regs.map((reg, idx) => (
        <ShowReg reg={reg} key={idx}></ShowReg>
      ))}
    </div>
  );
};
