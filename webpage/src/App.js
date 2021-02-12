import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="background">
      {/* <div className="rectangle"> 
      </div> */}
      <div className="App">
      <video width="750" height="500" controls >
      <source src="/test.mp4" type="video/mp4"/>
     </video>
      </div>
      <div className="buttons">
        <button>Forward</button>
        <button>Backward</button>
        <button>Switch camera</button>
      </div>
    </div>
    // <div className="App">
    //   <header className="App-header">
    //     <img src={logo} className="App-logo" alt="logo" />
    //     <p>
    //       Edit <code>src/App.js</code> and save to reload.
    //     </p>
    //     <a
    //       className="App-link"
    //       href="https://reactjs.org"
    //       target="_blank"
    //       rel="noopener noreferrer"
    //     >
    //       Learn React
    //     </a>
    //   </header>
    // </div>
  );
}

export default App;
