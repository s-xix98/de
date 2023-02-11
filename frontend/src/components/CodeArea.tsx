import { ShowCode } from '../features/code/components/ShowCode';

export const CodeArea = ({ codeArr }: { codeArr: string[] }) => {
  return (
    <div>
      <h1>CodeArea</h1>
      <ShowCode codeArr={codeArr} />
    </div>
  );
};
