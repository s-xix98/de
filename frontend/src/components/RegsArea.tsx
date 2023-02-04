import { RegType } from '../features/regs/types/RegType';
import { ShowRegs } from '../features/regs/components/ShowRegs';

export const RegsArea = () => {
  const regsArr: Array<RegType> = [
    { name: 'RAX', val: 0 },
    { name: 'RBX', val: 1 },
  ];

  return <ShowRegs regs={regsArr} />;
};
