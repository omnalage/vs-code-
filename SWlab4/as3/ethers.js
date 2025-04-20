import React, { useState } from 'react';
import { ethers } from 'ethers';
import MyNFT from './artifacts/contracts/MyNFT.sol/MyNFT.json';

const CONTRACT_ADDRESS = 'YOUR_DEPLOYED_CONTRACT_ADDRESS';

const App = () => {
    const [account, setAccount] = useState(null);
    const [uri, setUri] = useState('');
    const [status, setStatus] = useState('');

    const connectWallet = async () => {
        if (window.ethereum) {
            const accounts = await window.ethereum.request({ method: 'eth_requestAccounts' });
            setAccount(accounts[0]);
        } else {
            alert('MetaMask not detected');
        }
    };

    const mintNFT = async () => {
        if (!uri) return;

        try {
            const provider = new ethers.providers.Web3Provider(window.ethereum);
            const signer = provider.getSigner();
            const contract = new ethers.Contract(CONTRACT_ADDRESS, MyNFT.abi, signer);

            const transaction = await contract.mintNFT(account, uri);
            await transaction.wait();

            setStatus('NFT Minted Successfully!');
        } catch (error) {
            console.error(error);
            setStatus('Error minting NFT');
        }
    };

    return (
        <div className="App">
            <button onClick={connectWallet}>Connect Wallet</button>
            <br />
            <input
                type="text"
                placeholder="Enter IPFS URI"
                value={uri}
                onChange={(e) => setUri(e.target.value)}
            />
            <button onClick={mintNFT}>Mint NFT</button>
            <p>{status}</p>
        </div>
    );
};

export default App;
