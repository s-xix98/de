import { RegType } from '../features/regs/types/RegType';
import { ShowRegs } from '../features/regs/components/ShowRegs';

export const RegsArea = ({ regsArr }: { regsArr: RegType[] }) => {
  return (
    <div>
      <h1>RegsArea</h1>
      <ShowRegs regs={regsArr} />
    </div>
  );
};
