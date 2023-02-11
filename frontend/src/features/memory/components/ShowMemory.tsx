import { MemoryType } from '../types/MemoryType';

const ShowMemoryLine = ({ addr, val }: { addr: string; val: string }) => {
  return (
    <p>
      {addr} : {val}
    </p>
  );
};

export const ShowMemory = ({ memArr }: { memArr: MemoryType[] }) => {
  return (
    <div>
      {memArr.map((mem, idx) => (
        <ShowMemoryLine addr={mem.addr} val={mem.val} key={idx} />
      ))}
    </div>
  );
};
