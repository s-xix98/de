const ShowCodeLine = ({ line }: { line: string }) => {
  return <pre>{line}</pre>;
};

export const ShowCode = ({ codeArr }: { codeArr: string[] }) => {
  return (
    <div>
      {codeArr.map((line, idx) => (
        <ShowCodeLine line={line} key={idx} />
      ))}
    </div>
  );
};
