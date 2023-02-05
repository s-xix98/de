import { io } from 'socket.io-client';

import { RegsArea } from './components/RegsArea';

const socket = io('http://localhost:8000');

function App() {
  socket.on('connect', () => {
    console.log('socket connect', socket.connect());
  });

  return <RegsArea socket={socket} />;
}

export default App;
