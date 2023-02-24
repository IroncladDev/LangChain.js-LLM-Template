---
title: Getting Started with Solidity on Replit
author: Osinachi Chukwujama
date: 02-18-2022
cover: https://blog.replit.com/images/solidity-web3.png
categories: projects
---

Have you ever wanted to quickly prototype an idea, reproduce a bug, or share a code demo? Maybe you just got an idea for a new smart contract that allows users to bet on soccer teams, and you want to quickly prototype this and share it with your teammates. In all of these instances, [Replit](https://replit.com) is the perfect solution. 

Replit is a powerful online integrated developer environment (IDE) with a simple user interface that supports more than fifty programming languages. It also supports real-time collaboration, allowing for use cases like team member onboarding or hands-on learning for students. 

It integrates seamlessly with [GitHub](https://github.com), allowing you to create repositories from a repl or load a repo from GitHub without any manual setup. Replit also gives you the power to share demos through a link that can be accessed by any device, anywhere in the world.

In this article you’ll learn how to get started with [Solidity](https://docs.soliditylang.org/en/v0.8.11/) on Replit. Solidity is a statically typed, curly-braces programming language designed for developing smart contracts that run on [Ethereum](https://ethereum.org/en/). It can also be used by other blockchains for interoperability and easier migration.


## Getting Started with Solidity on Replit

In this section, you’ll learn how to get started with Solidity on Replit and deploy your first smart contract.

### Setting Up Your Account

To get started, you need to [create a Replit account](https://replit.com/signup) or [login to your existing one](https://replit.com/login). You need an account so you can create new repls and collaborate with peers.

### Creating a Solidity Repl

After setting up your account, create a new repl. 

First, select Solidity as the template and choose a title.

![Creating a new repl](https://i.imgur.com/eJiKQbL.png)

After initialization, you should be presented with a `README.md` file with a preview on the side. You can review the file for additional information.

![Basic view](https://i.imgur.com/8nkj7Al.png)

Locate and open the `contract.sol` file. The first line in the file tells you that the source code is licensed under the [MIT License](https://opensource.org/licenses/MIT). The next line, which starts with `pragma`, specifies that the source code is written for Solidity versions 0.8.2 or lower. 

This line is followed by two code blocks for smart contracts that start with the `contract` keyword. The first, `SimpleStorage`, is a basic smart contract that showcases encapsulation and data write operations in Solidity. The second, `MathTest`, is a contract that performs multiplication, but you can add other mathematical operations to it as well.

```sol
//  X-License-Identifier: MIT
pragma solidity ^0.8.2;

contract SimpleStorage {
  uint256 storedData;

  function get() public view returns (uint) {
    return storedData;
  }

  function set(uint x) public {
    storedData = x;
  }

  function double() public {
    storedData *= 2;
  }
}

contract MathTest {
	function multiply(uint a, uint b) public pure returns (uint) {
    return a*b;
  }
}
```

### Deploying Your First Smart Contract

Go ahead and click the **Run** button at the top of the interface.

![Repl interface before run](https://i.imgur.com/iEfLVkP.png)

The run action will compile the `contract.sol` file and prepare the contracts specified in it for deployment. It also initializes a new UI view where you can deploy individual contracts.

![Result of run action](https://i.imgur.com/gyhxVz4.png)

Do you notice the **Connect wallet** button in the image above? A wallet is needed to interact with the smart contracts in the repl. It’s similar to a regular wallet, which stores fiat currency, debit, and credit cards. However, it differs in its digital nature.

Technically, a wallet is a public and private key pair that allows you to view, store, and send assets across a blockchain network. You can think of the public key of your wallet like your PayPal email address. Users can send money to you through PayPal if they know your PayPal email address.

Your wallet's private key is the key used for signing transactions. It should never be made public or shared with friends. If your private key gets compromised, all the assets stored in your wallet can be wiped.

[Decentralized applications (dApps)](https://www.investopedia.com/terms/d/decentralized-applications-dapps.asp) differ from regular apps in the way they handle user identity. A regular app may require your email and password or a Social Auth provider to identify you. However, a dApp only requires your wallet address. This address is a hashed version of your public key that makes it easier to share, and can be in the form of a string or QR code.

Wallets are usually hard to use on their own because you need to figure out the network you want to send the asset to, and use code to initialize and sign transactions. Luckily, an app like [MetaMask](https://metamask.io) exists to simplify the use of wallets on the Ethereum blockchain. 

MetaMask consists of a set of tools that provides a way to create wallets and authorize actions on a dApp. You can install it as a browser extension or mobile app, but to follow along with this article, you only need to install it as a browser extension. It’s supported on Chrome, Firefox, Brave, and Edge.

![Supported browsers](https://i.imgur.com/7QQOrPp.png)

After setting up MetaMask, proceed by clicking the **Connect wallet** button on Replit. 

MetaMask will prompt you to choose an account. After choosing an account and completing the setup, you need to add some Ether to the account. This will be used for deploying smart contracts on the network, which in this case is “Replit Testnet.”

> The testnet can be used to test your smart contracts before they are ready to be deployed on the main Ethereum network.

Click **Get 1 ETH for testing** to add 1 fake ETH. Afterwards, click the **Deploy** button. This action will deploy the `MathTest` contract to the Replit Testnet.

![Deploy contract](https://i.imgur.com/AfwELlQ.png)

MetaMask will prompt you to set the gas fees and confirm the contract deployment. After confirmation, the contract will be deployed on Replit Testnet and will be available for use on the UI. Go ahead and test the multiplication function with different values.

![Deployed MathTest contract](https://i.imgur.com/dSb11Pk.png)

### Modifying the Deployed Smart Contract

To complete the calculator, add the remaining arithmetic operation functions to the `MathTest` contract:

```sol
function add(uint a, uint b) public pure returns (uint) {
    return a+b;
}
function subtract(uint a, uint b) public pure returns (uint) {
    return a-b;
}
function divide(uint a, uint b) public pure returns (uint) {
    return a/b;
}
```

If you save the file with Ctrl-S, you will notice that the UI reloads and the values are reset, but the new functions do not reflect this change. This is due to the immutable nature of smart contracts. When you make a change to a contract, you have to deploy a new contract. To fix this, click the **Deploy** button again to deploy a new version of the smart contract. 

After accepting MetaMask's prompt, you should notice two versions of the deployed contract with the most recent at the top. If you expand the deployed contract, you should see the other arithmetic operations.

![Other arithmetic operations in smart contract](https://i.imgur.com/Fsgz2p0.png)

To get a better feel for the calculator, you can take some time to play around with different math problems.

### Reading and Writing Data on a Smart Contract

The arithmetic functions in the `MathTest` smart contract are pure functions. This means they don't modify any data or read data from the contract. 

However, the `SimpleStorage` contract contains a state variable called `storedData`. This variable can be set by passing a number to the `set` method, doubled using the `double` method, and returned by calling the `get` method.

```sol
contract SimpleStorage {
  uint256 storedData;

  function get() public view returns (uint) {
    return storedData;
  }

  function set(uint x) public {
    storedData = x;
  }

  function double() public {
    storedData *= 2;
  }
}
```

You can deploy the `SimpleStorage` contract the same way you did the `MathTest` contract. After the deployment completes, take some time to explore the three deployed functions. If you hover over the **read** and **write** icons close to the **Run** button, you’ll see the type of function each contract implements.

![Function types in smart contract](https://i.imgur.com/Wa92qeg.png)

The `get` function is a view function and only accesses the state variables in a contract, which in this case is the `storedData` variable. It doesn’t require gas to run.

The other functions are non-payable functions that require gas fees to run since they modify the state of the Ethereum network.

> You should only store important data on the blockchain and ensure that all variables have the required types so that you don’t waste resources.

## Conclusion

[Solidity](https://docs.soliditylang.org/en/v0.8.11/) is a statically typed language used for smart contract development on the Ethereum blockchain. Learning how to develop smart contracts using Solidity is an important step to developing blockchain solutions.

In this article, you were guided through how to get started with the Solidity programming language on Replit. 

Even though [web3](https://web3.foundation) is still in its early stages, its decentralized online ecosystem based on blockchain has a lot of potential. [Replit](https://replit.com/) reduces the time required for web3 innovation with powerful features like team collaboration and version control, which are enabled by default on Solidity projects.
