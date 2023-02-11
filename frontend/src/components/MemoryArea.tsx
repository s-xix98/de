import { MemoryType } from '../features/memory/types/MemoryType';

import { ShowMemory } from '../features/memory/components/ShowMemory';

export const MemoryArea = ({ memArr }: { memArr: MemoryType[] }) => {
  return (
    <div>
      <h1>MemoryArea</h1>
      <ShowMemory memArr={memArr} />
    </div>
  );
};
